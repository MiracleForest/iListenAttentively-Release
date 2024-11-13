#include "ActorRideEvent.h"

namespace ila::mc::inline actor
{

Actor& ActorRideBeforeEvent::getTarget() const { return mTarget; }

Actor const& ActorRideAfterEvent::getTarget() const { return mTarget; }
bool&        ActorRideAfterEvent::getResult() const { return mResult; }

LL_TYPE_INSTANCE_HOOK(
    ActorRideEventHook,
    HookPriority::Normal,
    Actor,
    "?canAddPassenger@Actor@@UEBA_NAEAV1@@Z",
    bool,
    Actor& pPassenger
)
{
    auto beforeEvent = ActorRideBeforeEvent(pPassenger, *this);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pPassenger);
    eventBus.publish(ActorRideAfterEvent(pPassenger, *this, result));
    return result;
}

Event_Factory(ActorRide, <ActorRideEventHook>);

} // namespace ila::mc::inline actor