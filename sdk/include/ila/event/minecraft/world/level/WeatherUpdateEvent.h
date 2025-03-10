#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/LevelEvent.h>
#include <mc/world/level/block/actor/SculkCatalystBlockActor.h>

namespace ila::mc::inline world::inline level
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

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI float& rainLevel() const;
    ILNDAPI int&   rainTime() const;
    ILNDAPI float& lightningLevel() const;
    ILNDAPI int&   lightningTime() const;
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

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI float const& rainLevel() const;
    ILNDAPI int const&   rainTime() const;
    ILNDAPI float const& lightningLevel() const;
    ILNDAPI int const&   lightningTime() const;
};
} // namespace ila::mc::inline world::inline level