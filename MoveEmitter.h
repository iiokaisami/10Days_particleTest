#pragma once
#include <Novice.h>
#include "MoveParticle.h"
#include <list>
#define _USE_MATH_DEFINES
#include <math.h>

class MoveEmitter
{
public:

	~MoveEmitter();
	void MoveEmitterInitialize();

	void Update(Vector2 pos,Vector2 vel,Vector2 playerSize);
	void Draw();

	void Emit(Vector2 pos,Vector2 playerSize);

private:

	std::list<MoveParticle> particleList;

	Vector2 vel_ = {};
	Vector2 pos_ = {};
	int range_ = 7;

	int timer_ = 0;
	int interval_ = 1;
};

