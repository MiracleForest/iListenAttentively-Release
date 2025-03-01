#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>

namespace ila::mc::inline blockActor
{
class BlockActorTickBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockActor& mBlockActor;

public:
    constexpr explicit BlockActorTickBeforeEvent(BlockSource& blockSource, BlockActor& blockActor)
        : Cancellable(blockSource)
        , mBlockActor(blockActor)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockActor& getBlockActor() const;
};

class BlockActorTickAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockActor& mBlockActor;

public:
    constexpr explicit BlockActorTickAfterEvent(BlockSource& blockSource, BlockActor& blockActor)
        : WorldEvent(blockSource)
        , mBlockActor(blockActor)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockActor& getBlockActor() const;
};
} // namespace ila::mc::inline world