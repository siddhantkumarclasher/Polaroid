#include <Polaroid.h>

class ExampleLayer : public Polaroid::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		PL_INFO("ExampleLayer::Update");
	}

	void OnEvent(Polaroid::Event& event) override
	{
		PL_TRACE("{0}", event);
	}
};

class Sandbox :public Polaroid::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Polaroid::ImGuiLayer());
	}
	~Sandbox()
	{

	}
	
};

Polaroid::Application* Polaroid::CreateApplication()
{
	return new Sandbox();
}
