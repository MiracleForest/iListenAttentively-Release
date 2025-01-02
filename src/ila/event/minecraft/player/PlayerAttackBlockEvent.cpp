#include "ila/event/minecraft/player/PlayerAttackBlockEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/level/block/Block.h>

namespace ila::mc::inline player
{

void PlayerAttackBlockBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"] = ListTag { getPos().x, getPos().y, getPos().z };
}
void PlayerAttackBlockBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getPos().x = nbt["pos"][0ull]->as<IntTag>();
    getPos().x = nbt["pos"][1ull]->as<IntTag>();
    getPos().x = nbt["pos"][2ull]->as<IntTag>();
}
BlockPos& PlayerAttackBlockBeforeEvent::getPos() const { return mPos; }

void PlayerAttackBlockAfterEvent::serialize(CompoundTag& nbt) const
{
    PlayerEvent::serialize(nbt);
    nbt["pos"] = ListTag { getPos().x, getPos().y, getPos().z };
}
BlockPos const& PlayerAttackBlockAfterEvent::getPos() const { return mPos; }

LL_TYPE_INSTANCE_HOOK(
    PlayerAttackBlockEventHook,
    HookPriority::Normal,
    Block,
    &Block::attack,
    bool,
    Player*         pPlayer,
    BlockPos const& pPos
)
{
    if (pPlayer == nullptr) return origin(pPlayer, pPos);
    auto beforeEvent = PlayerAttackBlockBeforeEvent(*pPlayer, const_cast<BlockPos&>(pPos));
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return false; }
    auto result = origin(pPlayer, pPos);
    if (result) { LLEventBus.publish(PlayerAttackBlockAfterEvent(*pPlayer, pPos)); }
    return result;
}

Event_Hook_Factory(PlayerAttackBlock, <PlayerAttackBlockEventHook>);

} // namespace ila::mc::inline player