#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/ActorEvent.h>

// clang-format off
class MobEffectInstance;
// clang-format on

namespace ila::mc::inline world::inline actor
{
class ActorGetEffectBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
protected:
    MobEffectInstance& mEffect;

public:
    constexpr explicit ActorGetEffectBeforeEvent(Actor& actor, MobEffectInstance& effect)
        : Cancellable(actor)
        , mEffect(effect)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI MobEffectInstance& effect() const;
};

class ActorGetEffectAfterEvent final : public ll::event::entity::ActorEvent
{
protected:
    MobEffectInstance const& mEffect;

public:
    constexpr explicit ActorGetEffectAfterEvent(Actor& actor, MobEffectInstance const& effect)
        : ActorEvent(actor)
        , mEffect(effect)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI MobEffectInstance const& effect() const;
};
} // namespace ila::mc::inline world::inline actor