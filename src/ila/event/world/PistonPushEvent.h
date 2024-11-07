#include "Global.h"
#include <mc/world/level/BlockPos.h>

namespace ila::inline world
{
class PistonPushBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mPos;
    uchar&          mBranchFacing;
    uchar&          mPistonMoveFacing;

public:
    constexpr explicit PistonPushBeforeEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        uchar&          branchFacing,
        uchar&          pistonMoveFacing
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mBranchFacing(branchFacing)
        , mPistonMoveFacing(pistonMoveFacing)
    {
    }

    ILAPI BlockPos const& getPos() const { return mPos; }
    ILAPI uchar&          getBranchFacing() const { return mBranchFacing; }
    ILAPI uchar&          getPistonMoveFacing() const { return mPistonMoveFacing; }
};

class PistonPushAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    uchar const&    mBranchFacing;
    uchar const&    mPistonMoveFacing;
    bool&           mResult;

public:
    constexpr explicit PistonPushAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        uchar&          branchFacing,
        uchar&          pistonMoveFacing,
        bool&           result
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mBranchFacing(branchFacing)
        , mPistonMoveFacing(pistonMoveFacing)
        , mResult(result)
    {
    }

    ILAPI BlockPos const& getPos() const { return mPos; }
    ILAPI uchar const&    getBranchFacing() const { return mBranchFacing; }
    ILAPI uchar const&    getPistonMoveFacing() const { return mPistonMoveFacing; }
    ILAPI bool&           getResult() const { return mResult; }
};
} // namespace ila::inline world