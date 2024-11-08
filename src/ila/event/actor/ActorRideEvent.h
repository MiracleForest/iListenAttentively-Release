#include "Global.h"

namespace ila::inline actor
{
class ActorRideBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
protected:
    Actor& mTarget;

public:
    constexpr explicit ActorRideBeforeEvent(Actor& actor, Actor& target)
        : Cancellable(actor)
        , mTarget(target)
    {
    }

    ILAPI Actor& getTarget() const { return mTarget; }
};

class ActorRideAfterEvent final : public ll::event::entity::ActorEvent
{
protected:
    Actor const& mTarget;
    bool&        mResult;

public:
    constexpr explicit ActorRideAfterEvent(Actor& actor, Actor const& target, bool& result)
        : ActorEvent(actor)
        , mTarget(target)
        , mResult(result)
    {
    }

    ILAPI Actor const& getTarget() const { return mTarget; }
    ILAPI bool&        getResult() const { return mResult; }
};
} // namespace ila::inline actor