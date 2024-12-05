#include "ila/event/minecraft/world/PressurePlateTriggerEvent.h"
#include <mc/world/level/block/BasePressurePlateBlock.h>

namespace ila::mc::inline world
{

BlockPos const& PressurePlateTriggerBeforeEvent::getPos() const { return mPos; }
Actor&          PressurePlateTriggerBeforeEvent::getActor() const { return mActor; }

BlockPos const& PressurePlateTriggerAfterEvent::getPos() const { return mPos; }
Actor const&    PressurePlateTriggerAfterEvent::getActor() const { return mActor; }
bool&           PressurePlateTriggerAfterEvent::getResult() const { return mResult; }

LL_TYPE_INSTANCE_HOOK(
    PressurePlateTriggerEventHook,
    HookPriority::Normal,
    BasePressurePlateBlock,
    "?shouldTriggerEntityInside@BasePressurePlateBlock@@UEBA_NAEAVBlockSource@@AEBVBlockPos@@AEAVActor@@@Z",
    bool,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    Actor&          pActor
)
{
    auto before = PressurePlateTriggerBeforeEvent(pRegion, pPos, pActor);
    eventBus.publish(before);
    if (before.isCancelled()) return false;
    auto result = origin(pRegion, pPos, pActor);
    eventBus.publish(PressurePlateTriggerAfterEvent(pRegion, pPos, pActor, result));
    return result;
}

Event_Factory(PressurePlateTrigger, <PressurePlateTriggerEventHook>);

} // namespace ila::mc::inline world