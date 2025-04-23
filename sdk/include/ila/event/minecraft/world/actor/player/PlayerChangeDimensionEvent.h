#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/player/PlayerEvent.h>

// clang-format off
class ChangeDimensionRequest;
class Dimension;
// clang-format on

namespace ila::mc::inline world::inline actor::inline player
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

    ILNDAPI ChangeDimensionRequest const& changeDimensionRequest() const;
    ILNDAPI Dimension const&              dimension() const;
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

    ILNDAPI ChangeDimensionRequest const& changeDimensionRequest() const;
    ILNDAPI Dimension const&              dimension() const;
};
} // namespace ila::mc::inline world::inline actor::inline player