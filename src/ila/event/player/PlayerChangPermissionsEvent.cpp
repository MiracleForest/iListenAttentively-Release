#include "PlayerChangPermissionsEvent.h"

namespace ila::inline player
{
LL_TYPE_INSTANCE_HOOK(
    PlayerChangPermissionsEventHook,
    HookPriority::Normal,
    Player,
    &Player::setPermissions,
    void,
    CommandPermissionLevel pPermissions
)
{
    auto beforeEvent = PlayerChangPermissionsBeforeEvent(*this, pPermissions);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pPermissions);
    eventBus.publish(PlayerChangPermissionsAfterEvent(*this, pPermissions));
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