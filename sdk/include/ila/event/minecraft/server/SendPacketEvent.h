#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <mc/common/SubClientId.h>
#include <mc/deps/core/utility/optional_ref.h>

// clang-format off
class NetworkSystem;
class NetworkIdentifier;
class Packet;
class ServerPlayer;
// clang-format on

namespace ila::mc::inline server
{
class ISendPacketBeforeEvent : public ll::event::Cancellable<ll::event::Event>
{
private:
    NetworkSystem&           mNetworkSystem;
    Packet&                  mPacket;
    NetworkIdentifier const& mNetworkIdentifier;
    SubClientId&             mSenderSubId;

public:
    constexpr explicit ISendPacketBeforeEvent(
        NetworkSystem&           networkSystem,
        Packet&                  packet,
        NetworkIdentifier const& networkIdentifier,
        SubClientId&             senderSubId
    )
        : Cancellable()
        , mNetworkSystem(networkSystem)
        , mPacket(packet)
        , mNetworkIdentifier(networkIdentifier)
        , mSenderSubId(senderSubId)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI NetworkSystem&           networkSystem() const;
    ILNDAPI Packet&                  packet() const;
    ILNDAPI NetworkIdentifier const& networkIdentifier() const;
    ILNDAPI SubClientId&             senderSubId() const;
    ILNDAPI optional_ref<ServerPlayer> player() const;
};

template<std::derived_from<Packet> PacketType = Packet>
class SendPacketBeforeEvent final : public ISendPacketBeforeEvent
{
public:
    constexpr explicit SendPacketBeforeEvent(
        NetworkSystem&           networkSystem,
        PacketType&              packet,
        NetworkIdentifier const& networkIdentifier,
        SubClientId&             senderSubId
    )
        : ISendPacketBeforeEvent(networkSystem, packet, networkIdentifier, senderSubId)
    {
    }

    PacketType& packet() const { return static_cast<PacketType&>(ISendPacketBeforeEvent::packet()); }
};

class ISendPacketAfterEvent : public ll::event::Event
{
private:
    NetworkSystem&           mNetworkSystem;
    Packet const&            mPacket;
    NetworkIdentifier const& mNetworkIdentifier;
    SubClientId const&       mSenderSubId;

public:
    constexpr explicit ISendPacketAfterEvent(
        NetworkSystem&           networkSystem,
        Packet const&            packet,
        NetworkIdentifier const& networkIdentifier,
        SubClientId const&       senderSubId
    )
        : Event()
        , mNetworkSystem(networkSystem)
        , mPacket(packet)
        , mNetworkIdentifier(networkIdentifier)
        , mSenderSubId(senderSubId)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI NetworkSystem&           networkSystem() const;
    ILNDAPI Packet const&            packet() const;
    ILNDAPI NetworkIdentifier const& networkIdentifier() const;
    ILNDAPI SubClientId const&       senderSubId() const;
    ILNDAPI optional_ref<ServerPlayer> player() const;
};

template<std::derived_from<Packet> PacketType = Packet>
class SendPacketAfterEvent final : public ISendPacketAfterEvent
{
public:
    constexpr explicit SendPacketAfterEvent(
        NetworkSystem&           networkSystem,
        PacketType const&        packet,
        NetworkIdentifier const& networkIdentifier,
        SubClientId const&       senderSubId
    )
        : ISendPacketAfterEvent(networkSystem, packet, networkIdentifier, senderSubId)
    {
    }

    PacketType const& packet() const
    {
        return static_cast<PacketType const&>(ISendPacketAfterEvent::packet());
    }
};
} // namespace ila::mc::inline server
