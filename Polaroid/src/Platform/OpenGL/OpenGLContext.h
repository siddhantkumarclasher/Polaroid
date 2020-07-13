#pragma once

#include "Polaroid/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Polaroid {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}