#include "ila/event/minecraft/actor/ArmorStandSwapItemEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/actor/ArmorStand.h>

namespace ila::mc::inline actor
{

void ArmorStandSwapItemBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["player"] = reinterpret_cast<uintptr_t>(&getPlayer());
    nbt["slot"]   = magic_enum::enum_name(getSlot());
}
void ArmorStandSwapItemBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getSlot() = magic_enum::enum_cast<SharedTypes::Legacy::EquipmentSlot>(nbt["slot"].get<StringTag>())
                    .value_or(getSlot());
}
Player&                             ArmorStandSwapItemBeforeEvent::getPlayer() const { return mPlayer; }
SharedTypes::Legacy::EquipmentSlot& ArmorStandSwapItemBeforeEvent::getSlot() const { return mSlot; }

void ArmorStandSwapItemAfterEvent::serialize(CompoundTag& nbt) const
{
    ActorEvent::serialize(nbt);
    nbt["player"] = reinterpret_cast<uintptr_t>(&getPlayer());
    nbt["slot"]   = magic_enum::enum_name(getSlot());
}
Player const&                             ArmorStandSwapItemAfterEvent::getPlayer() const { return mPlayer; }
SharedTypes::Legacy::EquipmentSlot const& ArmorStandSwapItemAfterEvent::getSlot() const { return mSlot; }

LL_TYPE_INSTANCE_HOOK(
    ArmorStandSwapItemEventHook,
    HookPriority::Normal,
    ArmorStand,
    &ArmorStand::_trySwapItem,
    bool,
    Player&                            pPlayer,
    SharedTypes::Legacy::EquipmentSlot pSlot
)
{
    auto beforeEvent = ArmorStandSwapItemBeforeEvent(*this, pPlayer, pSlot);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return false; }
    auto result = origin(pPlayer, pSlot);
    if (result) { LLEventBus.publish(ArmorStandSwapItemAfterEvent(*this, pPlayer, pSlot)); }
    return result;
}

Event_Hook_Factory(ArmorStandSwapItem, <ArmorStandSwapItemEventHook>);
} // namespace ila::mc::inline actor