#include "PlayerRequestItemActionEvent.h"
#include <mc/world/inventory/network/ItemStackRequestActionHandler.h>

namespace ila::mc::inline player
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
    ItemStackRequestAction& pRequestAction
)
{
    auto beforeEvent = PlayerRequestItemActionBeforeEvent(
        this->mPlayer,
        (ItemStackRequestActionTransferBase&)pRequestAction
    );
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return ItemStackNetResult::Error;
    auto result = origin(pRequestAction);
    eventBus.publish(PlayerRequestItemActionAfterEvent(
        this->mPlayer,
        (ItemStackRequestActionTransferBase&)pRequestAction,
        result
    ));
    return result;
}

Event_Factory(PlayerRequestItemAction, <PlayerRequestItemActionEventHook>);

} // namespace ila::mc::inline player