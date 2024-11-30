#include <gtest/gtest.h>
#include <memory>
#include <npc.h>
#include <elf.h>
#include <dragon.h>
#include <druid.h>
#include <visitor.h>
#include <observer.h>
#include <factory.h>

TEST(NPCTest, CreationTest) {
    auto elf = NPCFactory::createNPC(NpcType::ElfType, "Legolas", 100, 200);
    auto dragon = NPCFactory::createNPC(NpcType::DragonType, "Smaug", 300, 400);
    auto druid = NPCFactory::createNPC(NpcType::DruidType, "Radagast", 150, 250);

    ASSERT_NE(elf, nullptr);
    ASSERT_NE(dragon, nullptr);
    ASSERT_NE(druid, nullptr);

    EXPECT_EQ(elf->name, "Legolas");
    EXPECT_EQ(dragon->name, "Smaug");
    EXPECT_EQ(druid->name, "Radagast");

    EXPECT_EQ(elf->x, 100);
    EXPECT_EQ(elf->y, 200);
    EXPECT_EQ(dragon->x, 300);
    EXPECT_EQ(dragon->y, 400);
    EXPECT_EQ(druid->x, 150);
    EXPECT_EQ(druid->y, 250);
}

TEST(NPCTest, DistanceTest) {
    auto npc1 = NPCFactory::createNPC(NpcType::ElfType, "Elf1", 0, 0);
    auto npc2 = NPCFactory::createNPC(NpcType::DragonType, "Dragon1", 3, 4); // Расстояние 5 от npc1

    EXPECT_TRUE(npc1->isClose(npc2, 5));
    EXPECT_FALSE(npc1->isClose(npc2, 4));
}

TEST(NPCTest, FightTest) {
    auto elf = std::dynamic_pointer_cast<Elf>(NPCFactory::createNPC(NpcType::ElfType, "Legolas", 0, 0));
    auto dragon = std::dynamic_pointer_cast<Dragon>(NPCFactory::createNPC(NpcType::DragonType, "Smaug", 0, 0));
    auto druid = std::dynamic_pointer_cast<Druid>(NPCFactory::createNPC(NpcType::DruidType, "Radagast", 0, 0));

    // Наблюдатели
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    elf->addObserver(consoleObserver);
    dragon->addObserver(consoleObserver);
    druid->addObserver(consoleObserver);

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

TEST(NPCTest, ObserverTest) {
    auto elf = NPCFactory::createNPC(NpcType::ElfType, "Legolas", 0, 0);
    auto druid = NPCFactory::createNPC(NpcType::DruidType, "Radagast", 0, 0);

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

    EXPECT_EQ(mockObserver->lastEvent, "Legolas killed Radagast");
}

TEST(NPCTest, SaveLoadTest) {
    auto elf = NPCFactory::createNPC(NpcType::ElfType, "Legolas", 100, 200);

    // Сохраняем в строковый поток
    std::ostringstream oss;
    elf->save(oss);

    // Загружаем из строкового потока
    std::istringstream iss(oss.str());
    auto loadedElf = NPC::load(iss);

    ASSERT_NE(loadedElf, nullptr);
    EXPECT_EQ(loadedElf->type, NpcType::ElfType);
    EXPECT_EQ(loadedElf->name, "Legolas");
    EXPECT_EQ(loadedElf->x, 100);
    EXPECT_EQ(loadedElf->y, 200);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}