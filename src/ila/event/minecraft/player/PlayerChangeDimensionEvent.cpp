#include "PlayerChangeDimensionEvent.h"
#include <mc/world/actor/player/PlayerDimensionTransferer.h>

namespace ila::mc::inline player
{

ChangeDimensionRequest const& PlayerChangeDimensionBeforeEvent::getChangeDimensionRequest() const
{
    return mChangeDimensionRequest;
}
Dimension const& PlayerChangeDimensionBeforeEvent::getDimension() const { return mDimension; }

ChangeDimensionRequest const& PlayerChangeDimensionAfterEvent::getChangeDimensionRequest() const
{
    return mChangeDimensionRequest;
}
Dimension const& PlayerChangeDimensionAfterEvent::getDimension() const { return mDimension; }

LL_TYPE_INSTANCE_HOOK(
    PlayerChangeDimensionEventHook,
    HookPriority::Normal,
    PlayerDimensionTransferer,
    "?playerPrepareRegion@PlayerDimensionTransferer@@UEAAXAEAVPlayer@@AEBVChangeDimensionRequest@@"
    "AEBVDimension@@@Z",
    void,
    Player&                       pPlayer,
    ChangeDimensionRequest const& pChangeDimensionRequest,
    Dimension const&              pDimension
)
{
    eventBus.publish(PlayerChangeDimensionBeforeEvent(pPlayer, pChangeDimensionRequest, pDimension));
    origin(pPlayer, pChangeDimensionRequest, pDimension);
    eventBus.publish(PlayerChangeDimensionAfterEvent(pPlayer, pChangeDimensionRequest, pDimension));
}

Event_Factory(PlayerChangeDimension, <PlayerChangeDimensionEventHook>);
} // namespace ila::mc::inline player