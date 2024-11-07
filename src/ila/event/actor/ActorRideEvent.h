#include "Global.h"

namespace ila::inline actor
{
class ActorRideBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
protected:
    Actor& mTarget;

public:
    constexpr explicit ActorRideBeforeEvent(Actor& acotr, Actor& target)
        : Cancellable(acotr)
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
    constexpr explicit ActorRideAfterEvent(Actor& acotr, Actor const& target, bool& result)
        : ActorEvent(acotr)
        , mTarget(target)
        , mResult(result)
    {
    }

    ILAPI Actor const& getTarget() const { return mTarget; }
    ILAPI bool&        getResult() const { return mResult; }
};
} // namespace ila::inline actor