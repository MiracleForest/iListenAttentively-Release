#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <mc/world/level/GameType.h>

namespace ila::mc::inline server
{
class ServerPongBeforeEvent final : public ll::event::Cancellable<ll::event::Event>
{
protected:
    std::string&              mMotd;
    int&                      mProtocolVersion;
    std::string&              mNetworkVersion;
    int&                      mPlayerCount;
    int&                      mMaxPlayerCount;
    std::string&              mGuid;
    std::string&              mLevelName;
    GameType&                 mGameMode;
    ushort&                   mLocalPort;
    ushort&                   mLocalPortV6;
    std::vector<std::string>& mOther;

public:
    constexpr explicit ServerPongBeforeEvent(
        std::string&              motd,
        int&                      protocolVersion,
        std::string&              networkVersion,
        int&                      playerCount,
        int&                      maxPlayerCount,
        std::string&              guid,
        std::string&              levelName,
        GameType&                 gameMode,
        ushort&                   localPort,
        ushort&                   localPortV6,
        std::vector<std::string>& other
    )
        : mMotd(motd)
        , mProtocolVersion(protocolVersion)
        , mNetworkVersion(networkVersion)
        , mPlayerCount(playerCount)
        , mMaxPlayerCount(maxPlayerCount)
        , mGuid(guid)
        , mLevelName(levelName)
        , mGameMode(gameMode)
        , mLocalPort(localPort)
        , mLocalPortV6(localPortV6)
        , mOther(other)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI std::string& motd() const;
    ILNDAPI int&         protocolVersion() const;
    ILNDAPI std::string& networkVersion() const;
    ILNDAPI int&         playerCount() const;
    ILNDAPI int&         maxPlayerCount() const;
    ILNDAPI std::string& guid() const;
    ILNDAPI std::string& levelName() const;
    ILNDAPI GameType&    gameMode() const;
    ILNDAPI ushort&      localPort() const;
    ILNDAPI ushort&      localPortV6() const;
    ILNDAPI std::vector<std::string>& other() const;
}; // class ServerPongEvent

class ServerPongAfterEvent final : public ll::event::Event
{
protected:
    std::string const&       mMotd;
    int const&               mProtocolVersion;
    std::string const&       mNetworkVersion;
    int const&               mPlayerCount;
    int const&               mMaxPlayerCount;
    std::string const&       mGuid;
    std::string const&       mLevelName;
    GameType const&          mGameMode;
    ushort const&            mLocalPort;
    ushort const&            mLocalPortV6;
    std::vector<std::string> mOther;

public:
    constexpr explicit ServerPongAfterEvent(
        std::string const&              motd,
        int const&                      protocolVersion,
        std::string&                    networkVersion,
        int const&                      playerCount,
        int const&                      maxPlayerCount,
        std::string const&              guid,
        std::string const&              levelName,
        GameType const&                 gameMode,
        ushort const&                   localPort,
        ushort const&                   localPortV6,
        std::vector<std::string> const& other
    )
        : mMotd(motd)
        , mProtocolVersion(protocolVersion)
        , mNetworkVersion(networkVersion)
        , mPlayerCount(playerCount)
        , mMaxPlayerCount(maxPlayerCount)
        , mGuid(guid)
        , mLevelName(levelName)
        , mGameMode(gameMode)
        , mLocalPort(localPort)
        , mLocalPortV6(localPortV6)
        , mOther(other)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI std::string const& motd() const;
    ILNDAPI int const&         protocolVersion() const;
    ILNDAPI std::string const& networkVersion() const;
    ILNDAPI int const&         playerCount() const;
    ILNDAPI int const&         maxPlayerCount() const;
    ILNDAPI std::string const& guid() const;
    ILNDAPI std::string const& levelName() const;
    ILNDAPI GameType const&    gameMode() const;
    ILNDAPI ushort const&      localPort() const;
    ILNDAPI ushort const&      localPortV6() const;
    ILNDAPI std::vector<std::string> const& other() const;
}; // class ServerPongEvent
} // namespace ila::mc::inline server