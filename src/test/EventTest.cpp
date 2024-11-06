#include "event/player/PlayerChangGameTypeEvent.h"
#include "event/player/PlayerChangeDimensionEvent.h"
#include "event/player/PlayerInteractEntity.h"
#include "event/server/ServerPongEvent.h"
#include "event/world/DragonEggBlockTeleportEvent.h"
#include <ll/api/event/EventBus.h>
#include <ll/api/memory/Hook.h>
#include <magic_enum.hpp>
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