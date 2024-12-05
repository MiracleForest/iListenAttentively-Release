#include "ila/Global.h"

namespace ila::mc::inline actor
{
class ActorTickBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
public:
    constexpr explicit ActorTickBeforeEvent(Actor& actor)
        : Cancellable(actor)
    {
    }
};

class ActorTickAfterEvent final : public ll::event::entity::ActorEvent
{
public:
    constexpr explicit ActorTickAfterEvent(Actor& actor)
        : ActorEvent(actor)
    {
    }
};
} // namespace ila::mc::inline actor