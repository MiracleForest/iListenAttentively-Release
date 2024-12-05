#include "ila/event/minecraft/actor/ProjectileCreateEvent.h"
#include <mc/entity/components/ProjectileComponent.h>

namespace ila::mc::inline actor
{

LL_TYPE_INSTANCE_HOOK(
    ProjectileCreateEventHook,
    HookPriority::Normal,
    ProjectileComponent,
    "?shoot@ProjectileComponent@@QEAAXAEAVActor@@AEBVVec3@@MM1PEAV2@@Z",
    void,
    class Actor&      pProjectile,
    class Vec3 const& pDirection,
    float             pPower,
    float             pOffset,
    class Vec3 const& pBaseSpeed,
    class Actor*      pTarget
)
{
    auto beforeEvent = ProjectileCreateBeforeEvent(pProjectile);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return pProjectile.remove();
    origin(pProjectile, pDirection, pPower, pOffset, pBaseSpeed, pTarget);
    eventBus.publish(ProjectileCreateAfterEvent(pProjectile));
}

Event_Factory(ProjectileCreate, <ProjectileCreateEventHook>);

} // namespace ila::mc::inline actor