#include "Global.h"

namespace ila::inline player
{
class PlayerChangPermissionsBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    CommandPermissionLevel const& mOldPermissions;
    CommandPermissionLevel&       mNewPermissions;

public:
    constexpr explicit PlayerChangPermissionsBeforeEvent(
        Player&                       player,
        CommandPermissionLevel const& oldPermissions,
        CommandPermissionLevel&       newPermissions
    )
        : Cancellable(player)
        , mOldPermissions(oldPermissions)
        , mNewPermissions(newPermissions)
    {
    }

    CommandPermissionLevel const& getOldPermissions() const { return mOldPermissions; };
    CommandPermissionLevel&       getNewPermissions() const { return mNewPermissions; };
};

class PlayerChangPermissionsAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    CommandPermissionLevel const& mOldPermissions;
    CommandPermissionLevel const& mNewPermissions;

public:
    constexpr explicit PlayerChangPermissionsAfterEvent(
        Player&                       player,
        CommandPermissionLevel const& oldPermissions,
        CommandPermissionLevel const& newPermissions
    )
        : PlayerEvent(player)
        , mOldPermissions(oldPermissions)
        , mNewPermissions(newPermissions)
    {
    }

    CommandPermissionLevel const& getOldPermissions() const { return mOldPermissions; };
    CommandPermissionLevel const& getNewPermissions() const { return mNewPermissions; };
};
} // namespace ila::inline player