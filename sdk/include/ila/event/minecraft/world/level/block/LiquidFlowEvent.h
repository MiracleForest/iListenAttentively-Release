#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world::inline level::inline block
{
class LiquidFlowBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos& mPos;
    int&      mDepth;
    bool&     mPreserveExisting;

public:
    constexpr explicit LiquidFlowBeforeEvent(
        BlockSource& blockSource,
        BlockPos&    pos,
        int&         depth,
        bool&        preserveExisting
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mDepth(depth)
        , mPreserveExisting(preserveExisting)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& pos() const;
    ILNDAPI int&      depth() const;
    ILNDAPI bool&     preserveExisting() const;
};

class LiquidFlowAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    int const&      mDepth;
    bool const&     mPreserveExisting;

public:
    constexpr explicit LiquidFlowAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        int const&      depth,
        bool const&     preserveExisting
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mDepth(depth)
        , mPreserveExisting(preserveExisting)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& pos() const;
    ILNDAPI int const&      depth() const;
    ILNDAPI bool const&     preserveExisting() const;
};
} // namespace ila::mc::inline world::inline level::inline block