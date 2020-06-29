#pragma once

#ifdef PL_PLATFORM_WINDOWS

extern Polaroid::Application* Polaroid::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Polaroid::CreateApplication();
	app->Run();
	delete app;
}

#endif