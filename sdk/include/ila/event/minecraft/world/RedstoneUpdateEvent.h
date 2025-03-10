#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world
{
class RedstoneUpdateBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos& mPos;
    int&      mStrength;
    bool&     mIsFirstTime;

public:
    constexpr explicit RedstoneUpdateBeforeEvent(
        BlockSource& blockSource,
        BlockPos&    pos,
        int&         strength,
        bool&        isFirstTime
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mStrength(strength)
        , mIsFirstTime(isFirstTime)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& pos() const;
    ILNDAPI int&      strength() const;
    ILNDAPI bool&     isFirstTime() const;
};

class RedstoneUpdateAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    int const&      mStrength;
    bool const&     mIsFirstTime;

public:
    constexpr explicit RedstoneUpdateAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        int const&      strength,
        bool const&     isFirstTime
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mStrength(strength)
        , mIsFirstTime(isFirstTime)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& pos() const;
    ILNDAPI int const&      strength() const;
    ILNDAPI bool const&     isFirstTime() const;
};
} // namespace ila::mc::inline world