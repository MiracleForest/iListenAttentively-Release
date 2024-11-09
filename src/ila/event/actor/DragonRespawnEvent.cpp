#include "DragonRespawnEvent.h"
#include <mc/world/level/dimension/end/EndDragonFight.h>

namespace ila::inline actor
{

LL_TYPE_INSTANCE_HOOK(
    DragonRespawnEventHook,
    HookPriority::Normal,
    EndDragonFight,
    "?_setRespawnStage@EndDragonFight@@AEAAXW4RespawnAnimation@@@Z",
    void,
    RespawnAnimation stage
)
{
    auto beforeEvent = DragonRespawnBeforeEvent();
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(stage);
    eventBus.publish(DragonRespawnAfterEvent());
}

Event_Factory(DragonRespawn, <DragonRespawnEventHook>);

} // namespace ila::inline actor