#include "ExplosionEvent.h"

namespace ila::inline world
{

LL_TYPE_INSTANCE_HOOK(ExplosionEventHook, HookPriority::Normal, Explosion, &Explosion::explode, bool)
{
    auto beforeEvent = ExplosionBeforeEvent(*((BlockSource*)this + 13), *this);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin();
    eventBus.publish(ExplosionAfterEvent(*((BlockSource*)this + 13), *this, result));
    return result;
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class ExplosionBeforeEventEmitter : public ll::event::Emitter<emitterFactory1, ExplosionBeforeEvent>
{
    ll::memory::HookRegistrar<ExplosionEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<ExplosionBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class ExplosionAfterEventEmitter : public ll::event::Emitter<emitterFactory2, ExplosionAfterEvent>
{
    ll::memory::HookRegistrar<ExplosionEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<ExplosionAfterEventEmitter>();
}
} // namespace ila::inline world