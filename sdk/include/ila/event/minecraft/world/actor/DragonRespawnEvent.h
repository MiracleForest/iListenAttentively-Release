#pragma once
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/MobEvent.h>
#include <mc/deps/core/utility/optional_ref.h>
#include <mc/world/actor/monster/EnderDragon.h>

namespace ila::mc::inline world::inline actor
{
class DragonRespawnBeforeEvent final : public ll::event::Cancellable<ll::event::Event>
{
public:
    constexpr explicit DragonRespawnBeforeEvent()
        : Cancellable()
    {
    }
};

class DragonRespawnAfterEvent final : public ll::event::entity::MobEvent
{
public:
    constexpr explicit DragonRespawnAfterEvent(EnderDragon& dragon)
        : MobEvent(dragon)
    {
    }
};
} // namespace ila::mc::inline world::inline actor