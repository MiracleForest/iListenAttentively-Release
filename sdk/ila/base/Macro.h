#pragma once

#include <ll/api/base/CompilerPredefine.h>

#ifndef ILAPI
#    ifdef ILA_EXPORT
#        define ILAPI [[maybe_unused]] LL_SHARED_EXPORT
#    else
#        define ILAPI [[maybe_unused]] LL_SHARED_IMPORT
#    endif
#endif

#ifndef ILCAPI
#    define ILCAPI extern "C" ILAPI
#endif

#ifndef ILNDAPI
#    define ILNDAPI [[nodiscard]] ILAPI
#endif

#ifndef EXAPI
#    define EXAPI [[maybe_unused]] LL_SHARED_IMPORT
#endif

#ifndef EXCAPI
#    define EXCAPI extern "C" EXAPI
#endif

#ifndef EXNDAPI
#    define EXNDAPI [[nodiscard]] EXAPI
#endif