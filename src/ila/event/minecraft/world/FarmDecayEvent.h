#include "Global.h"

namespace ila::mc::inline world
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
        Actor*&         actor,
        float&          fallDistance
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mActor(actor)
        , mFallDistance(fallDistance)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI Actor*&         getActor() const;
    ILAPI float&          getFallDistance() const;
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
        Actor* const&   actor,
        float const&    fallDistance
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mActor(actor)
        , mFallDistance(fallDistance)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI Actor* const&   getActor() const;
    ILAPI float const&    getFallDistance() const;
};
} // namespace ila::mc::inline world