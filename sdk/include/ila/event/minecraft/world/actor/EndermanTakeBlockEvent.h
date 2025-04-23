#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/MobEvent.h>
#include <mc/world/actor/monster/EnderMan.h>

// clang-format off
class BlockPos;
// clang-format on

namespace ila::mc::inline world::inline actor
{
class EndermanTakeBlockBeforeEvent final : public ll::event::Cancellable<ll::event::entity::MobEvent>
{
protected:
    BlockPos& mPos;

public:
    constexpr explicit EndermanTakeBlockBeforeEvent(Mob& mob, BlockPos& pos)
        : Cancellable(mob)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI EnderMan& self() const;
    ILNDAPI BlockPos& pos() const;
};

class EndermanTakeBlockAfterEvent final : public ll::event::entity::MobEvent
{
protected:
    BlockPos& mPos;

public:
    constexpr explicit EndermanTakeBlockAfterEvent(Mob& mob, BlockPos& pos)
        : MobEvent(mob)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI EnderMan&       self() const;
    ILNDAPI BlockPos const& pos() const;
};
} // namespace ila::mc::inline world::inline actor