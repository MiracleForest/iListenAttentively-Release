#include "ila/event/minecraft/world/DragonEggBlockTeleportEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/deps/core/math/Random.h>
#include <mc/deps/core/math/Vec3.h>
#include <mc/world/events/gameevents/GameEventRegistry.h>
#include <mc/world/level/Level.h>
#include <mc/world/level/block/DragonEggBlock.h>
#include <mc/world/level/block/VanillaBlockTypeIds.h>
#include <mc/world/level/block/registry/BlockTypeRegistry.h>

namespace ila::mc::inline world
{

void DragonEggBlockTeleportBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"]       = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["random"]    = serializeRefObj(getRandom());
    nbt["targetPos"] = ListTag { getTargetPos().x, getTargetPos().y, getTargetPos().z };
}
void DragonEggBlockTeleportBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getTargetPos().x = nbt["targetPos"][0];
    getTargetPos().y = nbt["targetPos"][1];
    getTargetPos().z = nbt["targetPos"][2];
}
BlockPos const& DragonEggBlockTeleportBeforeEvent::getPos() const { return mPos; }
Random&         DragonEggBlockTeleportBeforeEvent::getRandom() const { return mRandom; }
BlockPos&       DragonEggBlockTeleportBeforeEvent::getTargetPos() const { return mTargetPos; }

void DragonEggBlockTeleportAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["pos"]       = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["random"]    = serializeRefObj(getRandom());
    nbt["targetPos"] = ListTag { getTargetPos().x, getTargetPos().y, getTargetPos().z };
}
BlockPos const& DragonEggBlockTeleportAfterEvent::getPos() const { return mPos; }
Random const&   DragonEggBlockTeleportAfterEvent::getRandom() const { return mRandom; }
BlockPos const& DragonEggBlockTeleportAfterEvent::getTargetPos() const { return mTargetPos; }

LL_STATIC_HOOK(
    DragonEggBlockTeleportEventHook,
    HookPriority::Low,
    &DragonEggBlock::_attemptTeleport,
    void,
    BlockSource&    pRegion,
    Random&         pRandom,
    BlockPos const& pPos
)
{
    auto& level = pRegion.getLevel();
    if (level.isClientSide()) { return; }

    int      attemptCount    = 0;
    auto&    randomGenerator = pRandom.mRandom;
    BlockPos targetPos;

    // clang-format off
    while (true)
    {
        int verticalOffset = (randomGenerator->mObject._genRandInt32() & 7) - (randomGenerator->mObject._genRandInt32() & 7);
        targetPos.x = ((randomGenerator->mObject._genRandInt32() & 0xF) - (randomGenerator->mObject._genRandInt32() & 0xF)) + pPos.x;
        targetPos.z = (randomGenerator->mObject._genRandInt32() & 0xF) + pPos.z - (randomGenerator->mObject._genRandInt32() & 0xF);
        targetPos.y = (verticalOffset > pRegion.getMaxHeight() ? 0 : verticalOffset) + pPos.y;

        if (pRegion.isEmptyBlock(targetPos)){ break;}
        if (++attemptCount >= 1000){ return;}
    }
    // clang-format on

    auto beforeEvent = DragonEggBlockTeleportBeforeEvent(pRegion, pPos, pRandom, targetPos);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }

    pRegion.postGameEvent(nullptr, GameEventRegistry::teleport(), pPos, nullptr);
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
        BlockTypeRegistry::getDefaultBlockState(VanillaBlockTypeIds::DragonEgg(), true),
        3 /* BlockUpdateFlag::All */,
        nullptr,
        nullptr
    );
    pRegion.removeBlock(pPos);
    LLEventBus.publish(DragonEggBlockTeleportAfterEvent(pRegion, pPos, pRandom, targetPos));
}

Event_Hook_Factory(DragonEggBlockTeleport, <DragonEggBlockTeleportEventHook>);

} // namespace ila::mc::inline world