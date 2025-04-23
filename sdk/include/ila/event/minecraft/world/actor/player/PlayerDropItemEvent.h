#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

// clang-format off
class ItemStack;
// clang-format on

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerDropItemBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    ItemStack& mItem;

public:
    constexpr explicit PlayerDropItemBeforeEvent(Player& player, ItemStack& item)
        : Cancellable(player)
        , mItem(item)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ItemStack const& item() const;
};

class PlayerDropItemAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    ItemStack const& mItem;

public:
    constexpr explicit PlayerDropItemAfterEvent(Player& player, ItemStack const& item)
        : PlayerEvent(player)
        , mItem(item)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ItemStack const& item() const;
};
} // namespace ila::mc::inline world::inline actor::inline player