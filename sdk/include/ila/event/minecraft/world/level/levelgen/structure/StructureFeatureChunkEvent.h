#pragma once

#include "ila/base/Macro.h"
#include "ila/event/minecraft/world/level/levelgen/structure/StructureEvent.h"
#include <ll/api/event/Cancellable.h>
#include <mc/deps/core/string/HashedString.h>

// clang-format off
class IPreliminarySurfaceProvider;
class BiomeSource;
class Dimension;
class ChunkPos;
class Random;
class StructureFeature;
// clang-format on

namespace ila::mc::inline world::inline level::inline levelgen::inline structure
{

class StructureFeatureChunkEvent final : public ll::event::Cancellable<StructureEvent>
{
protected:
    StructureFeature&                  mFeature;
    HashedString const&                mFeatureIdentifier;
    IPreliminarySurfaceProvider const& mPreliminarySurfaceLevel;
    BiomeSource const&                 mBiomeSource;
    Dimension const&                   mDimension;
    ChunkPos const&                    mChunkPos;
    Random&                            mRandom;
    uint&                              mLevelSeed;

public:
    StructureFeatureChunkEvent(
        StructureFeature&                  feature,
        HashedString const&                featureIdentifier,
        IPreliminarySurfaceProvider const& preliminarySurfaceLevel,
        BiomeSource const&                 biomeSource,
        Dimension const&                   dimension,
        ChunkPos const&                    chunkPos,
        Random&                            random,
        uint&                              levelSeed
    );

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI StructureFeature&                  structureFeature() const;
    ILNDAPI HashedString const&                featureIdentifier() const;
    ILNDAPI IPreliminarySurfaceProvider const& preliminarySurfaceLevel() const;
    ILNDAPI BiomeSource const&                 biomeSource() const;
    ILNDAPI Dimension const&                   dimension() const;
    ILNDAPI ChunkPos const&                    chunkPos() const;
    ILNDAPI Random&                            random() const;
    ILNDAPI uint&                              levelSeed() const;
};

} // namespace ila::mc::inline world::inline level::inline levelgen::inline structure
