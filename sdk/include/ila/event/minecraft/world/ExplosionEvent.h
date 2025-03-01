#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/Explosion.h>

namespace ila::mc::inline world
{
class ExplosionBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    Explosion& mExplosion;

public:
    constexpr explicit ExplosionBeforeEvent(BlockSource& blockSource, Explosion& explosion)
        : Cancellable(blockSource)
        , mExplosion(explosion)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI Explosion& getExplosion() const;
};

class ExplosionAfterEvent final : public ll::event::WorldEvent
{

protected:
    Explosion& mExplosion;

public:
    constexpr explicit ExplosionAfterEvent(BlockSource& blockSource, Explosion& explosion)
        : WorldEvent(blockSource)
        , mExplosion(explosion)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI Explosion const& getExplosion() const;
};
} // namespace ila::mc::inline world