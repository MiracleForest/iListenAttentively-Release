#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/MobEvent.h>

// clang-format off
class BlockPos;
// clang-format on

namespace ila::mc::inline world::inline actor
{
class MobTakeBlockBeforeEvent final : public ll::event::Cancellable<ll::event::entity::MobEvent>
{
protected:
    BlockPos& mPos;

public:
    constexpr explicit MobTakeBlockBeforeEvent(Mob& mob, BlockPos& pos)
        : Cancellable(mob)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& pos() const;
};

class MobTakeBlockAfterEvent final : public ll::event::entity::MobEvent
{
protected:
    BlockPos& mPos;

public:
    constexpr explicit MobTakeBlockAfterEvent(Mob& mob, BlockPos& pos)
        : MobEvent(mob)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& pos() const;
};
} // namespace ila::mc::inline world::inline actor