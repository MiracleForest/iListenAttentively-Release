#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <mc/deps/core/utility/optional_ref.h>

// clang-format off
class NetworkIdentifier;
class ServerPlayer;
class Packet;
// clang-format on

namespace ila::mc::inline server
{

class IReceivePacketBeforeEvent : public ll::event::Cancellable<ll::event::Event>
{
protected:
    Packet&                  mPacket;
    NetworkIdentifier const& mNetworkIdentifier;

public:
    constexpr explicit IReceivePacketBeforeEvent(Packet& packet, NetworkIdentifier const& networkIdentifier)
        : mPacket(packet)
        , mNetworkIdentifier(networkIdentifier)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI Packet&                  packet() const;
    ILNDAPI NetworkIdentifier const& networkIdentifier() const;
    ILNDAPI optional_ref<ServerPlayer> player() const;
}; // class ReceivePacketEvent

template<std::derived_from<Packet> PacketType = Packet>
class ReceivePacketBeforeEvent final : public IReceivePacketBeforeEvent
{
public:
    constexpr explicit ReceivePacketBeforeEvent(
        PacketType&              packet,
        NetworkIdentifier const& networkIdentifier
    )
        : IReceivePacketBeforeEvent(packet, networkIdentifier)
    {
    }

    PacketType& packet() const { return static_cast<PacketType&>(IReceivePacketBeforeEvent::packet()); }
};

class IReceivePacketAfterEvent : public ll::event::Cancellable<ll::event::Event>
{
protected:
    Packet const&            mPacket;
    NetworkIdentifier const& mNetworkIdentifier;

public:
    constexpr explicit IReceivePacketAfterEvent(
        Packet const&            packet,
        NetworkIdentifier const& networkIdentifier
    )
        : mPacket(packet)
        , mNetworkIdentifier(networkIdentifier)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI Packet const&            packet() const;
    ILNDAPI NetworkIdentifier const& networkIdentifier() const;
    ILNDAPI optional_ref<ServerPlayer> player() const;
}; // class ReceivePacketEvent

template<std::derived_from<Packet> PacketType = Packet>
class ReceivePacketAfterEvent final : public IReceivePacketAfterEvent
{
public:
    constexpr explicit ReceivePacketAfterEvent(
        PacketType const&        packet,
        NetworkIdentifier const& networkIdentifier
    )
        : IReceivePacketAfterEvent(packet, networkIdentifier)
    {
    }

    PacketType const& packet() const
    {
        return static_cast<PacketType const&>(IReceivePacketAfterEvent::packet());
    }
};

} // namespace ila::mc::inline server