#include "Global.h"

namespace ila::mc::inline world
{
class SculkBlockGrowthBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mPos;

public:
    constexpr explicit SculkBlockGrowthBeforeEvent(BlockSource& blockSource, BlockPos const& pos)
        : Cancellable(blockSource)
        , mPos(pos)
    {
    }

    ILAPI BlockPos const& getPos() const;
};

class SculkBlockGrowthAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;

public:
    constexpr explicit SculkBlockGrowthAfterEvent(BlockSource& blockSource, BlockPos const& pos)
        : WorldEvent(blockSource)
        , mPos(pos)
    {
    }

    ILAPI BlockPos const& getPos() const;
};
} // namespace ila::mc::inline world