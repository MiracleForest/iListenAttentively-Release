#include "Global.h"
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

    ILAPI ChangeDimensionRequest const& getChangeDimensionRequest() const;
    ILAPI Dimension const&              getDimension() const;
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

    ILAPI ChangeDimensionRequest const& getChangeDimensionRequest() const;
    ILAPI Dimension const&              getDimension() const;
};
} // namespace ila::mc::inline player