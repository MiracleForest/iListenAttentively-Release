#include "Global.h"
#include <mc/common/wrapper/optional_ref.h>
#include <mc/world/actor/monster/EnderDragon.h>

namespace ila::mc::inline actor
{
class DragonRespawnBeforeEvent final : public ll::event::Cancellable<ll::event::Event>
{
public:
    constexpr explicit DragonRespawnBeforeEvent()
        : Cancellable()
    {
    }
};

class DragonRespawnAfterEvent final : public ll::event::entity::ActorEvent
{
protected:
    optional_ref<EnderDragon> mEnderDragon;

public:
    constexpr explicit DragonRespawnAfterEvent(optional_ref<EnderDragon> dragon)
        : ActorEvent(dragon)
        , mEnderDragon(dragon)
    {
    }

    ILAPI optional_ref<EnderDragon> getEnderDragon() const;
};
} // namespace ila::mc::inline actor