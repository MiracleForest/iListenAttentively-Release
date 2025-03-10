#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Event.h>
#include <mc/server/commands/CommandFlag.h>
#include <mc/server/commands/CommandPermissionLevel.h>

class CommandRegistry;

namespace ila::mc::inline server
{

class RegisterCmdBeforeEvent final : public ll::event::Event
{
protected:
    CommandRegistry&        mRegistry;
    std::string const&      mName;
    std::string&            mDescription;
    CommandPermissionLevel& mRequirement;
    CommandFlag&            mFlag1;
    CommandFlag&            mFlag2;

public:
    constexpr explicit RegisterCmdBeforeEvent(
        CommandRegistry&        registry,
        std::string const&      name,
        std::string&            description,
        CommandPermissionLevel& requirement,
        CommandFlag&            flag1,
        CommandFlag&            flag2
    )
        : Event()
        , mRegistry(registry)
        , mName(name)
        , mDescription(description)
        , mRequirement(requirement)
        , mFlag1(flag1)
        , mFlag2(flag2)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI CommandRegistry& registry() const;
    ILNDAPI std::string const& commandName() const;
    ILNDAPI std::string&            description() const;
    ILNDAPI CommandPermissionLevel& requirement() const;
    ILNDAPI CommandFlag&            flag1() const;
    ILNDAPI CommandFlag&            flag2() const;
};

class RegisterCmdAfterEvent final : public ll::event::Event
{
protected:
    CommandRegistry&              mRegistry;
    std::string const&            mName;
    std::string const&            mDescription;
    CommandPermissionLevel const& mRequirement;
    CommandFlag const&            mFlag1;
    CommandFlag const&            mFlag2;

public:
    constexpr explicit RegisterCmdAfterEvent(
        CommandRegistry&              registry,
        std::string const&            name,
        std::string const&            description,
        CommandPermissionLevel const& requirement,
        CommandFlag const&            flag1,
        CommandFlag const&            flag2
    )
        : Event()
        , mRegistry(registry)
        , mName(name)
        , mDescription(description)
        , mRequirement(requirement)
        , mFlag1(flag1)
        , mFlag2(flag2)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI CommandRegistry& registry() const;
    ILNDAPI std::string const& commandName() const;
    ILNDAPI std::string const&            description() const;
    ILNDAPI CommandPermissionLevel const& requirement() const;
    ILNDAPI CommandFlag const&            flag1() const;
    ILNDAPI CommandFlag const&            flag2() const;
};

} // namespace ila::mc::inline server