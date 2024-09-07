#include "Emitter.h"

Emitter::~Emitter(){}

Emitter::Emitter(){}

void Emitter::Update(Vector2 pos, bool particleStart)
{
	particleStart;
	pos;
	for (auto itr = particleList.begin(); itr != particleList.end();) {
		itr->Update();

		
		if (itr->GetDeathFlag()) {
			itr = particleList.erase(itr);
		}
		else {
			itr++; 
		}
	}
}

void Emitter::Draw()
{
	for (auto& particle : particleList) {
		particle.Draw();
	}
}

void Emitter::Emit(Vector2 pos)
{
	// 
	for (int i = 0; i <= kParticleNum_; i++)
	{
		float size = static_cast<float>(rand() % 40 + 80) * 0.1f;

		// 
		BrockParticle newParticle = BrockParticle(pos, size);
		particleList.push_back(newParticle);
	}
}
