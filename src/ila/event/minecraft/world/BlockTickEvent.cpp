#include "ila/event/minecraft/world/BlockTickEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/level/block/Block.h>

namespace ila::mc::inline world
{

void BlockTickBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"]    = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["random"] = serializeRefObj(getRandom());
}
void BlockTickBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getPos().x = nbt["pos"][0];
    getPos().y = nbt["pos"][1];
    getPos().z = nbt["pos"][2];
}
BlockPos& BlockTickBeforeEvent::getPos() const { return mPos; }
Random&   BlockTickBeforeEvent::getRandom() const { return mRandom; }

void BlockTickAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["pos"]    = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["random"] = serializeRefObj(getRandom());
}
BlockPos const& BlockTickAfterEvent::getPos() const { return mPos; }
Random const&   BlockTickAfterEvent::getRandom() const { return mRandom; }

LL_TYPE_INSTANCE_HOOK(
    BlockTickEventHook,
    HookPriority::Normal,
    Block,
    &Block::randomTick,
    void,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    Random&         pRandom
)
{
    auto beforeEvent = BlockTickBeforeEvent(pRegion, const_cast<BlockPos&>(pPos), pRandom);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }
    origin(pRegion, pPos, pRandom);
    LLEventBus.publish(BlockTickAfterEvent(pRegion, pPos, pRandom));
}

Event_Hook_Factory(BlockTick, <BlockTickEventHook>);

} // namespace ila::mc::inline world