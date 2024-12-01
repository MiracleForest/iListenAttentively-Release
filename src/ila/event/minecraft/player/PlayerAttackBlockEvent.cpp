#include "PlayerAttackBlockEvent.h"
#include <mc/world/level/block/Block.h>

namespace ila::mc::inline player
{

BlockPos const& PlayerAttackBlockBeforeEvent::getPos() const { return mPos; }

BlockPos const& PlayerAttackBlockAfterEvent::getPos() const { return mPos; }
bool&           PlayerAttackBlockAfterEvent::getResult() const { return mResult; }

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
    auto beforeEvent = PlayerAttackBlockBeforeEvent(*pPlayer, pPos);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pPlayer, pPos);
    eventBus.publish(PlayerAttackBlockAfterEvent(*pPlayer, pPos, result));
    return result;
}

Event_Factory(PlayerAttackBlock, <PlayerAttackBlockEventHook>);

} // namespace ila::mc::inline player