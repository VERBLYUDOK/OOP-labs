#include "factory.h"
#include "elf.h"
#include "dragon.h"
#include "druid.h"
#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::createNPC(NpcType type, const std::string& name, int x, int y) {
    switch (type) {
        case NpcType::ElfType:
            return std::make_shared<Elf>(name, x, y);
        case NpcType::DragonType:
            return std::make_shared<Dragon>(name, x, y);
        case NpcType::DruidType:
            return std::make_shared<Druid>(name, x, y);
        default:
            throw std::invalid_argument("Unknown NPC type");
    }
}