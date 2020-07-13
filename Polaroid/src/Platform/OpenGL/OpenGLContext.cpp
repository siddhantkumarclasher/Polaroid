#include "plpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include "GL/GL.h"

namespace Polaroid {
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		PL_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PL_CORE_ASSERT(status, "Failed to initialize Glad!")

		PL_CORE_INFO("OpenGL Info:");
		PL_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		PL_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		PL_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
	
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}