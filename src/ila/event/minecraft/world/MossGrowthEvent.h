#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/util/Random.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world
{
class MossGrowthBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos& mPos;
    Random&   mRandom;
    int&      mXRadius;
    int&      mZRadius;

public:
    constexpr explicit MossGrowthBeforeEvent(
        BlockSource& blockSource,
        BlockPos&    pos,
        Random&      random,
        int&         xRadius,
        int&         zRadius
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mRandom(random)
        , mXRadius(xRadius)
        , mZRadius(zRadius)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& getPos() const;
    ILNDAPI Random&   getRandom() const;
    ILNDAPI int&      getXRadius() const;
    ILNDAPI int&      getZRadius() const;
};

class MossGrowthAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const&        mPos;
    Random const&          mRandom;
    int const&             mXRadius;
    int const&             mZRadius;
    std::vector<BlockPos>& mTargetPoss;

public:
    constexpr explicit MossGrowthAfterEvent(
        BlockSource&           blockSource,
        BlockPos const&        pos,
        Random const&          random,
        int const&             xRadius,
        int const&             zRadius,
        std::vector<BlockPos>& targetPoss
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mRandom(random)
        , mXRadius(xRadius)
        , mZRadius(zRadius)
        , mTargetPoss(targetPoss)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos const& getPos() const;
    ILNDAPI Random const&   getRandom() const;
    ILNDAPI int const&      getXRadius() const;
    ILNDAPI int const&      getZRadius() const;
    ILNDAPI std::vector<BlockPos>& getTargetPoss() const;
};
} // namespace ila::mc::inline world