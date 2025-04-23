#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>

// clang-format off
class LoopbackPacketSender;
class NetworkIdentifier;
class ServerPlayer;
class Packet;
template <typename T>
class optional_ref;
// clang-format on

namespace ila::mc::inline server
{
class ReceivePacketEvent final : public ll::event::Cancellable<ll::event::Event>
{
protected:
    Packet&            mPacket;
    NetworkIdentifier& mNetworkIdentifier;

public:
    constexpr explicit ReceivePacketEvent(Packet& packet, NetworkIdentifier& networkIdentifier)
        : mPacket(packet)
        , mNetworkIdentifier(networkIdentifier)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI Packet&            packet() const;
    ILNDAPI NetworkIdentifier& networkIdentifier() const;
    ILNDAPI optional_ref<ServerPlayer> player() const;
}; // class ReceivePacketEvent
} // namespace ila::mc::inline server