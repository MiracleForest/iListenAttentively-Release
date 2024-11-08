#include "PistonPushEvent.h"
#include <mc/world/level/block/actor/PistonBlockActor.h>

namespace ila::inline world
{

BlockPos const& PistonPushBeforeEvent::getPos() const { return mPos; }
uchar&          PistonPushBeforeEvent::getBranchFacing() const { return mBranchFacing; }
uchar&          PistonPushBeforeEvent::getPistonMoveFacing() const { return mPistonMoveFacing; }

BlockPos const& PistonPushAfterEvent::getPos() const { return mPos; }
uchar const&    PistonPushAfterEvent::getBranchFacing() const { return mBranchFacing; }
uchar const&    PistonPushAfterEvent::getPistonMoveFacing() const { return mPistonMoveFacing; }
bool&           PistonPushAfterEvent::getResult() const { return mResult; }

LL_TYPE_INSTANCE_HOOK(
    PistonPushEventHook,
    HookPriority::Normal,
    PistonBlockActor,
    &PistonBlockActor::_attachedBlockWalker,
    bool,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    uchar           pBranchFacing,
    uchar           pPistonMoveFacing
)
{
    auto beforeEvent = PistonPushBeforeEvent(pRegion, pPos, pBranchFacing, pPistonMoveFacing);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pRegion, pPos, pBranchFacing, pPistonMoveFacing);
    eventBus.publish(PistonPushAfterEvent(pRegion, pPos, pBranchFacing, pPistonMoveFacing, result));
    return result;
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class PistonPushBeforeEventEmitter : public ll::event::Emitter<emitterFactory1, PistonPushBeforeEvent>
{
    ll::memory::HookRegistrar<PistonPushEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<PistonPushBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class PistonPushAfterEventEmitter : public ll::event::Emitter<emitterFactory2, PistonPushAfterEvent>
{
    ll::memory::HookRegistrar<PistonPushEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<PistonPushAfterEventEmitter>();
}
} // namespace ila::inline world