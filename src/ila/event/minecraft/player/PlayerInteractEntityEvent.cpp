#include "PlayerInteractEntityEvent.h"

namespace ila::mc::inline player
{

Actor& PlayerInteractEntityBeforeEvent::getTarget() const { return mTarget; }
Vec3&  PlayerInteractEntityBeforeEvent::getPos() const { return mPos; }

Actor const& PlayerInteractEntityAfterEvent::getTarget() const { return mTarget; }
Vec3 const&  PlayerInteractEntityAfterEvent::getPos() const { return mPos; }
bool&        PlayerInteractEntityAfterEvent::getResult() const { return mResult; }

LL_TYPE_INSTANCE_HOOK(
    PlayerInteractEntityEventHook,
    HookPriority::Normal,
    Player,
    "?interact@Player@@QEAA_NAEAVActor@@AEBVVec3@@@Z",
    bool,
    Actor& pActor,
    Vec3&  pLocation
)
{
    auto beforeEvent = PlayerInteractEntityBeforeEvent(*this, pActor, pLocation);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pActor, pLocation);
    eventBus.publish(PlayerInteractEntityAfterEvent(*this, pActor, pLocation, result));
    return result;
}

Event_Factory(PlayerInteractEntity, <PlayerInteractEntityEventHook>);

} // namespace ila::mc::inline player