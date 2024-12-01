#include "WeatherUpdateEvent.h"

namespace ila::mc::inline level
{

float& WeatherUpdateBeforeEvent::getRainLevel() const { return mRainLevel; };
int&   WeatherUpdateBeforeEvent::getRainTime() const { return mRainTime; }
float& WeatherUpdateBeforeEvent::getLightningLevel() const { return mLightningLevel; };
int&   WeatherUpdateBeforeEvent::getLightningTime() const { return mLightningTime; };

float const& WeatherUpdateAfterEvent::getRainLevel() const { return mRainLevel; };
int const&   WeatherUpdateAfterEvent::getRainTime() const { return mRainTime; }
float const& WeatherUpdateAfterEvent::getLightningLevel() const { return mLightningLevel; };
int const&   WeatherUpdateAfterEvent::getLightningTime() const { return mLightningTime; };

LL_TYPE_INSTANCE_HOOK(
    WeatherUpdateEventHook,
    HookPriority::Normal,
    Level,
    "?updateWeather@Level@@UEAAXMHMH@Z",
    void,
    float pRainLevel,
    int   pRainTime,
    float pLightningLevel,
    int   pLightningTime
)
{
    auto beforeEvent =
        WeatherUpdateBeforeEvent(*this, pRainLevel, pRainTime, pLightningLevel, pLightningTime);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pRainLevel, pRainTime, pLightningLevel, pLightningTime);
    eventBus.publish(WeatherUpdateAfterEvent(*this, pRainLevel, pRainTime, pLightningLevel, pLightningTime));
}

Event_Factory(WeatherUpdate, <WeatherUpdateEventHook>);

} // namespace ila::mc::inline level