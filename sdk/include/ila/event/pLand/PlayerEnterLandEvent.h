#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

namespace land
{

class PlayerEnterLandEvent final : public ll::event::PlayerEvent
{
protected:
    uint64_t mLandId;

public:
    constexpr explicit PlayerEnterLandEvent(Player& player, uint64_t landID)
        : PlayerEvent(player)
        , mLandId(landID)
    {
    }

    void serialize(CompoundTag& nbt) const override;

    ILNDAPI uint64_t getLandId() const;
};
} // namespace land