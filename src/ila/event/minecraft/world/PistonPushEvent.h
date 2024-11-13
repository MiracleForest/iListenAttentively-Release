#include "Global.h"

namespace ila::mc::inline world
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

    ILAPI BlockPos const& getPos() const;
    ILAPI uchar&          getBranchFacing() const;
    ILAPI uchar&          getPistonMoveFacing() const;
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

    ILAPI BlockPos const& getPos() const;
    ILAPI uchar const&    getBranchFacing() const;
    ILAPI uchar const&    getPistonMoveFacing() const;
    ILAPI bool&           getResult() const;
};
} // namespace ila::mc::inline world