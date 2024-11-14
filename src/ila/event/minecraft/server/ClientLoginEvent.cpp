#include "ClientLoginEvent.h"
#include <ll/api/service/Bedrock.h>
#include <mc/certificates/ExtendedCertificate.h>
#include <mc/network/packet/LoginPacket.h>


namespace ila::mc::inline server
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
    HookPriority::Normal,
    ServerNetworkHandler,
    "?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVLoginPacket@@@Z",
    void,
    NetworkIdentifier const& pSource,
    LoginPacket const&       pPacket
)
{
    auto beforeEvent = ClientLoginBeforeEvent(*this, pSource);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pSource, pPacket);
    auto* cert           = pPacket.mConnectionRequest->getCertificate();
    auto  uuid           = ExtendedCertificate::getIdentity(*cert);
    auto  serverAuthXuid = ExtendedCertificate::getXuid(*cert, false);
    auto  clientAuthXuid = ExtendedCertificate::getXuid(*cert, true);
    auto  realName       = ExtendedCertificate::getIdentityName(*cert);
    auto  ipAndPort      = pSource.getIPAndPort();
    eventBus.publish(
        ClientLoginAfterEvent(*this, pSource, uuid, serverAuthXuid, clientAuthXuid, realName, ipAndPort)
    );
}

Event_Factory(ClientLogin, <ClientLoginEventHook>);

} // namespace ila::mc::inline server