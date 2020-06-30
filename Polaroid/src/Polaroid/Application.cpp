#include "Application.h"

#include "Polaroid/Events/ApplicationEvent.h"
#include "Polaroid/Log.h"

namespace Polaroid {

	Application::Application()
	{

	}
	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		PL_TRACE(e);

		while (true);
	}

}