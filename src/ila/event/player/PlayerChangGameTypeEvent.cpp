#include "PlayerChangGameTypeEvent.h"
#include <mc/network/packet/SetPlayerGameTypePacket.h>

namespace ila::inline player
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

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class PlayerChangGameTypeBeforeEventEmitter
    : public ll::event::Emitter<emitterFactory1, PlayerChangGameTypeBeforeEvent>
{
    ll::memory::HookRegistrar<PlayerChangGameTypeEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<PlayerChangGameTypeBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class PlayerChangGameTypeAfterEventEmitter
    : public ll::event::Emitter<emitterFactory2, PlayerChangGameTypeAfterEvent>
{
    ll::memory::HookRegistrar<PlayerChangGameTypeEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<PlayerChangGameTypeAfterEventEmitter>();
}

} // namespace ila::inline player