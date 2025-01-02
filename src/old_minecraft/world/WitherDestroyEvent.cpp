#include "ila/event/minecraft/world/WitherDestroyEvent.h"
#include <mc/world/actor/boss/WitherBoss.h>

namespace ila::mc::inline world
{

Level&      WitherDestroyBeforeEvent::level() const { return mLevel; }
AABB const& WitherDestroyBeforeEvent::getBox() const { return mBox; };
int&        WitherDestroyBeforeEvent::getRadius() const { return mRadius; };

Level&      WitherDestroyAfterEvent::level() const { return mLevel; }
AABB const& WitherDestroyAfterEvent::getBox() const { return mBox; };
int const&  WitherDestroyAfterEvent::getRadius() const { return mRadius; };

LL_TYPE_INSTANCE_HOOK(
    WitherDestroyEventHook,
    HookPriority::Normal,
    WitherBoss,
    &WitherBoss::_destroyBlocks,
    void,
    Level&                       pLevel,
    AABB const&                  pBox,
    BlockSource&                 pRegion,
    int                          pRange,
    WitherBoss::WitherAttackType pType
)
{
    auto beforeEvent = WitherDestroyBeforeEvent(pRegion, pLevel, pBox, pRange);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pLevel, pBox, pRegion, pRange, pType);
    eventBus.publish(WitherDestroyAfterEvent(pRegion, pLevel, pBox, pRange));
}

Event_Factory(WitherDestroy, <WitherDestroyEventHook>);

} // namespace ila::mc::inline world