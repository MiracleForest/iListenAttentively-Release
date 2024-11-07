#include "Global.h"
#include <mc/world/level/BlockPos.h>

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

    ILAPI BlockPos const& getPos() const { return mPos; }
    ILAPI BlockPos const& getFlowFromPos() const { return mFlowFromPos; }
    ILAPI uchar&          getFlowFromDirection() const { return mFlowFromDirection; }
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

    ILAPI BlockPos const& getPos() const { return mPos; }
    ILAPI BlockPos const& getFlowFromPos() const { return mFlowFromPos; }
    ILAPI uchar const&    getFlowFromDirection() const { return mFlowFromDirection; }
    ILAPI bool&           getResult() const { return mResult; }
};
} // namespace ila::inline world