#include "elf.h"
#include "visitor.h"

Elf::Elf(const std::string& name, int x, int y)
    : NPC(NpcType::ElfType, name, x, y) {}

void Elf::accept(Visitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visit(*this, other);
}

void Elf::print() const {
    if (alive) {
        std::cout << "Elf - Name: " << name
                  << ", Coordinates: (" << x << ", " << y << ")" << std::endl;
    }
}

void Elf::save(std::ostream& os) const {
    NPC::save(os);
}