#include "ServerPongEvent.h"
#include <mc/deps/raknet/SystemAddress.h>

namespace ila::mc::inline server
{

std::string& ServerPongBeforeEvent::getMotd() const { return mMotd; }
int&         ServerPongBeforeEvent::getProtocolVersion() const { return mProtocolVersion; }
std::string& ServerPongBeforeEvent::getNetworkVersion() const { return mNetworkVersion; }
int&         ServerPongBeforeEvent::getPlayerCount() const { return mPlayerCount; }
int&         ServerPongBeforeEvent::getMaxPlayerCount() const { return mMaxPlayerCount; }
std::string& ServerPongBeforeEvent::getGuid() const { return mGuid; }
std::string& ServerPongBeforeEvent::getLevelName() const { return mLevelName; }
GameType&    ServerPongBeforeEvent::getGameMode() const { return mGameMode; }
ushort&      ServerPongBeforeEvent::getLocalPort() const { return mLoaclPort; }
ushort&      ServerPongBeforeEvent::getLocalPortV6() const { return mLoaclPortV6; }

std::string const& ServerPongAfterEvent::getMotd() const { return mMotd; }
int const&         ServerPongAfterEvent::getProtocolVersion() const { return mProtocolVersion; }
std::string const& ServerPongAfterEvent::getNetworkVersion() const { return mNetworkVersion; }
int const&         ServerPongAfterEvent::getPlayerCount() const { return mPlayerCount; }
int const&         ServerPongAfterEvent::getMaxPlayerCount() const { return mMaxPlayerCount; }
std::string const& ServerPongAfterEvent::getGuid() const { return mGuid; }
std::string const& ServerPongAfterEvent::getLevelName() const { return mLevelName; }
GameType const&    ServerPongAfterEvent::getGameMode() const { return mGameMode; }
ushort const&      ServerPongAfterEvent::getLocalPort() const { return mLoaclPort; }
ushort const&      ServerPongAfterEvent::getLocalPortV6() const { return mLoaclPortV6; }
int&               ServerPongAfterEvent::getResult() const { return mResult; }

struct RNS2_SendParameters
{
    char*                 data;
    int                   length;
    RakNet::SystemAddress system_address;
    int                   ttl;
};

LL_STATIC_HOOK(
    ServerPongEventHook,
    HookPriority::Normal,
    "?Send_Windows_Linux_360NoVDP@RNS2_Windows_Linux_360@RakNet@@KAHHPEAURNS2_SendParameters@2@PEBDI@Z",
    int,
    int                  pRns2Socket,
    RNS2_SendParameters* pSendParameters,
    char const*          pFile,
    uint                 pLine
)
{
    if (pSendParameters->data[0] == 28)
    {
        constexpr static int head_size = sizeof(char) + sizeof(std::uint64_t) + sizeof(std::uint64_t) + 16;
        const char*          data      = pSendParameters->data;
        std::size_t          strlen    = data[head_size] << 8 | data[head_size + 1];
        if (strlen == 0) { return origin(pRns2Socket, pSendParameters, pFile, pLine); }
        std::istringstream       iss(std::string({ data + head_size + 2, strlen }));
        std::string              tmp;
        std::vector<std::string> parts;
        while (std::getline(iss, tmp, ';')) { parts.push_back(tmp); }
        if (parts.size() != 13) { return origin(pRns2Socket, pSendParameters, pFile, pLine); }

        std::string motd            = parts[1];
        int         protocolVersion = std::stoi(parts[2]);
        std::string networkVersion  = parts[3];
        int         playerCount     = std::stoi(parts[4]);
        int         maxPlayerCount  = std::stoi(parts[5]);
        std::string guid            = parts[6];
        std::string levelName       = parts[7];
        auto        gameType        = magic_enum::enum_cast<GameType>(parts[8]);
        if (!gameType.has_value()) { return origin(pRns2Socket, pSendParameters, pFile, pLine); }
        GameType mGameType    = gameType.value();
        ushort   mLoaclPort   = static_cast<ushort>(std::stoi(parts[10]));
        ushort   mLoaclPortV6 = static_cast<ushort>(std::stoi(parts[11]));

        eventBus.publish(ServerPongBeforeEvent(
            motd,
            protocolVersion,
            networkVersion,
            playerCount,
            maxPlayerCount,
            guid,
            levelName,
            mGameType,
            mLoaclPort,
            mLoaclPortV6
        ));

        std::string text = fmt::format(
            "MCPE;{};{};{};{};{};{};{};{};1;{};{};0;",
            motd,
            protocolVersion,
            networkVersion,
            playerCount,
            maxPlayerCount,
            guid,
            levelName,
            magic_enum::enum_name(mGameType),
            mLoaclPort,
            mLoaclPortV6
        );

        std::vector<char> packet;
        packet.reserve(256);
        packet.insert(packet.end(), data, data + head_size);
        strlen = text.length();
        packet.push_back(static_cast<char>((strlen >> 8) & 0xFF));
        packet.push_back(static_cast<char>(strlen & 0xFF));
        packet.insert(packet.end(), text.begin(), text.end());
        pSendParameters->data   = packet.data();
        pSendParameters->length = static_cast<int>(packet.size());

        auto result = origin(pRns2Socket, pSendParameters, pFile, pLine);
        eventBus.publish(ServerPongAfterEvent(
            motd,
            protocolVersion,
            networkVersion,
            playerCount,
            maxPlayerCount,
            guid,
            levelName,
            mGameType,
            mLoaclPort,
            mLoaclPortV6,
            result
        ));
        return result;
    }
    return origin(pRns2Socket, pSendParameters, pFile, pLine);
}

Event_Factory(ServerPong, <ServerPongEventHook>);

} // namespace ila::mc::inline server