#include "ExplosionEvent.h"

namespace ila::inline world
{

Explosion&     ExplosionBeforeEvent::getExplosion() const { return mExplosion; }
Vec3&          ExplosionBeforeEvent::getPos() const { return *(Vec3*)&getExplosion(); }
float&         ExplosionBeforeEvent::getRadius() const { return *((float*)&getExplosion() + 3); }
ActorUniqueID& ExplosionBeforeEvent::getSource() const { return *((ActorUniqueID*)&getExplosion() + 12); }
ExplosionBeforeEvent::CustomKnockbackCalculationFunc& ExplosionBeforeEvent::getCustomKnockbackCalculation(
) const
{
    return *((CustomKnockbackCalculationFunc*)&getExplosion() + 17);
}
float& ExplosionBeforeEvent::getMaxResistance() const { return *((float*)&getExplosion() + 28); }
float& ExplosionBeforeEvent::getKnockbackScaling() const { return *((float*)&getExplosion() + 32); }
bool&  ExplosionBeforeEvent::getOverrideInWater() const { return *((bool*)&getExplosion() + 58); }
bool&  ExplosionBeforeEvent::getFire() const { return *((bool*)&getExplosion() + 80); }
bool&  ExplosionBeforeEvent::getBreaking() const { return *((bool*)&getExplosion() + 81); }
bool&  ExplosionBeforeEvent::getAllowUnderwater() const { return *((bool*)&getExplosion() + 82); }
bool&  ExplosionBeforeEvent::getCanToggleBlocks() const { return *((bool*)&getExplosion() + 83); }
bool&  ExplosionBeforeEvent::getShouldTakeDamage() const { return *((bool*)&getExplosion() + 84); }
bool&  ExplosionBeforeEvent::getIgnoreBlockResistance() const { return *((bool*)&getExplosion() + 85); }

Explosion const&     ExplosionAfterEvent::getExplosion() const { return mExplosion; }
bool&                ExplosionAfterEvent::getResult() { return mResult; }
Vec3 const&          ExplosionAfterEvent::getPos() const { return *(Vec3*)&getExplosion(); }
float const&         ExplosionAfterEvent::getRadius() const { return *((float*)&getExplosion() + 3); }
ActorUniqueID const& ExplosionAfterEvent::getSource() const
{
    return *((ActorUniqueID*)&getExplosion() + 12);
}
ExplosionBeforeEvent::CustomKnockbackCalculationFunc const& ExplosionAfterEvent::
    getCustomKnockbackCalculation() const
{
    return *((CustomKnockbackCalculationFunc*)&getExplosion() + 17);
}
float const& ExplosionAfterEvent::getMaxResistance() const { return *((float*)&getExplosion() + 28); }
float const& ExplosionAfterEvent::getKnockbackScaling() const { return *((float*)&getExplosion() + 32); }
bool const&  ExplosionAfterEvent::getOverrideInWater() const { return *((bool*)&getExplosion() + 58); }
bool const&  ExplosionAfterEvent::getFire() const { return *((bool*)&getExplosion() + 80); }
bool const&  ExplosionAfterEvent::getBreaking() const { return *((bool*)&getExplosion() + 81); }
bool const&  ExplosionAfterEvent::getAllowUnderwater() const { return *((bool*)&getExplosion() + 82); }
bool const&  ExplosionAfterEvent::getCanToggleBlocks() const { return *((bool*)&getExplosion() + 83); }
bool const&  ExplosionAfterEvent::getShouldTakeDamage() const { return *((bool*)&getExplosion() + 84); }
bool const&  ExplosionAfterEvent::getIgnoreBlockResistance() const { return *((bool*)&getExplosion() + 85); }

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