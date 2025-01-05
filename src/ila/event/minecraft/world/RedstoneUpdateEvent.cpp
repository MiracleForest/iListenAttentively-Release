#include "ila/event/minecraft/world/RedstoneUpdateEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/level/block/ActivatorRailBlock.h>
#include <mc/world/level/block/BaseRailBlock.h>
#include <mc/world/level/block/BigDripleafBlock.h>
#include <mc/world/level/block/CommandBlock.h>
#include <mc/world/level/block/ComparatorBlock.h>
#include <mc/world/level/block/CopperBulbBlock.h>
#include <mc/world/level/block/CrafterBlock.h>
#include <mc/world/level/block/DiodeBlock.h>
#include <mc/world/level/block/DispenserBlock.h>
#include <mc/world/level/block/DoorBlock.h>
#include <mc/world/level/block/FenceGateBlock.h>
#include <mc/world/level/block/HopperBlock.h>
#include <mc/world/level/block/NoteBlock.h>
#include <mc/world/level/block/PoweredRailBlock.h>
#include <mc/world/level/block/RedStoneWireBlock.h>
#include <mc/world/level/block/RedstoneLampBlock.h>
#include <mc/world/level/block/RedstoneTorchBlock.h>
#include <mc/world/level/block/StructureBlock.h>
#include <mc/world/level/block/TntBlock.h>
#include <mc/world/level/block/TrapDoorBlock.h>

namespace ila::mc::inline world
{

void RedstoneUpdateBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"]         = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["strength"]    = getStrength();
    nbt["isFirstTime"] = getIsFirstTime();
}
void RedstoneUpdateBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getPos().x       = nbt["pos"]["x"];
    getPos().y       = nbt["pos"]["y"];
    getPos().z       = nbt["pos"]["z"];
    getStrength()    = nbt["strength"];
    getIsFirstTime() = nbt["isFirstTime"];
}
BlockPos& RedstoneUpdateBeforeEvent::getPos() const { return mPos; }
int&      RedstoneUpdateBeforeEvent::getStrength() const { return mStrength; }
bool&     RedstoneUpdateBeforeEvent::getIsFirstTime() const { return mIsFirstTime; }

void RedstoneUpdateAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["pos"]         = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["strength"]    = getStrength();
    nbt["isFirstTime"] = getIsFirstTime();
}
BlockPos const& RedstoneUpdateAfterEvent::getPos() const { return mPos; }
int const&      RedstoneUpdateAfterEvent::getStrength() const { return mStrength; }
bool const&     RedstoneUpdateAfterEvent::getIsFirstTime() const { return mIsFirstTime; }

#define RedstoneUpdateHookMacro(type)                                                                        \
    LL_TYPE_INSTANCE_HOOK(                                                                                   \
        type##RedstoneUpdateEventHook,                                                                       \
        HookPriority::Normal,                                                                                \
        type,                                                                                                \
        &type::$onRedstoneUpdate,                                                                            \
        void,                                                                                                \
        BlockSource&    pRegion,                                                                             \
        BlockPos const& pPos,                                                                                \
        int             pStrength,                                                                           \
        bool            pIsFirstTime                                                                         \
    )                                                                                                        \
    {                                                                                                        \
        auto beforeEvent =                                                                                   \
            RedstoneUpdateBeforeEvent(pRegion, const_cast<BlockPos&>(pPos), pStrength, pIsFirstTime);        \
        LLEventBus.publish(beforeEvent);                                                                     \
        if (beforeEvent.isCancelled()) { return; }                                                           \
        origin(pRegion, pPos, pStrength, pIsFirstTime);                                                      \
        LLEventBus.publish(RedstoneUpdateAfterEvent(pRegion, pPos, pStrength, pIsFirstTime));                \
    }


RedstoneUpdateHookMacro(FenceGateBlock);
RedstoneUpdateHookMacro(HopperBlock);
RedstoneUpdateHookMacro(BaseRailBlock);
RedstoneUpdateHookMacro(BigDripleafBlock);
RedstoneUpdateHookMacro(CommandBlock);
RedstoneUpdateHookMacro(ComparatorBlock);
RedstoneUpdateHookMacro(CopperBulbBlock);
RedstoneUpdateHookMacro(CrafterBlock);
RedstoneUpdateHookMacro(DiodeBlock);
RedstoneUpdateHookMacro(DispenserBlock);
RedstoneUpdateHookMacro(DoorBlock);
RedstoneUpdateHookMacro(ActivatorRailBlock);
RedstoneUpdateHookMacro(TntBlock);
RedstoneUpdateHookMacro(TrapDoorBlock);
RedstoneUpdateHookMacro(NoteBlock);
RedstoneUpdateHookMacro(PoweredRailBlock);
RedstoneUpdateHookMacro(RedStoneWireBlock);
RedstoneUpdateHookMacro(RedstoneLampBlock);
RedstoneUpdateHookMacro(RedstoneTorchBlock);
RedstoneUpdateHookMacro(StructureBlock);

Event_Hook_Factory(RedstoneUpdate, <FenceGateBlockRedstoneUpdateEventHook, HopperBlockRedstoneUpdateEventHook, BaseRailBlockRedstoneUpdateEventHook, BigDripleafBlockRedstoneUpdateEventHook, CommandBlockRedstoneUpdateEventHook, ComparatorBlockRedstoneUpdateEventHook, CopperBulbBlockRedstoneUpdateEventHook, CrafterBlockRedstoneUpdateEventHook, DiodeBlockRedstoneUpdateEventHook, DispenserBlockRedstoneUpdateEventHook, DoorBlockRedstoneUpdateEventHook, ActivatorRailBlockRedstoneUpdateEventHook, TntBlockRedstoneUpdateEventHook, TrapDoorBlockRedstoneUpdateEventHook, NoteBlockRedstoneUpdateEventHook, PoweredRailBlockRedstoneUpdateEventHook, RedStoneWireBlockRedstoneUpdateEventHook, RedstoneLampBlockRedstoneUpdateEventHook, RedstoneTorchBlockRedstoneUpdateEventHook, StructureBlockRedstoneUpdateEventHook>);

} // namespace ila::mc::inline world