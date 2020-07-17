#include "plpch.h"
#include "Polaroid/Renderer/GraphicsContext.h"

#include "Polaroid/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Polaroid {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    PL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		PL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
