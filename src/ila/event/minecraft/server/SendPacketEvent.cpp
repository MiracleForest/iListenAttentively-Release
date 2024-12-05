#include "ila/event/minecraft/server/SendPacketEvent.h"
#include <ll/api/service/Bedrock.h>
#include <mc/network/ServerNetworkHandler.h>

namespace ila::mc::inline server
{

Packet&               SendPacketBeforeEvent::getPacket() const { return mPacket; }
ServerPlayer*         SendPacketBeforeEvent::getPlayer() const { return mPlayer; }
bool const&           SendPacketBeforeEvent::getIsBroadcast() const { return mIsBroadcast; }
LoopbackPacketSender& SendPacketBeforeEvent::getPacketSender() const { return mPacketSender; }

Packet const&         SendPacketAfterEvent::getPacket() const { return mPacket; }
ServerPlayer*         SendPacketAfterEvent::getPlayer() const { return mPlayer; }
bool const&           SendPacketAfterEvent::getIsBroadcast() const { return mIsBroadcast; }
LoopbackPacketSender& SendPacketAfterEvent::getPacketSender() const { return mPacketSender; }

LL_TYPE_INSTANCE_HOOK(
    SendPacketEventHook1,
    HookPriority::Normal,
    LoopbackPacketSender,
    "?sendToClient@LoopbackPacketSender@@UEAAXPEBVUserEntityIdentifierComponent@@AEBVPacket@@@Z",
    void,
    UserEntityIdentifierComponent const* pUser,
    Packet&                              pPacket
)
{
    ServerPlayer* player = nullptr;
    ll::service::getServerNetworkHandler().and_then([&pUser, &player](ServerNetworkHandler& handler) -> bool {
        player = handler._getServerPlayer(pUser->mNetworkId, pUser->mClientSubId);
        return true;
    });
    auto beforeEvent = SendPacketBeforeEvent(pPacket, player, false, *this);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pUser, pPacket);
    eventBus.publish(SendPacketAfterEvent(pPacket, player, false, *this));
}

LL_TYPE_INSTANCE_HOOK(
    SendPacketEventHook2,
    HookPriority::Normal,
    LoopbackPacketSender,
    "?sendToClient@LoopbackPacketSender@@UEAAXAEBVNetworkIdentifier@@AEBVPacket@@W4SubClientId@@@Z",
    void,
    NetworkIdentifier const& pUser,
    Packet&                  pPacket,
    SubClientId              pId
)
{
    ServerPlayer* player = nullptr;
    ll::service::getServerNetworkHandler().and_then(
        [&pUser, &pId, &player](ServerNetworkHandler& handler) -> bool {
            player = handler._getServerPlayer(pUser, pId);
            return true;
        }
    );
    auto beforeEvent = SendPacketBeforeEvent(pPacket, player, false, *this);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pUser, pPacket, pId);
    eventBus.publish(SendPacketAfterEvent(pPacket, player, false, *this));
}

LL_TYPE_INSTANCE_HOOK(
    SendPacketEventHook3,
    HookPriority::Normal,
    LoopbackPacketSender,
    "?sendBroadcast@LoopbackPacketSender@@UEAAXAEBVPacket@@@Z",
    void,
    Packet& pPacket
)
{
    auto beforeEvent = SendPacketBeforeEvent(pPacket, nullptr, true, *this);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pPacket);
    eventBus.publish(SendPacketAfterEvent(pPacket, nullptr, true, *this));
}

LL_TYPE_INSTANCE_HOOK(
    SendPacketEventHook4,
    HookPriority::Normal,
    LoopbackPacketSender,
    "?sendBroadcast@LoopbackPacketSender@@UEAAXAEBVNetworkIdentifier@@W4SubClientId@@AEBVPacket@@@Z",
    void,
    NetworkIdentifier const& pUser,
    SubClientId              pId,
    Packet&                  pPacket
)
{
    auto beforeEvent = SendPacketBeforeEvent(pPacket, nullptr, true, *this);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pUser, pId, pPacket);
    eventBus.publish(SendPacketAfterEvent(pPacket, nullptr, true, *this));
}

Event_Factory(SendPacket, <SendPacketEventHook1, SendPacketEventHook2, SendPacketEventHook3, SendPacketEventHook4>);

} // namespace ila::mc::inline server