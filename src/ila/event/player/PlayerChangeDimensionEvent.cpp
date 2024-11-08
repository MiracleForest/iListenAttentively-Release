#include "PlayerChangeDimensionEvent.h"
#include <mc/world/actor/player/PlayerDimensionTransferer.h>

namespace ila::inline player
{

ChangeDimensionRequest const& PlayerChangeDimensionBeforeEvent::getChangeDimensionRequest() const
{
    return mChangeDimensionRequest;
}
Dimension const& PlayerChangeDimensionBeforeEvent::getDimension() const { return mDimension; }

ChangeDimensionRequest const& PlayerChangeDimensionAfterEvent::getChangeDimensionRequest() const
{
    return mChangeDimensionRequest;
}
Dimension const& PlayerChangeDimensionAfterEvent::getDimension() const { return mDimension; }

LL_TYPE_INSTANCE_HOOK(
    PlayerChangeDimensionEventHook,
    HookPriority::Normal,
    PlayerDimensionTransferer,
    "?playerPrepareRegion@PlayerDimensionTransferer@@UEAAXAEAVPlayer@@AEBVChangeDimensionRequest@@"
    "AEBVDimension@@@Z",
    void,
    Player&                       pPlayer,
    ChangeDimensionRequest const& pChangeDimensionRequest,
    Dimension const&              pDimension
)
{
    eventBus.publish(PlayerChangeDimensionBeforeEvent(pPlayer, pChangeDimensionRequest, pDimension));
    origin(pPlayer, pChangeDimensionRequest, pDimension);
    eventBus.publish(PlayerChangeDimensionAfterEvent(pPlayer, pChangeDimensionRequest, pDimension));
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class PlayerChangeDimensionBeforeEventEmitter
    : public ll::event::Emitter<emitterFactory1, PlayerChangeDimensionBeforeEvent>
{
    ll::memory::HookRegistrar<PlayerChangeDimensionEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<PlayerChangeDimensionBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class PlayerChangeDimensionAfterEventEmitter
    : public ll::event::Emitter<emitterFactory2, PlayerChangeDimensionAfterEvent>
{
    ll::memory::HookRegistrar<PlayerChangeDimensionEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<PlayerChangeDimensionAfterEventEmitter>();
}

} // namespace ila::inline player