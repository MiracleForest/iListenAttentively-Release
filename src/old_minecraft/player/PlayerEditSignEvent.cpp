#include "ila/event/minecraft/player/PlayerEditSignEvent.h"
#include <mc/server/ServerPlayer.h>
#include <mc/network/ServerNetworkHandler.h>
#include <mc/world/level/BlockPos.h>
#include <mc/network/NetworkBlockPosition.h>
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
    &ServerNetworkHandler::$handle,
    void,
    NetworkIdentifier const&              pSource,
    std::shared_ptr<BlockActorDataPacket> pPacket
)
{
    // clang-format off
    if (
        pPacket == nullptr 
        || !pPacket->mData->contains("id", Tag::Type::String)
        || pPacket->mData->at("id").get<StringTag>() != "Sign"
    ) return origin(pSource, pPacket);

    auto handle = static_cast<decltype(this)>(static_cast<NetEventCallback*>(this));
    auto player = handle->_getServerPlayer(pSource, pPacket->mClientSubId);
    if (!player) return origin(pSource, pPacket);

    auto* blockActor = static_cast<SignBlockActor*>(player->getDimensionBlockSource().getBlockEntity(pPacket->mPos.get()));
    if (blockActor == nullptr) return origin(pSource, pPacket);

    bool frontEdit = false;
    bool backEdit  = false;

    if (blockActor->getMessage(SignTextSide::Front) != pPacket->mData.get()["FrontText"]["Text"])
    {
        frontEdit        = true;
        auto beforeEvent = PlayerEditSignBeforeEvent(*player, pPacket->mPos.get(), pPacket->mData.get()["FrontText"]["Text"].get<StringTag>(), SignTextSide::Front);
        eventBus.publish(beforeEvent);
        if (beforeEvent.isCancelled()) return;
    }
    if (blockActor->getMessage(SignTextSide::Back) != pPacket->mData.get()["BackText"]["Text"])
    {
        backEdit         = true;
        auto beforeEvent = PlayerEditSignBeforeEvent(*player, pPacket->mPos.get(), pPacket->mData.get()["BackText"]["Text"].get<StringTag>(), SignTextSide::Back);
        eventBus.publish(beforeEvent);
        if (beforeEvent.isCancelled()) return;
    }

    origin(pSource, pPacket);

    if (frontEdit)
        eventBus.publish(PlayerEditSignAfterEvent(*player, pPacket->mPos.get(), pPacket->mData.get()["FrontText"]["Text"].get<StringTag>(), SignTextSide::Front));
    if (backEdit)
        eventBus.publish(PlayerEditSignAfterEvent(*player, pPacket->mPos.get(), pPacket->mData.get()["BackText"]["Text"].get<StringTag>(), SignTextSide::Back));
    // clang-format on
}

Event_Factory(PlayerEditSign, <PlayerEditSignEventHook>);

} // namespace ila::mc::inline player