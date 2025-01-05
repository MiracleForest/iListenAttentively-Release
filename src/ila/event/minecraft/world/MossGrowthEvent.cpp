#include "ila/event/minecraft/world/MossGrowthEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/level/WorldBlockTarget.h>
#include <mc/world/level/levelgen/feature/VegetationPatchFeature.h>

namespace ila::mc::inline world
{

void MossGrowthBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"]     = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["random"]  = serializeRefObj(getRandom());
    nbt["xRadius"] = getXRadius();
    nbt["zRadius"] = getZRadius();
}
void MossGrowthBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getPos().x   = nbt["pos"][0];
    getPos().y   = nbt["pos"][1];
    getPos().z   = nbt["pos"][2];
    getXRadius() = nbt["xRadius"];
    getZRadius() = nbt["zRadius"];
}
BlockPos& MossGrowthBeforeEvent::getPos() const { return mPos; };
Random&   MossGrowthBeforeEvent::getRandom() const { return mRandom; };
int&      MossGrowthBeforeEvent::getXRadius() const { return mXRadius; };
int&      MossGrowthBeforeEvent::getZRadius() const { return mZRadius; };

void MossGrowthAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["pos"]        = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["random"]     = serializeRefObj(getRandom());
    nbt["xRadius"]    = getXRadius();
    nbt["zRadius"]    = getZRadius();
    nbt["targetPoss"] = ListTag {};
    for (auto const& pos : getTargetPoss()) { nbt["targetPoss"].push_back(ListTag { pos.x, pos.y, pos.z }); }
}
void MossGrowthAfterEvent::deserialize(CompoundTag const& nbt)
{
    WorldEvent::deserialize(nbt);
    getTargetPoss().clear();
    for (auto& pos : nbt["targetPoss"].get<ListTag>())
    {
        getTargetPoss().push_back(
            { static_cast<int>(pos[0]), static_cast<int>(pos[1]), static_cast<int>(pos[2]) }
        );
    }
}
BlockPos const&        MossGrowthAfterEvent::getPos() const { return mPos; };
Random const&          MossGrowthAfterEvent::getRandom() const { return mRandom; };
int const&             MossGrowthAfterEvent::getXRadius() const { return mXRadius; };
int const&             MossGrowthAfterEvent::getZRadius() const { return mZRadius; };
std::vector<BlockPos>& MossGrowthAfterEvent::getTargetPoss() const { return mTargetPoss; };

LL_TYPE_INSTANCE_HOOK(
    MossGrowthEventHook,
    HookPriority::Normal,
    VegetationPatchFeature,
    &VegetationPatchFeature::_placeGroundPatch,
    std::vector<BlockPos>,
    IBlockWorldGenAPI& pTarget,
    Random&            pRandom,
    BlockPos const&    pPos,
    int                pXRadius,
    int                pZRadius
)
{
    auto& region = static_cast<WorldBlockTarget&>(pTarget).mBlockSource;
    auto  beforeEvent =
        MossGrowthBeforeEvent(region, const_cast<BlockPos&>(pPos), pRandom, pXRadius, pZRadius);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return {}; }
    auto result = origin(pTarget, pRandom, pPos, pXRadius, pZRadius);
    if (!result.empty())
    {
        LLEventBus.publish(MossGrowthAfterEvent(region, pPos, pRandom, pXRadius, pZRadius, result));
    }
    return result;
}

Event_Hook_Factory(MossGrowth, <MossGrowthEventHook>);

} // namespace ila::mc::inline world