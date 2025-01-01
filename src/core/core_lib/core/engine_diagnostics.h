#pragma once

#include <assert.h> 

#include "core_lib/core/resource_manager.h"
#include "core_lib/chrono/clock.h"

namespace sauna_core
{

class EngineDiagnostics
{
public:
	static inline void setFrameData(sauna_chrono::FrameDiagnostics *frameData)
	{
		s_frameData = frameData;
	};

	static inline void setResourceData(ResourceDiagnostics *resourceData)
	{
		s_resourceData = resourceData;
	};

	static inline sauna_chrono::FrameDiagnostics* getFrameDiagnostics()
	{
		assert(s_frameData != nullptr && "FrameDiagnostics pointer cannot be null!");
		return s_frameData;
	}

	static inline ResourceDiagnostics* getResourceDiagnostics()
	{
		assert(s_resourceData != nullptr && "ResourceDiagnostics pointer cannot be null!");
		return s_resourceData;
	}

private:
    static sauna_chrono::FrameDiagnostics* s_frameData;
    static ResourceDiagnostics* s_resourceData;
};

}; // namespace sauna_core