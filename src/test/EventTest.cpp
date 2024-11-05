#include "event/player/PlayerInteractEntity.h"
#include "event/server/ServerPongEvent.h"
#include "event/world/DragonEggBlockTeleportEvent.h"
#include <ll/api/event/EventBus.h>
#include <ll/api/memory/Hook.h>
#include <mc/world/events/ServerInstanceEventCoordinator.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    EventTest,
    ll::memory::HookPriority::Normal,
    ServerInstanceEventCoordinator,
    &ServerInstanceEventCoordinator::sendServerThreadStarted,
    void,
    ServerInstance& ins
)
{
    origin(ins);
}