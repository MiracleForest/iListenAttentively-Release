#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world
{
class FireTryBurnBlockBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mPos;

public:
    constexpr explicit FireTryBurnBlockBeforeEvent(BlockSource& blockSource, BlockPos const& pos)
        : Cancellable(blockSource)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& pos() const;
};

class FireTryBurnBlockAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;

public:
    constexpr explicit FireTryBurnBlockAfterEvent(BlockSource& blockSource, BlockPos const& pos)
        : WorldEvent(blockSource)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& pos() const;
};
} // namespace ila::mc::inline world