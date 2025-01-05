#include "ila/event/minecraft/server/RegisterCmdEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/server/commands/CommandRegistry.h>

namespace ila::mc::inline server
{

void RegisterCmdBeforeEvent::serialize(CompoundTag& nbt) const
{
    Event::serialize(nbt);
    nbt["name"]        = getCommandName();
    nbt["description"] = getDescription();
    nbt["requirement"] = magic_enum::enum_name(getRequirement());
    nbt["flag1"]       = magic_enum::enum_name(getFlag1().value);
    nbt["flag2"]       = magic_enum::enum_name(getFlag2().value);
}
void RegisterCmdBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Event::deserialize(nbt);
    getDescription() = nbt["description"];
    getRequirement() = magic_enum::enum_cast<CommandPermissionLevel>(nbt["requirement"].get<StringTag>())
                           .value_or(getRequirement());
    getFlag1().value =
        magic_enum::enum_cast<CommandFlagValue>(nbt["flag1"].get<StringTag>()).value_or(getFlag1().value);
    getFlag2().value =
        magic_enum::enum_cast<CommandFlagValue>(nbt["flag2"].get<StringTag>()).value_or(getFlag2().value);
}
std::string const&      RegisterCmdBeforeEvent::getCommandName() const { return mName; }
std::string&            RegisterCmdBeforeEvent::getDescription() const { return mDescription; }
CommandPermissionLevel& RegisterCmdBeforeEvent::getRequirement() const { return mRequirement; }
CommandFlag&            RegisterCmdBeforeEvent::getFlag1() const { return mFlag1; }
CommandFlag&            RegisterCmdBeforeEvent::getFlag2() const { return mFlag2; }

void RegisterCmdAfterEvent::serialize(CompoundTag& nbt) const
{
    Event::serialize(nbt);
    nbt["name"]        = getCommandName();
    nbt["description"] = getDescription();
    nbt["requirement"] = magic_enum::enum_name(getRequirement());
    nbt["flag1"]       = magic_enum::enum_name(getFlag1().value);
    nbt["flag2"]       = magic_enum::enum_name(getFlag2().value);
}
std::string const&            RegisterCmdAfterEvent::getCommandName() const { return mName; }
std::string const&            RegisterCmdAfterEvent::getDescription() const { return mDescription; }
CommandPermissionLevel const& RegisterCmdAfterEvent::getRequirement() const { return mRequirement; }
CommandFlag const&            RegisterCmdAfterEvent::getFlag1() const { return mFlag1; }
CommandFlag const&            RegisterCmdAfterEvent::getFlag2() const { return mFlag2; }

LL_TYPE_INSTANCE_HOOK(
    RegisterCmdEventHook,
    HookPriority::Normal,
    CommandRegistry,
    &CommandRegistry::registerCommand,
    void,
    std::string const&     pName,
    char const*            pDescription,
    CommandPermissionLevel pRequirement,
    CommandFlag            pFlag1,
    CommandFlag            pFlag2
)
{
    auto description = std::string { pDescription };
    LLEventBus.publish(RegisterCmdBeforeEvent(*this, pName, description, pRequirement, pFlag1, pFlag2));
    origin(pName, description.c_str(), pRequirement, pFlag1, pFlag2);
    LLEventBus.publish(RegisterCmdAfterEvent(*this, pName, description, pRequirement, pFlag1, pFlag2));
}

Event_Hook_Factory(RegisterCmd, <RegisterCmdEventHook>);

} // namespace ila::mc::inline server