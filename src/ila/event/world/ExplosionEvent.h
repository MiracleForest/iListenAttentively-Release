#include "Global.h"
#include <mc/world/level/Explosion.h>

namespace ila::inline world
{
class ExplosionBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
public:
    using CustomKnockbackCalculationFunc = Vec3 (*)(Explosion const&, Actor const&, float);

protected:
    Explosion& mExplosion;

public:
    constexpr explicit ExplosionBeforeEvent(BlockSource& blockSource, Explosion& explosion)
        : Cancellable(blockSource)
        , mExplosion(explosion)
    {
    }

    ILAPI Explosion& getExplosion() const;

    ILAPI Vec3&                           getPos() const;
    ILAPI float&                          getRadius() const;
    ILAPI ActorUniqueID&                  getSource() const;
    ILAPI CustomKnockbackCalculationFunc& getCustomKnockbackCalculation() const;
    ILAPI float&                          getMaxResistance() const;
    ILAPI float&                          getKnockbackScaling() const;
    ILAPI bool&                           getOverrideInWater() const;
    ILAPI bool&                           getFire() const;
    ILAPI bool&                           getBreaking() const;
    ILAPI bool&                           getAllowUnderwater() const;
    ILAPI bool&                           getCanToggleBlocks() const;
    ILAPI bool&                           getShouldTakeDamage() const;
    ILAPI bool&                           getIgnoreBlockResistance() const;
};

class ExplosionAfterEvent final : public ll::event::WorldEvent
{
public:
    using CustomKnockbackCalculationFunc = Vec3 (*)(Explosion const&, Actor const&, float);

protected:
    Explosion& mExplosion;
    bool&      mResult;

public:
    constexpr explicit ExplosionAfterEvent(BlockSource& blockSource, Explosion& explosion, bool& result)
        : WorldEvent(blockSource)
        , mExplosion(explosion)
        , mResult(result)
    {
    }

    ILAPI Explosion const& getExplosion() const;
    ILAPI bool&            getResult();

    ILAPI Vec3 const&                           getPos() const;
    ILAPI float const&                          getRadius() const;
    ILAPI ActorUniqueID const&                  getSource() const;
    ILAPI CustomKnockbackCalculationFunc const& getCustomKnockbackCalculation() const;
    ILAPI float const&                          getMaxResistance() const;
    ILAPI float const&                          getKnockbackScaling() const;
    ILAPI bool const&                           getOverrideInWater() const;
    ILAPI bool const&                           getFire() const;
    ILAPI bool const&                           getBreaking() const;
    ILAPI bool const&                           getAllowUnderwater() const;
    ILAPI bool const&                           getCanToggleBlocks() const;
    ILAPI bool const&                           getShouldTakeDamage() const;
    ILAPI bool const&                           getIgnoreBlockResistance() const;
};
} // namespace ila::inline world