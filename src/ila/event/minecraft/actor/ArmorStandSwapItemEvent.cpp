#include "ila/event/minecraft/actor/ArmorStandSwapItemEvent.h"
#include <mc/world/actor/ArmorStand.h>

namespace ila::mc::inline actor
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

Event_Factory(ArmorStandSwapItem, <ArmorStandSwapItemEventHook>);
} // namespace ila::mc::inline actor