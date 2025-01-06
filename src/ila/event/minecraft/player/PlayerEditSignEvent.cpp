#include "ila/event/minecraft/player/PlayerEditSignEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/network/NetworkBlockPosition.h>
#include <mc/network/Packet/BlockActorDataPacket.h>
#include <mc/network/ServerNetworkHandler.h>
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/block/actor/SignBlockActor.h>

namespace ila::mc::inline player
{

void PlayerEditSignBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"]  = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["side"] = magic_enum::enum_name(getTextSide());
    nbt["text"] = getText();
}
void PlayerEditSignBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getPos().x = nbt["pos"][0];
    getPos().y = nbt["pos"][1];
    getPos().z = nbt["pos"][2];
    getText()  = nbt["text"].get<StringTag>();
}
BlockPos&           PlayerEditSignBeforeEvent::getPos() const { return mPos; }
SignTextSide const& PlayerEditSignBeforeEvent::getTextSide() const { return mTextSide; }
StringTag&          PlayerEditSignBeforeEvent::getText() const { return mText; }

void PlayerEditSignAfterEvent::serialize(CompoundTag& nbt) const
{
    ServerPlayerEvent::serialize(nbt);
    nbt["pos"]  = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["side"] = magic_enum::enum_name(getTextSide());
    nbt["text"] = getText();
}
BlockPos const&     PlayerEditSignAfterEvent::getPos() const { return mPos; }
SignTextSide const& PlayerEditSignAfterEvent::getTextSide() const { return mTextSide; }
StringTag const&    PlayerEditSignAfterEvent::getText() const { return mText; }

LL_TYPE_INSTANCE_HOOK(
    PlayerEditSignEventHook,
    HookPriority::Normal,
    ServerNetworkHandler,
    &ServerNetworkHandler::$handle,
    void,
    NetworkIdentifier const&              pSource,
    std::shared_ptr<BlockActorDataPacket> pPacket
)
{
    if (pPacket == nullptr || !pPacket->mData->contains("id", Tag::Type::String)
        || (*pPacket->mData)["id"] != "Sign")
        return origin(pSource, pPacket);

    auto* player = thisFor<NetEventCallback>()->_getServerPlayer(pSource, pPacket->mClientSubId);
    if (!player) return origin(pSource, pPacket);

    auto* blockActor =
        static_cast<SignBlockActor*>(player->getDimensionBlockSource().getBlockEntity(pPacket->mPos));
    if (blockActor == nullptr) return origin(pSource, pPacket);

    bool frontEdit = false;
    bool backEdit  = false;

    if (blockActor->getMessage(SignTextSide::Front) != pPacket->mData.get()["FrontText"]["Text"])
    {
        frontEdit        = true;
        auto beforeEvent = PlayerEditSignBeforeEvent(
            *player,
            pPacket->mPos,
            (*pPacket->mData)["FrontText"]["Text"].get<StringTag>(),
            SignTextSide::Front
        );
        LLEventBus.publish(beforeEvent);
        if (beforeEvent.isCancelled()) return;
    }
    if (blockActor->getMessage(SignTextSide::Back) != pPacket->mData.get()["BackText"]["Text"])
    {
        backEdit         = true;
        auto beforeEvent = PlayerEditSignBeforeEvent(
            *player,
            pPacket->mPos,
            (*pPacket->mData)["BackText"]["Text"].get<StringTag>(),
            SignTextSide::Back
        );
        LLEventBus.publish(beforeEvent);
        if (beforeEvent.isCancelled()) return;
    }

    origin(pSource, pPacket);

    if (frontEdit)
    {
        LLEventBus.publish(PlayerEditSignAfterEvent(
            *player,
            pPacket->mPos.get(),
            pPacket->mData.get()["FrontText"]["Text"].get<StringTag>(),
            SignTextSide::Front
        ));
    }
    if (backEdit)
    {
        LLEventBus.publish(PlayerEditSignAfterEvent(
            *player,
            pPacket->mPos.get(),
            pPacket->mData.get()["BackText"]["Text"].get<StringTag>(),
            SignTextSide::Back
        ));
    }
}

Event_Hook_Factory(PlayerEditSign, <PlayerEditSignEventHook>);

} // namespace ila::mc::inline player