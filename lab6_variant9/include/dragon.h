#ifndef DRAGON_H
#define DRAGON_H

#include "npc.h"

struct Dragon : public NPC {
    Dragon(const std::string& name, int x, int y);
    ~Dragon() override = default;

    void accept(Visitor& visitor, std::shared_ptr<NPC> other) override;

    void print() const override;
    void save(std::ostream& os) const override;
};

#endif