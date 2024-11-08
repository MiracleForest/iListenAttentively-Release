#include "Global.h"
#include "event/actor/ActorRideEvent.h"
#include "event/actor/ArmorStandSwapItemEvent.h"
#include "event/player/PlayerChangGameTypeEvent.h"
#include "event/player/PlayerChangPermissionsEvent.h"
#include "event/player/PlayerChangeDimensionEvent.h"
#include "event/player/PlayerInteractEntityEvent.h"
#include "event/server/ServerPongEvent.h"
#include "event/world/DragonEggBlockTeleportEvent.h"
#include "event/world/FarmDecayEvent.h"
#include "event/world/LiquidFlowEvent.h"
#include "event/world/LiquidTryFlowEvent.h"
#include "event/world/ExplosionEvent.h"
#include "event/world/PistonPushEvent.h"
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