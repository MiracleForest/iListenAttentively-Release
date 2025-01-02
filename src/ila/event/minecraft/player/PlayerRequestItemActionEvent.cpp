#include "ila/event/minecraft/player/PlayerRequestItemActionEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/containers/FullContainerName.h>
#include <mc/world/inventory/network/ItemStackRequestActionHandler.h>
#include <mc/world/inventory/network/ItemStackRequestSlotInfo.h>

namespace ila::mc::inline player
{

void PlayerRequestItemActionBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["isDstSerialized"]    = getRequestAction().mIsDstSerialized;
    nbt["isAmountSerialized"] = getRequestAction().mIsAmountSerialized;
    nbt["amount"]             = getRequestAction().mAmount;
    // clang-format off
    nbt["src"] = {
        {"fullContainerName", getRequestAction().mSrc->mFullContainerName.toString()},
        {"slot", getRequestAction().mSrc->mSlot}
    };
    if (getRequestAction().mSrc->mNetIdVariant.hasServerNetId()) {
        nbt["src"]["serverNetId"] = getRequestAction().mSrc->mNetIdVariant.tryGetServerNetId()->mRawId;
    }
    nbt["dst"] = {
        {"fullContainerName", getRequestAction().mDst->mFullContainerName.toString()},
        {"slot", getRequestAction().mDst->mSlot}
    };
    if (getRequestAction().mDst->mNetIdVariant.hasServerNetId()) {
        nbt["dst"]["serverNetId"] = getRequestAction().mDst->mNetIdVariant.tryGetServerNetId()->mRawId;
    }
    // clang-format on
}
void PlayerRequestItemActionBeforeEvent::deserialize(CompoundTag const& nbt)
{
    PlayerEvent::deserialize(nbt);
    getRequestAction().mIsDstSerialized    = nbt["isDstSerialized"];
    getRequestAction().mIsAmountSerialized = nbt["isAmountSerialized"];
    getRequestAction().mAmount             = nbt["amount"];
    // getRequestAction().mSrc->mFullContainerName = ;
    getRequestAction().mSrc->mSlot = nbt["src"]["slot"];
    if (nbt["src"].contains("serverNetId"))
    {
        getRequestAction().mSrc->mNetIdVariant = ItemStackNetId(nbt["src"]["serverNetId"]);
    }
    // getRequestAction().mDst->mFullContainerName = ;
    getRequestAction().mDst->mSlot = nbt["dst"]["slot"];
    if (nbt["dst"].contains("serverNetId"))
    {
        getRequestAction().mDst->mNetIdVariant = ItemStackNetId(nbt["dst"]["serverNetId"]);
    }
}
ItemStackRequestActionTransferBase& PlayerRequestItemActionBeforeEvent::getRequestAction() const
{
    return mRequestAction;
}

void PlayerRequestItemActionAfterEvent::serialize(CompoundTag& nbt) const
{
    PlayerEvent::serialize(nbt);
    nbt["isDstSerialized"]    = getRequestAction().mIsDstSerialized;
    nbt["isAmountSerialized"] = getRequestAction().mIsAmountSerialized;
    nbt["amount"]             = getRequestAction().mAmount;
    nbt["result"]             = magic_enum::enum_name(getResult());
    // clang-format off
    nbt["src"] = {
        {"fullContainerName", getRequestAction().mSrc->mFullContainerName.toString()},
        {"slot", getRequestAction().mSrc->mSlot}
    };
    if (getRequestAction().mSrc->mNetIdVariant.hasServerNetId()) {
        nbt["src"]["serverNetId"] = getRequestAction().mSrc->mNetIdVariant.tryGetServerNetId()->mRawId;
    }
    nbt["dst"] = {
        {"fullContainerName", getRequestAction().mDst->mFullContainerName.toString()},
        {"slot", getRequestAction().mDst->mSlot}
    };
    if (getRequestAction().mDst->mNetIdVariant.hasServerNetId()) {
        nbt["dst"]["serverNetId"] = getRequestAction().mDst->mNetIdVariant.tryGetServerNetId()->mRawId;
    }
    // clang-format on
}
void PlayerRequestItemActionAfterEvent::deserialize(CompoundTag const& nbt)
{
    PlayerEvent::deserialize(nbt);
    getResult() =
        magic_enum::enum_cast<ItemStackNetResult>(nbt["result"].get<StringTag>()).value_or(getResult());
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
    &ItemStackRequestActionHandler::handleRequestAction,
    ItemStackNetResult,
    ItemStackRequestAction const& pRequestAction
)
{
    auto beforeEvent = PlayerRequestItemActionBeforeEvent(
        mPlayer,
        static_cast<ItemStackRequestActionTransferBase&>(const_cast<ItemStackRequestAction&>(pRequestAction))
    );
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return ItemStackNetResult::Error; }
    auto result = origin(pRequestAction);
    LLEventBus.publish(PlayerRequestItemActionAfterEvent(
        mPlayer,
        static_cast<ItemStackRequestActionTransferBase const&>(pRequestAction),
        result
    ));
    return result;
}

Event_Hook_Factory(PlayerRequestItemAction, <PlayerRequestItemActionEventHook>);

} // namespace ila::mc::inline player