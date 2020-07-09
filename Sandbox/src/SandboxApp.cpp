#include <Polaroid.h>

#include "imgui/imgui.h"

class ExampleLayer : public Polaroid::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Polaroid::Input::IsKeyPressed(PL_KEY_TAB))
			PL_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		// ImGui::Begin("Test");
		// ImGui::Text("Hello World");
		// ImGui::End();
	}
	void OnEvent(Polaroid::Event& event) override
	{
		if (event.GetEventType() == Polaroid::EventType::KeyPressed)
		{
			Polaroid::KeyPressedEvent& e = (Polaroid::KeyPressedEvent&)event;
			if (e.GetKeyCode() == PL_KEY_TAB)
				PL_TRACE("Tab key is pressed (event)!");
			PL_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox :public Polaroid::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
	
};

Polaroid::Application* Polaroid::CreateApplication()
{
	return new Sandbox();
}
