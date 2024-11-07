#include "LiquidTryFlowEvent.h"
#include <mc/world/level/block/LiquidBlockDynamic.h>

namespace ila::inline world
{

LL_TYPE_INSTANCE_HOOK(
    LiquidTryFlowEventHook,
    HookPriority::Normal,
    LiquidBlockDynamic,
    &LiquidBlockDynamic::_canSpreadTo,
    bool,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    BlockPos const& pFlowFromPos,
    uchar           pFlowFromDirection
)
{
    auto beforeEvent = LiquidTryFlowBeforeEvent(pRegion, pPos, pFlowFromPos, pFlowFromDirection);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pRegion, pPos, pFlowFromPos, pFlowFromDirection);
    eventBus.publish(LiquidTryFlowAfterEvent(pRegion, pPos, pFlowFromPos, pFlowFromDirection, result));
    return result;
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class LiquidTryFlowBeforeEventEmitter : public ll::event::Emitter<emitterFactory1, LiquidTryFlowBeforeEvent>
{
    ll::memory::HookRegistrar<LiquidTryFlowEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<LiquidTryFlowBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class LiquidTryFlowAfterEventEmitter : public ll::event::Emitter<emitterFactory2, LiquidTryFlowAfterEvent>
{
    ll::memory::HookRegistrar<LiquidTryFlowEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<LiquidTryFlowAfterEventEmitter>();
}
} // namespace ila::inline world