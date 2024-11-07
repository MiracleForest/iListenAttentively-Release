#pragma once

#include "iListenAttentively.h"
#include <ll/api/Logger.h>
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Emitter.h>
#include <ll/api/event/Event.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/entity/ActorEvent.h>
#include <ll/api/event/player/PlayerEvent.h>
#include <ll/api/event/world/WorldEvent.h>
#include <ll/api/memory/Hook.h>

#define SelfLogger ila::iListenAttentively::getInstance().getSelf().getLogger()
#define eventBus   ll::event::EventBus::getInstance()

#ifdef ILA_EXPORT
#    define ILAPI __declspec(dllexport)
#else
#    define ILAPI __declspec(dllimport)
#endif