#include "Global.h"
#include <mc/deps/core/mce/UUID.h>
#include <mc/network/NetworkIdentifier.h>
#include <mc/network/ServerNetworkHandler.h>

namespace ila::inline server
{

class ClientLoginBeforeEvent final : public ll::event::Cancellable<ll::event::Event>
{
protected:
    ServerNetworkHandler const& mServerNetworkHandler;
    NetworkIdentifier const&    mNetworkIdentifier;

public:
    constexpr explicit ClientLoginBeforeEvent(
        ServerNetworkHandler const& serverNetworkHandler,
        NetworkIdentifier const&    networkIdentifier
    )
        : Cancellable()
        , mServerNetworkHandler(serverNetworkHandler)
        , mNetworkIdentifier(networkIdentifier)
    {
    }

    ILAPI ServerNetworkHandler const& getServerNetworkHandler() const;
    ILAPI NetworkIdentifier const&    getNetworkIdentifier() const;
};

class ClientLoginAfterEvent final : public ll::event::Event
{
protected:
    ServerNetworkHandler const& mServerNetworkHandler;
    NetworkIdentifier const&    mNetworkIdentifier;
    mce::UUID const&            mUuid;
    std::string const&          mServerAuthXuid;
    std::string const&          mClientAuthXuid;
    std::string const&          mRealName;
    std::string const&          mIpAndPort;

public:
    constexpr explicit ClientLoginAfterEvent(
        ServerNetworkHandler const& serverNetworkHandler,
        NetworkIdentifier const&    networkIdentifier,
        mce::UUID const&            uuid,
        std::string const&          serverAuthXuid,
        std::string const&          clientAuthXuid,
        std::string const&          realName,
        std::string const&          ipAndPort
    )
        : mServerNetworkHandler(serverNetworkHandler)
        , mNetworkIdentifier(networkIdentifier)
        , mUuid(uuid)
        , mServerAuthXuid(serverAuthXuid)
        , mClientAuthXuid(clientAuthXuid)
        , mRealName(realName)
        , mIpAndPort(ipAndPort)
    {
    }

    ILAPI ServerNetworkHandler const& getServerNetworkHandler() const;
    ILAPI NetworkIdentifier const&    getNetworkIdentifier() const;
    ILAPI mce::UUID const& getUuid() const;
    ILAPI std::string const& getServerAuthXuid() const;
    ILAPI std::string const& getClientAuthXuid() const;
    ILAPI std::string const& getRealName() const;
    ILAPI std::string const& getIpAndPort() const;
    ILAPI std::string getIp() const;
    ILAPI std::string getPort() const;
    ILAPI void        disConnectClient(std::string reason = "") const;
};

} // namespace ila::inline server