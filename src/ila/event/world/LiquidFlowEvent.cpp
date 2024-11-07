#include "LiquidFlowEvent.h"
#include <mc/world/level/block/LiquidBlockDynamic.h>

namespace ila::inline world
{

LL_TYPE_INSTANCE_HOOK(
    LiquidFlowEventHook,
    HookPriority::Normal,
    LiquidBlockDynamic,
    &LiquidBlockDynamic::_trySpreadTo,
    void,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    int             pNeighbor,
    BlockPos const& pFlowFromPos,
    uchar           pFlowFromDirection
)
{
    auto beforeEvent = LiquidFlowBeforeEvent(pRegion, pPos, pNeighbor, pFlowFromPos, pFlowFromDirection);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pRegion, pPos, pNeighbor, pFlowFromPos, pFlowFromDirection);
    eventBus.publish(LiquidFlowAfterEvent(pRegion, pPos, pNeighbor, pFlowFromPos, pFlowFromDirection));
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class LiquidFlowBeforeEventEmitter : public ll::event::Emitter<emitterFactory1, LiquidFlowBeforeEvent>
{
    ll::memory::HookRegistrar<LiquidFlowEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<LiquidFlowBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class LiquidFlowAfterEventEmitter : public ll::event::Emitter<emitterFactory2, LiquidFlowAfterEvent>
{
    ll::memory::HookRegistrar<LiquidFlowEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<LiquidFlowAfterEventEmitter>();
}
} // namespace ila::inline world