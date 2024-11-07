#include "FarmDecayEvent.h"
#include <mc/world/level/block/FarmBlock.h>

namespace ila::inline world
{

LL_TYPE_INSTANCE_HOOK(
    FarmDecayEventHook,
    HookPriority::Normal,
    FarmBlock,
    "?transformOnFall@FarmBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@PEAVActor@@M@Z",
    void,
    BlockSource&    region,
    BlockPos const& pos,
    Actor*          actor,
    float           fallDistance
)
{
    auto beforeEvent = FarmDecayBeforeEvent(region, pos, actor, fallDistance);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(region, pos, actor, fallDistance);
    eventBus.publish(FarmDecayAfterEvent(region, pos, actor, fallDistance));
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