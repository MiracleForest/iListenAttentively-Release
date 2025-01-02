#include "ila/event/minecraft/server/ClientLoginEvent.h"
#include "ila/base/Gloabl.h"
#include <ll/api/service/Bedrock.h>
#include <mc/certificates/ExtendedCertificate.h>
#include <mc/network/ConnectionRequest.h>
#include <mc/network/packet/LoginPacket.h>

namespace ila::mc::inline server
{

void ClientLoginBeforeEvent::serialize(CompoundTag& nbt) const {
    Cancellable::serialize(nbt);
    nbt["serverNetworkHandler"] = reinterpret_cast<uintptr_t>(&getServerNetworkHandler());
    nbt["networkIdentifier"] = reinterpret_cast<uintptr_t>(&getNetworkIdentifier());
}
ServerNetworkHandler const& ClientLoginBeforeEvent::getServerNetworkHandler() const
{
    return mServerNetworkHandler;
}
NetworkIdentifier const& ClientLoginBeforeEvent::getNetworkIdentifier() const { return mNetworkIdentifier; }

void ClientLoginAfterEvent::serialize(CompoundTag& nbt) const {
    Event::serialize(nbt);
    nbt["serverNetworkHandler"] = reinterpret_cast<uintptr_t>(&getServerNetworkHandler());
    nbt["networkIdentifier"] = reinterpret_cast<uintptr_t>(&getNetworkIdentifier());
    nbt["uuid"] = getUuid().asString();
    nbt["serverAuthXuid"] = getServerAuthXuid();
    nbt["clientAuthXuid"] = getClientAuthXuid();
    nbt["realName"] = getRealName();
    nbt["ipAndPort"] = getIpAndPort();
}
ServerNetworkHandler const& ClientLoginAfterEvent::getServerNetworkHandler() const
{
    return mServerNetworkHandler;
}
NetworkIdentifier const& ClientLoginAfterEvent::getNetworkIdentifier() const { return mNetworkIdentifier; }
mce::UUID const&         ClientLoginAfterEvent::getUuid() const { return mUuid; }
std::string const&       ClientLoginAfterEvent::getServerAuthXuid() const { return mServerAuthXuid; }
std::string const&       ClientLoginAfterEvent::getClientAuthXuid() const { return mClientAuthXuid; }
std::string const&       ClientLoginAfterEvent::getRealName() const { return mRealName; }
std::string const&       ClientLoginAfterEvent::getIpAndPort() const { return mIpAndPort; }
std::string              ClientLoginAfterEvent::getIp() const
{
    auto ipAndPort = getIpAndPort();
    return ipAndPort.substr(0, ipAndPort.find(":"));
}
std::string ClientLoginAfterEvent::getPort() const
{
    auto ipAndPort = getIpAndPort();
    return ipAndPort.substr(ipAndPort.find(":") + 1);
}
void ClientLoginAfterEvent::disConnectClient(std::string reason) const
{
    ll::service::getServerNetworkHandler()->disconnectClient(
        getNetworkIdentifier(),
        Connection::DisconnectFailReason::Kicked,
        reason,
        std::nullopt,
        false
    );
}

LL_TYPE_INSTANCE_HOOK(
    ClientLoginEventHook,
    HookPriority::Normal,
    ServerNetworkHandler,
    &ServerNetworkHandler::$handle,
    void,
    NetworkIdentifier const& pSource,
    LoginPacket const&       pPacket
)
{
    auto beforeEvent = ClientLoginBeforeEvent(*this, pSource);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pSource, pPacket);
    auto* cert = pPacket.mConnectionRequest->getCertificate();
    LLEventBus.publish(ClientLoginAfterEvent(
        *this,
        pSource,
        ExtendedCertificate::getIdentity(*cert),
        ExtendedCertificate::getXuid(*cert, false),
        ExtendedCertificate::getXuid(*cert, true),
        ExtendedCertificate::getIdentityName(*cert),
        pSource.getIPAndPort()
    ));
}

Event_Hook_Factory(ClientLogin, <ClientLoginEventHook>);

} // namespace ila::mc::inline server