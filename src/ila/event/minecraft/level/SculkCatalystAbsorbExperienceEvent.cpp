#include "ila/event/minecraft/level/SculkCatalystAbsorbExperienceEvent.h"

namespace ila::mc::inline level
{

SculkCatalystBlockActor& SculkCatalystAbsorbExperienceBeforeEvent::getBlockActor() const
{
    return mBlockActor;
};
Actor& SculkCatalystAbsorbExperienceBeforeEvent::getActor() const { return mActor; };

SculkCatalystBlockActor const& SculkCatalystAbsorbExperienceAfterEvent::getBlockActor() const
{
    return mBlockActor;
};
Actor const& SculkCatalystAbsorbExperienceAfterEvent::getActor() const { return mActor; };

LL_TYPE_INSTANCE_HOOK(
    SculkCatalystAbsorbExperienceEventHook,
    HookPriority::Normal,
    SculkCatalystBlockActor,
    "?_tryConsumeOnDeathExperience@SculkCatalystBlockActor@@AEAAXAEAVLevel@@AEAVActor@@@Z",
    void,
    Level& pLevel,
    Actor& pActor
)
{
    auto beforeEvent = SculkCatalystAbsorbExperienceBeforeEvent(pLevel, *this, pActor);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pLevel, pActor);
    eventBus.publish(SculkCatalystAbsorbExperienceAfterEvent(pLevel, *this, pActor));
}

Event_Factory(SculkCatalystAbsorbExperience, <SculkCatalystAbsorbExperienceEventHook>);

} // namespace ila::mc::inline level