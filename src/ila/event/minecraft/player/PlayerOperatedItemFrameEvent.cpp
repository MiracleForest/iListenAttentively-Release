#include "ila/event/minecraft/player/PlayerOperatedItemFrameEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/item/ItemInstance.h>
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/block/BlockLegacy.h>
#include <mc/world/level/block/ItemFrameBlock.h>
#include <mc/world/level/block/actor/ItemFrameBlockActor.h>

namespace ila::mc::inline world
{

void PlayerOperatedItemFrameBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"]  = ListTag { getBlockPos().x, getBlockPos().y, getBlockPos().z };
    nbt["type"] = magic_enum::enum_name(getType());
}
BlockPos const& PlayerOperatedItemFrameBeforeEvent::getBlockPos() const { return mBlockPos; }
PlayerOperatedItemFrameEvent::Type const& PlayerOperatedItemFrameBeforeEvent::getType() const
{
    return mType;
}

void PlayerOperatedItemFrameAfterEvent::serialize(CompoundTag& nbt) const
{
    PlayerEvent::serialize(nbt);
    nbt["pos"]  = ListTag { getBlockPos().x, getBlockPos().y, getBlockPos().z };
    nbt["type"] = magic_enum::enum_name(getType());
}
BlockPos const& PlayerOperatedItemFrameAfterEvent::getBlockPos() const { return mBlockPos; }
PlayerOperatedItemFrameEvent::Type const& PlayerOperatedItemFrameAfterEvent::getType() const { return mType; }

using Type = PlayerOperatedItemFrameEvent::Type;

LL_TYPE_INSTANCE_HOOK(
    PlayerOperatedItemFrameEventHook1,
    HookPriority::Normal,
    ItemFrameBlock,
    &ItemFrameBlock::$use,
    bool,
    Player&         pPlayer,
    BlockPos const& pPos,
    uchar           pFace
)
{
    auto blockActor =
        static_cast<ItemFrameBlockActor*>(pPlayer.getDimensionBlockSource().getBlockEntity(pPos));
    if (!blockActor) { return origin(pPlayer, pPos, pFace); }
    auto type        = blockActor->getFramedItem().isNull() ? Type::Place : Type::Rotate;
    auto beforeEvent = PlayerOperatedItemFrameBeforeEvent(pPlayer, const_cast<BlockPos&>(pPos), type);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return false; }
    auto result = origin(pPlayer, pPos, pFace);
    if (result)
    {
        LLEventBus.publish(PlayerOperatedItemFrameAfterEvent(pPlayer, const_cast<BlockPos&>(pPos), type));
    }
    return result;
}

LL_TYPE_INSTANCE_HOOK(
    PlayerOperatedItemFrameEventHook2,
    HookPriority::Normal,
    ItemFrameBlock,
    &ItemFrameBlock::$attack,
    bool,
    Player*         pPlayer,
    BlockPos const& pPos
)
{
    if (pPlayer == nullptr) { return origin(pPlayer, pPos); }
    auto beforeEvent = PlayerOperatedItemFrameBeforeEvent(*pPlayer, const_cast<BlockPos&>(pPos), Type::Take);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return false; }
    auto result = origin(pPlayer, pPos);
    if (result) { LLEventBus.publish(PlayerOperatedItemFrameAfterEvent(*pPlayer, pPos, Type::Take)); }
    return result;
}

LL_TYPE_INSTANCE_HOOK(
    PlayerOperatedItemFrameEventHook3,
    HookPriority::Normal,
    ItemFrameBlockActor,
    &ItemFrameBlockActor::dropFramedItem,
    void,
    BlockSource& pRegion,
    bool         pIsSurvival,
    Actor*       pActor
)
{
    if (pActor == nullptr || !pActor->isPlayer() || !((Player*)pActor)->isCreative())
    {
        return origin(pRegion, pIsSurvival, pActor);
    }
    auto beforeEvent = PlayerOperatedItemFrameBeforeEvent(
        static_cast<Player&>(*pActor),
        const_cast<BlockPos&>(getPosition()),
        Type::Take
    );
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }
    origin(pRegion, pIsSurvival, pActor);
    LLEventBus.publish(PlayerOperatedItemFrameAfterEvent(
        static_cast<Player&>(*pActor),
        const_cast<BlockPos&>(getPosition()),
        Type::Take
    ));
}

Event_Hook_Factory(PlayerOperatedItemFrame, <PlayerOperatedItemFrameEventHook1, PlayerOperatedItemFrameEventHook2, PlayerOperatedItemFrameEventHook3>);

} // namespace ila::mc::inline world