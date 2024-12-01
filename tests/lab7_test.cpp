#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <atomic>
#include <sstream>
#include <npc.h>
#include <elf.h>
#include <dragon.h>
#include <druid.h>
#include <visitor.h>
#include <observer.h>
#include <factory.h>
#include <scheduler.h>

std::vector<std::shared_ptr<NPC>> npcs;
std::atomic<bool> game_over(false);

class NPCTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Инициализация NPC
        auto elf = NPCFactory::createNPC(NpcType::ElfType, "TestElf", 10, 10);
        auto dragon = NPCFactory::createNPC(NpcType::DragonType, "TestDragon", 20, 20);
        auto druid = NPCFactory::createNPC(NpcType::DruidType, "TestDruid", 30, 30);
        
        npcs.push_back(elf);
        npcs.push_back(dragon);
        npcs.push_back(druid);
    }
    
    void TearDown() override {
        npcs.clear();
        game_over.store(false);
    }
};

// Тест создания NPC (из старых тестов)
TEST_F(NPCTest, CreationTest) {
    ASSERT_EQ(npcs.size(), 3);

    EXPECT_EQ(npcs[0]->name, "TestElf");
    EXPECT_EQ(npcs[1]->name, "TestDragon");
    EXPECT_EQ(npcs[2]->name, "TestDruid");

    EXPECT_EQ(npcs[0]->x, 10);
    EXPECT_EQ(npcs[0]->y, 10);
    EXPECT_EQ(npcs[1]->x, 20);
    EXPECT_EQ(npcs[1]->y, 20);
    EXPECT_EQ(npcs[2]->x, 30);
    EXPECT_EQ(npcs[2]->y, 30);
}

TEST_F(NPCTest, Movement) {
    auto initial_x = npcs[0]->x;
    auto initial_y = npcs[0]->y;

    // Запускаем корутину перемещения NPC
    auto task = npcs[0]->run();
    Scheduler::instance().schedule(std::move(task));
    Scheduler::instance().run();

    // Проверяем, что NPC переместился
    EXPECT_NE(npcs[0]->x, initial_x);
    EXPECT_NE(npcs[0]->y, initial_y);
}

TEST_F(NPCTest, Interaction) {
    // Устанавливаем NPC близко друг к другу для сражения
    npcs[0]->x = 50;
    npcs[0]->y = 50;

    npcs[1]->x = 50;
    npcs[1]->y = 50;

    // Запускаем корутину
    auto task0 = npcs[0]->run();
    auto task1 = npcs[1]->run();
    Scheduler::instance().schedule(std::move(task0));
    Scheduler::instance().schedule(std::move(task1));

    // Запускаем планировщик несколько раз, чтобы произошёл бой
    for (int i = 0; i < 10; ++i) {
        Scheduler::instance().run();
    }

    bool dragon_alive = npcs[1]->alive;
    bool elf_alive = npcs[0]->alive;

    EXPECT_TRUE(!dragon_alive || !elf_alive);
}

// Тест завершения корутины при `game_over`
TEST_F(NPCTest, GameOver) {
    game_over.store(true);

    auto task = npcs[0]->run();
    Scheduler::instance().schedule(std::move(task));
    Scheduler::instance().run();

    // Проверяем, что NPC завершил свою корутину
    EXPECT_TRUE(task.done());
}

// Тест метода `isClose` (из старых тестов)
TEST_F(NPCTest, DistanceTest) {
    auto npc1 = npcs[0]; // TestElf at (10,10)
    auto npc2 = NPCFactory::createNPC(NpcType::DragonType, "Dragon1", 13, 14); // Расстояние 5 от npc1

    EXPECT_TRUE(npc1->isClose(npc2, 5));
    EXPECT_FALSE(npc1->isClose(npc2, 4));
}

// Тест боя между NPC (из старых тестов)
TEST_F(NPCTest, FightTest) {
    auto elf = npcs[0];
    auto dragon = npcs[1];
    auto druid = npcs[2];

    // Эльф атакует друида
    FightVisitor fight1(*elf);
    druid->accept(fight1, elf);

    EXPECT_FALSE(fight1.attackerDies);
    EXPECT_TRUE(fight1.defenderDies);

    // Дракон атакует эльфа
    FightVisitor fight2(*dragon);
    elf->accept(fight2, dragon);

    EXPECT_FALSE(fight2.attackerDies);
    EXPECT_TRUE(fight2.defenderDies);

    // Друид атакует дракона
    FightVisitor fight3(*druid);
    dragon->accept(fight3, druid);

    EXPECT_FALSE(fight3.attackerDies);
    EXPECT_TRUE(fight3.defenderDies);
}

// Тест работы наблюдателя (из старых тестов)
TEST_F(NPCTest, ObserverTest) {
    auto elf = npcs[0];
    auto druid = npcs[2];

    // Создаем mock-объект для наблюдателя
    class MockObserver : public Observer {
    public:
        std::string lastEvent;
        void onEvent(const std::string& event) override {
            lastEvent = event;
        }
    };

    auto mockObserver = std::make_shared<MockObserver>();
    elf->addObserver(mockObserver);

    // Эльф атакует друида
    FightVisitor fight(*elf);
    druid->accept(fight, elf);

    if (fight.defenderDies) {
        elf->notify(elf->name + " killed " + druid->name);
    }

    EXPECT_EQ(mockObserver->lastEvent, "TestElf killed TestDruid");
}

TEST_F(NPCTest, SaveLoadTest) {
    auto elf = npcs[0]; // TestElf

    // Сохраняем в строковый поток
    std::ostringstream oss;
    elf->save(oss);

    // Загружаем из строкового потока
    std::istringstream iss(oss.str());
    auto loadedElf = NPC::load(iss);

    ASSERT_NE(loadedElf, nullptr);
    EXPECT_EQ(loadedElf->type, NpcType::ElfType);
    EXPECT_EQ(loadedElf->name, "TestElf");
    EXPECT_EQ(loadedElf->x, elf->x);
    EXPECT_EQ(loadedElf->y, elf->y);
    EXPECT_EQ(loadedElf->alive, elf->alive);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}