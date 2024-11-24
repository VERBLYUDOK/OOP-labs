#ifndef FACTORY_H
#define FACTORY_H

#include "npc.h"

struct NPCFactory {
    static std::shared_ptr<NPC> createNPC(NpcType type, const std::string& name, int x, int y);
};

#endif