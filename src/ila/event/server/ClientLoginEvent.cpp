#include "ClientLoginEvent.h"
#include <ll/api/service/Bedrock.h>
#include <mc/certificates/ExtendedCertificate.h>
#include <mc/network/packet/LoginPacket.h>


namespace ila::inline server
{

ServerNetworkHandler const& ClientLoginBeforeEvent::getServerNetworkHandler() const
{
    return mServerNetworkHandler;
}
NetworkIdentifier const& ClientLoginBeforeEvent::getNetworkIdentifier() const { return mNetworkIdentifier; }

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
    ll::service::getServerNetworkHandler()
        ->disconnectClient(getNetworkIdentifier(), Connection::DisconnectFailReason::Kicked, reason, false);
}

LL_TYPE_INSTANCE_HOOK(
    ClientLoginEventHook,
    ll::memory::HookPriority::Normal,
    ServerNetworkHandler,
    "?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVLoginPacket@@@Z",
    void,
    NetworkIdentifier const& source,
    LoginPacket const&       packet
)
{
    auto beforeEvent = ClientLoginBeforeEvent(*this, source);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(source, packet);
    auto* cert           = packet.mConnectionRequest->getCertificate();
    auto  uuid           = ExtendedCertificate::getIdentity(*cert);
    auto  serverAuthXuid = ExtendedCertificate::getXuid(*cert, false);
    auto  clientAuthXuid = ExtendedCertificate::getXuid(*cert, true);
    auto  realName       = ExtendedCertificate::getIdentityName(*cert);
    auto  ipAndPort      = source.getIPAndPort();
    eventBus.publish(
        ClientLoginAfterEvent(*this, source, uuid, serverAuthXuid, clientAuthXuid, realName, ipAndPort)
    );
}

Event_Factory(ClientLogin, <ClientLoginEventHook>);

} // namespace ila::inline server