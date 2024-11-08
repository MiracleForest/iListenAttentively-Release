#include "ProjectileCreateEvent.h"
#include <mc/entity/components/ProjectileComponent.h>

namespace ila::inline actor
{

LL_TYPE_INSTANCE_HOOK(
    ProjectileCreateEventHook,
    HookPriority::Normal,
    ProjectileComponent,
    "?shoot@ProjectileComponent@@QEAAXAEAVActor@@AEBVVec3@@MM1PEAV2@@Z",
    void,
    class Actor&      projectile,
    class Vec3 const& direction,
    float             power,
    float             offset,
    class Vec3 const& baseSpeed,
    class Actor*      target
)
{
    auto beforeEvent = ProjectileCreateBeforeEvent(projectile);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return projectile.remove();
    origin(projectile, direction, power, offset, baseSpeed, target);
    eventBus.publish(ProjectileCreateAfterEvent(projectile));
}

Event_Factory(ProjectileCreate, <ProjectileCreateEventHook>);

} // namespace ila::inline actor