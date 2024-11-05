#include "DragonEggBlockTeleportEvent.h"
#include <mc/enums/BlockUpdateFlag.h>
#include <mc/math/Vec3.h>
#include <mc/world/events/GameEventRegistry.h>
#include <mc/world/level/Level.h>
#include <mc/world/level/block/registry/BlockTypeRegistry.h>
#include <mc/world/level/block/utils/VanillaBlockTypeIds.h>

namespace ila::inline world
{

LL_STATIC_HOOK(
    DragonEggBlockTeleportEventHook,
    HookPriority::Normal,
    "?_attemptTeleport@DragonEggBlock@@CAXAEAVBlockSource@@AEAVRandom@@AEBVBlockPos@@@Z",
    void,
    BlockSource&    pRegion,
    Random&         pRandom,
    BlockPos const& pPos
)
{
    auto& level = pRegion.getLevel();
    if (level.isClientSide()) return;

    int      attemptCount    = 0;
    auto&    randomGenerator = pRandom.mRandom;
    BlockPos targetPos;

    // clang-format off
    while (true)
    {
        int verticalOffset = (randomGenerator.mObject._genRandInt32() & 7) - (randomGenerator.mObject._genRandInt32() & 7);
        targetPos.x = ((randomGenerator.mObject._genRandInt32() & 0xF) - (randomGenerator.mObject._genRandInt32() & 0xF)) + pPos.x;
        targetPos.z = (randomGenerator.mObject._genRandInt32() & 0xF) + pPos.z - (randomGenerator.mObject._genRandInt32() & 0xF);
        targetPos.y = (verticalOffset > pRegion.getMaxHeight() ? 0 : verticalOffset) + pPos.y;

        if (pRegion.isEmptyBlock(targetPos)) break;
        if (++attemptCount >= 1000) return;
    }
    // clang-format on

    auto beforeEvent = DragonEggBlockTeleportBeforeEvent(pRegion, pPos, pRandom, targetPos);
    ll::event::EventBus::getInstance().publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;

    // pRegion.postGameEvent(nullptr, GameEventRegistry::teleport, pPos, nullptr);
    auto x = pPos.x - targetPos.x;
    auto y = pPos.y - targetPos.y;
    auto z = pPos.z - targetPos.z;
    level.broadcastLocalEvent(
        pRegion,
        LevelEvent::ParticlesDragonEgg,
        pPos,
        abs(z) | ((abs(y) | (((((x >> 31) | (2 * ((y >> 31) | (2 * (z >> 31))))) << 8) | abs(x)) << 8)) << 8)
    );
    pRegion.setBlock(
        targetPos,
        BlockTypeRegistry::getDefaultBlockState(VanillaBlockTypeIds::DragonEgg, true),
        (int)BlockUpdateFlag::All,
        nullptr,
        nullptr
    );
    pRegion.removeBlock(pPos);
    ll::event::EventBus::getInstance().publish(
        DragonEggBlockTeleportAfterEvent(pRegion, pPos, pRandom, targetPos)
    );
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class DragonEggBlockTeleportBeforeEventEmitter
    : public ll::event::Emitter<emitterFactory1, DragonEggBlockTeleportBeforeEvent>
{
    ll::memory::HookRegistrar<DragonEggBlockTeleportEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<DragonEggBlockTeleportBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class DragonEggBlockTeleportAfterEventEmitter
    : public ll::event::Emitter<emitterFactory2, DragonEggBlockTeleportAfterEvent>
{
    ll::memory::HookRegistrar<DragonEggBlockTeleportEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<DragonEggBlockTeleportAfterEventEmitter>();
}
} // namespace iListenAttentively::World