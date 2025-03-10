#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>
#include <mc/deps/core/math/Vec3.h>

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerInteractEntityBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    Actor& mTarget;
    Vec3&  mPos;

public:
    constexpr explicit PlayerInteractEntityBeforeEvent(Player& player, Actor& target, Vec3& pos)
        : Cancellable(player)
        , mTarget(target)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILAPI Actor& target() const;
    ILAPI Vec3&  pos() const;
};

class PlayerInteractEntityAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    Actor const& mTarget;
    Vec3 const&  mPos;

public:
    constexpr explicit PlayerInteractEntityAfterEvent(Player& player, Actor const& target, Vec3 const& pos)
        : PlayerEvent(player)
        , mTarget(target)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILAPI Actor const& target() const;
    ILAPI Vec3 const&  pos() const;
};
} // namespace ila::mc::inline world::inline actor::inline player