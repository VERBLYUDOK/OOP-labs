#include "npc.h"
#include "factory.h"
#include "visitor.h"
#include "observer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using NPCSet = std::set<std::shared_ptr<NPC>>;

void saveNPCs(const NPCSet& npcs, const std::string& filename) {
    std::ofstream ofs(filename);
    if (ofs.is_open()) {
        ofs << npcs.size() << '\n';
        for (const auto& npc : npcs) {
            npc->save(ofs);
        }
    }
}

NPCSet loadNPCs(const std::string& filename) {
    NPCSet npcs;
    std::ifstream ifs(filename);
    if (ifs.is_open()) {
        size_t count;
        ifs >> count;
        for (size_t i = 0; i < count; ++i) {
            auto npc = NPC::load(ifs);
            if (npc) {
                npcs.insert(npc);
            }
        }
    }
    return npcs;
}

NPCSet fight(NPCSet& npcs, size_t distance) {
    NPCSet deadNPCs;
    auto npcsCopy = npcs; // Копия для безопасной итерации
    for (const auto& attacker : npcsCopy) {
        for (const auto& defender : npcsCopy) {
            if (attacker != defender && attacker->isClose(defender, distance)) {
                FightVisitor fight(*attacker);
                defender->accept(fight, attacker);
                if (fight.defenderDies) {
                    deadNPCs.insert(defender);
                    attacker->notify(attacker->name + " killed " + defender->name);
                }
                if (fight.attackerDies) {
                    deadNPCs.insert(attacker);
                    defender->notify(defender->name + " killed " + attacker->name);
                }
            }
        }
    }
    return deadNPCs;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    NPCSet npcs;

    // Создание наблюдателей
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("log.txt");

    // Генерация NPC
    for (int i = 0; i < 10; ++i) {
        NpcType type = static_cast<NpcType>(std::rand() % 3 + 1);
        std::string name = "NPC_" + std::to_string(i);
        int x = std::rand() % 501;
        int y = std::rand() % 501;

        auto npc = NPCFactory::createNPC(type, name, x, y);
        npc->addObserver(consoleObserver);
        npc->addObserver(fileObserver);
        npcs.insert(npc);
    }

    // Сохранение и загрузка NPC в файл
    saveNPCs(npcs, "npcs.txt");
    npcs = loadNPCs("npcs.txt");

    std::cout << "List of NPCs:" << std::endl;
    for (const auto& npc : npcs) {
        npc->print();
    }

    // Запуск боевого режима
    size_t battleDistance;
    std::cout << "Enter battle distance: ";
    std::cin >> battleDistance;

    while (!npcs.empty()) {
        auto deadNPCs = fight(npcs, battleDistance);
        if (deadNPCs.empty()) {
            break;
        }
        for (const auto& dead : deadNPCs) {
            npcs.erase(dead);
        }
    }

    // Печать самых стойких
    std::cout << "Surviving NPCs:" << std::endl;
    for (const auto& npc : npcs) {
        npc->print();
    }

    return 0;
}
