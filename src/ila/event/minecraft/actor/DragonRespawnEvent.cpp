#include "DragonRespawnEvent.h"
#include <mc/world/level/dimension/end/EndDragonFight.h>

namespace ila::mc::inline actor
{

LL_TYPE_INSTANCE_HOOK(
    DragonRespawnEventHook,
    HookPriority::Normal,
    EndDragonFight,
    "?_setRespawnStage@EndDragonFight@@AEAAXW4RespawnAnimation@@@Z",
    void,
    RespawnAnimation pStage
)
{
    auto beforeEvent = DragonRespawnBeforeEvent();
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pStage);
    eventBus.publish(DragonRespawnAfterEvent());
}

Event_Factory(DragonRespawn, <DragonRespawnEventHook>);

} // namespace ila::mc::inline actor