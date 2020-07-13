#pragma once

#ifdef PL_PLATFORM_WINDOWS

extern Polaroid::Application* Polaroid::CreateApplication();

int main(int argc, char** argv)
{
	Polaroid::Log::Init();
	PL_CORE_WARN("Initialized Log!");
	int a = 5;
	PL_INFO("Hello! Var = {0}", a);

	auto app = Polaroid::CreateApplication();
	app->Run();
	delete app;
}

#endif