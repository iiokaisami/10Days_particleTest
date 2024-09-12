#pragma once
#include <Novice.h>
#include "BrockParticle.h"
#include <list>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Easing.h"

class BrockEmitter{
public:
	
	~BrockEmitter();
	void BrockEmitterInitialize();

	void Update();
	void Draw();

	void Emit(Vector2 pos,Vector2 brockSize);

	void LaserPop(Vector2 pos, Vector2 blockSize);
	void LaserUpdate();
	void LaserDraw();

	void QuadVer(Vector2 pos, float width, float height, Vector2& lt, Vector2& rt, Vector2& lb, Vector2& rb);

	Vector2 Lerp(const Vector2& v1, const Vector2& v2, float t);

private:

	std::list<BrockParticle> particleList;

	const int kParticleNum_ = 5;
	Vector2 pos_ = {};


	Quad laser_[2];
	Vector2 laserStartRad_[2];
	Vector2 laserStopRad_[2];

	int laserTexture_ = 0;

	const float kLaserTimeCount = 0.05f;
	float laserTime_ = 100;

};

