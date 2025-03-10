#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/MobEvent.h>
#include <mc/deps/core/utility/optional_ref.h>
#include <mc/deps/shared_types/legacy/actor/ActorDamageCause.h>

namespace ila::mc::inline world::inline actor
{
class MobHurtEffectBeforeEvent final : public ll::event::Cancellable<ll::event::entity::MobEvent>
{
protected:
    optional_ref<Actor>                    mSource;
    float&                                 mValue;
    SharedTypes::Legacy::ActorDamageCause& mCause;

public:
    constexpr explicit MobHurtEffectBeforeEvent(
        Mob&                                   actor,
        optional_ref<Actor>                    mSource,
        float&                                 value,
        SharedTypes::Legacy::ActorDamageCause& cause
    )
        : Cancellable(actor)
        , mSource(mSource)
        , mValue(value)
        , mCause(cause)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI optional_ref<Actor> source() const;
    ILNDAPI float&              value() const;
    ILNDAPI SharedTypes::Legacy::ActorDamageCause& cause() const;
};

class MobHurtEffectAfterEvent final : public ll::event::entity::MobEvent
{
protected:
    optional_ref<Actor const>                    mSource;
    float const&                                 mValue;
    SharedTypes::Legacy::ActorDamageCause const& mCause;

public:
    constexpr explicit MobHurtEffectAfterEvent(
        Mob&                                         actor,
        optional_ref<Actor const>                    mSource,
        float const&                                 value,
        SharedTypes::Legacy::ActorDamageCause const& cause
    )
        : MobEvent(actor)
        , mSource(mSource)
        , mValue(value)
        , mCause(cause)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI optional_ref<Actor const> source() const;
    ILNDAPI float const&              value() const;
    ILNDAPI SharedTypes::Legacy::ActorDamageCause const& cause() const;
};
} // namespace ila::mc::inline world::inline actor