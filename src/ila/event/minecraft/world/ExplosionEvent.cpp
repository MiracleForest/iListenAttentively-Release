#include "ila/event/minecraft/world/ExplosionEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/common/ActorUniqueID.h>
#include <mc/world/level/BlockPos.h>
#include <mc/deps/core/math/Vec3.h>

namespace ila::mc::inline world
{

void ExplosionBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"]    = ListTag { getExplosion().mPos->x, getExplosion().mPos->y, getExplosion().mPos->z };
    nbt["radius"] = getExplosion().mRadius;
    nbt["affectedBlocks"] = ListTag {};
    for (auto& blockPos : *getExplosion().mAffectedBlocks)
    {
        nbt["affectedBlocks"].push_back(ListTag { blockPos.x, blockPos.y, blockPos.z });
    }
    nbt["fire"]                           = getExplosion().mFire;
    nbt["breaking"]                       = getExplosion().mBreaking;
    nbt["allowUnderwater"]                = getExplosion().mAllowUnderwater;
    nbt["canToggleBlocks"]                = getExplosion().mCanToggleBlocks;
    nbt["damageScaling"]                  = getExplosion().mDamageScaling;
    nbt["ignoreBlockExplosionResistance"] = getExplosion().mIgnoreBlockExplosionResistance;
    nbt["particleType"]                   = magic_enum::enum_name(getExplosion().mParticleType);
    nbt["soundExplosionType"]             = magic_enum::enum_name(getExplosion().mSoundExplosionType);
    nbt["sourceId"]                       = getExplosion().mSourceID->rawID;
    nbt["maxResistance"]                  = getExplosion().mMaxResistance;
    if (getExplosion().mInWaterOverride->has_value())
    {
        nbt["inWaterOverride"] = getExplosion().mInWaterOverride->value();
    }
    if (getExplosion().mTotalDamageOverride->has_value())
    {
        nbt["totalDamageOverride"] = getExplosion().mTotalDamageOverride->value();
    }
    nbt["knockbackScaling"] = getExplosion().mKnockbackScaling;
}
void ExplosionBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getExplosion().mPos->x = nbt["pos"]["x"];
    getExplosion().mPos->y = nbt["pos"]["y"];
    getExplosion().mPos->z = nbt["pos"]["z"];
    getExplosion().mRadius = nbt["radius"];
    getExplosion().mAffectedBlocks->clear();
    for (auto& blockPos : nbt["affectedBlocks"].get<ListTag>())
    {
        getExplosion().mAffectedBlocks->insert(BlockPos { static_cast<int>(blockPos["x"]),
                                                          static_cast<int>(blockPos["y"]),
                                                          static_cast<int>(blockPos["z"]) });
    }
    getExplosion().mFire                           = nbt["fire"];
    getExplosion().mBreaking                       = nbt["breaking"];
    getExplosion().mAllowUnderwater                = nbt["allowUnderwater"];
    getExplosion().mCanToggleBlocks                = nbt["canToggleBlocks"];
    getExplosion().mDamageScaling                  = nbt["damageScaling"];
    getExplosion().mIgnoreBlockExplosionResistance = nbt["ignoreBlockExplosionResistance"];
    getExplosion().mParticleType = magic_enum::enum_cast<LevelEvent>(nbt["particleType"].get<StringTag>())
                                       .value_or(getExplosion().mParticleType);
    getExplosion().mSoundExplosionType =
        magic_enum::enum_cast<SharedTypes::Legacy::LevelSoundEvent>(nbt["soundExplosionType"].get<StringTag>()
        )
            .value_or(getExplosion().mSoundExplosionType);
    getExplosion().mSourceID->rawID = nbt["sourceId"];
    getExplosion().mMaxResistance   = nbt["maxResistance"];
    if (nbt.contains("inWaterOverride")) { getExplosion().mInWaterOverride = nbt["inWaterOverride"]; }
    if (nbt.contains("totalDamageOverride"))
    {
        getExplosion().mTotalDamageOverride = nbt["totalDamageOverride"];
    }
    getExplosion().mKnockbackScaling = nbt["knockbackScaling"];
}
Explosion& ExplosionBeforeEvent::getExplosion() const { return mExplosion; }

void ExplosionAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["pos"]    = ListTag { getExplosion().mPos->x, getExplosion().mPos->y, getExplosion().mPos->z };
    nbt["radius"] = getExplosion().mRadius;
    nbt["affectedBlocks"] = ListTag {};
    for (auto& blockPos : *getExplosion().mAffectedBlocks)
    {
        nbt["affectedBlocks"].push_back(ListTag { blockPos.x, blockPos.y, blockPos.z });
    }
    nbt["fire"]                           = getExplosion().mFire;
    nbt["breaking"]                       = getExplosion().mBreaking;
    nbt["allowUnderwater"]                = getExplosion().mAllowUnderwater;
    nbt["canToggleBlocks"]                = getExplosion().mCanToggleBlocks;
    nbt["damageScaling"]                  = getExplosion().mDamageScaling;
    nbt["ignoreBlockExplosionResistance"] = getExplosion().mIgnoreBlockExplosionResistance;
    nbt["particleType"]                   = magic_enum::enum_name(getExplosion().mParticleType);
    nbt["soundExplosionType"]             = magic_enum::enum_name(getExplosion().mSoundExplosionType);
    nbt["sourceId"]                       = getExplosion().mSourceID->rawID;
    nbt["maxResistance"]                  = getExplosion().mMaxResistance;
    if (getExplosion().mInWaterOverride->has_value())
    {
        nbt["inWaterOverride"] = getExplosion().mInWaterOverride->value();
    }
    if (getExplosion().mTotalDamageOverride->has_value())
    {
        nbt["totalDamageOverride"] = getExplosion().mTotalDamageOverride->value();
    }
    nbt["knockbackScaling"] = getExplosion().mKnockbackScaling;
}
Explosion const& ExplosionAfterEvent::getExplosion() const { return mExplosion; }

LL_TYPE_INSTANCE_HOOK(ExplosionEventHook, HookPriority::Normal, Explosion, &Explosion::explode, bool)
{
    auto beforeEvent = ExplosionBeforeEvent(mRegion, *this);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return false; }
    auto result = origin();
    if (result) { LLEventBus.publish(ExplosionAfterEvent(mRegion, *this)); }
    return result;
}

Event_Hook_Factory(Explosion, <ExplosionEventHook>);

} // namespace ila::mc::inline world