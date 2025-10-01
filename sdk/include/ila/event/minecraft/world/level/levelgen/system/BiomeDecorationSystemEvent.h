#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <mc/world/level/BlockVolumeTarget.h>
#include <mc/world/level/biome/components/BiomeDecorationFeature.h>
#include <mc/world/level/biome/systems/BiomeDecorationSystem.h>

namespace ila::mc::inline world::inline level::inline levelgen::inline system
{
class BiomeDecorationSystemEvent : public ::ll::event::Event
{
    LevelChunk&        mLevelChunk;
    std::string const& mPass;
    Random&            mRandom;

public:
    explicit BiomeDecorationSystemEvent(LevelChunk& pLevelChunk, std::string const& pPass, Random& pRandom)
        : ll::event::Event()
        , mLevelChunk(pLevelChunk)
        , mPass(pPass)
        , mRandom(pRandom)
    {
    }

public:
    ILAPI LevelChunk& levelChunk() const;
    ILAPI std::string const& pass() const;
    ILAPI Random&            random() const;

public:
    ILAPI void serialize(CompoundTag& nbt) const;
};

class DecorateEvent final : public ::ll::event::Cancellable<BiomeDecorationSystemEvent>
{
    BlockSource&                       mBlockSource;
    std::vector<::Biome const*>&       mUniqueBiomes;
    IPreliminarySurfaceProvider const& mPreliminarySurfaceProvider;

public:
    explicit DecorateEvent(
        ::LevelChunk&                        pLevelChunk,
        ::BlockSource&                       pBlockSource,
        ::Random&                            pRandom,
        ::std::vector<::Biome const*>&       pUniqueBiomes,
        ::std::string const&                 pPass,
        ::IPreliminarySurfaceProvider const& pPreliminarySurfaceProvider
    )
        : ll::event::Cancellable<BiomeDecorationSystemEvent>(pLevelChunk, pPass, pRandom)
        , mBlockSource(pBlockSource)
        , mUniqueBiomes(pUniqueBiomes)
        , mPreliminarySurfaceProvider(pPreliminarySurfaceProvider)
    {
    }

public:
    ILAPI BlockSource& blockSource() const;
    ILAPI std::vector<::Biome const*>&       uniqueBiomes() const;
    ILAPI IPreliminarySurfaceProvider const& preliminarySurfaceProvider() const;

public:
    ILAPI void serialize(CompoundTag& nbt) const;
};

class DecorateBiomeEvent final : public ::ll::event::Cancellable<BiomeDecorationSystemEvent>
{
    ::gsl::span<::BiomeDecorationFeature const>& mFeatureList;
    ::Biome const*&                              mBiome;
    ::IPreliminarySurfaceProvider const&         mPreliminarySurfaceProvider;
    ::BlockSource&                               mBlockSource;

public:
    explicit DecorateBiomeEvent(
        ::LevelChunk&                                pLevelChunk,
        ::BlockSource&                               pBlockSource,
        ::Random&                                    pRandom,
        ::gsl::span<::BiomeDecorationFeature const>& pFeatureList,
        ::std::string const&                         pPass,
        ::Biome const*&                              pBiome,
        ::IPreliminarySurfaceProvider const&         pPreliminarySurfaceProvider
    )
        : ll::event::Cancellable<BiomeDecorationSystemEvent>(pLevelChunk, pPass, pRandom)
        , mFeatureList(pFeatureList)
        , mBiome(pBiome)
        , mPreliminarySurfaceProvider(pPreliminarySurfaceProvider)
        , mBlockSource(pBlockSource)
    {
    }

public:
    ILAPI gsl::span<::BiomeDecorationFeature const>& featureList() const;
    ILAPI Biome const*&                              biome() const;
    ILAPI IPreliminarySurfaceProvider const&         preliminarySurfaceProvider() const;
    ILAPI BlockSource&                               blockSource() const;

public:
    ILAPI void serialize(CompoundTag& nbt) const;
};

class DecorateLargeFeature1Event final : public ::ll::event::Cancellable<BiomeDecorationSystemEvent>
{
    ::GeneratorType&                             mGeneratorType;
    uint const&                                  mSeed;
    ::BlockVolumeTarget&                         mTarget;
    ::gsl::span<::BiomeDecorationFeature const>& mFeatureList;
    ::ChunkPos const&                            mChunkPos;

public:
    explicit DecorateLargeFeature1Event(
        ::GeneratorType&                             pGeneratorType,
        uint const&                                  pSeed,
        ::BlockVolumeTarget&                         pTarget,
        ::Random&                                    pRandom,
        ::gsl::span<::BiomeDecorationFeature const>& pFeatureList,
        ::ChunkPos const&                            pChunkPos,
        ::std::string const&                         pPass
    )
        : ll::event::Cancellable<BiomeDecorationSystemEvent>(*pTarget.getChunk(pChunkPos), pPass, pRandom)
        , mGeneratorType(pGeneratorType)
        , mSeed(pSeed)
        , mTarget(pTarget)
        , mFeatureList(pFeatureList)
        , mChunkPos(pChunkPos)
    {
    }

public:
    ILAPI GeneratorType&     generatorType() const;
    ILAPI uint const&        seed() const;
    ILAPI BlockVolumeTarget& target() const;
    ILAPI gsl::span<::BiomeDecorationFeature const>& featureList() const;
    ILAPI ChunkPos const&                            chunkPos() const;

public:
    ILAPI void serialize(CompoundTag& nbt) const;
};

class DecorateLargeFeature2Event final : public ::ll::event::Cancellable<BiomeDecorationSystemEvent>
{
    ::Biome const&       mBiome;
    ::BlockVolumeTarget& mTarget;
    ::ChunkPos const&    mChunkPos;

public:
    explicit DecorateLargeFeature2Event(
        ::Biome const&       pBiome,
        ::LevelChunk&        pLevelChunk,
        ::BlockVolumeTarget& pTarget,
        ::Random&            pRandom,
        ::ChunkPos const&    pChunkPos,
        ::std::string const& pPass
    )
        : ll::event::Cancellable<BiomeDecorationSystemEvent>(pLevelChunk, pPass, pRandom)
        , mBiome(pBiome)
        , mTarget(pTarget)
        , mChunkPos(pChunkPos)
    {
    }

public:
    ILAPI Biome const&       biome() const;
    ILAPI BlockVolumeTarget& target() const;
    ILAPI ChunkPos const&    chunkPos() const;

public:
    ILAPI void serialize(CompoundTag& nbt) const;
};
} // namespace ila::mc::inline world::inline level::inline levelgen::inline system