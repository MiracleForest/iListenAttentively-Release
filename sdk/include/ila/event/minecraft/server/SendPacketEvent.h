#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <mc/deps/core/utility/optional_ref.h>

// clang-format off
class LoopbackPacketSender;
class Packet;
class ServerPlayer;
// clang-format on

namespace ila::mc::inline server
{
class SendPacketBeforeEvent final : public ll::event::Cancellable<ll::event::Event>
{
protected:
    LoopbackPacketSender&      mPacketSender;
    Packet&                    mPacket;
    bool const&                mIsBroadcast;
    optional_ref<ServerPlayer> mPlayer;

public:
    constexpr explicit SendPacketBeforeEvent(
        LoopbackPacketSender&      packetSender,
        Packet&                    packet,
        bool const&                isBroadcast,
        optional_ref<ServerPlayer> player
    )
        : mPacketSender(packetSender)
        , mPacket(packet)
        , mIsBroadcast(isBroadcast)
        , mPlayer(player)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI LoopbackPacketSender& packetSender() const;
    ILNDAPI Packet&               packet() const;
    ILNDAPI bool const&           isBroadcast() const;
    ILNDAPI optional_ref<ServerPlayer> player() const;
}; // class SendPacketEvent

class SendPacketAfterEvent final : public ll::event::Event
{
protected:
    LoopbackPacketSender&      mPacketSender;
    Packet const&              mPacket;
    bool const&                mIsBroadcast;
    optional_ref<ServerPlayer> mPlayer;

public:
    constexpr explicit SendPacketAfterEvent(
        LoopbackPacketSender&      packetSender,
        Packet const&              packet,
        bool const&                isBroadcast,
        optional_ref<ServerPlayer> player
    )
        : mPacketSender(packetSender)
        , mPacket(packet)
        , mIsBroadcast(isBroadcast)
        , mPlayer(player)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI LoopbackPacketSender& packetSender() const;
    ILNDAPI Packet const&         packet() const;
    ILNDAPI bool const&           isBroadcast() const;
    ILNDAPI optional_ref<ServerPlayer> player() const;
}; // class SendPacketEvent
} // namespace ila::mc::inline server