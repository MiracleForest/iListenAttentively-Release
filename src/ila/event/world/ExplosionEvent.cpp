#include "ExplosionEvent.h"

namespace ila::inline world
{

Explosion& ExplosionBeforeEvent::getExplosion() const { return mExplosion; }

Explosion const& ExplosionAfterEvent::getExplosion() const { return mExplosion; }
bool&            ExplosionAfterEvent::getResult() { return mResult; }

LL_TYPE_INSTANCE_HOOK(ExplosionEventHook, HookPriority::Normal, ::Explosion, &Explosion::explode, bool)
{
    auto& explosion   = *(Explosion*)this;
    auto  beforeEvent = ExplosionBeforeEvent(explosion.mRegion, explosion);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin();
    eventBus.publish(ExplosionAfterEvent(explosion.mRegion, explosion, result));
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