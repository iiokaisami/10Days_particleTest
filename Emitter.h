#pragma once
#include <Novice.h>
#include "BrockParticle.h"
#include <list>
#define _USE_MATH_DEFINES
#include <math.h>

class Emitter{
public:
	
	~Emitter();
	Emitter();

	void Update(Vector2 pos);
	void Draw();

	void Emit(Vector2 pos);

private:

	std::list<BrockParticle> particleList;


	const int kParticleNum_ = 5; //
	bool isEmit_ = 0;
};

