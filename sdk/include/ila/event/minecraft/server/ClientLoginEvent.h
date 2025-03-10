#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <mc/network/NetworkIdentifier.h>
#include <mc/network/ServerNetworkHandler.h>
#include <mc/platform/UUID.h>

namespace ila::mc::inline server
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

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ServerNetworkHandler const& serverNetworkHandler() const;
    ILNDAPI NetworkIdentifier const&    networkIdentifier() const;
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

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ServerNetworkHandler const& serverNetworkHandler() const;
    ILNDAPI NetworkIdentifier const&    networkIdentifier() const;
    ILNDAPI mce::UUID const& uuid() const;
    ILNDAPI std::string const& serverAuthXuid() const;
    ILNDAPI std::string const& clientAuthXuid() const;
    ILNDAPI std::string const& realName() const;
    ILNDAPI std::string const& ipAndPort() const;
    ILNDAPI std::string ip() const;
    ILNDAPI std::string port() const;
    ILAPI void          disConnectClient(std::string reason = "") const;
};

} // namespace ila::mc::inline server