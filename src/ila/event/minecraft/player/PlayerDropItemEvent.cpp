#include "ila/event/minecraft/player/PlayerDropItemEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/inventory/transaction/ComplexInventoryTransaction.h>
#include <mc/world/inventory/transaction/InventoryAction.h>
#include <mc/world/inventory/transaction/InventorySourceType.h>
#include <mc/world/inventory/transaction/InventoryTransaction.h>

class InventorySource
{
public:
    enum class InventorySourceFlags : uint
    {
        NoFlag                 = 0,
        WorldInteractionRandom = 1,
    };

public:
    InventorySourceType                   mType;
    ContainerID                           mContainerId;
    InventorySource::InventorySourceFlags mFlags;

public:
    constexpr explicit InventorySource(
        InventorySourceType  pType,
        ContainerID          pContainerId,
        InventorySourceFlags pFlags = InventorySourceFlags::NoFlag
    )
        : mType(pType)
        , mContainerId(pContainerId)
        , mFlags(pFlags)
    {
    }
};

namespace ila::mc::inline player
{

void PlayerDropItemBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["item"] = reinterpret_cast<uintptr_t>(&getItem());
}
ItemStack const& PlayerDropItemBeforeEvent::getItem() const { return mItem; }

void PlayerDropItemAfterEvent::serialize(CompoundTag& nbt) const
{
    PlayerEvent::serialize(nbt);
    nbt["item"] = reinterpret_cast<uintptr_t>(&getItem());
}
ItemStack const& PlayerDropItemAfterEvent::getItem() const { return mItem; }

LL_TYPE_INSTANCE_HOOK(
    PlayerDropItemEventHook1,
    HookPriority::Normal,
    Player,
    &Player::$drop,
    bool,
    ItemStack const& pItem,
    bool             pRandomly
)
{
    auto beforeEvent = PlayerDropItemBeforeEvent(*this, const_cast<ItemStack&>(pItem));
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pItem, pRandomly);
    if (result) { LLEventBus.publish(PlayerDropItemAfterEvent(*this, pItem)); }
    return result;
}

LL_TYPE_INSTANCE_HOOK(
    PlayerDropItemEventHook2,
    HookPriority::Normal,
    ComplexInventoryTransaction,
    &ComplexInventoryTransaction::$handle,
    InventoryTransactionError,
    Player& pPlayer,
    bool    pIsSenderAuthority
)
{
    if (mType != ComplexInventoryTransaction::Type::NormalTransaction)
    {
        return origin(pPlayer, pIsSenderAuthority);
    }
    InventorySource source { InventorySourceType::ContainerInventory, ContainerID::Inventory };
    auto&           actions = mTransaction->getActions(source);
    if (actions.size() != 1) { return origin(pPlayer, pIsSenderAuthority); }
    auto& item        = pPlayer.getInventory().getItem(actions[0].mSlot);
    auto  beforeEvent = PlayerDropItemBeforeEvent(pPlayer, const_cast<ItemStack&>(item));
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return InventoryTransactionError::AuthorityMismatch; }
    auto result = origin(pPlayer, pIsSenderAuthority);
    if (result == InventoryTransactionError::NoError)
    {
        LLEventBus.publish(PlayerDropItemAfterEvent(pPlayer, item));
    }
    return result;
}

Event_Hook_Factory(PlayerDropItem, <PlayerDropItemEventHook1, PlayerDropItemEventHook2>);

} // namespace ila::mc::inline player