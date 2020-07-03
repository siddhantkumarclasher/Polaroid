#pragma once

#include "Core.h"
#include "Polaroid/Events/Event.h"
#include "Window.h"

namespace Polaroid {

	class POLAROID_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in client
	Application* CreateApplication();

}