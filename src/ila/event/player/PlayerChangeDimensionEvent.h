#include "Global.h"
#include <mc/world/level/ChangeDimensionRequest.h>

namespace ila::inline player
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

    ChangeDimensionRequest const& getChangeDimensionRequest() const { return mChangeDimensionRequest; };
    Dimension const&              getDimension() const { return mDimension; };
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

    ChangeDimensionRequest const& getChangeDimensionRequest() const { return mChangeDimensionRequest; };
    Dimension const&              getDimension() const { return mDimension; };
};
} // namespace ila::inline player