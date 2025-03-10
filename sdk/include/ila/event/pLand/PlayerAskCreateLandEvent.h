#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

namespace land
{

class PlayerAskCreateLandBeforeEvent final : public ll::event::Cancellable<ll::event::PlayerEvent>
{
public:
    constexpr explicit PlayerAskCreateLandBeforeEvent(Player& player)
        : Cancellable(player)
    {
    }
};

class PlayerAskCreateLandAfterEvent final : public ll::event::PlayerEvent
{
protected:
    bool mIs3DLand;

public:
    constexpr explicit PlayerAskCreateLandAfterEvent(Player& player, bool is3DLand)
        : PlayerEvent(player)
        , mIs3DLand(is3DLand)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI bool is3DLand() const;
};

} // namespace land