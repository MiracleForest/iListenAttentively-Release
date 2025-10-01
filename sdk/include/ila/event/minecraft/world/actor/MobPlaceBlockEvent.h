#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/MobEvent.h>

// clang-format off
class BlockPos;
// clang-format on

namespace ila::mc::inline world::inline actor
{
class MobPlaceBlockBeforeEvent final : public ll::event::Cancellable<ll::event::entity::MobEvent>
{
protected:
    BlockPos&    mPos;
    Block const* mBlock;

public:
    constexpr explicit MobPlaceBlockBeforeEvent(Mob& mob, BlockPos& pos, Block const* block)
        : Cancellable(mob)
        , mPos(pos)
        , mBlock(block)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos&    pos() const;
    ILNDAPI Block const* block() const;
};

class MobPlaceBlockAfterEvent final : public ll::event::entity::MobEvent
{
protected:
    BlockPos&    mPos;
    Block const* mBlock;

public:
    constexpr explicit MobPlaceBlockAfterEvent(Mob& mob, BlockPos& pos, Block const* block)
        : MobEvent(mob)
        , mPos(pos)
        , mBlock(block)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& pos() const;
    ILNDAPI Block const*    block() const;
};
} // namespace ila::mc::inline world::inline actor