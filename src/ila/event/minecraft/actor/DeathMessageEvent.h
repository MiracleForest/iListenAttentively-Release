#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/ActorEvent.h>
#include <mc/world/actor/ActorDamageSource.h>

namespace ila::mc::inline actor
{
class DeathMessageBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
protected:
    ActorDamageSource&                                mDamageSource;
    std::pair<std::string, std::vector<std::string>>& mResult;

public:
    constexpr explicit DeathMessageBeforeEvent(
        Actor&                                            actor,
        ActorDamageSource&                                damageSource,
        std::pair<std::string, std::vector<std::string>>& result
    )
        : Cancellable(actor)
        , mDamageSource(damageSource)
        , mResult(result)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI ActorDamageSource& getDamageSource() const;
    ILNDAPI std::pair<std::string, std::vector<std::string>>& getResult() const;
};

class DeathMessageAfterEvent final : public ll::event::entity::ActorEvent
{
protected:
    ActorDamageSource const&                                mDamageSource;
    std::pair<std::string, std::vector<std::string>> const& mResult;

public:
    constexpr explicit DeathMessageAfterEvent(
        Actor&                                                  actor,
        ActorDamageSource const&                                damageSource,
        std::pair<std::string, std::vector<std::string>> const& result
    )
        : ActorEvent(actor)
        , mDamageSource(damageSource)
        , mResult(result)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ActorDamageSource const& getDamageSource() const;
    ILNDAPI std::pair<std::string, std::vector<std::string>> const& getResult() const;
};
} // namespace ila::mc::inline actor