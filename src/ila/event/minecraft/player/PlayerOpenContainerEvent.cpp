#include "ila/event/minecraft/player/PlayerOpenContainerEvent.h"
#include "ila/event/minecraft/server/SendPacketEvent.h"
#include <mc/enums/MinecraftPacketIds.h>
#include <mc/network/packet/ContainerOpenPacket.h>

namespace ila::mc::inline player
{

BlockPos&      PlayerOpenContainerBeforeEvent::getContainerBlockPos() const { return mPos; }
ContainerID&   PlayerOpenContainerBeforeEvent::getContainerId() const { return mContainerId; }
ContainerType& PlayerOpenContainerBeforeEvent::getContainerType() const { return mContainerType; }
ActorUniqueID& PlayerOpenContainerBeforeEvent::getContainerActorId() const { return mContainerActorId; }

BlockPos const&      PlayerOpenContainerAfterEvent::getContainerBlockPos() const { return mPos; }
ContainerID const&   PlayerOpenContainerAfterEvent::getContainerId() const { return mContainerId; }
ContainerType const& PlayerOpenContainerAfterEvent::getContainerType() const { return mContainerType; }
ActorUniqueID const& PlayerOpenContainerAfterEvent::getContainerActorId() const { return mContainerActorId; }

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class PlayerOpenContainerBeforeEventEmitter
    : public ll::event::Emitter<emitterFactory1, PlayerOpenContainerBeforeEvent>
{
protected:
    ll::event::ListenerPtr mListener = nullptr;

public:
    PlayerOpenContainerBeforeEventEmitter()
    {
        mListener = eventBus.emplaceListener<ila::mc::server::SendPacketBeforeEvent>(
            [](ila::mc::server::SendPacketBeforeEvent& event) -> void {
                if (event.getPacket().getId() != MinecraftPacketIds::ContainerOpen || event.getIsBroadcast()
                    || event.getPlayer() == nullptr)
                    return;
                auto& packet      = (ContainerOpenPacket&)event.getPacket();
                auto  beforeEvent = PlayerOpenContainerBeforeEvent(
                    *event.getPlayer(),
                    packet.mPos,
                    packet.mContainerId,
                    packet.mType,
                    packet.mEntityUniqueID
                );
                eventBus.publish(beforeEvent);
                if (beforeEvent.isCancelled())
                {
                    event.cancel();
                    event.getPlayer()->doDeleteContainerManager(false);
                }
            }
        );
    }
    ~PlayerOpenContainerBeforeEventEmitter()
    {
        try
        {
            eventBus.removeListener(mListener);
        }
        catch (...)
        {
        }
    }
};
static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<PlayerOpenContainerBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class PlayerOpenContainerAfterEventEmitter
    : public ll::event::Emitter<emitterFactory2, PlayerOpenContainerAfterEvent>
{
protected:
    ll::event::ListenerPtr mListener = nullptr;

public:
    PlayerOpenContainerAfterEventEmitter()
    {
        mListener = eventBus.emplaceListener<ila::mc::server::SendPacketAfterEvent>(
            [](ila::mc::server::SendPacketAfterEvent& event) -> void {
                if (event.getPacket().getId() != MinecraftPacketIds::ContainerOpen || event.getIsBroadcast()
                    || event.getPlayer() == nullptr)
                    return;
                auto& packet = (ContainerOpenPacket&)event.getPacket();
                eventBus.publish(PlayerOpenContainerAfterEvent(
                    *event.getPlayer(),
                    packet.mPos,
                    packet.mContainerId,
                    packet.mType,
                    packet.mEntityUniqueID
                ));
            }
        );
    }
    ~PlayerOpenContainerAfterEventEmitter()
    {
        try
        {
            eventBus.removeListener(mListener);
        }
        catch (...)
        {
        }
    }
};
static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<PlayerOpenContainerAfterEventEmitter>();
};

} // namespace ila::mc::inline player