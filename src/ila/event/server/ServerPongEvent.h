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

    ILAPI std::string& getMotd() const { return mMotd; }
    ILAPI int&         getProtocolVersion() const { return mProtocolVersion; }
    ILAPI std::string& getNetworkVersion() const { return mNetworkVersion; }
    ILAPI int&         getPlayerCount() const { return mPlayerCount; }
    ILAPI int&         getMaxPlayerCount() const { return mMaxPlayerCount; }
    ILAPI std::string& getGuid() const { return mGuid; }
    ILAPI std::string& getLevelName() const { return mLevelName; }
    ILAPI GameType&    getGameMode() const { return mGameMode; }
    ILAPI ushort&      getLocalPort() const { return mLoaclPort; }
    ILAPI ushort&      getLocalPortV6() const { return mLoaclPortV6; }
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

    ILAPI std::string const& getMotd() const { return mMotd; }
    ILAPI int const&         getProtocolVersion() const { return mProtocolVersion; }
    ILAPI std::string const& getNetworkVersion() const { return mNetworkVersion; }
    ILAPI int const&         getPlayerCount() const { return mPlayerCount; }
    ILAPI int const&         getMaxPlayerCount() const { return mMaxPlayerCount; }
    ILAPI std::string const& getGuid() const { return mGuid; }
    ILAPI std::string const& getLevelName() const { return mLevelName; }
    ILAPI GameType const&    getGameMode() const { return mGameMode; }
    ILAPI ushort const&      getLocalPort() const { return mLoaclPort; }
    ILAPI ushort const&      getLocalPortV6() const { return mLoaclPortV6; }
    ILAPI int&               getResult() const { return mResult; }
}; // class ServerPongEvent
} // namespace ila::inline server