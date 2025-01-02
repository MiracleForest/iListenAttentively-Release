#include "ila/event/minecraft/level/WeatherUpdateEvent.h"
#include "ila/base/Gloabl.h"

namespace ila::mc::inline level
{

void WeatherUpdateBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["rainLevel"]      = getRainLevel();
    nbt["rainTime"]       = getRainTime();
    nbt["lightningLevel"] = getLightningLevel();
    nbt["lightningTime"]  = getLightningTime();
}
void WeatherUpdateBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getRainLevel()      = nbt["rainLevel"];
    getRainTime()       = nbt["rainTime"];
    getLightningLevel() = nbt["lightningLevel"];
    getLightningTime()  = nbt["lightningTime"];
}
float& WeatherUpdateBeforeEvent::getRainLevel() const { return mRainLevel; };
int&   WeatherUpdateBeforeEvent::getRainTime() const { return mRainTime; }
float& WeatherUpdateBeforeEvent::getLightningLevel() const { return mLightningLevel; };
int&   WeatherUpdateBeforeEvent::getLightningTime() const { return mLightningTime; };

void WeatherUpdateAfterEvent::serialize(CompoundTag& nbt) const
{
    LevelEvent::serialize(nbt);
    nbt["rainLevel"]      = getRainLevel();
    nbt["rainTime"]       = getRainTime();
    nbt["lightningLevel"] = getLightningLevel();
    nbt["lightningTime"]  = getLightningTime();
}
float const& WeatherUpdateAfterEvent::getRainLevel() const { return mRainLevel; };
int const&   WeatherUpdateAfterEvent::getRainTime() const { return mRainTime; }
float const& WeatherUpdateAfterEvent::getLightningLevel() const { return mLightningLevel; };
int const&   WeatherUpdateAfterEvent::getLightningTime() const { return mLightningTime; };

LL_TYPE_INSTANCE_HOOK(
    WeatherUpdateEventHook,
    HookPriority::Normal,
    Level,
    &Level::$updateWeather,
    void,
    float pRainLevel,
    int   pRainTime,
    float pLightningLevel,
    int   pLightningTime
)
{
    auto beforeEvent =
        WeatherUpdateBeforeEvent(*this, pRainLevel, pRainTime, pLightningLevel, pLightningTime);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }
    origin(pRainLevel, pRainTime, pLightningLevel, pLightningTime);
    LLEventBus.publish(WeatherUpdateAfterEvent(*this, pRainLevel, pRainTime, pLightningLevel, pLightningTime));
}

Event_Hook_Factory(WeatherUpdate, <WeatherUpdateEventHook>);

} // namespace ila::mc::inline level