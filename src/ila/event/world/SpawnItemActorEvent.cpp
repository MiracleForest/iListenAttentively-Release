#include "SpawnItemActorEvent.h"
#include <mc/world/level/Spawner.h>

namespace ila::inline world
{

Vec3&      SpawnItemActorBeforeEvent::getPos() const { return mPos; }
ItemStack& SpawnItemActorBeforeEvent::getItem() const { return mItem; }
Actor*&    SpawnItemActorBeforeEvent::getSpawner() const { return mSpawner; }
int&       SpawnItemActorBeforeEvent::getThrowTime() const { return mThrowTime; }

Vec3 const&      SpawnItemActorAfterEvent::getPos() const { return mPos; }
ItemStack const& SpawnItemActorAfterEvent::getItem() const { return mItem; }
Actor* const&    SpawnItemActorAfterEvent::getSpawner() const { return mSpawner; }
int const&       SpawnItemActorAfterEvent::getThrowTime() const { return mThrowTime; }
ItemActor*&      SpawnItemActorAfterEvent::getItemActor() const { return mItemActor; }

LL_TYPE_INSTANCE_HOOK(
    SpawnItemActorEventHook,
    HookPriority::Normal,
    Spawner,
    "?spawnItem@Spawner@@QEAAPEAVItemActor@@AEAVBlockSource@@AEBVItemStack@@PEAVActor@@AEBVVec3@@H@Z",
    ItemActor*,
    BlockSource& pRegion,
    ItemStack&   pItem,
    Actor*       pSpawner,
    Vec3&        pPos,
    int          pThrowTime
)
{
    auto beforeEvent = SpawnItemActorBeforeEvent(pRegion, pPos, pItem, pSpawner, pThrowTime);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return nullptr;
    auto* result = origin(pRegion, pItem, pSpawner, pPos, pThrowTime);
    eventBus.publish(SpawnItemActorAfterEvent(pRegion, pPos, pItem, pSpawner, pThrowTime, result));
    return result;
}

Event_Factory(SpawnItemActor, <SpawnItemActorEventHook>);

} // namespace ila::inline world