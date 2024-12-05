#include "ila/event/minecraft/actor/ActorTickEvent.h"

namespace ila::mc::inline actor
{
LL_TYPE_INSTANCE_HOOK(ActorTickEventHook, HookPriority::Normal, Actor, "?normalTick@Actor@@UEAAXXZ", void)
{
    auto beforeEvent = ActorTickBeforeEvent(*this);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin();
    eventBus.publish(ActorTickAfterEvent(*this));
}

Event_Factory(ActorTick, <ActorTickEventHook>);

} // namespace ila::mc::inline actor