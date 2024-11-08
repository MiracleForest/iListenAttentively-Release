#include "Global.h"
#include "world/level/Explosion.h"

namespace ila::inline world
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

    ILAPI Explosion& getExplosion() const;
};

class ExplosionAfterEvent final : public ll::event::WorldEvent
{

protected:
    Explosion& mExplosion;
    bool&                      mResult;

public:
    constexpr explicit ExplosionAfterEvent(
        BlockSource&               blockSource,
        Explosion& explosion,
        bool&                      result
    )
        : WorldEvent(blockSource)
        , mExplosion(explosion)
        , mResult(result)
    {
    }

    ILAPI Explosion const& getExplosion() const;
    ILAPI bool&                            getResult();
};
} // namespace ila::inline world