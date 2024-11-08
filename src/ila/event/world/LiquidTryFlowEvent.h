#include "Global.h"

namespace ila::inline world
{
class LiquidTryFlowBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mPos;
    BlockPos const& mFlowFromPos;
    uchar&          mFlowFromDirection;

public:
    constexpr explicit LiquidTryFlowBeforeEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        BlockPos const& flowFromPos,
        uchar&          flowFromDirection
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mFlowFromPos(flowFromPos)
        , mFlowFromDirection(flowFromDirection)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI BlockPos const& getFlowFromPos() const;
    ILAPI uchar&          getFlowFromDirection() const;
};

class LiquidTryFlowAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    BlockPos const& mFlowFromPos;
    uchar const&    mFlowFromDirection;
    bool&           mResult;

public:
    constexpr explicit LiquidTryFlowAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        BlockPos const& flowFromPos,
        uchar&          flowFromDirection,
        bool&           result
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mFlowFromPos(flowFromPos)
        , mFlowFromDirection(flowFromDirection)
        , mResult(result)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI BlockPos const& getFlowFromPos() const;
    ILAPI uchar const&    getFlowFromDirection() const;
    ILAPI bool&           getResult() const;
};
} // namespace ila::inline world