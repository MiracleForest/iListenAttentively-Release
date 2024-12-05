#include "ila/event/minecraft/player/PlayerChangGameTypeEvent.h"
#include <mc/network/packet/SetPlayerGameTypePacket.h>

namespace ila::mc::inline player
{

GameType const& PlayerChangGameTypeBeforeEvent::getOldGameType() const { return mOldGameType; }
GameType&       PlayerChangGameTypeBeforeEvent::getNewGameType() const { return mNewGameType; }

GameType const& PlayerChangGameTypeAfterEvent::getOldGameType() const { return mOldGameType; }
GameType const& PlayerChangGameTypeAfterEvent::getNewGameType() const { return mNewGameType; }

LL_TYPE_INSTANCE_HOOK(
    PlayerChangGameTypeEventHook,
    HookPriority::Normal,
    ServerPlayer,
    "?setPlayerGameType@ServerPlayer@@UEAAXW4GameType@@@Z",
    void,
    GameType pNewGameType
)
{
    auto const oldGameType = this->getPlayerGameType();
    auto       beforeEvent = PlayerChangGameTypeBeforeEvent(*this, oldGameType, pNewGameType);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pNewGameType);
    eventBus.publish(PlayerChangGameTypeAfterEvent(*this, oldGameType, pNewGameType));
}

Event_Factory(PlayerChangGameType, <PlayerChangGameTypeEventHook>);

} // namespace ila::mc::inline player