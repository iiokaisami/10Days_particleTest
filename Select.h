#pragma once
#include <Novice.h>
#include "Vector2.h"

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
	const float kStageChangeCo = 0.1f;
	const int kButtonTime = 300;
	const int kStarTime = 120;
	const int kStarEraseTime = 10;
	const int kStageChangeTime = 20;

	int buttonTime_ = 0;
	int starTime_ = 0;
	int stageChangeInterval = 0;
	float stageChangeTime = 0;

	bool isStarDraw_ = true;

	int stageNum_ = 0;
	int changeStage = 0;
	Vector2 topPos_{};
	Vector2 nowPos_{};
	Vector2 underPos_{};
	Vector2 mainRad_{};
	Vector2 subRad_{};
};
