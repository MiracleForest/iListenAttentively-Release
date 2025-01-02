#include "ila/base/Gloabl.h"
#include "ila/include_all.h"
#include "mc/nbt/CompoundTag.h"
#include <mc/world/events/ServerInstanceEventCoordinator.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    EventTest,
    HookPriority::Normal,
    ServerInstanceEventCoordinator,
    &ServerInstanceEventCoordinator::sendServerThreadStarted,
    void,
    ServerInstance& ins
)
{
    origin(ins);

    LLEventBus.emplaceListener<ila::mc::PlayerOpenContainerBeforeEvent>(
        [](ila::mc::PlayerOpenContainerBeforeEvent& event) -> void {
            CompoundTag nbt;
            event.serialize(nbt);
            SelfLogger.debug(nbt.toSnbt());
        }
    );
}