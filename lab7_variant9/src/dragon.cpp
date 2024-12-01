#include "dragon.h"
#include "visitor.h"

Dragon::Dragon(const std::string& name, int x, int y)
    : NPC(NpcType::DragonType, name, x, y) {}

void Dragon::accept(Visitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visit(*this, other);
}

void Dragon::print() const {
    if (alive) {
        std::cout << "Dragon - Name: " << name
                  << ", Coordinates: (" << x << ", " << y << ")" << std::endl;
    }
}

void Dragon::save(std::ostream& os) const {
    NPC::save(os);
}
