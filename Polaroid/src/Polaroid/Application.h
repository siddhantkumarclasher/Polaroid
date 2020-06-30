#pragma once

#include "Core.h"
#include "Polaroid/Events/Event.h"

namespace Polaroid {

	class POLAROID_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();

}