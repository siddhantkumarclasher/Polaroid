#include "plpch.h"
#include "Polaroid/Renderer/Buffer.h"

#include "Polaroid/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Polaroid {

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    PL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLVertexBuffer>(vertices, size);
		}

		PL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    PL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLIndexBuffer>(indices, size);
		}

		PL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}