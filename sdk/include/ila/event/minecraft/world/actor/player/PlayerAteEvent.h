#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/player/PlayerEvent.h>

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerAteEvent final : public ll::event::PlayerEvent
{
protected:
    ItemStack& mItem;

public:
    constexpr explicit PlayerAteEvent(Player& player, ItemStack& item)
        : PlayerEvent(player)
        , mItem(item)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI ItemStack& item() const;
};
} // namespace ila::mc::inline player