#include "ila/event/minecraft/player/PlayerInteractEntityEvent.h"
#include "ila/base/Gloabl.h"

namespace ila::mc::inline player
{

void PlayerInteractEntityBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["target"] = reinterpret_cast<uintptr_t>(&getTarget());
    nbt["pos"]    = ListTag { getPos().x, getPos().y, getPos().z };
}
void PlayerInteractEntityBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getPos().x = nbt["pos"][0ull].get<FloatTag>();
    getPos().y = nbt["pos"][1ull].get<FloatTag>();
    getPos().z = nbt["pos"][2ull].get<FloatTag>();
}
Actor& PlayerInteractEntityBeforeEvent::getTarget() const { return mTarget; }
Vec3&  PlayerInteractEntityBeforeEvent::getPos() const { return mPos; }

void PlayerInteractEntityAfterEvent::serialize(CompoundTag& nbt) const
{
    PlayerEvent::serialize(nbt);
    nbt["target"] = reinterpret_cast<uintptr_t>(&getTarget());
    nbt["pos"]    = ListTag { getPos().x, getPos().y, getPos().z };
}
Actor const& PlayerInteractEntityAfterEvent::getTarget() const { return mTarget; }
Vec3 const&  PlayerInteractEntityAfterEvent::getPos() const { return mPos; }

LL_TYPE_INSTANCE_HOOK(
    PlayerInteractEntityEventHook,
    HookPriority::Normal,
    Player,
    &Player::interact,
    bool,
    Actor&      pActor,
    Vec3 const& pLocation
)
{
    auto beforeEvent = PlayerInteractEntityBeforeEvent(*this, pActor, const_cast<Vec3&>(pLocation));
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return false; }
    auto result = origin(pActor, pLocation);
    if (result) { LLEventBus.publish(PlayerInteractEntityAfterEvent(*this, pActor, pLocation)); }
    return result;
}

Event_Hook_Factory(PlayerInteractEntity, <PlayerInteractEntityEventHook>);

} // namespace ila::mc::inline player