#include "ila/event/minecraft/server/SendPacketEvent.h"
#include "ila/base/Gloabl.h"
#include <ll/api/service/Bedrock.h>
#include <mc/network/ServerNetworkHandler.h>

namespace ila::mc::inline server
{

void SendPacketBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["packetSender"] = reinterpret_cast<uintptr_t>(&getPacketSender());
    nbt["packet"]       = reinterpret_cast<uintptr_t>(&getPacket());
    nbt["broadcast"]    = getIsBroadcast();
    nbt["player"]       = reinterpret_cast<uintptr_t>(getPlayer().as_ptr());
}
LoopbackPacketSender&      SendPacketBeforeEvent::getPacketSender() const { return mPacketSender; }
Packet&                    SendPacketBeforeEvent::getPacket() const { return mPacket; }
bool const&                SendPacketBeforeEvent::getIsBroadcast() const { return mIsBroadcast; }
optional_ref<ServerPlayer> SendPacketBeforeEvent::getPlayer() const { return mPlayer; }

void SendPacketAfterEvent::serialize(CompoundTag& nbt) const
{
    Event::serialize(nbt);
    nbt["packetSender"] = reinterpret_cast<uintptr_t>(&getPacketSender());
    nbt["packet"]       = reinterpret_cast<uintptr_t>(&getPacket());
    nbt["broadcast"]    = getIsBroadcast();
    nbt["player"]       = reinterpret_cast<uintptr_t>(getPlayer().as_ptr());
}
LoopbackPacketSender&      SendPacketAfterEvent::getPacketSender() const { return mPacketSender; }
Packet const&              SendPacketAfterEvent::getPacket() const { return mPacket; }
bool const&                SendPacketAfterEvent::getIsBroadcast() const { return mIsBroadcast; }
optional_ref<ServerPlayer> SendPacketAfterEvent::getPlayer() const { return mPlayer; }

LL_TYPE_INSTANCE_HOOK(
    SendPacketEventHook1,
    HookPriority::Normal,
    LoopbackPacketSender,
    &LoopbackPacketSender::$sendToClient,
    void,
    UserEntityIdentifierComponent const* pUser,
    Packet const&                        pPacket
)
{
    optional_ref<ServerPlayer> player = std::nullopt;
    ll::service::getServerNetworkHandler().and_then([&pUser, &player](ServerNetworkHandler& handler) -> bool {
        player = handler._getServerPlayer(pUser->mNetworkId, pUser->mClientSubId);
        return true;
    });
    auto beforeEvent = SendPacketBeforeEvent(*this, const_cast<Packet&>(pPacket), false, player);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pUser, pPacket);
    LLEventBus.publish(SendPacketAfterEvent(*this, pPacket, false, player));
}

LL_TYPE_INSTANCE_HOOK(
    SendPacketEventHook2,
    HookPriority::Normal,
    LoopbackPacketSender,
    &LoopbackPacketSender::$sendToClient,
    void,
    NetworkIdentifier const& pUser,
    Packet const&            pPacket,
    SubClientId              pId
)
{
    optional_ref<ServerPlayer> player = std::nullopt;
    ll::service::getServerNetworkHandler().and_then(
        [&pUser, &pId, &player](ServerNetworkHandler& handler) -> bool {
            player = handler._getServerPlayer(pUser, pId);
            return true;
        }
    );
    auto beforeEvent = SendPacketBeforeEvent(*this, const_cast<Packet&>(pPacket), false, player);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pUser, pPacket, pId);
    LLEventBus.publish(SendPacketAfterEvent(*this, pPacket, false, player));
}

LL_TYPE_INSTANCE_HOOK(
    SendPacketEventHook3,
    HookPriority::Normal,
    LoopbackPacketSender,
    &LoopbackPacketSender::$sendBroadcast,
    void,
    Packet const& pPacket
)
{
    auto beforeEvent = SendPacketBeforeEvent(*this, const_cast<Packet&>(pPacket), true, std::nullopt);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pPacket);
    LLEventBus.publish(SendPacketAfterEvent(*this, pPacket, true, std::nullopt));
}

LL_TYPE_INSTANCE_HOOK(
    SendPacketEventHook4,
    HookPriority::Normal,
    LoopbackPacketSender,
    &LoopbackPacketSender::$sendBroadcast,
    void,
    NetworkIdentifier const& pUser,
    SubClientId              pId,
    Packet const&            pPacket
)
{
    auto beforeEvent = SendPacketBeforeEvent(*this, const_cast<Packet&>(pPacket), true, std::nullopt);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pUser, pId, pPacket);
    LLEventBus.publish(SendPacketAfterEvent(*this, pPacket, true, std::nullopt));
}

Event_Hook_Factory(SendPacket, <SendPacketEventHook1, SendPacketEventHook2, SendPacketEventHook3, SendPacketEventHook4>);

} // namespace ila::mc::inline server