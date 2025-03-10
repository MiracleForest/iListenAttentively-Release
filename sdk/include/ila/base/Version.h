#pragma once

// clang-format off
#define IL_VERSION_MAJOR         0
#define IL_VERSION_MINOR         3
#define IL_VERSION_PATCH         1
/* #undef IL_VERSION_PRERELEASE */
#define IL_VERSION_COMMIT_SHA    4d75753
// clang-format on

#define IL_WORKSPACE_FOLDER R"(D:\Github项目\MiracleForest\iListenAttentively\)"

#define IL_VERSION_TO_STRING_INNER(ver) #ver
#define IL_VERSION_TO_STRING(ver)       IL_VERSION_TO_STRING_INNER(ver)

#ifdef IL_VERSION_PRERELEASE
#define IL_FILE_VERSION_FLAG VS_FF_DEBUG
#define IL_FILE_VERSION_STRING                                                                                         \
    IL_VERSION_TO_STRING(IL_VERSION_MAJOR)                                                                             \
    "." IL_VERSION_TO_STRING(IL_VERSION_MINOR) "." IL_VERSION_TO_STRING(IL_VERSION_PATCH                               \
    ) "-" IL_VERSION_PRERELEASE "+" IL_VERSION_TO_STRING(IL_VERSION_COMMIT_SHA)
#else
#define IL_FILE_VERSION_FLAG 0x00000000L
#define IL_FILE_VERSION_STRING                                                                                         \
    IL_VERSION_TO_STRING(IL_VERSION_MAJOR)                                                                             \
    "." IL_VERSION_TO_STRING(IL_VERSION_MINOR) "." IL_VERSION_TO_STRING(IL_VERSION_PATCH                               \
    ) "+" IL_VERSION_TO_STRING(IL_VERSION_COMMIT_SHA)
#endif
