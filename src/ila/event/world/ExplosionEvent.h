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

    Vec3&                           getPos() const { return *(Vec3*)&getExplosion(); }
    float&                          getRadius() const { return *((float*)&getExplosion() + 3); }
    ActorUniqueID&                  getSource() const { return *((ActorUniqueID*)&getExplosion() + 12); }
    CustomKnockbackCalculationFunc& getCustomKnockbackCalculationFunc() const
    {
        return *((CustomKnockbackCalculationFunc*)&getExplosion() + 17);
    }
    float& getMaxResistance() const { return *((float*)&getExplosion() + 28); }
    float& getKnockbackScaling() const { return *((float*)&getExplosion() + 32); }
    bool&  getOverrideInWater() const { return *((bool*)&getExplosion() + 58); }
    bool&  getFire() const { return *((bool*)&getExplosion() + 80); }
    bool&  getBreaking() const { return *((bool*)&getExplosion() + 81); }
    bool&  getAllowUnderwater() const { return *((bool*)&getExplosion() + 82); }
    bool&  getCanToggleBlocks() const { return *((bool*)&getExplosion() + 83); }
    bool&  getShouldTakeDamage() const { return *((bool*)&getExplosion() + 84); }
    bool&  getIgnoreBlockResistance() const { return *((bool*)&getExplosion() + 85); }
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

    Explosion const& getExplosion() const { return mExplosion; }
    bool&            getResult() { return mResult; }

    Vec3 const&          getPos() const { return *(Vec3*)&getExplosion(); }
    float const&         getRadius() const { return *((float*)&getExplosion() + 3); }
    ActorUniqueID const& getSource() const { return *((ActorUniqueID*)&getExplosion() + 12); }
    CustomKnockbackCalculationFunc const& getCustomKnockbackCalculationFunc() const
    {
        return *((CustomKnockbackCalculationFunc*)&getExplosion() + 17);
    }
    float const& getMaxResistance() const { return *((float*)&getExplosion() + 28); }
    float const& getKnockbackScaling() const { return *((float*)&getExplosion() + 32); }
    bool const&  getOverrideInWater() const { return *((bool*)&getExplosion() + 58); }
    bool const&  getFire() const { return *((bool*)&getExplosion() + 80); }
    bool const&  getBreaking() const { return *((bool*)&getExplosion() + 81); }
    bool const&  getAllowUnderwater() const { return *((bool*)&getExplosion() + 82); }
    bool const&  getCanToggleBlocks() const { return *((bool*)&getExplosion() + 83); }
    bool const&  getShouldTakeDamage() const { return *((bool*)&getExplosion() + 84); }
    bool const&  getIgnoreBlockResistance() const { return *((bool*)&getExplosion() + 85); }
};
} // namespace ila::inline world