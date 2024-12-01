#include "visitor.h"
#include "elf.h"
#include "dragon.h"
#include "druid.h"

FightVisitor::FightVisitor(NPC& attacker)
    : attacker(attacker), attackerDies(false), defenderDies(false) {}

void FightVisitor::visit(Elf& elf, std::shared_ptr<NPC> other) {
    if (attacker.type == NpcType::DragonType) {
        defenderDies = true;
    } else if (attacker.type == NpcType::DruidType) {
        attackerDies = true;
    }
}

void FightVisitor::visit(Dragon& dragon, std::shared_ptr<NPC> other) {
    if (attacker.type == NpcType::DruidType) {
        defenderDies = true;
    } else if (attacker.type == NpcType::ElfType) {
        attackerDies = true;
    }
}

void FightVisitor::visit(Druid& druid, std::shared_ptr<NPC> other) {
    if (attacker.type == NpcType::ElfType) {
        defenderDies = true;
    } else if (attacker.type == NpcType::DragonType) {
        attackerDies = true;
    }
}
