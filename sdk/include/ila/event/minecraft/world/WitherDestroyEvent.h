#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/phys/AABB.h>

namespace ila::mc::inline world
{
class WitherDestroyBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    Level& mLevel;
    AABB&  mBox;
    int&   mRadius;

public:
    constexpr explicit WitherDestroyBeforeEvent(
        BlockSource& blockSource,
        Level&       level,
        AABB&        box,
        int&         radius
    )
        : Cancellable(blockSource)
        , mLevel(level)
        , mBox(box)
        , mRadius(radius)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI Level& level() const;
    ILNDAPI AABB&  box() const;
    ILNDAPI int&   radius() const;
};

class WitherDestroyAfterEvent final : public ll::event::WorldEvent
{
protected:
    Level&      mLevel;
    AABB const& mBox;
    int const&  mRadius;

public:
    constexpr explicit WitherDestroyAfterEvent(
        BlockSource& blockSource,
        Level&       level,
        AABB const&  box,
        int const&   radius
    )
        : WorldEvent(blockSource)
        , mLevel(level)
        , mBox(box)
        , mRadius(radius)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI Level&      level() const;
    ILNDAPI AABB const& box() const;
    ILNDAPI int const&  radius() const;
};
} // namespace ila::mc::inline world