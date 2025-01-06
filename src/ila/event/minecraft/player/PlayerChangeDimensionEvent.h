#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/player/PlayerEvent.h>
#include <mc/world/level/ChangeDimensionRequest.h>

namespace ila::mc::inline player
{
class PlayerChangeDimensionBeforeEvent final : public ll::event::player::PlayerEvent
{
protected:
    ChangeDimensionRequest const& mChangeDimensionRequest;
    Dimension const&              mDimension;

public:
    constexpr explicit PlayerChangeDimensionBeforeEvent(
        Player&                       player,
        ChangeDimensionRequest const& changeDimensionRequest,
        Dimension const&              dimension
    )
        : PlayerEvent(player)
        , mChangeDimensionRequest(changeDimensionRequest)
        , mDimension(dimension)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ChangeDimensionRequest const& getChangeDimensionRequest() const;
    ILNDAPI Dimension const&              getDimension() const;
};

class PlayerChangeDimensionAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    ChangeDimensionRequest const& mChangeDimensionRequest;
    Dimension const&              mDimension;

public:
    constexpr explicit PlayerChangeDimensionAfterEvent(
        Player&                       player,
        ChangeDimensionRequest const& changeDimensionRequest,
        Dimension const&              dimension
    )
        : PlayerEvent(player)
        , mChangeDimensionRequest(changeDimensionRequest)
        , mDimension(dimension)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ChangeDimensionRequest const& getChangeDimensionRequest() const;
    ILNDAPI Dimension const&              getDimension() const;
};
} // namespace ila::mc::inline player