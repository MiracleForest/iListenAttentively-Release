#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

// clang-format off
class ItemStack;
// clang-format on

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerAteBeforeEvent final : public ll::event::Cancellable<ll::event::PlayerEvent>
{
protected:
    ItemStack& mItem;

public:
    constexpr explicit PlayerAteBeforeEvent(Player& player, ItemStack& item)
        : Cancellable(player)
        , mItem(item)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ItemStack& item() const;
};

class PlayerAteAfterEvent final : public ll::event::PlayerEvent
{
protected:
    int mSlot;

public:
    constexpr explicit PlayerAteAfterEvent(Player& player, int slot)
        : PlayerEvent(player)
        , mSlot(slot)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI int slot() const;
};
} // namespace ila::mc::inline world::inline actor::inline player