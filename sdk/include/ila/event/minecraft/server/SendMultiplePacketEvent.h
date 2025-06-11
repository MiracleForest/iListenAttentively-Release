#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <mc/common/SubClientId.h>
#include <mc/deps/core/utility/optional_ref.h>

// clang-format off
class NetworkSystem;
class Packet;
class ServerPlayer;
struct NetworkIdentifierWithSubId;
// clang-format on

namespace ila::mc::inline server
{
class ISendMultiplePacketBeforeEvent : public ll::event::Cancellable<ll::event::Event>
{
private:
    NetworkSystem&                                 mNetworkSystem;
    Packet&                                        mPacket;
    std::vector<NetworkIdentifierWithSubId> const& mNetworkIdentifiers;

public:
    constexpr explicit ISendMultiplePacketBeforeEvent(
        NetworkSystem&                                 networkSystem,
        Packet&                                        packet,
        std::vector<NetworkIdentifierWithSubId> const& networkIdentifiers
    )
        : Cancellable()
        , mNetworkSystem(networkSystem)
        , mPacket(packet)
        , mNetworkIdentifiers(networkIdentifiers)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI NetworkSystem& networkSystem() const;
    ILNDAPI Packet&        packet() const;
    ILNDAPI std::vector<NetworkIdentifierWithSubId> const& networkIdentifiers() const;
    ILNDAPI optional_ref<ServerPlayer> player(NetworkIdentifierWithSubId const& networkIdentifier) const;
};

template<std::derived_from<Packet> PacketType = Packet>
class SendMultiplePacketBeforeEvent final : public ISendMultiplePacketBeforeEvent
{
public:
    constexpr explicit SendMultiplePacketBeforeEvent(
        NetworkSystem&                                 networkSystem,
        PacketType&                                    packet,
        std::vector<NetworkIdentifierWithSubId> const& networkIdentifiers
    )
        : ISendMultiplePacketBeforeEvent(networkSystem, packet, networkIdentifiers)
    {
    }

    PacketType& packet() const { return static_cast<PacketType&>(ISendMultiplePacketBeforeEvent::packet()); }
};

class ISendMultiplePacketAfterEvent : public ll::event::Event
{
private:
    NetworkSystem&                                 mNetworkSystem;
    Packet const&                                  mPacket;
    std::vector<NetworkIdentifierWithSubId> const& mNetworkIdentifiers;

public:
    constexpr explicit ISendMultiplePacketAfterEvent(
        NetworkSystem&                                 networkSystem,
        Packet const&                                  packet,
        std::vector<NetworkIdentifierWithSubId> const& networkIdentifiers
    )
        : Event()
        , mNetworkSystem(networkSystem)
        , mPacket(packet)
        , mNetworkIdentifiers(networkIdentifiers)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI NetworkSystem& networkSystem() const;
    ILNDAPI Packet const&  packet() const;
    ILNDAPI std::vector<NetworkIdentifierWithSubId> const& networkIdentifiers() const;
    ILNDAPI optional_ref<ServerPlayer> player(NetworkIdentifierWithSubId const& networkIdentifier) const;
};

template<std::derived_from<Packet> PacketType = Packet>
class SendMultiplePacketAfterEvent final : public ISendMultiplePacketAfterEvent
{
public:
    constexpr explicit SendMultiplePacketAfterEvent(
        NetworkSystem&                                 networkSystem,
        PacketType const&                              packet,
        std::vector<NetworkIdentifierWithSubId> const& networkIdentifiers
    )
        : ISendMultiplePacketAfterEvent(networkSystem, packet, networkIdentifiers)
    {
    }

    PacketType const& packet() const
    {
        return static_cast<PacketType const&>(ISendMultiplePacketAfterEvent::packet());
    }
};
} // namespace ila::mc::inline server
