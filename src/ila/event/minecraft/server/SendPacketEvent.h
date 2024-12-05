#include "ila/Global.h"
#include <mc/network/packet/Packet.h>
#include <mc/server/LoopbackPacketSender.h>

namespace ila::mc::inline server
{
class SendPacketBeforeEvent final : public ll::event::Cancellable<ll::event::Event>
{
protected:
    Packet&               mPacket;
    ServerPlayer*         mPlayer;
    bool const&           mIsBroadcast;
    LoopbackPacketSender& mPacketSender;

public:
    constexpr explicit SendPacketBeforeEvent(
        Packet&               packet,
        ServerPlayer*         player,
        bool const&           isBroadcast,
        LoopbackPacketSender& packetSender
    )
        : mPacket(packet)
        , mPlayer(player)
        , mIsBroadcast(isBroadcast)
        , mPacketSender(packetSender)
    {
    }

    ILAPI Packet&               getPacket() const;
    ILAPI ServerPlayer*         getPlayer() const;
    ILAPI bool const&           getIsBroadcast() const;
    ILAPI LoopbackPacketSender& getPacketSender() const;
}; // class SendPacketEvent

class SendPacketAfterEvent final : public ll::event::Event
{
protected:
    Packet const&         mPacket;
    ServerPlayer*         mPlayer;
    bool const&           mIsBroadcast;
    LoopbackPacketSender& mPacketSender;

public:
    constexpr explicit SendPacketAfterEvent(
        Packet const&         packet,
        ServerPlayer*         player,
        bool const&           isBroadcast,
        LoopbackPacketSender& packetSender
    )
        : mPacket(packet)
        , mPlayer(player)
        , mIsBroadcast(isBroadcast)
        , mPacketSender(packetSender)
    {
    }

    ILAPI Packet const&         getPacket() const;
    ILAPI ServerPlayer*         getPlayer() const;
    ILAPI bool const&           getIsBroadcast() const;
    ILAPI LoopbackPacketSender& getPacketSender() const;
}; // class SendPacketEvent
} // namespace ila::mc::inline server