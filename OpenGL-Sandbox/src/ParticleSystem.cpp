#include "ParticleSystem.h"

#include "Random.h"
#include "VertexBufferLayout.h"

#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

ParticleSystem::ParticleSystem()
{
	m_ParticlePool.resize(1000);
}

void ParticleSystem::Initialize(GLCore::Utils::OrthographicCamera& camera)
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0
	};
	
	va = std::unique_ptr<VertexArray>(new VertexArray());

	vb = std::unique_ptr<VertexBuffer>(new VertexBuffer(vertices, 5 * 4 * sizeof(float)));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);
	
	ib = std::unique_ptr<IndexBuffer>(new IndexBuffer(indices, 6));
	m_ParticleShader = std::unique_ptr<GLCore::Utils::Shader>(GLCore::Utils::Shader::FromGLSLTextFiles("res/shaders/vert.shader", "res/shaders/frag.shader"));
	m_ParticleShader->Bind();

	texture0 = std::unique_ptr<Texture>(new Texture("res/textures/USC_LOGO.png"));
	texture0->Bind();
	m_ParticleShader->SetUniform1i("u_Texture", 0);
}

void ParticleSystem::OnUpdate(GLCore::Timestep ts)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= ts;
		particle.Position += particle.Velocity * (float)ts;
		particle.Rotation += 0.01f * ts;
	}
}

void ParticleSystem::OnRender(GLCore::Utils::OrthographicCamera& camera)
{
	m_ParticleShader->Bind();
	m_ParticleShader->SetUniformMat4f("u_ViewProj", camera.GetViewProjectionMatrix());

	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		// Fade away particles
		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
		m_ParticleShader->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
		//color.a = color.a * life;

		float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
		
		// Render
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { particle.Position.x, particle.Position.y, 0.0f })
			* glm::rotate(glm::mat4(1.0f), particle.Rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size, size, 1.0f });
		m_ParticleShader->SetUniformMat4f("u_Transform", transform);
		
		va->Bind();
		ib->Bind();
		glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * (Random::Float() - 0.5f);
	particle.Velocity.y += particleProps.VelocityVariation.y * (Random::Float() - 0.5f);

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}
