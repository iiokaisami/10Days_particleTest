#include "BrockEmitter.h"
#include <time.h>
#include <stdio.h>

BrockEmitter::~BrockEmitter(){}

void BrockEmitter::BrockEmitterInitialize()
{
	unsigned int currenttime = (unsigned int)time(nullptr);
	srand(currenttime);
}

//BrockEmitter::BrockEmitter(){}

void BrockEmitter::Update()
{
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

void BrockEmitter::Draw()
{
	for (auto& particle : particleList) {
		particle.Draw();
	}

	Novice::DrawBox((int)pos_.x, (int)pos_.y, 10, 10, 0.0f, RED, kFillModeSolid);
}

void BrockEmitter::Emit(Vector2 pos, Vector2 brockSize)
{
	
	for (int i = 0; i <= kParticleNum_; i++)
	{
		float size = static_cast<float>(rand() % 40 + 80) * 0.1f;
		pos_.x = float(rand() % int(brockSize.x) + int(pos.x - brockSize.x/2));
		pos_.y = float(rand() % int(brockSize.y) + int(pos.y - brockSize.y / 2));
		

		BrockParticle newParticle = BrockParticle(pos_, size);
		particleList.push_back(newParticle);
	}
}
