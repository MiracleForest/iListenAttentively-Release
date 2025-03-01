#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

namespace land
{
class LandOwnerChangeBeforeEvent final : public ll::event::Cancellable<ll::event::PlayerEvent>
{
protected:
    Player&  mNewOwner;
    uint64_t mLandId;

public:
    constexpr explicit LandOwnerChangeBeforeEvent(Player& player, Player& newOwner, uint64_t landID)
        : Cancellable(player)
        , mNewOwner(newOwner)
        , mLandId(landID)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI Player&  getNewOwner() const;
    ILNDAPI uint64_t getLandId() const;
};

class LandOwnerChangeAfterEvent final : public ll::event::PlayerEvent
{
protected:
    Player&  mNewOwner;
    uint64_t mLandId;

public:
    constexpr explicit LandOwnerChangeAfterEvent(Player& player, Player& newOwner, uint64_t landID)
        : PlayerEvent(player)
        , mNewOwner(newOwner)
        , mLandId(landID)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI Player&  getNewOwner() const;
    ILNDAPI uint64_t getLandId() const;
};
} // namespace land