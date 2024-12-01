#include "npc.h"
#include "factory.h"
#include "visitor.h"
#include "observer.h"
#include "task.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <chrono>

std::vector<std::shared_ptr<NPC>> npcs;
std::shared_mutex npcs_mutex;
std::mutex console_mutex;
std::atomic<bool> game_over(false);

const int max_x = 100;
const int max_y = 100;
const int num_npcs = 50;
const int game_duration = 30; // секунд

std::shared_ptr<ConsoleObserver> consoleObserver;
std::shared_ptr<FileObserver> fileObserver;

// Корутин для перемещения и сражения
Task npc_coroutine() {
    static std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> dice_distribution(1, 6);
    std::uniform_int_distribution<int> move_distribution(-10, 10);

    auto start_time = std::chrono::steady_clock::now();

    while (!game_over) {
        {
            // Перемещение NPC
            std::unique_lock<std::shared_mutex> lock(npcs_mutex);
            for (auto& npc : npcs) {
                if (!npc->alive) continue;

                int dx = move_distribution(generator) % (npc->move_distance + 1);
                int dy = move_distribution(generator) % (npc->move_distance + 1);

                npc->x += dx;
                npc->y += dy;

                if (npc->x < 0) npc->x = 0;
                if (npc->x > max_x) npc->x = max_x;
                if (npc->y < 0) npc->y = 0;
                if (npc->y > max_y) npc->y = max_y;
            }
        }

        // Проверяем возможность боя
        {
            std::shared_lock<std::shared_mutex> lock(npcs_mutex);
            for (size_t i = 0; i < npcs.size(); ++i) {
                auto& attacker = npcs[i];
                if (!attacker->alive) continue;

                for (size_t j = i + 1; j < npcs.size(); ++j) {
                    auto& defender = npcs[j];
                    if (!defender->alive) continue;

                    if (attacker->isClose(defender, attacker->kill_distance)) {
                        // Проверяем совместимость
                        FightVisitor fight(*attacker);
                        defender->accept(fight, attacker);

                        if (fight.attackerDies || fight.defenderDies) {
                            int attack_strength = dice_distribution(generator);
                            int defense_strength = dice_distribution(generator);

                            if (attack_strength > defense_strength) {
                                if (fight.defenderDies) {
                                    std::unique_lock<std::shared_mutex> lock(npcs_mutex);
                                    defender->alive = false;
                                    defender->notify(defender->name + " was killed by " + attacker->name);
                                }
                            } else {
                                if (fight.attackerDies) {
                                    std::unique_lock<std::shared_mutex> lock(npcs_mutex);
                                    attacker->alive = false;
                                    attacker->notify(attacker->name + " was killed by " + defender->name);
                                }
                            }
                        }
                    }
                }
            }
        }

        // Приостанавливаем корутину на некоторое время
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        co_await std::suspend_always{};
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    consoleObserver = std::make_shared<ConsoleObserver>();
    fileObserver = std::make_shared<FileObserver>("log.txt");

    // Генерация npc
    for (int i = 0; i < num_npcs; ++i) {
        NpcType type = static_cast<NpcType>(std::rand() % 3 + 1);
        std::string name = "NPC_" + std::to_string(i);
        int x = std::rand() % (max_x + 1);
        int y = std::rand() % (max_y + 1);

        auto npc = NPCFactory::createNPC(type, name, x, y);
        npc->addObserver(consoleObserver);
        npc->addObserver(fileObserver);

        npcs.push_back(npc);
    }

    auto npc_task = npc_coroutine();

    auto start_time = std::chrono::steady_clock::now();

    // Основной поток
    while (true) {
        {
            std::shared_lock<std::shared_mutex> lock(npcs_mutex);

            {
                std::lock_guard<std::mutex> cout_lock(console_mutex);
                std::cout << "Current NPC positions:" << std::endl;
                for (const auto& npc : npcs) {
                    if (npc->alive) {
                        npc->print();
                    }
                }
                std::cout << "-------------------------------------" << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Прошло ли 30 секунд?
        auto elapsed = std::chrono::steady_clock::now() - start_time;
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() >= game_duration) {
            game_over = true;
            break;
        }
    }

    npc_task = {}; // Завершаем корутину

    // Печать самых стойких
    {
        std::shared_lock<std::shared_mutex> lock(npcs_mutex);

        std::cout << "Game over! Survivors:" << std::endl;
        for (const auto& npc : npcs) {
            if (npc->alive) {
                npc->print();
            }
        }
    }

    return 0;
}
