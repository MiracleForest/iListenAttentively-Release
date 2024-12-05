#include "ila/Global.h"

namespace ila::mc::inline actor
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

    ILAPI DimensionType const& getFromDimensionId() const;
    ILAPI DimensionType&       getToDimensionId() const;
};

class ActorChangeDimensionAfterEvent final : public ll::event::entity::ActorEvent
{
protected:
    DimensionType const& mFromDimensionId;
    DimensionType const& mToDimensionId;

public:
    constexpr explicit ActorChangeDimensionAfterEvent(
        Actor&               actor,
        DimensionType const& fromDimensionId,
        DimensionType const& toDimensionId
    )
        : ActorEvent(actor)
        , mFromDimensionId(fromDimensionId)
        , mToDimensionId(toDimensionId)
    {
    }

    ILAPI DimensionType const& getFromDimensionId() const;
    ILAPI DimensionType const& getToDimensionId() const;
};
} // namespace ila::mc::inline actor