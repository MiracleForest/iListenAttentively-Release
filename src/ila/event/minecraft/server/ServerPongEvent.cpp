#include "ila/event/minecraft/server/ServerPongEvent.h"
#include "ila/base/Gloabl.h"
#include <ll/api/Versions.h>
#include <mc/deps/raknet/RNS2_SendParameters.h>
#include <mc/deps/raknet/RNS2_Windows_Linux_360.h>
#include <mc/deps/raknet/SystemAddress.h>

namespace ila::mc::inline server
{

void ServerPongBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["motd"]            = getMotd();
    nbt["protocolVersion"] = getProtocolVersion();
    nbt["networkVersion"]  = getNetworkVersion();
    nbt["playerCount"]     = getPlayerCount();
    nbt["maxPlayerCount"]  = getMaxPlayerCount();
    nbt["guid"]            = getGuid();
    nbt["levelName"]       = getLevelName();
    nbt["gameMode"]        = magic_enum::enum_name(getGameMode());
    nbt["localPort"]       = getLocalPort();
    nbt["localPortV6"]     = getLocalPortV6();
    nbt["others"]          = ListTag {};
    for (auto& other : getOther()) { nbt["others"].push_back(other); }
}
void ServerPongBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getMotd()            = nbt["motd"];
    getProtocolVersion() = nbt["protocolVersion"];
    getNetworkVersion()  = nbt["networkVersion"];
    getPlayerCount()     = nbt["playerCount"];
    getMaxPlayerCount()  = nbt["maxPlayerCount"];
    getGuid()            = nbt["guid"];
    getLevelName()       = nbt["levelName"];
    getGameMode() = magic_enum::enum_cast<GameType>(nbt["gameMode"].get<StringTag>()).value_or(getGameMode());
    getLocalPort()   = nbt["localPort"];
    getLocalPortV6() = nbt["localPortV6"];
    getOther().clear();
    for (auto& other : nbt["others"].get<ListTag>()) { getOther().push_back(other); }
}
std::string&              ServerPongBeforeEvent::getMotd() const { return mMotd; }
int&                      ServerPongBeforeEvent::getProtocolVersion() const { return mProtocolVersion; }
std::string&              ServerPongBeforeEvent::getNetworkVersion() const { return mNetworkVersion; }
int&                      ServerPongBeforeEvent::getPlayerCount() const { return mPlayerCount; }
int&                      ServerPongBeforeEvent::getMaxPlayerCount() const { return mMaxPlayerCount; }
std::string&              ServerPongBeforeEvent::getGuid() const { return mGuid; }
std::string&              ServerPongBeforeEvent::getLevelName() const { return mLevelName; }
GameType&                 ServerPongBeforeEvent::getGameMode() const { return mGameMode; }
ushort&                   ServerPongBeforeEvent::getLocalPort() const { return mLoaclPort; }
ushort&                   ServerPongBeforeEvent::getLocalPortV6() const { return mLoaclPortV6; }
std::vector<std::string>& ServerPongBeforeEvent::getOther() const { return mOther; }

void ServerPongAfterEvent::serialize(CompoundTag& nbt) const
{
    Event::serialize(nbt);
    nbt["motd"]            = getMotd();
    nbt["protocolVersion"] = getProtocolVersion();
    nbt["networkVersion"]  = getNetworkVersion();
    nbt["playerCount"]     = getPlayerCount();
    nbt["maxPlayerCount"]  = getMaxPlayerCount();
    nbt["guid"]            = getGuid();
    nbt["levelName"]       = getLevelName();
    nbt["gameMode"]        = magic_enum::enum_name(getGameMode());
    nbt["localPort"]       = getLocalPort();
    nbt["localPortV6"]     = getLocalPortV6();
}
std::string const&              ServerPongAfterEvent::getMotd() const { return mMotd; }
int const&                      ServerPongAfterEvent::getProtocolVersion() const { return mProtocolVersion; }
std::string const&              ServerPongAfterEvent::getNetworkVersion() const { return mNetworkVersion; }
int const&                      ServerPongAfterEvent::getPlayerCount() const { return mPlayerCount; }
int const&                      ServerPongAfterEvent::getMaxPlayerCount() const { return mMaxPlayerCount; }
std::string const&              ServerPongAfterEvent::getGuid() const { return mGuid; }
std::string const&              ServerPongAfterEvent::getLevelName() const { return mLevelName; }
GameType const&                 ServerPongAfterEvent::getGameMode() const { return mGameMode; }
ushort const&                   ServerPongAfterEvent::getLocalPort() const { return mLoaclPort; }
ushort const&                   ServerPongAfterEvent::getLocalPortV6() const { return mLoaclPortV6; }
std::vector<std::string> const& ServerPongAfterEvent::getOther() const { return mOther; }

LL_STATIC_HOOK(
    ServerPongEventHook,
    HookPriority::Normal,
    &RakNet::RNS2_Windows_Linux_360::Send_Windows_Linux_360NoVDP,
    int,
    int                          pRns2Socket,
    RakNet::RNS2_SendParameters* pSendParameters,
    char const*                  pFile,
    uint                         pLine
)
{
    if (pSendParameters->mUnk98c838.as<char*>()[0] == 28)
    {
        constexpr static int head_size = sizeof(char) + sizeof(std::uint64_t) + sizeof(std::uint64_t) + 16;
        const char*          data      = pSendParameters->mUnk98c838.as<char*>();
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
        GameType    mGameType       = magic_enum::enum_cast<GameType>(parts[8]).value_or(GameType::Survival);
        ushort      mLoaclPort      = static_cast<ushort>(std::stoi(parts[10]));
        ushort      mLoaclPortV6    = static_cast<ushort>(std::stoi(parts[11]));
        std::vector<std::string> mOther = { "LeviLamina", ll::getLoaderVersion().to_string() };
        for (size_t i = 13; i < parts.size(); i++) { mOther.push_back(parts[i]); }

        auto beforeEvent = ServerPongBeforeEvent(
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
            mOther
        );
        LLEventBus.publish(beforeEvent);
        if (beforeEvent.isCancelled()) { return 133; }

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
        for (auto& other : mOther) { text += other + ";"; }

        std::vector<char> packet;
        packet.reserve(256);
        packet.insert(packet.end(), data, data + head_size);
        strlen = text.length();
        packet.push_back(static_cast<char>((strlen >> 8) & 0xFF));
        packet.push_back(static_cast<char>(strlen & 0xFF));
        packet.insert(packet.end(), text.begin(), text.end());
        pSendParameters->mUnk98c838.as<char*>() = packet.data();
        pSendParameters->mUnke627d8.as<int>()   = static_cast<int>(packet.size());

        auto result = origin(pRns2Socket, pSendParameters, pFile, pLine);
        LLEventBus.publish(ServerPongAfterEvent(
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
            mOther
        ));
        return result;
    }
    return origin(pRns2Socket, pSendParameters, pFile, pLine);
}

Event_Hook_Factory(ServerPong, <ServerPongEventHook>);

} // namespace ila::mc::inline server