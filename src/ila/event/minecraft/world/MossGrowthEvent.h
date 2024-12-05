#include "ila/Global.h"

namespace ila::mc::inline world
{
class MossGrowthBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const&        mPos;
    Random&                mRandom;
    std::vector<BlockPos>& mTargetPoss;

public:
    constexpr explicit MossGrowthBeforeEvent(
        BlockSource&           blockSource,
        BlockPos const&        pos,
        Random&                random,
        std::vector<BlockPos>& targetPoss
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mRandom(random)
        , mTargetPoss(targetPoss)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI Random&         getRandom() const;
    ILAPI std::vector<BlockPos>& getTargetPoss() const;
};

class MossGrowthAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const&              mPos;
    Random const&                mRandom;
    std::vector<BlockPos> const& mTargetPoss;

public:
    constexpr explicit MossGrowthAfterEvent(
        BlockSource&                 blockSource,
        BlockPos const&              pos,
        Random const&                random,
        std::vector<BlockPos> const& targetPoss
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mRandom(random)
        , mTargetPoss(targetPoss)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI Random const&   getRandom() const;
    ILAPI std::vector<BlockPos> const& getTargetPoss() const;
};
} // namespace ila::mc::inline world