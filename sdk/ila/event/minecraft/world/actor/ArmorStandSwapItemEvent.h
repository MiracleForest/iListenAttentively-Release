#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>
#include <mc/deps/shared_types/EquipmentSlot.h>

namespace ila::mc::inline actor
{
class ArmorStandSwapItemBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
protected:
    Player&                             mPlayer;
    SharedTypes::Legacy::EquipmentSlot& mSlot;

public:
    constexpr explicit ArmorStandSwapItemBeforeEvent(
        Actor&                              actor,
        Player&                             player,
        SharedTypes::Legacy::EquipmentSlot& slot
    )
        : Cancellable(actor)
        , mPlayer(player)
        , mSlot(slot)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI Player& getPlayer() const;
    ILNDAPI SharedTypes::Legacy::EquipmentSlot& getSlot() const;
};

class ArmorStandSwapItemAfterEvent final : public ll::event::entity::ActorEvent
{
protected:
    Player const&                             mPlayer;
    SharedTypes::Legacy::EquipmentSlot const& mSlot;

public:
    constexpr explicit ArmorStandSwapItemAfterEvent(
        Actor&                                    actor,
        Player const&                             player,
        SharedTypes::Legacy::EquipmentSlot const& slot
    )
        : ActorEvent(actor)
        , mPlayer(player)
        , mSlot(slot)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI Player const& getPlayer() const;
    ILNDAPI SharedTypes::Legacy::EquipmentSlot const& getSlot() const;
};
} // namespace ila::mc::inline actor