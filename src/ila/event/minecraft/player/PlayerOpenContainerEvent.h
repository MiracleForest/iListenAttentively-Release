#include "Global.h"
#include <mc/world/events/EventResult.h>

namespace ila::mc::inline player
{
class PlayerOpenContainerBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    BlockPos const& mPos;

public:
    constexpr explicit PlayerOpenContainerBeforeEvent(Player& player, BlockPos const& pos)
        : Cancellable(player)
        , mPos(pos)
    {
    }

    ILAPI BlockPos const& getContainerBlockPos() const;
};

class PlayerOpenContainerAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    BlockPos const& mPos;
    EventResult&    mResult;

public:
    constexpr explicit PlayerOpenContainerAfterEvent(Player& player, BlockPos const& pos, EventResult& result)
        : PlayerEvent(player)
        , mPos(pos)
        , mResult(result)
    {
    }

    ILAPI BlockPos const& getContainerBlockPos() const;
    ILAPI EventResult&    getResult() const;
};
} // namespace ila::mc::inline player