#include "ila/event/minecraft/player/PlayerChangGameTypeEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/network/packet/SetPlayerGameTypePacket.h>

namespace ila::mc::inline player
{

void PlayerChangGameTypeBeforeEvent::serialize(CompoundTag& nbt) const {
    Cancellable::serialize(nbt);
    nbt["oldGameType"] = magic_enum::enum_name(getOldGameType());
    nbt["newGameType"] = magic_enum::enum_name(getNewGameType());
}
void PlayerChangGameTypeBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getNewGameType() =
        magic_enum::enum_cast<GameType>(nbt["newGameType"].get<StringTag>()).value_or(getNewGameType());
}
GameType const& PlayerChangGameTypeBeforeEvent::getOldGameType() const { return mOldGameType; }
GameType&       PlayerChangGameTypeBeforeEvent::getNewGameType() const { return mNewGameType; }

void PlayerChangGameTypeAfterEvent::serialize(CompoundTag& nbt) const {
    ServerPlayerEvent::serialize(nbt);
    nbt["oldGameType"] = magic_enum::enum_name(getOldGameType());
    nbt["newGameType"] = magic_enum::enum_name(getNewGameType());
}
GameType const& PlayerChangGameTypeAfterEvent::getOldGameType() const { return mOldGameType; }
GameType const& PlayerChangGameTypeAfterEvent::getNewGameType() const { return mNewGameType; }

LL_TYPE_INSTANCE_HOOK(
    PlayerChangGameTypeEventHook,
    HookPriority::Normal,
    ServerPlayer,
    &ServerPlayer::$setPlayerGameType,
    void,
    GameType pNewGameType
)
{
    auto const oldGameType = getPlayerGameType();
    if (oldGameType == pNewGameType) { return origin(pNewGameType); }
    auto       beforeEvent = PlayerChangGameTypeBeforeEvent(*this, oldGameType, pNewGameType);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }
    origin(pNewGameType);
    if (pNewGameType == getPlayerGameType())
    {
        LLEventBus.publish(PlayerChangGameTypeAfterEvent(*this, oldGameType, pNewGameType));
    }
}

Event_Hook_Factory(PlayerChangGameType, <PlayerChangGameTypeEventHook>);

} // namespace ila::mc::inline player