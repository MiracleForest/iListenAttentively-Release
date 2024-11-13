#include "Global.h"
#include <mc/world/level/block/actor/SculkCatalystBlockActor.h>

namespace ila::mc::inline level
{
class WeatherUpdateBeforeEvent final : public ll::event::Cancellable<ll::event::LevelEvent>
{
protected:
    float& mRainLevel;
    int&   mRainTime;
    float& mLightningLevel;
    int&   mLightningTime;

public:
    constexpr explicit WeatherUpdateBeforeEvent(
        Level& level,
        float& rainLevel,
        int&   rainTime,
        float& lightningLevel,
        int&   lightningTime
    )
        : Cancellable(level)
        , mRainLevel(rainLevel)
        , mRainTime(rainTime)
        , mLightningLevel(lightningLevel)
        , mLightningTime(lightningTime)
    {
    }

    ILAPI float& getRainLevel() const;
    ILAPI int&   getRainTime() const;
    ILAPI float& getLightningLevel() const;
    ILAPI int&   getLightningTime() const;
};

class WeatherUpdateAfterEvent final : public ll::event::LevelEvent
{
protected:
    float const& mRainLevel;
    int const&   mRainTime;
    float const& mLightningLevel;
    int const&   mLightningTime;

public:
    constexpr explicit WeatherUpdateAfterEvent(
        Level&       level,
        float const& rainLevel,
        int const&   rainTime,
        float const& lightningLevel,
        int const&   lightningTime
    )
        : LevelEvent(level)
        , mRainLevel(rainLevel)
        , mRainTime(rainTime)
        , mLightningLevel(lightningLevel)
        , mLightningTime(lightningTime)
    {
    }

    ILAPI float const& getRainLevel() const;
    ILAPI int const&   getRainTime() const;
    ILAPI float const& getLightningLevel() const;
    ILAPI int const&   getLightningTime() const;
};
} // namespace ila::mc::inline level