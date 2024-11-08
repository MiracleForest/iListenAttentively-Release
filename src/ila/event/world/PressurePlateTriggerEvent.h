#include "Global.h"

namespace ila::inline world
{
class PressurePlateTriggerBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mPos;
    Actor&          mActor;

public:
    constexpr explicit PressurePlateTriggerBeforeEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        Actor&          actor
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mActor(actor)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI Actor&          getActor() const;
};

class PressurePlateTriggerAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    Actor const&    mActor;
    bool&           mResult;

public:
    constexpr explicit PressurePlateTriggerAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        Actor const&    actor,
        bool&           result
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mActor(actor)
        , mResult(result)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI Actor const&    getActor() const;
    ILAPI bool&           getResult() const;
};
} // namespace ila::inline world