#include "core_lib/core/engine_diagnostics.h"

using namespace sauna_core;

sauna_chrono::FrameDiagnostics* EngineDiagnostics::s_frameData = nullptr;
ResourceDiagnostics* EngineDiagnostics::s_resourceData = nullptr;