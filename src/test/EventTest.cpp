#include "Global.h"
#include "event/legacyMoney/MoneyChangeEvent.h"
#include "event/minecraft/actor/ActorChangeDimensionEvent.h"
#include "event/minecraft/actor/ActorGetEffectEvent.h"
#include "event/minecraft/actor/ActorPickupItemEvent.h"
#include "event/minecraft/actor/ActorRideEvent.h"
#include "event/minecraft/actor/ArmorStandSwapItemEvent.h"
#include "event/minecraft/actor/DeathMessageEvent.h"
#include "event/minecraft/actor/DragonRespawnEvent.h"
#include "event/minecraft/actor/ProjectileCreateEvent.h"
#include "event/minecraft/level/SculkCatalystAbsorbExperienceEvent.h"
#include "event/minecraft/level/WeatherUpdateEvent.h"
#include "event/minecraft/player/PlayerAttackBlockEvent.h"
#include "event/minecraft/player/PlayerChangGameTypeEvent.h"
#include "event/minecraft/player/PlayerChangPermissionsEvent.h"
#include "event/minecraft/player/PlayerChangeDimensionEvent.h"
#include "event/minecraft/player/PlayerDropItemEvent.h"
#include "event/minecraft/player/PlayerEditSignEvent.h"
#include "event/minecraft/player/PlayerInteractEntityEvent.h"
#include "event/minecraft/player/PlayerRequestItemActionEvent.h"
#include "event/minecraft/server/ClientLoginEvent.h"
#include "event/minecraft/server/ServerPongEvent.h"
#include "event/minecraft/world/DragonEggBlockTeleportEvent.h"
#include "event/minecraft/world/ExplosionEvent.h"
#include "event/minecraft/world/FarmDecayEvent.h"
#include "event/minecraft/world/ItemFrameBlockEvent.h"
#include "event/minecraft/world/LiquidFlowEvent.h"
#include "event/minecraft/world/LiquidTryFlowEvent.h"
#include "event/minecraft/world/MossGrowthEvent.h"
#include "event/minecraft/world/PistonPushEvent.h"
#include "event/minecraft/world/PressurePlateTriggerEvent.h"
#include "event/minecraft/world/RedstoneUpdateEvent.h"
#include "event/minecraft/world/SculkBlockGrowthEvent.h"
#include "event/minecraft/world/SculkSpreadEvent.h"
#include "event/minecraft/world/SpawnItemActorEvent.h"
#include "event/minecraft/world/SpawnWanderingTraderEvent.h"
#include "event/minecraft/world/WitherDestroyEvent.h"
#include <ll/api/event/EventBus.h>
#include <ll/api/memory/Hook.h>
#include <mc/world/events/ServerInstanceEventCoordinator.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    EventTest,
    HookPriority::Normal,
    ServerInstanceEventCoordinator,
    &ServerInstanceEventCoordinator::sendServerThreadStarted,
    void,
    ServerInstance& ins
)
{
    origin(ins);
}