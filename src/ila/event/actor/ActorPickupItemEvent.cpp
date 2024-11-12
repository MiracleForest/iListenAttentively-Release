#include "ActorPickupItemEvent.h"
#include <mc/world/actor/ai/goal/PickupItemsGoal.h>

namespace ila::inline actor
{

ItemActor& ActorPickupItemBeforeEvent::getItemActor() const { return mItemActor; };

ItemActor const& ActorPickupItemAfterEvent::getItemActor() const { return mItemActor; };

LL_TYPE_INSTANCE_HOOK(
    ActorPickupItemEventHook,
    ll::memory::HookPriority::Normal,
    PickupItemsGoal,
    &PickupItemsGoal::_pickItemUp,
    void,
    ItemActor* item
)
{
    if (item == nullptr) return origin(item);
    auto* actor = ll::memory::dAccess<Mob*>(this, 112);
    if (actor == nullptr) return origin(item);
    auto beforeEvent = ActorPickupItemBeforeEvent(*actor, *item);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(item);
    eventBus.publish(ActorPickupItemAfterEvent(*actor, *item));
}

Event_Factory(ActorPickupItem, <ActorPickupItemEventHook>);

} // namespace ila::inline actor