#include "Global.h"

namespace ila::mc::inline world
{
class WitherDestroyBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    Level&      mLevel;
    AABB const& mBox;
    int&        mRadius;

public:
    constexpr explicit WitherDestroyBeforeEvent(
        BlockSource& blockSource,
        Level&       level,
        AABB const&  box,
        int&         radius
    )
        : Cancellable(blockSource)
        , mLevel(level)
        , mBox(box)
        , mRadius(radius)
    {
    }

    ILAPI Level&      level() const;
    ILAPI AABB const& getBox() const;
    ILAPI int&        getRadius() const;
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

    ILAPI Level&      level() const;
    ILAPI AABB const& getBox() const;
    ILAPI int const&  getRadius() const;
};
} // namespace ila::mc::inline world