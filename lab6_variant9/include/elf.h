#ifndef ELF_H
#define ELF_H

#include "npc.h"

struct Elf : public NPC {
    Elf(const std::string& name, int x, int y);
    ~Elf() override = default;

    void accept(Visitor& visitor, std::shared_ptr<NPC> other) override;

    void print() const override;
    void save(std::ostream& os) const override;
};

#endif