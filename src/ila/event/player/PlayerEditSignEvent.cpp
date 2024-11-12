#include "PlayerEditSignEvent.h"
#include <mc/network/ServerNetworkHandler.h>
#include <mc/network/packet/BlockActorDataPacket.h>
#include <mc/world/level/block/actor/SignBlockActor.h>

namespace ila::inline player
{

BlockPos const&     PlayerEditSignBeforeEvent::getPos() const { return mPos; }
SignTextSide const& PlayerEditSignBeforeEvent::getTextSide() const { return mTextSide; }
StringTag&          PlayerEditSignBeforeEvent::getText() const { return mText; }

BlockPos const&     PlayerEditSignAfterEvent::getPos() const { return mPos; }
SignTextSide const& PlayerEditSignAfterEvent::getTextSide() const { return mTextSide; }
StringTag const&    PlayerEditSignAfterEvent::getText() const { return mText; }

LL_AUTO_TYPE_INSTANCE_HOOK(
    PlayerEditSignEventHook,
    HookPriority::Normal,
    ServerNetworkHandler,
    &ServerNetworkHandler::handle,
    void,
    NetworkIdentifier const&              source,
    std::shared_ptr<BlockActorDataPacket> packet
)
{
    // clang-format off
    if (
        packet == nullptr 
        || !packet->mData.contains("id", Tag::Type::String)
        || packet->mData.at("id").get<StringTag>() != "Sign"
    ) return origin(source, packet);

    auto player = getServerPlayer(source, packet->mClientSubId);
    if (!player.has_value()) return origin(source, packet);

    auto* blockActor = (SignBlockActor*)player->getDimensionBlockSource().getBlockEntity(packet->mPos);
    if (blockActor == nullptr) return origin(source, packet);

    bool frontEdit = false;
    bool backEdit  = false;

    if (blockActor->getMessage(SignTextSide::Front) != packet->mData["FrontText"]["Text"])
    {
        frontEdit        = true;
        auto beforeEvent = PlayerEditSignBeforeEvent(*player, packet->mPos, packet->mData["FrontText"]["Text"].get<StringTag>(), SignTextSide::Front);
        eventBus.publish(beforeEvent);
        if (beforeEvent.isCancelled()) return;
    }
    if (blockActor->getMessage(SignTextSide::Back) != packet->mData["BackText"]["Text"])
    {
        backEdit         = true;
        auto beforeEvent = PlayerEditSignBeforeEvent(*player, packet->mPos, packet->mData["BackText"]["Text"].get<StringTag>(), SignTextSide::Back);
        eventBus.publish(beforeEvent);
        if (beforeEvent.isCancelled()) return;
    }

    origin(source, packet);

    if (frontEdit)
        eventBus.publish(PlayerEditSignAfterEvent(*player, packet->mPos, packet->mData["FrontText"]["Text"].get<StringTag>(), SignTextSide::Front));
    if (backEdit)
        eventBus.publish(PlayerEditSignAfterEvent(*player, packet->mPos, packet->mData["BackText"]["Text"].get<StringTag>(), SignTextSide::Back));
    // clang-format on
}

Event_Factory(PlayerEditSign, <PlayerEditSignEventHook>);

} // namespace ila::inline player