#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Texture.h"

struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;
};

class ParticleSystem
{
public:
	ParticleSystem();

	void Initialize(GLCore::Utils::OrthographicCamera& camera);
	void OnUpdate(GLCore::Timestep ts);
	void OnRender(GLCore::Utils::OrthographicCamera& camera);

	void Emit(const ParticleProps& particleProps);
private:
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 999;

	std::unique_ptr<GLCore::Utils::Shader> m_ParticleShader;
	std::unique_ptr<VertexArray> va;
	std::unique_ptr<VertexBuffer> vb;
	std::unique_ptr<IndexBuffer> ib;
	std::unique_ptr<Texture> texture0;
};