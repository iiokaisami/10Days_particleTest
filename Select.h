#pragma once
#include <Novice.h>
#include "Vector2.h"
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

const int kStageNum = 5;

struct  Quad
{
	Vector2 center;
	Vector2 rad;
	Vector2 LT;
	Vector2 LB;
	Vector2 RT;
	Vector2 RB;
};

template<class T> T EasingFunc(T start, T movement, std::function<T(T)> func, T t) { return start + func(t) * movement; }

template<class T> T EaseOutElastic(T x) {
	const T c4 = float((2 * M_PI) / 3);

	return x == 0 ? 0 : x == 1 ? 1 : powf(2, -10 * x) * sinf((x * 10 - 0.75f) * c4) + 1;
}

class Select
{
public:
	~Select();
	void Initialize();

	void Update();
	void Draw();

	int GetStageNum() { return stageNum_; }

	void PlusStageNum();
	void MinasStageNum();

	void StageSelectUpdate();
	void StarUpdate();
	void ArrowUpdate();
	void ButtonUpdate();

	Vector2 Lerp(const Vector2& v1, const Vector2& v2, float t);

	void QuadVer(Vector2 pos, float width, float height, Vector2& lt, Vector2& rt, Vector2& lb, Vector2& rb);

private:

	int bgTexture_ = 0;
	int starTexture_ = 0;
	int stageTexture_[kStageNum];
	int arrowTexture_[2];
	int buttonTexture_ = 0;

	Quad bg_{};
	Quad star_{};
	Quad stage_[kStageNum];
	Quad arrow_[2];
	Quad button_{};

	const int kTimeCount = 1;
	const int kButtonTime = 300;
	const int kStarTime = 120;
	const int kStarEraseTime = 10;
	const int kStageChangeTime = 20;
	const float kStageChangeCo = 0.1f;

	int buttonTime_ = 0;
	float poyonTime_ = 0;
	float ButtonCo_ = 0.1f;
	int starTime_ = 0;
	int stageChangeInterval_ = 0;
	float stageChangeTime_ = 0;
	float arrowTimeCo = 0.02f;
	float arrowTime_ = 0;

	bool isStarDraw_ = true;

	int stageNum_ = 0;
	int changeStage = 0;
	Vector2 topPos_{};
	Vector2 nowPos_{};
	Vector2 underPos_{};
	Vector2 mainRad_{};
	Vector2 subRad_{};

	Vector2 arrowStartPos_[2];
	Vector2 arrowStopPos_[2];

	Vector2 buttonStartRad_{};
	Vector2 buttonStopRad_{};

	bool isPoyon_ = false;
};
