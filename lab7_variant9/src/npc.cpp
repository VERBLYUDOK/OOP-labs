#include "npc.h"
#include "visitor.h"
#include "scheduler.h"
#include "factory.h"
#include "logger.h"
#include <random>
#include <atomic>

// Объявляем внешние переменные
extern std::vector<std::shared_ptr<NPC>> npcs;
extern std::atomic<bool> game_over;

NPC::NPC(NpcType type, const std::string& name, int x, int y)
    : type(type), name(name), x(x), y(y), alive(true) {
    // Устанавливаем расстояния хода и убийства в зависимости от типа NPC
    switch (type) {
        case NpcType::ElfType:
            move_distance = 10;
            kill_distance = 50;
            break;
        case NpcType::DragonType:
            move_distance = 50;
            kill_distance = 30;
            break;
        case NpcType::DruidType:
            move_distance = 10;
            kill_distance = 10;
            break;
        default:
            move_distance = 0;
            kill_distance = 0;
            break;
    }
}

void NPC::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void NPC::notify(const std::string& event) {
    for (auto& weakObs : observers) {
        if (auto obs = weakObs.lock()) {
            obs->onEvent(event);
        }
    }
}

bool NPC::isClose(const std::shared_ptr<NPC>& other, size_t distance) const {
    int dx = x - other->x;
    int dy = y - other->y;
    return (dx * dx + dy * dy) <= (distance * distance);
}

void NPC::print() const {
    if (alive) {
        std::cout << "Type: " << static_cast<int>(type)
                  << ", Name: " << name
                  << ", Coordinates: (" << x << ", " << y << ")" << std::endl;
    }
}

Task NPC::run() {
    static thread_local std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> dice_distribution(1, 6);
    std::uniform_int_distribution<int> move_distribution(-move_distance, move_distance);

    while (alive && !game_over.load()) {
        // Перемещение
        x += move_distribution(generator);
        y += move_distribution(generator);

        // Не позволяем NPC покинуть пределы карты
        if (x < 0) x = 0;
        if (x > 100) x = 100;
        if (y < 0) y = 0;
        if (y > 100) y = 100;

        // Сражение
        for (auto& other : npcs) {
            if (other.get() == this || !other->alive) continue;

            if (isClose(other, kill_distance)) {
                // Проверяем совместимость для боя
                FightVisitor fight(*this);
                other->accept(fight, shared_from_this());

                if (fight.attackerDies || fight.defenderDies) {
                    // Бросаем кубики
                    int attack_strength = dice_distribution(generator);
                    int defense_strength = dice_distribution(generator);

                    if (attack_strength > defense_strength) {
                        if (fight.defenderDies) {
                            other->alive = false;
                            other->notify(other->name + " was killed by " + name);
                        }
                    } else {
                        if (fight.attackerDies) {
                            alive = false;
                            notify(name + " was killed by " + other->name);
                            co_return; // Завершаем корутину, если NPC умер
                        }
                    }
                }
            }
        }

        co_await std::suspend_always{};
    }
}

void NPC::save(std::ostream& os) const {
    os << static_cast<int>(type) << ' ' << name << ' ' << x << ' ' << y << ' ' << alive << '\n';
}

// Реализация статического метода load()
std::shared_ptr<NPC> NPC::load(std::istream& is) {
    int typeInt;
    std::string name;
    int x, y;
    bool alive;
    if (!(is >> typeInt >> name >> x >> y >> alive)) {
        return nullptr; // Ошибка при чтении данных
    }

    NpcType type = static_cast<NpcType>(typeInt);
    auto npc = NPCFactory::createNPC(type, name, x, y);
    npc->alive = alive;
    return npc;
}