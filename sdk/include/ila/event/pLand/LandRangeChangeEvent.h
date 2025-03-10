#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

namespace land
{
class LandRangeChangeBeforeEvent final : public ll::event::Cancellable<ll::event::PlayerEvent>
{
protected:
    std::shared_ptr<class LandData> const& mLandData;
    class LandPos const&                   mNewRange;
    int const&                             mNeedPay;
    int const&                             mRefundPrice;

public:
    constexpr explicit LandRangeChangeBeforeEvent(
        Player&                                player,
        std::shared_ptr<class LandData> const& landData,
        class LandPos const&                   newRange,
        int const&                             needPay,
        int const&                             refundPrice
    )
        : Cancellable(player)
        , mLandData(landData)
        , mNewRange(newRange)
        , mNeedPay(needPay)
        , mRefundPrice(refundPrice)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI std::shared_ptr<class LandData> const& landData() const;
    ILNDAPI class LandPos const&                   newRange() const;
    ILNDAPI int const&                             needPay() const;
    ILNDAPI int const&                             refundPrice() const;
};

class LandRangeChangeAfterEvent final : public ll::event::PlayerEvent
{
protected:
    std::shared_ptr<class LandData> const& mLandData;
    LandPos const&                         mNewRange;
    int const&                             mNeedPay;
    int const&                             mRefundPrice;

public:
    constexpr explicit LandRangeChangeAfterEvent(
        Player&                                player,
        std::shared_ptr<class LandData> const& landData,
        LandPos const&                         newRange,
        int const&                             needPay,
        int const&                             refundPrice
    )
        : PlayerEvent(player)
        , mLandData(landData)
        , mNewRange(newRange)
        , mNeedPay(needPay)
        , mRefundPrice(refundPrice)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI std::shared_ptr<class LandData> const& landData() const;
    ILNDAPI LandPos const&                         newRange() const;
    ILNDAPI int const&                             needPay() const;
    ILNDAPI int const&                             refundPrice() const;
};
} // namespace land