#pragma once
#include "ila/base/Macro.h"
#include "ila/event/minecraft/world/level/block/actor/BlockActorEvent.h"
#include <ll/api/event/Cancellable.h>
#include <mc/world/level/block/actor/ChestBlockActor.h>

namespace ila::mc::inline blockActor
{
class ChestPairWithBeforeEvent final
    : public ll::event::Cancellable<ila::event::blockActor::BlockActorEvent>
{
protected:
    ChestBlockActor& mChest;
    bool&            mLead;

public:
    constexpr explicit ChestPairWithBeforeEvent(ChestBlockActor& self, ChestBlockActor& chest, bool& lead)
        : Cancellable(self)
        , mChest(chest)
        , mLead(lead)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI ChestBlockActor& self() const;
    ILNDAPI ChestBlockActor& getChest() const;
    ILNDAPI bool&            getLead() const;
};

class ChestPairWithAfterEvent final : public ila::event::blockActor::BlockActorEvent
{
protected:
    ChestBlockActor& mChest;
    bool const&      mLead;

public:
    constexpr explicit ChestPairWithAfterEvent(ChestBlockActor& self, ChestBlockActor& chest, bool& lead)
        : BlockActorEvent(self)
        , mChest(chest)
        , mLead(lead)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ChestBlockActor& self() const;
    ILNDAPI ChestBlockActor& getChest() const;
    ILNDAPI bool const&      getLead() const;
};
} // namespace ila::mc::inline world