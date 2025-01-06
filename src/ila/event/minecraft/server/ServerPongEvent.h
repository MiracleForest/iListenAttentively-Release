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
    ushort&                   mLoaclPort;
    ushort&                   mLoaclPortV6;
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
        , mLoaclPort(localPort)
        , mLoaclPortV6(localPortV6)
        , mOther(other)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI std::string& getMotd() const;
    ILNDAPI int&         getProtocolVersion() const;
    ILNDAPI std::string& getNetworkVersion() const;
    ILNDAPI int&         getPlayerCount() const;
    ILNDAPI int&         getMaxPlayerCount() const;
    ILNDAPI std::string& getGuid() const;
    ILNDAPI std::string& getLevelName() const;
    ILNDAPI GameType&    getGameMode() const;
    ILNDAPI ushort&      getLocalPort() const;
    ILNDAPI ushort&      getLocalPortV6() const;
    ILNDAPI std::vector<std::string>& getOther() const;
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
    ushort const&            mLoaclPort;
    ushort const&            mLoaclPortV6;
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
        , mLoaclPort(localPort)
        , mLoaclPortV6(localPortV6)
        , mOther(other)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI std::string const& getMotd() const;
    ILNDAPI int const&         getProtocolVersion() const;
    ILNDAPI std::string const& getNetworkVersion() const;
    ILNDAPI int const&         getPlayerCount() const;
    ILNDAPI int const&         getMaxPlayerCount() const;
    ILNDAPI std::string const& getGuid() const;
    ILNDAPI std::string const& getLevelName() const;
    ILNDAPI GameType const&    getGameMode() const;
    ILNDAPI ushort const&      getLocalPort() const;
    ILNDAPI ushort const&      getLocalPortV6() const;
    ILNDAPI std::vector<std::string> const& getOther() const;
}; // class ServerPongEvent
} // namespace ila::mc::inline server