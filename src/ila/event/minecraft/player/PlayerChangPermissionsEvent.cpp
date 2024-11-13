#include "PlayerChangPermissionsEvent.h"

namespace ila::mc::inline player
{

CommandPermissionLevel const& PlayerChangPermissionsBeforeEvent::getOldPermissions() const
{
    return mOldPermissions;
}
CommandPermissionLevel& PlayerChangPermissionsBeforeEvent::getNewPermissions() const
{
    return mNewPermissions;
}

CommandPermissionLevel const& PlayerChangPermissionsAfterEvent::getOldPermissions() const
{
    return mOldPermissions;
}
CommandPermissionLevel const& PlayerChangPermissionsAfterEvent::getNewPermissions() const
{
    return mNewPermissions;
}

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

Event_Factory(PlayerChangPermissions, <PlayerChangPermissionsEventHook>);

} // namespace ila::mc::inline player