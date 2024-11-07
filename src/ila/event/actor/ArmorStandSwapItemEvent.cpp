#include "ArmorStandSwapItemEvent.h"
#include <mc/world/actor/ArmorStand.h>

namespace ila::inline actor
{
LL_TYPE_INSTANCE_HOOK(
    ArmorStandSwapItemEventHook,
    HookPriority::Normal,
    ArmorStand,
    &ArmorStand::_trySwapItem,
    bool,
    Player&                    player,
    Puv::Legacy::EquipmentSlot slot
)
{
    auto beforeEvent = ArmorStandSwapItemBeforeEvent(*this, player, slot);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(player, slot);
    eventBus.publish(ArmorStandSwapItemAfterEvent(*this, player, slot, result));
    return result;
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class ArmorStandSwapItemBeforeEventEmitter : public ll::event::Emitter<emitterFactory1, ArmorStandSwapItemBeforeEvent>
{
    ll::memory::HookRegistrar<ArmorStandSwapItemEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<ArmorStandSwapItemBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class ArmorStandSwapItemAfterEventEmitter : public ll::event::Emitter<emitterFactory2, ArmorStandSwapItemAfterEvent>
{
    ll::memory::HookRegistrar<ArmorStandSwapItemEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<ArmorStandSwapItemAfterEventEmitter>();
}

} // namespace ila::inline actor