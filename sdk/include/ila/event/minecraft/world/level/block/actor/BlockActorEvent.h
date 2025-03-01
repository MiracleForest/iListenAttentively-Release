#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Event.h>
#include <mc/world/level/block/actor/BlockActor.h>

namespace ila::event::inline blockActor
{

class BlockActorEvent : public ll::event::Event
{
protected:
    BlockActor& mSelf;

public:
    constexpr explicit BlockActorEvent(BlockActor& blockActor)
        : mSelf(blockActor)
    {
    }

    ILAPI void serialize(CompoundTag&) const override;

    ILNDAPI BlockActor& self() const;
};

} // namespace ila::event::inline block::actor