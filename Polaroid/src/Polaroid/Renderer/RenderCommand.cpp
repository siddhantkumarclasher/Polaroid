#include "plpch.h"
#include "Polaroid/Renderer/RenderCommand.h"

namespace Polaroid {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}