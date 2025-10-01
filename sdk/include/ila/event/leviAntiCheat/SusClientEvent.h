#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>

// clang-format off
namespace mce { class UUID; }
// clang-format on

namespace ila::lac
{
class SusClientEvent final : public ll::event::Cancellable<ll::event::Event>
{
protected:
    mce::UUID const&        mUuid;
    std::string_view const& mName;
    std::string_view const& mIp;

public:
    constexpr explicit SusClientEvent(
        mce::UUID const&        uuid,
        std::string_view const& name,
        std::string_view const& ip
    )
        : mUuid(uuid)
        , mName(name)
        , mIp(ip)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI mce::UUID const& uuid() const;
    ILNDAPI std::string_view const& name() const;
    ILNDAPI std::string_view const& ip() const;
};
} // namespace ila::lac