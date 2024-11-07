#include "Global.h"
#include <mc/world/level/BlockPos.h>

namespace ila::inline world
{
class FarmDecayBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mPos;
    Actor*&         mActor;
    float&          mFallDistance;

public:
    constexpr explicit FarmDecayBeforeEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        Actor*&         acotr,
        float&          fallDistance
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mActor(acotr)
        , mFallDistance(fallDistance)
    {
    }

    ILAPI BlockPos const& getPos() const { return mPos; }
    ILAPI Actor*&         getActor() const { return mActor; }
    ILAPI float&          getFallDistance() const { return mFallDistance; }
};

class FarmDecayAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    Actor* const&   mActor;
    float const&    mFallDistance;

public:
    constexpr explicit FarmDecayAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        Actor* const&   acotr,
        float const&    fallDistance
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mActor(acotr)
        , mFallDistance(fallDistance)
    {
    }

    ILAPI BlockPos const& getPos() const { return mPos; }
    ILAPI Actor* const&   getActor() const { return mActor; }
    ILAPI float const&    getFallDistance() const { return mFallDistance; }
};
} // namespace ila::inline world