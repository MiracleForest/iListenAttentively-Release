#include "ila/Global.h"

namespace ila::mc::inline world
{
class SpawnWanderingTraderBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos& mPos;

public:
    constexpr explicit SpawnWanderingTraderBeforeEvent(BlockSource& blockSource, BlockPos& pos)
        : Cancellable(blockSource)
        , mPos(pos)
    {
    }

    ILAPI BlockPos& getPos() const;
};

class SpawnWanderingTraderAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;

public:
    constexpr explicit SpawnWanderingTraderAfterEvent(BlockSource& blockSource, BlockPos const& pos)
        : WorldEvent(blockSource)
        , mPos(pos)
    {
    }

    ILAPI BlockPos const& getPos() const;
};
} // namespace ila::mc::inline world