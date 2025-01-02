#include "ila/event/minecraft/actor/DragonRespawnEvent.h"
#include "ila/base/Gloabl.h"
#include <ll/api/service/Bedrock.h>
#include <mc/common/ActorUniqueID.h>
#include <mc/world/level/Level.h>
#include <mc/world/level/dimension/end/EndDragonFight.h>

namespace ila::mc::inline actor
{

LL_TYPE_INSTANCE_HOOK(
    DragonRespawnEventHook,
    HookPriority::Normal,
    EndDragonFight,
    &EndDragonFight::_setRespawnStage,
    void,
    RespawnAnimation pStage
)
{
    auto beforeEvent = DragonRespawnBeforeEvent();
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }
    origin(pStage);
    if (auto* dragon = static_cast<EnderDragon*>(
            ll::service::getLevel()->fetchEntity(mUnk63c6c7.as<ActorUniqueID>(), false)
        ))
    {
        LLEventBus.publish(DragonRespawnAfterEvent(*dragon));
    }
}

Event_Hook_Factory(DragonRespawn, <DragonRespawnEventHook>);

} // namespace ila::mc::inline actor