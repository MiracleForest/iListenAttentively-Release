#include "Global.h"

namespace ila::inline actor
{
class DeathMessageBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
protected:
    ActorDamageSource& mDamageSource;

public:
    constexpr explicit DeathMessageBeforeEvent(Actor& actor, ActorDamageSource& damageSource)
        : Cancellable(actor)
        , mDamageSource(damageSource)
    {
    }

    ILAPI ActorDamageSource& getDamageSource() const;
};

class DeathMessageAfterEvent final : public ll::event::entity::ActorEvent
{
protected:
    ActorDamageSource const&                          mDamageSource;
    std::pair<std::string, std::vector<std::string>>& mResult;

public:
    constexpr explicit DeathMessageAfterEvent(
        Actor&                                            actor,
        ActorDamageSource const&                          damageSource,
        std::pair<std::string, std::vector<std::string>>& result
    )
        : ActorEvent(actor)
        , mDamageSource(damageSource)
        , mResult(result)
    {
    }

    ILAPI ActorDamageSource const& getDamageSource() const;
    ILAPI std::pair<std::string, std::vector<std::string>>& getResult();
};
} // namespace ila::inline actor