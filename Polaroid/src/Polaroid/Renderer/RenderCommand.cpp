#include "plpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Polaroid {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}