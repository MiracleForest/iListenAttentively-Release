#include "Global.h"

namespace ila::mc::inline actor
{
class ProjectileCreateBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
public:
    constexpr explicit ProjectileCreateBeforeEvent(Actor& actor)
        : Cancellable(actor)
    {
    }
};

class ProjectileCreateAfterEvent final : public ll::event::entity::ActorEvent
{

public:
    constexpr explicit ProjectileCreateAfterEvent(Actor& actor)
        : ActorEvent(actor)
    {
    }
};
} // namespace ila::mc::inline actor