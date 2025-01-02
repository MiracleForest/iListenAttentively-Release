#include "ila/event/minecraft/player/PlayerChangeDimensionEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/deps/core/math/Vec3.h>
#include <mc/world/level/PlayerDimensionTransferer.h>

namespace ila::mc::inline player
{

void PlayerChangeDimensionBeforeEvent::serialize(CompoundTag& nbt) const
{
    PlayerEvent::serialize(nbt);
    nbt["state"]           = magic_enum::enum_name(getChangeDimensionRequest().mState);
    nbt["fromDimensionId"] = getChangeDimensionRequest().mFromDimensionId->id;
    nbt["toDimensionId"]   = getChangeDimensionRequest().mToDimensionId->id;
    nbt["fromLocation"]    = ListTag { getChangeDimensionRequest().mFromLocation->x,
                                    getChangeDimensionRequest().mFromLocation->y,
                                    getChangeDimensionRequest().mFromLocation->z };
    nbt["toLocation"]      = ListTag { getChangeDimensionRequest().mToLocation->x,
                                  getChangeDimensionRequest().mToLocation->y,
                                  getChangeDimensionRequest().mToLocation->z };
    nbt["usePortal"]       = getChangeDimensionRequest().mUsePortal;
    nbt["respawn"]         = getChangeDimensionRequest().mRespawn;
    if (getChangeDimensionRequest().mAgentTag) { nbt["agentTag"] = *getChangeDimensionRequest().mAgentTag; }
}
ChangeDimensionRequest const& PlayerChangeDimensionBeforeEvent::getChangeDimensionRequest() const
{
    return mChangeDimensionRequest;
}
Dimension const& PlayerChangeDimensionBeforeEvent::getDimension() const { return mDimension; }

void PlayerChangeDimensionAfterEvent::serialize(CompoundTag& nbt) const
{
    PlayerEvent::serialize(nbt);
    nbt["state"]           = magic_enum::enum_name(getChangeDimensionRequest().mState);
    nbt["fromDimensionId"] = getChangeDimensionRequest().mFromDimensionId->id;
    nbt["toDimensionId"]   = getChangeDimensionRequest().mToDimensionId->id;
    nbt["fromLocation"]    = ListTag { getChangeDimensionRequest().mFromLocation->x,
                                    getChangeDimensionRequest().mFromLocation->y,
                                    getChangeDimensionRequest().mFromLocation->z };
    nbt["toLocation"]      = ListTag { getChangeDimensionRequest().mToLocation->x,
                                  getChangeDimensionRequest().mToLocation->y,
                                  getChangeDimensionRequest().mToLocation->z };
    nbt["usePortal"]       = getChangeDimensionRequest().mUsePortal;
    nbt["respawn"]         = getChangeDimensionRequest().mRespawn;
    if (getChangeDimensionRequest().mAgentTag) { nbt["agentTag"] = *getChangeDimensionRequest().mAgentTag; }
}
ChangeDimensionRequest const& PlayerChangeDimensionAfterEvent::getChangeDimensionRequest() const
{
    return mChangeDimensionRequest;
}
Dimension const& PlayerChangeDimensionAfterEvent::getDimension() const { return mDimension; }

LL_AUTO_TYPE_INSTANCE_HOOK(
    PlayerChangeDimensionEventHook,
    HookPriority::Normal,
    PlayerDimensionTransferer,
    &PlayerDimensionTransferer::$playerPrepareRegion,
    void,
    Player&                       pPlayer,
    ChangeDimensionRequest const& pChangeDimensionRequest,
    Dimension const&              pDimension
)
{
    LLEventBus.publish(PlayerChangeDimensionBeforeEvent(pPlayer, pChangeDimensionRequest, pDimension));
    origin(pPlayer, pChangeDimensionRequest, pDimension);
    LLEventBus.publish(PlayerChangeDimensionAfterEvent(pPlayer, pChangeDimensionRequest, pDimension));
}

Event_Hook_Factory(PlayerChangeDimension, <PlayerChangeDimensionEventHook>);
} // namespace ila::mc::inline player