#include "ArmorStandSwapItemEvent.h"
#include <mc/world/actor/ArmorStand.h>

namespace ila::inline actor
{

Player&                     ArmorStandSwapItemBeforeEvent::getPlayer() const { return mPlayer; }
Puv::Legacy::EquipmentSlot& ArmorStandSwapItemBeforeEvent::getSlot() const { return mSlot; }

Player const&                     ArmorStandSwapItemAfterEvent::getPlayer() const { return mPlayer; }
Puv::Legacy::EquipmentSlot const& ArmorStandSwapItemAfterEvent::getSlot() const { return mSlot; }
bool&                             ArmorStandSwapItemAfterEvent::getResult() const { return mResult; }

LL_TYPE_INSTANCE_HOOK(
    ArmorStandSwapItemEventHook,
    HookPriority::Normal,
    ArmorStand,
    &ArmorStand::_trySwapItem,
    bool,
    Player&                    pPlayer,
    Puv::Legacy::EquipmentSlot pSlot
)
{
    auto beforeEvent = ArmorStandSwapItemBeforeEvent(*this, pPlayer, pSlot);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pPlayer, pSlot);
    eventBus.publish(ArmorStandSwapItemAfterEvent(*this, pPlayer, pSlot, result));
    return result;
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class ArmorStandSwapItemBeforeEventEmitter
    : public ll::event::Emitter<emitterFactory1, ArmorStandSwapItemBeforeEvent>
{
    ll::memory::HookRegistrar<ArmorStandSwapItemEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<ArmorStandSwapItemBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class ArmorStandSwapItemAfterEventEmitter
    : public ll::event::Emitter<emitterFactory2, ArmorStandSwapItemAfterEvent>
{
    ll::memory::HookRegistrar<ArmorStandSwapItemEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<ArmorStandSwapItemAfterEventEmitter>();
}

} // namespace ila::inline actor