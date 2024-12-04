#include "MossGrowthEvent.h"
#include <mc/world/level/WorldBlockTarget.h>
#include <mc/world/level/levelgen/feature/VegetationPatchFeature.h>

namespace ila::mc::inline world
{

BlockPos const&        MossGrowthBeforeEvent::getPos() const { return mPos; };
Random&                MossGrowthBeforeEvent::getRandom() const { return mRandom; };
std::vector<BlockPos>& MossGrowthBeforeEvent::getTargetPoss() const { return mTargetPoss; };

BlockPos const&              MossGrowthAfterEvent::getPos() const { return mPos; };
Random const&                MossGrowthAfterEvent::getRandom() const { return mRandom; };
std::vector<BlockPos> const& MossGrowthAfterEvent::getTargetPoss() const { return mTargetPoss; };

LL_AUTO_TYPE_INSTANCE_HOOK(
    MossGrowthEventHook,
    HookPriority::Normal,
    VegetationPatchFeature,
    &VegetationPatchFeature::_placeGroundPatch,
    std::vector<BlockPos>,
    IBlockWorldGenAPI& pTarget,
    Random&            pRandom,
    BlockPos const&    pPos,
    int                pA4,
    int                pA5
)
{
    auto  result      = origin(pTarget, pRandom, pPos, pA4, pA5);
    auto& region      = ((WorldBlockTarget&)pTarget).mBlockSource;
    auto  beforeEvent = MossGrowthBeforeEvent(region, pPos, pRandom, result);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return {};
    eventBus.publish(MossGrowthAfterEvent(region, pPos, pRandom, result));
    return result;
}

Event_Factory(MossGrowth, <MossGrowthEventHook>);

} // namespace ila::mc::inline world