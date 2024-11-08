#include "PlayerChangPermissionsEvent.h"

namespace ila::inline player
{

CommandPermissionLevel const& PlayerChangPermissionsBeforeEvent::getOldPermissions() const { return mOldPermissions; }
CommandPermissionLevel&       PlayerChangPermissionsBeforeEvent::getNewPermissions() const { return mNewPermissions; }

CommandPermissionLevel const& PlayerChangPermissionsAfterEvent::getOldPermissions() const { return mOldPermissions; }
CommandPermissionLevel const& PlayerChangPermissionsAfterEvent::getNewPermissions() const { return mNewPermissions; }

LL_TYPE_INSTANCE_HOOK(
    PlayerChangPermissionsEventHook,
    HookPriority::Normal,
    Player,
    &Player::setPermissions,
    void,
    CommandPermissionLevel pNewPermissions
)
{
    auto const oldPermissions = this->getCommandPermissionLevel();
    auto       beforeEvent    = PlayerChangPermissionsBeforeEvent(*this, oldPermissions, pNewPermissions);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pNewPermissions);
    eventBus.publish(PlayerChangPermissionsAfterEvent(*this, oldPermissions, pNewPermissions));
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class PlayerChangPermissionsBeforeEventEmitter
    : public ll::event::Emitter<emitterFactory1, PlayerChangPermissionsBeforeEvent>
{
    ll::memory::HookRegistrar<PlayerChangPermissionsEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<PlayerChangPermissionsBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class PlayerChangPermissionsAfterEventEmitter
    : public ll::event::Emitter<emitterFactory2, PlayerChangPermissionsAfterEvent>
{
    ll::memory::HookRegistrar<PlayerChangPermissionsEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<PlayerChangPermissionsAfterEventEmitter>();
}
} // namespace ila::inline player