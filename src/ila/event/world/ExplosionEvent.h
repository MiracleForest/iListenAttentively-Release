#include "Global.h"
#include <mc/world/level/Explosion.h>

namespace ila::inline world
{

using CustomKnockbackCalculationFunc = Vec3 (*)(Explosion const&, Actor const&, float);

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

    Explosion& getExplosion() const { return mExplosion; }

    ILAPI Vec3&          getPos() const { return *(Vec3*)&getExplosion(); }
    ILAPI float&         getRadius() const { return *((float*)&getExplosion() + 3); }
    ILAPI ActorUniqueID& getSource() const { return *((ActorUniqueID*)&getExplosion() + 12); }
    ILAPI CustomKnockbackCalculationFunc& getCustomKnockbackCalculation() const
    {
        return *((CustomKnockbackCalculationFunc*)&getExplosion() + 17);
    }
    ILAPI float& getMaxResistance() const { return *((float*)&getExplosion() + 28); }
    ILAPI float& getKnockbackScaling() const { return *((float*)&getExplosion() + 32); }
    ILAPI bool&  getOverrideInWater() const { return *((bool*)&getExplosion() + 58); }
    ILAPI bool&  getFire() const { return *((bool*)&getExplosion() + 80); }
    ILAPI bool&  getBreaking() const { return *((bool*)&getExplosion() + 81); }
    ILAPI bool&  getAllowUnderwater() const { return *((bool*)&getExplosion() + 82); }
    ILAPI bool&  getCanToggleBlocks() const { return *((bool*)&getExplosion() + 83); }
    ILAPI bool&  getShouldTakeDamage() const { return *((bool*)&getExplosion() + 84); }
    ILAPI bool&  getIgnoreBlockResistance() const { return *((bool*)&getExplosion() + 85); }
};

class ExplosionAfterEvent final : public ll::event::WorldEvent
{
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

    ILAPI Explosion const& getExplosion() const { return mExplosion; }
    ILAPI bool&            getResult() { return mResult; }

    ILAPI Vec3 const&          getPos() const { return *(Vec3*)&getExplosion(); }
    ILAPI float const&         getRadius() const { return *((float*)&getExplosion() + 3); }
    ILAPI ActorUniqueID const& getSource() const { return *((ActorUniqueID*)&getExplosion() + 12); }
    ILAPI CustomKnockbackCalculationFunc const& getCustomKnockbackCalculation() const
    {
        return *((CustomKnockbackCalculationFunc*)&getExplosion() + 17);
    }
    ILAPI float const& getMaxResistance() const { return *((float*)&getExplosion() + 28); }
    ILAPI float const& getKnockbackScaling() const { return *((float*)&getExplosion() + 32); }
    ILAPI bool const&  getOverrideInWater() const { return *((bool*)&getExplosion() + 58); }
    ILAPI bool const&  getFire() const { return *((bool*)&getExplosion() + 80); }
    ILAPI bool const&  getBreaking() const { return *((bool*)&getExplosion() + 81); }
    ILAPI bool const&  getAllowUnderwater() const { return *((bool*)&getExplosion() + 82); }
    ILAPI bool const&  getCanToggleBlocks() const { return *((bool*)&getExplosion() + 83); }
    ILAPI bool const&  getShouldTakeDamage() const { return *((bool*)&getExplosion() + 84); }
    ILAPI bool const&  getIgnoreBlockResistance() const { return *((bool*)&getExplosion() + 85); }
};
} // namespace ila::inline world