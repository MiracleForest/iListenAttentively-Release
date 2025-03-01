#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

namespace land
{
class PlayerDeleteLandBeforeEvent final : public ll::event::Cancellable<ll::event::PlayerEvent>
{
protected:
    uint64_t   mLandId;
    int const& mRefundPrice;

public:
    constexpr explicit PlayerDeleteLandBeforeEvent(Player& player, uint64_t landID, int const& refundPrice)
        : Cancellable(player)
        , mLandId(landID)
        , mRefundPrice(refundPrice)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI uint64_t   getLandId() const;
    ILNDAPI int const& getRefundPrice() const;
};

class PlayerDeleteLandAfterEvent final : public ll::event::PlayerEvent
{
protected:
    uint64_t mLandId;

public:
    constexpr explicit PlayerDeleteLandAfterEvent(Player& player, uint64_t landID)
        : PlayerEvent(player)
        , mLandId(landID)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI uint64_t getLandId() const;
};
} // namespace land