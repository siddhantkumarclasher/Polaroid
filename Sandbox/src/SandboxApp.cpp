#include <Polaroid.h>

class Sandbox :public Polaroid::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
	
};

Polaroid::Application* Polaroid::CreateApplication()
{
	return new Sandbox();
}
