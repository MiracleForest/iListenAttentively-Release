#include "ItemFrameBlockEvent.h"
#include <mc/world/item/ItemInstance.h>
#include <mc/world/level/block/ItemFrameBlock.h>
#include <mc/world/level/block/actor/ItemFrameBlockActor.h>

namespace ila::inline world
{

BlockPos const&                ItemFrameBlockBeforeEvent::getPos() const { return mPos; }
Player&                        ItemFrameBlockBeforeEvent::getPlayer() const { return mPlayer; }
ItemFrameBlockEventType const& ItemFrameBlockBeforeEvent::getType() const { return mType; }

BlockPos const&                ItemFrameBlockAfterEvent::getPos() const { return mPos; }
Player const&                  ItemFrameBlockAfterEvent::getPlayer() const { return mPlayer; }
ItemFrameBlockEventType const& ItemFrameBlockAfterEvent::getType() const { return mType; }
bool&                          ItemFrameBlockAfterEvent::getResult() const { return mResult; }

LL_TYPE_INSTANCE_HOOK(
    ItemFrameBlockEventHook1,
    HookPriority::Normal,
    ItemFrameBlock,
    "?use@ItemFrameBlock@@UEBA_NAEAVPlayer@@AEBVBlockPos@@E@Z",
    bool,
    Player&         pPlayer,
    BlockPos const& pPos,
    uchar           pFace
)
{
    // clang-format off
    auto blockActor = (ItemFrameBlockActor*)pPlayer.getDimensionBlockSource().getBlockEntity(pPos);
    if (!blockActor) return origin(pPlayer, pPos, pFace);
    auto type        = blockActor->getFramedItem().isNull() ? ItemFrameBlockEventType::Place : ItemFrameBlockEventType::Rotate;
    auto beforeEvent = ItemFrameBlockBeforeEvent(pPlayer.getDimensionBlockSource(), pPos, pPlayer, type);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pPlayer, pPos, pFace);
    eventBus.publish(ItemFrameBlockAfterEvent(pPlayer.getDimensionBlockSource(), pPos, pPlayer, type, result));
    return result;
    // clang-format on
}

LL_TYPE_INSTANCE_HOOK(
    ItemFrameBlockEventHook2,
    HookPriority::Normal,
    ItemFrameBlock,
    "?attack@ItemFrameBlock@@UEBA_NPEAVPlayer@@AEBVBlockPos@@@Z",
    bool,
    Player*         pPlayer,
    BlockPos const& pPos
)
{
    if (pPlayer == nullptr) return origin(pPlayer, pPos);
    auto beforeEvent = ItemFrameBlockBeforeEvent(
        pPlayer->getDimensionBlockSource(),
        pPos,
        *pPlayer,
        ItemFrameBlockEventType::Take
    );
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pPlayer, pPos);
    eventBus.publish(ItemFrameBlockAfterEvent(
        pPlayer->getDimensionBlockSource(),
        pPos,
        *pPlayer,
        ItemFrameBlockEventType::Take,
        result
    ));
    return result;
}

LL_TYPE_INSTANCE_HOOK(
    ItemFrameBlockEventHook3,
    HookPriority::Normal,
    ItemFrameBlockActor,
    &ItemFrameBlockActor::dropFramedItem,
    void,
    BlockSource& pRegion,
    bool         pIsSurvival,
    Actor*       pActor
)
{
    if (pActor == nullptr || !pActor->isPlayer()) return origin(pRegion, pIsSurvival, pActor);
    auto beforeEvent = ItemFrameBlockBeforeEvent(
        pRegion,
        this->getPosition(),
        *(Player*)pActor,
        ItemFrameBlockEventType::Take
    );
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pRegion, pIsSurvival, pActor);
    bool result = true;
    eventBus.publish(ItemFrameBlockAfterEvent(
        pRegion,
        this->getPosition(),
        *(Player*)pActor,
        ItemFrameBlockEventType::Take,
        result
    ));
}

Event_Factory(ItemFrameBlock, <ItemFrameBlockEventHook1, , ItemFrameBlockEventHook2, ItemFrameBlockEventHook3>);

} // namespace ila::inline world