#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/ActorEvent.h>

// clang-format off
class Vec3;
// clang-format on

namespace ila::mc::inline world::inline actor
{
class ActorChangeDimensionBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
protected:
    DimensionType const& mFromDimensionId;
    DimensionType&       mToDimensionId;

public:
    constexpr explicit ActorChangeDimensionBeforeEvent(
        Actor&               actor,
        DimensionType const& fromDimensionId,
        DimensionType&       toDimensionId
    )
        : Cancellable(actor)
        , mFromDimensionId(fromDimensionId)
        , mToDimensionId(toDimensionId)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI DimensionType const& fromDimensionId() const;
    ILNDAPI DimensionType&       toDimensionId() const;
};

class ActorChangeDimensionAfterEvent final : public ll::event::entity::ActorEvent
{
protected:
    DimensionType const& mFromDimensionId;
    Vec3 const&          mFromPos;
    DimensionType const& mToDimensionId;

public:
    constexpr explicit ActorChangeDimensionAfterEvent(
        Actor&               actor,
        DimensionType const& fromDimensionId,
        Vec3 const&          fromPos,
        DimensionType const& toDimensionId
    )
        : ActorEvent(actor)
        , mFromDimensionId(fromDimensionId)
        , mFromPos(fromPos)
        , mToDimensionId(toDimensionId)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI DimensionType const& fromDimensionId() const;
    ILNDAPI Vec3 const&          getFromPos() const;
    ILNDAPI DimensionType const& toDimensionId() const;
};
} // namespace ila::mc::inline world::inline actor