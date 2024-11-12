#include "PlayerRequestItemActionEvent.h"
#include <mc/world/inventory/network/ItemStackRequestActionHandler.h>

namespace ila::inline player
{

ItemStackRequestActionTransferBase& PlayerRequestItemActionBeforeEvent::getRequestAction() const
{
    return mRequestAction;
}

ItemStackRequestActionTransferBase const& PlayerRequestItemActionAfterEvent::getRequestAction() const
{
    return mRequestAction;
}
ItemStackNetResult& PlayerRequestItemActionAfterEvent::getResult() const { return mResult; }

LL_TYPE_INSTANCE_HOOK(
    PlayerRequestItemActionEventHook,
    HookPriority::Normal,
    ItemStackRequestActionHandler,
    "?handleRequestAction@ItemStackRequestActionHandler@@QEAA?AW4ItemStackNetResult@@"
    "AEBVItemStackRequestAction@@@Z",
    ItemStackNetResult,
    ItemStackRequestAction& requestAction
)
{
    auto beforeEvent =
        PlayerRequestItemActionBeforeEvent(this->mPlayer, (ItemStackRequestActionTransferBase&)requestAction);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return ItemStackNetResult::Error;
    auto result = origin(requestAction);
    eventBus.publish(PlayerRequestItemActionAfterEvent(
        this->mPlayer,
        (ItemStackRequestActionTransferBase&)requestAction,
        result
    ));
    return result;
}

Event_Factory(PlayerRequestItemAction, <PlayerRequestItemActionEventHook>);

} // namespace ila::inline player