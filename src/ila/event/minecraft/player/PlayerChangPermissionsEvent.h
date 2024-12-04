#include "Global.h"

namespace ila::mc::inline player
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

    ILAPI CommandPermissionLevel const& getOldPermissions() const;
    ILAPI CommandPermissionLevel&       getNewPermissions() const;
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

    ILAPI CommandPermissionLevel const& getOldPermissions() const;
    ILAPI CommandPermissionLevel const& getNewPermissions() const;
};
} // namespace ila::mc::inline player