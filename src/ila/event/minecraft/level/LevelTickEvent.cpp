#include "ila/event/minecraft/level/LevelTickEvent.h"

namespace ila::mc::inline level
{

LL_TYPE_INSTANCE_HOOK(LevelTickEventHook, HookPriority::Normal, Level, &Level::tick, void)
{
    auto beforeEvent = LevelTickBeforeEvent(*this);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin();
    eventBus.publish(LevelTickAfterEvent(*this));
}

Event_Factory(LevelTick, <LevelTickEventHook>);

} // namespace ila::mc::inline level