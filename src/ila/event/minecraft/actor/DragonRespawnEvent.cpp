#include "DragonRespawnEvent.h"
#include <ll/api/service/Bedrock.h>
#include <mc/world/level/Level.h>
#include <mc/world/level/dimension/end/EndDragonFight.h>

namespace ila::mc::inline actor
{

optional_ref<EnderDragon> DragonRespawnAfterEvent::getEnderDragon() const { return mEnderDragon; }

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
    auto uid = ll::memory::dAccess<ActorUniqueID>(this, 64);
    if (auto* dragon = (EnderDragon*)ll::service::getLevel()->fetchEntity(uid); dragon != nullptr)
    {
        eventBus.publish(DragonRespawnAfterEvent(dragon));
    }
}

Event_Factory(DragonRespawn, <DragonRespawnEventHook>);

} // namespace ila::mc::inline actor