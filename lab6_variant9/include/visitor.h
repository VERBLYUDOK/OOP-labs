#ifndef VISITOR_H
#define VISITOR_H

#include <memory>

struct Elf;
struct Dragon;
struct Druid;
struct NPC;

struct Visitor {
    virtual void visit(Elf& elf, std::shared_ptr<NPC> other) = 0;
    virtual void visit(Dragon& dragon, std::shared_ptr<NPC> other) = 0;
    virtual void visit(Druid& druid, std::shared_ptr<NPC> other) = 0;
    virtual ~Visitor() = default;
};

struct FightVisitor : public Visitor {
    NPC& attacker;
    bool attackerDies;
    bool defenderDies;

    FightVisitor(NPC& attacker);

    void visit(Elf& elf, std::shared_ptr<NPC> other) override;
    void visit(Dragon& dragon, std::shared_ptr<NPC> other) override;
    void visit(Druid& druid, std::shared_ptr<NPC> other) override;
};

#endif