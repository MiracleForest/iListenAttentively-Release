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

Event_Factory(Explosion, <ExplosionEventHook>);

} // namespace ila::inline world