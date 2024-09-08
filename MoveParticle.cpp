#include "MoveParticle.h"
#define _USE_MATH_DEFINES
#include <math.h>

MoveParticle::~MoveParticle(){}

MoveParticle::MoveParticle(Vector2 pos, float rad,Vector2 vel)
{
	pos_ = pos;
	rad_ = rad;

	moveDir_ = { 0,0 };
	acc_ = { 0,0.1f };
	vel_ = vel;

	isDeath_ = true;
	timer_ = 0;

	leftTop_ = { 0,0 };
	rightTop_ = { 0,0 };
	leftBottom_ = { 0,0 };
	rightBottom_ = { 0,0 };

	color_ = 0xffffff90;
	alpha_ = 0x00000003;
}

void MoveParticle::Update()
{
	if (isDeath_)
	{

		color_ = 0xfffffff0;

		isDeath_ = false;
		timer_ = kParticleTime;

	}

	if (!isDeath_)
	{
		if (timer_ > 0)
		{
			timer_--;
		}
		else
		{
			isDeath_ = true;
			timer_ = kParticleTime;
		}


		if (timer_ <= 70) {
			vel_.y -= acc_.y;
		}


		pos_.x += moveDir_.x * 5;
		pos_.y += moveDir_.y * 5;


		QuadVer(pos_, rad_, rad_, leftTop_, rightTop_, leftBottom_, rightBottom_);
		color_ -= alpha_;

		if (rad_ > 0.0f) {
			rad_ -= 0.3f;
		}

	}
}

void MoveParticle::Draw()
{
	Novice::DrawQuad((int)leftTop_.x, (int)leftTop_.y,
		(int)rightTop_.x, (int)rightTop_.y,
		(int)leftBottom_.x, (int)leftBottom_.y,
		(int)rightBottom_.x, (int)rightBottom_.y,
		0, 0, 80, 80, particleTexture_, color_);
}

void MoveParticle::normalize(Vector2& vec)
{

	float length = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (length != 0)
	{
		vec.x = vec.x / length;
		vec.y = vec.y / length;
	}
}

void MoveParticle::QuadVer(Vector2 pos, float width, float height, Vector2& lt, Vector2& rt, Vector2& lb, Vector2& rb)
{
	float halfwidth = width / 2;
	float halfheight = height / 2;

	lt = { pos.x - halfwidth, pos.y - halfheight };
	rt = { pos.x + halfwidth, pos.y - halfheight };
	lb = { pos.x - halfwidth, pos.y + halfheight };
	rb = { pos.x + halfwidth, pos.y + halfheight };
}
