#include "Global.h"
#include <mc/enums/GameType.h>

namespace ila::inline server
{
class ServerPongBeforeEvent final : public ll::event::Event
{
protected:
    std::string& mMotd;
    int&         mProtocolVersion;
    std::string& mNetworkVersion;
    int&         mPlayerCount;
    int&         mMaxPlayerCount;
    std::string& mGuid;
    std::string& mLevelName;
    GameType&    mGameMode;
    ushort&      mLoaclPort;
    ushort&      mLoaclPortV6;

public:
    constexpr explicit ServerPongBeforeEvent(
        std::string& motd,
        int&         protocolVersion,
        std::string& networkVersion,
        int&         playerCount,
        int&         maxPlayerCount,
        std::string& guid,
        std::string& levelName,
        GameType&    gameMode,
        ushort&      localPort,
        ushort&      localPortV6
    )
        : mMotd(motd)
        , mProtocolVersion(protocolVersion)
        , mNetworkVersion(networkVersion)
        , mPlayerCount(playerCount)
        , mMaxPlayerCount(maxPlayerCount)
        , mGuid(guid)
        , mLevelName(levelName)
        , mGameMode(gameMode)
        , mLoaclPort(localPort)
        , mLoaclPortV6(localPortV6)
    {
    }

    std::string& getMotd() const { return mMotd; }
    int&         getProtocolVersion() const { return mProtocolVersion; }
    std::string& getNetworkVersion() const { return mNetworkVersion; }
    int&         getPlayerCount() const { return mPlayerCount; }
    int&         getMaxPlayerCount() const { return mMaxPlayerCount; }
    std::string& getGuid() const { return mGuid; }
    std::string& getLevelName() const { return mLevelName; }
    GameType&    getGameMode() const { return mGameMode; }
    ushort&      getLocalPort() const { return mLoaclPort; }
    ushort&      getLocalPortV6() const { return mLoaclPortV6; }
}; // class ServerPongEvent

class ServerPongAfterEvent final : public ll::event::Event
{
protected:
    std::string const& mMotd;
    int const&         mProtocolVersion;
    std::string const& mNetworkVersion;
    int const&         mPlayerCount;
    int const&         mMaxPlayerCount;
    std::string const& mGuid;
    std::string const& mLevelName;
    GameType const&    mGameMode;
    ushort const&      mLoaclPort;
    ushort const&      mLoaclPortV6;
    int&               mResult;

public:
    constexpr explicit ServerPongAfterEvent(
        std::string const& motd,
        int const&         protocolVersion,
        std::string&       networkVersion,
        int const&         playerCount,
        int const&         maxPlayerCount,
        std::string const& guid,
        std::string const& levelName,
        GameType const&    gameMode,
        ushort const&      localPort,
        ushort const&      localPortV6,
        int&               result
    )
        : mMotd(motd)
        , mProtocolVersion(protocolVersion)
        , mNetworkVersion(networkVersion)
        , mPlayerCount(playerCount)
        , mMaxPlayerCount(maxPlayerCount)
        , mGuid(guid)
        , mLevelName(levelName)
        , mGameMode(gameMode)
        , mLoaclPort(localPort)
        , mLoaclPortV6(localPortV6)
        , mResult(result)
    {
    }

    std::string const& getMotd() const { return mMotd; }
    int const&         getProtocolVersion() const { return mProtocolVersion; }
    std::string const& getNetworkVersion() const { return mNetworkVersion; }
    int const&         getPlayerCount() const { return mPlayerCount; }
    int const&         getMaxPlayerCount() const { return mMaxPlayerCount; }
    std::string const& getGuid() const { return mGuid; }
    std::string const& getLevelName() const { return mLevelName; }
    GameType const&    getGameMode() const { return mGameMode; }
    ushort const&      getLocalPort() const { return mLoaclPort; }
    ushort const&      getLocalPortV6() const { return mLoaclPortV6; }
    int&               getResult() const { return mResult; }
}; // class ServerPongEvent
} // namespace ila::inline server