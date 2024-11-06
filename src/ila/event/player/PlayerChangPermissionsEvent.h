#include "Global.h"

namespace ila::inline player
{
class PlayerChangPermissionsBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    CommandPermissionLevel& mPermissions;

public:
    constexpr explicit PlayerChangPermissionsBeforeEvent(Player& player, CommandPermissionLevel& permissions)
        : Cancellable(player)
        , mPermissions(permissions)
    {
    }

    CommandPermissionLevel& getPermissions() const { return mPermissions; };
};

class PlayerChangPermissionsAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    CommandPermissionLevel const& mPermissions;

public:
    constexpr explicit PlayerChangPermissionsAfterEvent(
        Player&                       player,
        CommandPermissionLevel const& permissions
    )
        : PlayerEvent(player)
        , mPermissions(permissions)
    {
    }

    CommandPermissionLevel const& getPermissions() const { return mPermissions; };
};
} // namespace ila::inline player