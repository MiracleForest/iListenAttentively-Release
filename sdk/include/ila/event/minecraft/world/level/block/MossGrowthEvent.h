#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>

// clang-format off
class BlockPos;
class Random;
// clang-format on

namespace ila::mc::inline world::inline level::inline block
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

    ILNDAPI BlockPos& pos() const;
    ILNDAPI Random&   random() const;
    ILNDAPI int&      xRadius() const;
    ILNDAPI int&      zRadius() const;
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

    ILNDAPI BlockPos const& pos() const;
    ILNDAPI Random const&   random() const;
    ILNDAPI int const&      xRadius() const;
    ILNDAPI int const&      zRadius() const;
    ILNDAPI std::vector<BlockPos>& getTargetPoss() const;
};
} // namespace ila::mc::inline world::inline level::inline block