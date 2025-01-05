#include "ila/event/minecraft/world/WitherDestroyEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/actor/boss/WitherBoss.h>

namespace ila::mc::inline world
{

void WitherDestroyBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["level"]  = serializeRefObj(level());
    nbt["box"]    = { { "min", ListTag { getBox().min.x, getBox().min.y, getBox().min.z } },
                      { "max", ListTag { getBox().max.x, getBox().max.y, getBox().max.z } } };
    nbt["radius"] = getRadius();
}
void WitherDestroyBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getBox().min.x = nbt["box"]["min"][0];
    getBox().min.y = nbt["box"]["min"][1];
    getBox().min.z = nbt["box"]["min"][2];
    getBox().max.x = nbt["box"]["max"][0];
    getBox().max.y = nbt["box"]["max"][1];
    getBox().max.z = nbt["box"]["max"][2];
    getRadius()    = nbt["radius"];
}
Level& WitherDestroyBeforeEvent::level() const { return mLevel; }
AABB&  WitherDestroyBeforeEvent::getBox() const { return mBox; };
int&   WitherDestroyBeforeEvent::getRadius() const { return mRadius; };

void WitherDestroyAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["level"]  = serializeRefObj(level());
    nbt["box"]    = { { "min", ListTag { getBox().min.x, getBox().min.y, getBox().min.z } },
                      { "max", ListTag { getBox().max.x, getBox().max.y, getBox().max.z } } };
    nbt["radius"] = getRadius();
}
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
    auto beforeEvent = WitherDestroyBeforeEvent(pRegion, pLevel, const_cast<AABB&>(pBox), pRange);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }
    origin(pLevel, pBox, pRegion, pRange, pType);
    LLEventBus.publish(WitherDestroyAfterEvent(pRegion, pLevel, pBox, pRange));
}

Event_Hook_Factory(WitherDestroy, <WitherDestroyEventHook>);

} // namespace ila::mc::inline world