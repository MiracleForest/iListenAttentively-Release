#include "ila/Global.h"

namespace ila::mc::inline world
{
class BlockTickBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mPos;
    Random&         mRandom;

public:
    constexpr explicit BlockTickBeforeEvent(BlockSource& blockSource, BlockPos const& pos, Random& random)
        : Cancellable(blockSource)
        , mPos(pos)
        , mRandom(random)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI Random&         getRandom() const;
};

class BlockTickAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    Random const&   mRandom;

public:
    constexpr explicit BlockTickAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        Random const&   random
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mRandom(random)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI Random const&   getRandom() const;
};
} // namespace ila::mc::inline world