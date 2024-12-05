#include "ila/event/minecraft/player/PlayerEditSignEvent.h"
#include <mc/network/ServerNetworkHandler.h>
#include <mc/network/Packet/BlockActorDataPacket.h>
#include <mc/world/level/block/actor/SignBlockActor.h>

namespace ila::mc::inline player
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
    NetworkIdentifier const&              pSource,
    std::shared_ptr<BlockActorDataPacket> pPacket
)
{
    // clang-format off
    if (
        pPacket == nullptr 
        || !pPacket->mData.contains("id", Tag::Type::String)
        || pPacket->mData.at("id").get<StringTag>() != "Sign"
    ) return origin(pSource, pPacket);

    auto player = getServerPlayer(pSource, pPacket->mClientSubId);
    if (!player.has_value()) return origin(pSource, pPacket);

    auto* blockActor = (SignBlockActor*)player->getDimensionBlockSource().getBlockEntity(pPacket->mPos);
    if (blockActor == nullptr) return origin(pSource, pPacket);

    bool frontEdit = false;
    bool backEdit  = false;

    if (blockActor->getMessage(SignTextSide::Front) != pPacket->mData["FrontText"]["Text"])
    {
        frontEdit        = true;
        auto beforeEvent = PlayerEditSignBeforeEvent(*player, pPacket->mPos, pPacket->mData["FrontText"]["Text"].get<StringTag>(), SignTextSide::Front);
        eventBus.publish(beforeEvent);
        if (beforeEvent.isCancelled()) return;
    }
    if (blockActor->getMessage(SignTextSide::Back) != pPacket->mData["BackText"]["Text"])
    {
        backEdit         = true;
        auto beforeEvent = PlayerEditSignBeforeEvent(*player, pPacket->mPos, pPacket->mData["BackText"]["Text"].get<StringTag>(), SignTextSide::Back);
        eventBus.publish(beforeEvent);
        if (beforeEvent.isCancelled()) return;
    }

    origin(pSource, pPacket);

    if (frontEdit)
        eventBus.publish(PlayerEditSignAfterEvent(*player, pPacket->mPos, pPacket->mData["FrontText"]["Text"].get<StringTag>(), SignTextSide::Front));
    if (backEdit)
        eventBus.publish(PlayerEditSignAfterEvent(*player, pPacket->mPos, pPacket->mData["BackText"]["Text"].get<StringTag>(), SignTextSide::Back));
    // clang-format on
}

Event_Factory(PlayerEditSign, <PlayerEditSignEventHook>);

} // namespace ila::mc::inline player