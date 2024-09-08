#pragma once
#include <Novice.h>
#include "BrockParticle.h"
#include <list>
#define _USE_MATH_DEFINES
#include <math.h>

class BrockEmitter{
public:
	
	~BrockEmitter();
	void BrockEmitterInitialize();

	void Update();
	void Draw();

	void Emit(Vector2 pos,Vector2 brockSize);

private:

	std::list<BrockParticle> particleList;

	const int kParticleNum_ = 5;
	Vector2 pos_ = {};
};

