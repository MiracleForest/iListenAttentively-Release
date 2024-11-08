#include "FarmDecayEvent.h"
#include <mc/world/level/block/FarmBlock.h>

namespace ila::inline world
{

BlockPos const& FarmDecayBeforeEvent::getPos() const { return mPos; }
Actor*&         FarmDecayBeforeEvent::getActor() const { return mActor; }
float&          FarmDecayBeforeEvent::getFallDistance() const { return mFallDistance; }

BlockPos const& FarmDecayAfterEvent::getPos() const { return mPos; }
Actor* const&   FarmDecayAfterEvent::getActor() const { return mActor; }
float const&    FarmDecayAfterEvent::getFallDistance() const { return mFallDistance; }

LL_TYPE_INSTANCE_HOOK(
    FarmDecayEventHook,
    HookPriority::Normal,
    FarmBlock,
    "?transformOnFall@FarmBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@PEAVActor@@M@Z",
    void,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    Actor*          pActor,
    float           pFallDistance
)
{
    auto beforeEvent = FarmDecayBeforeEvent(pRegion, pPos, pActor, pFallDistance);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pRegion, pPos, pActor, pFallDistance);
    eventBus.publish(FarmDecayAfterEvent(pRegion, pPos, pActor, pFallDistance));
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class FarmDecayBeforeEventEmitter : public ll::event::Emitter<emitterFactory1, FarmDecayBeforeEvent>
{
    ll::memory::HookRegistrar<FarmDecayEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<FarmDecayBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class FarmDecayAfterEventEmitter : public ll::event::Emitter<emitterFactory2, FarmDecayAfterEvent>
{
    ll::memory::HookRegistrar<FarmDecayEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<FarmDecayAfterEventEmitter>();
}
} // namespace ila::inline world