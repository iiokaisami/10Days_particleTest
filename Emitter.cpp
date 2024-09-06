#include "Emitter.h"

Emitter::~Emitter(){}

Emitter::Emitter(){}

void Emitter::Update(Vector2 pos, bool particleStart)
{
	if (particleStart && timer_==0) {
		isEmit_ = 1;
		timer_ = 0;
	}
	// 
	if (isEmit_ == 1) {
		timer_++;
	}

	// 
	if (timer_ % interval_ == 0 &&timer_ < kTimerMax_ && isEmit_ == 1) {
		Emitter::Emit({ pos.x,pos.y });
	}
	if (timer_ >= kTimerMax_) {
		isEmit_ = 1;
	}

	//
	for (auto itr = particleList.begin(); itr != particleList.end();) {

		if (isEmit_ != 0)
		{
			itr->Update();
		}

		// 
		if (itr->GetDeathFlag()) {
			itr = particleList.erase(itr);
		}
		else {
			itr++; //
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
	float size = static_cast<float>(rand() % 40 + 80) * 0.1f;

	// 
	BrockParticle newParticle = BrockParticle(pos, size);
	particleList.push_back(newParticle);
}
