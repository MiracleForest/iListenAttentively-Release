#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

namespace land
{

class PlayerBuyLandBeforeEvent final : public ll::event::Cancellable<ll::event::PlayerEvent>
{
protected:
    struct LandSelectorData* mLandSelectorData;
    int&                     mPrice;

public:
    constexpr explicit PlayerBuyLandBeforeEvent(
        Player&                  player,
        struct LandSelectorData* landSelectorData,
        int&                     price
    )
        : Cancellable(player)
        , mLandSelectorData(landSelectorData)
        , mPrice(price)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI struct LandSelectorData* getLandSelectorData() const;
    ILNDAPI int&                     getPrice() const;
};

class PlayerBuyLandAfterEvent final : public ll::event::PlayerEvent
{
protected:
    std::shared_ptr<class LandData> mLandData;

public:
    explicit PlayerBuyLandAfterEvent(Player& player, std::shared_ptr<class LandData> landData)
        : PlayerEvent(player)
        , mLandData(landData)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI std::shared_ptr<class LandData> getLandData() const;
};

} // namespace land