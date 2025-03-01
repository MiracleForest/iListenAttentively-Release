#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/MobEvent.h>
#include <mc/deps/core/utility/optional_ref.h>
#include <mc/deps/shared_types/legacy/actor/ActorDamageCause.h>

namespace ila::mc::inline actor
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

    ILNDAPI optional_ref<Actor> getSource() const;
    ILNDAPI float&              getValue() const;
    ILNDAPI SharedTypes::Legacy::ActorDamageCause& getCause() const;
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

    ILNDAPI optional_ref<Actor const> getSource() const;
    ILNDAPI float const&              getValue() const;
    ILNDAPI SharedTypes::Legacy::ActorDamageCause const& getCause() const;
};
} // namespace ila::mc::inline actor