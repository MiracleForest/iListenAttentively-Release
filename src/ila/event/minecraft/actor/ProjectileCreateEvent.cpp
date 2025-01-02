#include "ila/event/minecraft/actor/ProjectileCreateEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/entity/components_json_legacy/ProjectileComponent.h>

namespace ila::mc::inline actor
{

LL_TYPE_INSTANCE_HOOK(
    ProjectileCreateEventHook,
    HookPriority::Normal,
    ProjectileComponent,
    &ProjectileComponent::shoot,
    void,
    Actor&      pProjectile,
    Vec3 const& pDirection,
    float       pPower,
    float       pOffset,
    Vec3 const& pBaseSpeed,
    Actor*      pTarget
)
{
    origin(pProjectile, pDirection, pPower, pOffset, pBaseSpeed, pTarget);
    if (pProjectile.isRemoved()) { return; }
    auto beforeEvent = ProjectileCreateBeforeEvent(pProjectile);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { pProjectile.remove(); }
    if (!pProjectile.isRemoved()) { LLEventBus.publish(ProjectileCreateAfterEvent(pProjectile)); }
}

Event_Hook_Factory(ProjectileCreate, <ProjectileCreateEventHook>);

} // namespace ila::mc::inline actor