#include "ila/event/minecraft/level/SculkCatalystAbsorbExperienceEvent.h"
#include "ila/base/Gloabl.h"

namespace ila::mc::inline level
{

void SculkCatalystAbsorbExperienceBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["blockActor"] = reinterpret_cast<uintptr_t>(&getBlockActor());
    nbt["actor"]      = reinterpret_cast<uintptr_t>(&getActor());
}
SculkCatalystBlockActor& SculkCatalystAbsorbExperienceBeforeEvent::getBlockActor() const
{
    return mBlockActor;
};
Actor& SculkCatalystAbsorbExperienceBeforeEvent::getActor() const { return mActor; };

void SculkCatalystAbsorbExperienceAfterEvent::serialize(CompoundTag& nbt) const
{
    LevelEvent::serialize(nbt);
    nbt["blockActor"] = reinterpret_cast<uintptr_t>(&getBlockActor());
    nbt["actor"]      = reinterpret_cast<uintptr_t>(&getActor());
}
SculkCatalystBlockActor const& SculkCatalystAbsorbExperienceAfterEvent::getBlockActor() const
{
    return mBlockActor;
};
Actor const& SculkCatalystAbsorbExperienceAfterEvent::getActor() const { return mActor; };

LL_TYPE_INSTANCE_HOOK(
    SculkCatalystAbsorbExperienceEventHook,
    HookPriority::Normal,
    SculkCatalystBlockActor,
    &SculkCatalystBlockActor::_tryConsumeOnDeathExperience,
    void,
    Level& pLevel,
    Actor& pActor
)
{
    auto beforeEvent = SculkCatalystAbsorbExperienceBeforeEvent(pLevel, *this, pActor);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }
    origin(pLevel, pActor);
    LLEventBus.publish(SculkCatalystAbsorbExperienceAfterEvent(pLevel, *this, pActor));
}

Event_Hook_Factory(SculkCatalystAbsorbExperience, <SculkCatalystAbsorbExperienceEventHook>);

} // namespace ila::mc::inline level