#include "ila/Global.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/util/Random.h>
#include <mc/world/level/BlockPos.h>

namespace iListenAttentively::World
{
class DragonEggBlockTeleportBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mPos;
    Random&         mRandom;
    BlockPos&       mTargetPos;

public:
    constexpr explicit DragonEggBlockTeleportBeforeEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        Random&         random,
        BlockPos&       targetPos
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mRandom(random)
        , mTargetPos(targetPos)
    {
    }

    BlockPos const& getPos() const { return mPos; }
    Random&         getRandom() const { return mRandom; }
    BlockPos&       getTargetPos() const { return mTargetPos; }
};

class DragonEggBlockTeleportAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    Random const&   mRandom;
    BlockPos const& mTargetPos;

public:
    constexpr explicit DragonEggBlockTeleportAfterEvent(
        BlockSource& blockSource,
        BlockPos const&    pos,
        Random const&      random,
        BlockPos const&    targetPos
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mRandom(random)
        , mTargetPos(targetPos)
    {
    }

    BlockPos const& getPos() const { return mPos; }
    Random const&   getRandom() const { return mRandom; }
    BlockPos const& getTargetPos() const { return mTargetPos; }
};
} // namespace iListenAttentively::World