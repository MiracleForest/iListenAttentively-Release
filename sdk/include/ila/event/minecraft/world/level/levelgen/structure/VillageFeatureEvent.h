#pragma once
#include "ila/base/Macro.h"
#include "ila/event/minecraft/world/level/levelgen/structure/StructureEvent.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>
#include <mc/util/Random.h>
#include <mc/world/level/ChunkPos.h>
#include <mc/world/level/biome/source/BiomeSource.h>
#include <mc/world/level/dimension/Dimension.h>
#include <mc/world/level/levelgen/v1/IPreliminarySurfaceProvider.h>

namespace ila::mc::inline world::inline level::inline levelgen::inline structure
{

class VillageFeatureConstructionEvent final : public ila::mc::StructureEvent
{
protected:
    std::vector<uint64>& mAllowedBiomes;

    uint& mSeed;
    int&  mTownSpacing;
    int&  mMinTownSeparation;

public:
    constexpr explicit VillageFeatureConstructionEvent(
        std::vector<uint64>& pAllowedBiomes,
        uint&                pSeed,
        int&                 pTownSpacing,
        int&                 pMinTownSeparation
    )
        : StructureEvent()
        , mAllowedBiomes(pAllowedBiomes)
        , mSeed(pSeed)
        , mTownSpacing(pTownSpacing)
        , mMinTownSeparation(pMinTownSeparation)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

public:
    ILNDAPI std::vector<uint64>& allowedBiomes() const;
    ILNDAPI uint&                seed() const;
    ILNDAPI int&                 townSpacing() const;
    ILNDAPI int&                 minTownSeparation() const;
};

class CheckIfItIsAVillageGenerationChunkEvent final : public ll::event::Cancellable<ila::mc::StructureEvent>
{
protected:
    IPreliminarySurfaceProvider const& mPreliminarySurfaceLevel;
    BiomeSource const&                 mBiomeSource;
    Dimension const&                   mDimension;
    ChunkPos const&                    mChunkPos;
    Random&                            mRandom;
    uint&                              mLevelSeed;

public:
    constexpr explicit CheckIfItIsAVillageGenerationChunkEvent(
        IPreliminarySurfaceProvider const& pPreliminarySurfaceLevel,
        BiomeSource const&                 pBiomeSource,
        Dimension const&                   pDimension,
        ChunkPos const&                    pChunkPos,
        Random&                            pRandom,
        uint&                              pLevelSeed
    )
        : Cancellable()
        , mPreliminarySurfaceLevel(pPreliminarySurfaceLevel)
        , mBiomeSource(pBiomeSource)
        , mDimension(pDimension)
        , mChunkPos(pChunkPos)
        , mRandom(pRandom)
        , mLevelSeed(pLevelSeed)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

public:
    ILNDAPI IPreliminarySurfaceProvider const& preliminarySurfaceLevel() const;
    ILNDAPI BiomeSource const&                 biomeSource() const;
    ILNDAPI Dimension const&                   dimension() const;
    ILNDAPI ChunkPos const&                    chunkPos() const;
    ILNDAPI Random&                            random() const;
    ILNDAPI uint&                              levelSeed() const;
};

} // namespace ila::mc::inline world::inline level::inline levelgen::inline structure