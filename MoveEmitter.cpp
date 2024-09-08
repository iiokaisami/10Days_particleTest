#include "MoveEmitter.h"
#include "random"

MoveEmitter::~MoveEmitter(){}

void MoveEmitter::MoveEmitterInitialize()
{
	unsigned int currenttime = (unsigned int)time(nullptr);
	srand(currenttime);
}

//MoveEmitter::MoveEmitter(){}

void MoveEmitter::Update(Vector2 pos,Vector2 vel,Vector2 playerSize)
{
	vel_ = vel;

	timer_++;


	if (timer_ % interval_ == 0 ) {
		MoveEmitter::Emit({ pos.x,pos.y },playerSize);
	}

	
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

void MoveEmitter::Draw()
{
	for (auto& particle : particleList) {
		particle.Draw();
	}
}

void MoveEmitter::Emit(Vector2 pos,Vector2 playerSize)
{
	
	float size = static_cast<float>(rand() % 5 + 5);
	pos_.x = float(rand() % int(playerSize.x) + int(pos.x - playerSize.x / 2));
	pos_.y = float(rand() % int(playerSize.y) + int(pos.y - playerSize.y / 2));


	MoveParticle newParticle = MoveParticle(pos_, size, vel_);
	particleList.push_back(newParticle);
}
