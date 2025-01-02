#include "ila/event/minecraft/player/PlayerOpenContainerEvent.h"
#include "ila/event/minecraft/server/SendPacketEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/network/NetworkBlockPosition.h>
#include <mc/network/packet/ContainerOpenPacket.h>

namespace ila::mc::inline player
{

void PlayerOpenContainerBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["containerBlockPos"] =
        ListTag { getContainerBlockPos().x, getContainerBlockPos().y, getContainerBlockPos().z };
    nbt["containerId"]      = static_cast<schar>(getContainerId());
    nbt["containerType"]    = magic_enum::enum_name(getContainerType());
    nbt["containerActorId"] = getContainerActorId().rawID;
}
void PlayerOpenContainerBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getContainerBlockPos().x = nbt["containerBlockPos"][0ull].get<IntTag>();
    getContainerBlockPos().y = nbt["containerBlockPos"][1ull].get<IntTag>();
    getContainerBlockPos().z = nbt["containerBlockPos"][2ull].get<IntTag>();
    getContainerId()         = static_cast<ContainerID>(nbt["containerId"].get<ByteTag>().data);
    getContainerType()       = magic_enum::enum_cast<ContainerType>(nbt["containerType"].get<StringTag>())
                             .value_or(getContainerType());
    getContainerActorId().rawID = nbt["containerActorId"];
}
BlockPos&      PlayerOpenContainerBeforeEvent::getContainerBlockPos() const { return mPos; }
ContainerID&   PlayerOpenContainerBeforeEvent::getContainerId() const { return mContainerId; }
ContainerType& PlayerOpenContainerBeforeEvent::getContainerType() const { return mContainerType; }
ActorUniqueID& PlayerOpenContainerBeforeEvent::getContainerActorId() const { return mContainerActorId; }

void PlayerOpenContainerAfterEvent::serialize(CompoundTag& nbt) const
{
    ServerPlayerEvent::serialize(nbt);
    nbt["containerBlockPos"] =
        ListTag { getContainerBlockPos().x, getContainerBlockPos().y, getContainerBlockPos().z };
    nbt["containerId"]      = static_cast<schar>(getContainerId());
    nbt["containerType"]    = magic_enum::enum_name(getContainerType());
    nbt["containerActorId"] = getContainerActorId().rawID;
}
BlockPos const&      PlayerOpenContainerAfterEvent::getContainerBlockPos() const { return mPos; }
ContainerID const&   PlayerOpenContainerAfterEvent::getContainerId() const { return mContainerId; }
ContainerType const& PlayerOpenContainerAfterEvent::getContainerType() const { return mContainerType; }
ActorUniqueID const& PlayerOpenContainerAfterEvent::getContainerActorId() const { return mContainerActorId; }

Event_Listener_Factory(PlayerOpenContainerBefore)
{
    nextTick([this]() -> void { // Prevent deadlock
        mListeners.emplace_back(LLEventBus.emplaceListener<ila::mc::server::SendPacketBeforeEvent>(
            [](ila::mc::server::SendPacketBeforeEvent& event) -> void {
                if (event.getPacket().getId() != MinecraftPacketIds::ContainerOpen || event.getIsBroadcast()
                    || !event.getPlayer().has_value())
                {
                    return;
                }
                auto& packet      = static_cast<ContainerOpenPacket&>(event.getPacket());
                auto  beforeEvent = PlayerOpenContainerBeforeEvent(
                    *event.getPlayer(),
                    *packet.mPos,
                    packet.mContainerId,
                    packet.mType,
                    *packet.mEntityUniqueID
                );
                LLEventBus.publish(beforeEvent);
                if (beforeEvent.isCancelled())
                {
                    event.cancel();
                    event.getPlayer()->doDeleteContainerManager(false);
                }
            }
        ));
    });
}

Event_Listener_Factory(PlayerOpenContainerAfter)
{
    nextTick([this]() -> void { // Prevent deadlock
        mListeners.emplace_back(LLEventBus.emplaceListener<ila::mc::server::SendPacketAfterEvent>(
            [](ila::mc::server::SendPacketAfterEvent& event) -> void {
                if (event.getPacket().getId() != MinecraftPacketIds::ContainerOpen || event.getIsBroadcast()
                    || !event.getPlayer().has_value())
                {
                    return;
                }
                auto& packet = static_cast<ContainerOpenPacket const&>(event.getPacket());
                LLEventBus.publish(PlayerOpenContainerAfterEvent(
                    *event.getPlayer(),
                    *packet.mPos,
                    packet.mContainerId,
                    packet.mType,
                    *packet.mEntityUniqueID
                ));
            }
        ));
    });
}

} // namespace ila::mc::inline player