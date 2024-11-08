#include "Global.h"
#include <mc/world/level/block/actor/SculkCatalystBlockActor.h>

namespace ila::inline level
{
class SculkCatalystAbsorbExperienceBeforeEvent final : public ll::event::Cancellable<ll::event::LevelEvent>
{
protected:
    SculkCatalystBlockActor& mBlockActor;
    Actor&                   mActor;

public:
    constexpr explicit SculkCatalystAbsorbExperienceBeforeEvent(
        Level&                   level,
        SculkCatalystBlockActor& blockActor,
        Actor&                   actor
    )
        : Cancellable(level)
        , mBlockActor(blockActor)
        , mActor(actor)
    {
    }

    ILAPI SculkCatalystBlockActor& getBlockActor() const;
    ILAPI Actor&                   getActor() const;
};

class SculkCatalystAbsorbExperienceAfterEvent final : public ll::event::LevelEvent
{
protected:
    SculkCatalystBlockActor const& mBlockActor;
    Actor const&                   mActor;

public:
    constexpr explicit SculkCatalystAbsorbExperienceAfterEvent(
        Level&                         level,
        SculkCatalystBlockActor const& blockActor,
        Actor const&                   actor
    )
        : LevelEvent(level)
        , mBlockActor(blockActor)
        , mActor(actor)
    {
    }

    ILAPI SculkCatalystBlockActor const& getBlockActor() const;
    ILAPI Actor const&                   getActor() const;
};
} // namespace ila::inline level