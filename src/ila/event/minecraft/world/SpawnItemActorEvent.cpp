#include "ila/event/minecraft/world/SpawnItemActorEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/level/BedrockSpawner.h>

namespace ila::mc::inline world
{

void SpawnItemActorBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"]       = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["item"]      = serializeRefObj(getItem());
    nbt["spawner"]   = serializeRefObj(getSpawner());
    nbt["throwTime"] = getThrowTime();
}
void SpawnItemActorBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getPos().x     = nbt["pos"][0];
    getPos().y     = nbt["pos"][1];
    getPos().z     = nbt["pos"][2];
    getThrowTime() = nbt["throw_time"];
}
Vec3&      SpawnItemActorBeforeEvent::getPos() const { return mPos; }
ItemStack& SpawnItemActorBeforeEvent::getItem() const { return mItem; }
Actor*&    SpawnItemActorBeforeEvent::getSpawner() const { return mSpawner; }
int&       SpawnItemActorBeforeEvent::getThrowTime() const { return mThrowTime; }

void SpawnItemActorAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["pos"]       = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["item"]      = serializeRefObj(getItem());
    nbt["spawner"]   = serializeRefObj(getSpawner());
    nbt["throwtime"] = getThrowTime();
    nbt["itemActor"] = serializeRefObj(getItemActor());
}
Vec3 const&      SpawnItemActorAfterEvent::getPos() const { return mPos; }
ItemStack const& SpawnItemActorAfterEvent::getItem() const { return mItem; }
Actor* const&    SpawnItemActorAfterEvent::getSpawner() const { return mSpawner; }
int const&       SpawnItemActorAfterEvent::getThrowTime() const { return mThrowTime; }
ItemActor*&      SpawnItemActorAfterEvent::getItemActor() const { return mItemActor; }

LL_TYPE_INSTANCE_HOOK(
    SpawnItemActorEventHook,
    HookPriority::Normal,
    BedrockSpawner,
    &BedrockSpawner::$spawnItem,
    ItemActor*,
    BlockSource&     pRegion,
    ItemStack const& pItem,
    Actor*           pSpawner,
    Vec3 const&      pPos,
    int              pThrowTime
)
{
    auto beforeEvent = SpawnItemActorBeforeEvent(
        pRegion,
        const_cast<Vec3&>(pPos),
        const_cast<ItemStack&>(pItem),
        pSpawner,
        pThrowTime
    );
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return nullptr; }
    auto* result = origin(pRegion, pItem, pSpawner, pPos, pThrowTime);
    if (result != nullptr)
    {
        LLEventBus.publish(SpawnItemActorAfterEvent(pRegion, pPos, pItem, pSpawner, pThrowTime, result));
    }
    return result;
}

Event_Hook_Factory(SpawnItemActor, <SpawnItemActorEventHook>);

} // namespace ila::mc::inline world