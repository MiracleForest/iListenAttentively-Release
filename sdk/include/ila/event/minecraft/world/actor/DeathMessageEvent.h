#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/ActorEvent.h>

// clang-format off
class ActorDamageSource;
// clang-format on

namespace ila::mc::inline world::inline actor
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

    ILNDAPI ActorDamageSource& damageSource() const;
    ILNDAPI std::pair<std::string, std::vector<std::string>>& result() const;
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

    ILNDAPI ActorDamageSource const& damageSource() const;
    ILNDAPI std::pair<std::string, std::vector<std::string>> const& result() const;
};
} // namespace ila::mc::inline world::inline actor