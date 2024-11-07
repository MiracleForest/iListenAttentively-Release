#include "Global.h"
#include <mc/world/level/BlockPos.h>

namespace ila::inline world
{
class LiquidFlowBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mPos;
    int&            mNeighbor;
    BlockPos const& mFlowFromPos;
    uchar&          mFlowFromDirection;

public:
    constexpr explicit LiquidFlowBeforeEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        int&            neighbor,
        BlockPos const& flowFromPos,
        uchar&          flowFromDirection
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mNeighbor(neighbor)
        , mFlowFromPos(flowFromPos)
        , mFlowFromDirection(flowFromDirection)
    {
    }

    ILAPI BlockPos const& getPos() const { return mPos; }
    ILAPI int&            getNeighbor() const { return mNeighbor; }
    ILAPI BlockPos const& getFlowFromPos() const { return mFlowFromPos; }
    ILAPI uchar&          getFlowFromDirection() const { return mFlowFromDirection; }
};

class LiquidFlowAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    int const&      mNeighbor;
    BlockPos const& mFlowFromPos;
    uchar const&    mFlowFromDirection;

public:
    constexpr explicit LiquidFlowAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        int const&      neighbor,
        BlockPos const& flowFromPos,
        uchar&          flowFromDirection
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mNeighbor(neighbor)
        , mFlowFromPos(flowFromPos)
        , mFlowFromDirection(flowFromDirection)
    {
    }

    ILAPI BlockPos const& getPos() const { return mPos; }
    ILAPI int const&      getNeighbor() const { return mNeighbor; }
    ILAPI BlockPos const& getFlowFromPos() const { return mFlowFromPos; }
    ILAPI uchar const&    getFlowFromDirection() const { return mFlowFromDirection; }
};
} // namespace ila::inline world