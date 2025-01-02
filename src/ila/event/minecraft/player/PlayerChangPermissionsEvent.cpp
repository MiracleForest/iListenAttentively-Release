#include "ila/event/minecraft/player/PlayerChangPermissionsEvent.h"
#include "ila/base/Gloabl.h"
// #include <mc/network/ServerNetworkHandler.h>
// #include <mc/network/packet/RequestPermissionsPacket.h>

namespace ila::mc::inline player
{

void PlayerChangPermissionsBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["oldPermissions"] = magic_enum::enum_name(getOldPermissions());
    nbt["newPermissions"] = magic_enum::enum_name(getNewPermissions());
}
void PlayerChangPermissionsBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getNewPermissions() =
        magic_enum::enum_cast<CommandPermissionLevel>(nbt["oldPermissions"].get<StringTag>())
            .value_or(getNewPermissions());
}
CommandPermissionLevel const& PlayerChangPermissionsBeforeEvent::getOldPermissions() const
{
    return mOldPermissions;
}
CommandPermissionLevel& PlayerChangPermissionsBeforeEvent::getNewPermissions() const
{
    return mNewPermissions;
}

void PlayerChangPermissionsAfterEvent::serialize(CompoundTag& nbt) const
{
    PlayerEvent::serialize(nbt);
    nbt["oldPermissions"] = magic_enum::enum_name(getOldPermissions());
    nbt["newPermissions"] = magic_enum::enum_name(getNewPermissions());
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
    PlayerChangPermissionsEventHook1,
    HookPriority::Normal,
    Player,
    &Player::setPermissions,
    void,
    CommandPermissionLevel pNewPermissions
)
{
    auto const oldPermissions = getCommandPermissionLevel();
    if (oldPermissions == pNewPermissions) { return origin(pNewPermissions); }
    auto beforeEvent = PlayerChangPermissionsBeforeEvent(*this, oldPermissions, pNewPermissions);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }
    origin(pNewPermissions);
    if (getCommandPermissionLevel() == pNewPermissions)
    {
        LLEventBus.publish(PlayerChangPermissionsAfterEvent(*this, oldPermissions, pNewPermissions));
    }
}

// LL_AUTO_TYPE_INSTANCE_HOOK(
//     PlayerChangPermissionsEventHook2,
//     HookPriority::Normal,
//     ServerNetworkHandler,
//      &ServerNetworkHandler::_updatePermissions,
//     bool,
//     ServerPlayer const& player,
//     RequestPermissionsPacket const& packet,
//     Abilities&                      abilities,
//     PermissionsHandler&             permissions,
//     Player*                         target
// )
// {
// 507056   507008   506960   506912
// if (player == nullptr || packet.getPlayerPermissions() == player->getPlayerPermissionLevel()){
//     return origin(requester, packet, abilities, permissions, player);
// }
// packet.pe
// auto const oldPermissions = getCommandPermissionLevel();
// if (oldPermissions == pNewPermissions) { return origin(pNewPermissions); }
// auto beforeEvent = PlayerChangPermissionsBeforeEvent(*this, oldPermissions, pNewPermissions);
// LLEventBus.publish(beforeEvent);
// if (beforeEvent.isCancelled()) return;
// origin(pNewPermissions);
// if (getCommandPermissionLevel() == pNewPermissions)
// {
//     LLEventBus.publish(PlayerChangPermissionsAfterEvent(*this, oldPermissions, pNewPermissions));
// }
// }

Event_Hook_Factory(PlayerChangPermissions, <PlayerChangPermissionsEventHook1>);

} // namespace ila::mc::inline player