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

    ILAPI BlockPos const& getPos() const;
    ILAPI int&            getNeighbor() const;
    ILAPI BlockPos const& getFlowFromPos() const;
    ILAPI uchar&          getFlowFromDirection() const;
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

    ILAPI BlockPos const& getPos() const;
    ILAPI int const&      getNeighbor() const;
    ILAPI BlockPos const& getFlowFromPos() const;
    ILAPI uchar const&    getFlowFromDirection() const;
};
} // namespace ila::inline world