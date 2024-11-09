#include "PlayerDropItemEvent.h"
#include <mc/world/inventory/transaction/ComplexInventoryTransaction.h>

namespace ila::inline player
{

ItemStack const& PlayerDropItemBeforeEvent::getItem() const { return mItem; }

ItemStack const& PlayerDropItemAfterEvent::getItem() const { return mItem; }
bool             PlayerDropItemAfterEvent::getResult() const { return mResult; }

LL_TYPE_INSTANCE_HOOK(
    PlayerDropItemEventHook1,
    HookPriority::Normal,
    Player,
    "?drop@Player@@UEAA_NAEBVItemStack@@_N@Z",
    bool,
    ItemStack const& pItem,
    bool             pRandomly
)
{
    auto beforeEvent = PlayerDropItemBeforeEvent(*this, pItem);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pItem, pRandomly);
    eventBus.publish(PlayerDropItemAfterEvent(*this, pItem, result));
    return result;
}

LL_TYPE_INSTANCE_HOOK(
    PlayerDropItemEventHook2,
    HookPriority::Normal,
    ComplexInventoryTransaction,
    "?handle@ComplexInventoryTransaction@@UEBA?AW4InventoryTransactionError@@AEAVPlayer@@_N@Z",
    InventoryTransactionError,
    Player& pPlayer,
    bool    pIsSenderAuthority
)
{
    if (type == ComplexInventoryTransaction::Type::NormalTransaction)
    {
        InventorySource source(InventorySourceType::ContainerInventory, ContainerID::Inventory);
        auto&           actions = data.getActions(source);
        if (actions.size() == 1)
        {
            auto& item        = pPlayer.getInventory().getItem(actions[0].mSlot);
            auto  beforeEvent = PlayerDropItemBeforeEvent(pPlayer, item);
            eventBus.publish(beforeEvent);
            if (beforeEvent.isCancelled()) return InventoryTransactionError::AuthorityMismatch;
            auto result = origin(pPlayer, pIsSenderAuthority);
            eventBus.publish(
                PlayerDropItemAfterEvent(pPlayer, item, result == InventoryTransactionError::NoError)
            );
            return result;
        }
    }
    return origin(pPlayer, pIsSenderAuthority);
}

Event_Factory(PlayerDropItem, <PlayerDropItemEventHook1, PlayerDropItemEventHook2>);

} // namespace ila::inline player