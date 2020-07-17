#include <Polaroid.h>
#include <Polaroid/Core/EntryPoint.h>


#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

#include "Sandbox2D.h"

class ExampleLayer : public Polaroid::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray = Polaroid::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Polaroid::Ref<Polaroid::VertexBuffer> vertexBuffer = Polaroid::VertexBuffer::Create(vertices, sizeof(vertices));
		Polaroid::BufferLayout layout = {
			{ Polaroid::ShaderDataType::Float3, "a_Position" },
			{ Polaroid::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Polaroid::Ref<Polaroid::IndexBuffer> indexBuffer = Polaroid::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Polaroid::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Polaroid::Ref<Polaroid::VertexBuffer> squareVB = Polaroid::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Polaroid::ShaderDataType::Float3, "a_Position" },
			{ Polaroid::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		
		Polaroid::Ref<Polaroid::IndexBuffer> squareIB = Polaroid::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Polaroid::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);
		
		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Polaroid::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Polaroid::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Polaroid::Texture2D::Create("assets/textures/ChernoLogo.png");

		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);
	}

	void OnUpdate(Polaroid::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Polaroid::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Polaroid::RenderCommand::Clear();

		Polaroid::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		
		m_FlatColorShader->Bind();
		m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Polaroid::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Polaroid::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Polaroid::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


		// Triangle
		// Polaroid::Renderer::Submit(m_Shader, m_VertexArray);
		
		Polaroid::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Polaroid::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}
private:
	Polaroid::ShaderLibrary m_ShaderLibrary;
	Polaroid::Ref<Polaroid::Shader> m_Shader;
	Polaroid::Ref<Polaroid::VertexArray> m_VertexArray;

	Polaroid::Ref<Polaroid::Shader> m_FlatColorShader;
	Polaroid::Ref<Polaroid::VertexArray> m_SquareVA;

	Polaroid::Ref<Polaroid::Texture2D> m_Texture, m_ChernoLogoTexture;

	Polaroid::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Polaroid::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}

};

Polaroid::Application* Polaroid::CreateApplication()
{
	return new Sandbox();
}