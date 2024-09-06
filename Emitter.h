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

	void Update(Vector2 pos,bool particleStart);
	void Draw();

	void Emit(Vector2 pos);

private:

	std::list<BrockParticle> particleList;

	int timer_ = 0; // 
	const int kTimerMax_ = 10;
	int interval_ = 1; //
	bool isEmit_ = 0;
};

