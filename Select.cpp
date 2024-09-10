#include "Select.h"

Select::~Select()
{
}

void Select::Initialize()
{
	bgTexture_ = Novice::LoadTexture("./Resources/white1x1.png"); // 0x191970ff
	starTexture_ = Novice::LoadTexture("./Resources/white1x1.png"); // 0xffd700ff

	stageTexture_[0] = Novice::LoadTexture("./Resources/white1x1.png"); // 0x4169e1ff
	stageTexture_[1] = Novice::LoadTexture("./Resources/white1x1.png"); // 0xff4500ff
	stageTexture_[2] = Novice::LoadTexture("./Resources/white1x1.png"); // 0x4169e1ff
	stageTexture_[3] = Novice::LoadTexture("./Resources/white1x1.png"); // 0xff4500ff
	stageTexture_[4] = Novice::LoadTexture("./Resources/white1x1.png"); // 0x4169e1ff

	arrowTexture_[0] = Novice::LoadTexture("./Resources/white1x1.png"); // 0xb0c4deff
	arrowTexture_[1] = Novice::LoadTexture("./Resources/white1x1.png"); // 0xb0c4deff
	buttonTexture_ = Novice::LoadTexture("./Resources/white1x1.png"); // 0xffd700ff
		
	bg_.center = { 640.0f,360.0f };
	bg_.rad = { 1280.0f,720.0f };
	QuadVer(bg_.center, bg_.rad.x, bg_.rad.y, bg_.LT, bg_.RT, bg_.LB, bg_.RB);
	

	star_.center = { 50.0f,50.0f };
	star_.rad = { 20.0f,20.0f };
	QuadVer(star_.center, star_.rad.x, star_.rad.y, star_.LT, star_.RT, star_.LB, star_.RB);
	

	stage_[0].center = { 640.0f,360.0f };
	stage_[0].rad = { 980.0f,420.0f };
	QuadVer(stage_[0].center, stage_[0].rad.x, stage_[0].rad.y, stage_[0].LT, stage_[0].RT, stage_[0].LB, stage_[0].RB);
	
	stage_[1].center = { 640.0f,750.0f };
	stage_[1].rad = { 588.0f,216.0f };
	QuadVer(stage_[1].center, stage_[1].rad.x, stage_[1].rad.y, stage_[1].LT, stage_[1].RT, stage_[1].LB, stage_[1].RB);
	///////////////////////////////////
	stage_[2].center = { 640.0f,360.0f };
	stage_[2].rad = { 980.0f,420.0f };
	QuadVer(stage_[2].center, stage_[2].rad.x, stage_[2].rad.y, stage_[2].LT, stage_[2].RT, stage_[2].LB, stage_[2].RB);

	stage_[3].center = { 640.0f,360.0f };
	stage_[3].rad = { 980.0f,420.0f };
	QuadVer(stage_[3].center, stage_[3].rad.x, stage_[3].rad.y, stage_[3].LT, stage_[3].RT, stage_[3].LB, stage_[3].RB);

	stage_[4].center = { 640.0f,-30.0f };
	stage_[4].rad = { 588.0f,216.0f };
	QuadVer(stage_[4].center, stage_[4].rad.x, stage_[4].rad.y, stage_[4].LT, stage_[4].RT, stage_[4].LB, stage_[4].RB);
	



	arrow_[0].center = {640.0f,620.0f};
	arrow_[0].rad = {50.0f,50.0f};
	QuadVer(arrow_[0].center, arrow_[0].rad.x, arrow_[0].rad.y, arrow_[0].LT, arrow_[0].RT, arrow_[0].LB, arrow_[0].RB);

	
	arrow_[1].center = { 640.0f,100.0f };
	arrow_[1].rad = { 50.0f,50.0f };
	QuadVer(arrow_[1].center, arrow_[1].rad.x, arrow_[1].rad.y, arrow_[1].LT, arrow_[1].RT, arrow_[1].LB, arrow_[1].RB);


	button_.center = { 700.0f,500.0f };
	button_.rad = { 50.0f,50.0f };
	QuadVer(button_.center, button_.rad.x, button_.rad.y, button_.LT, button_.RT, button_.LB, button_.RB);

	
	buttonTime_ = kButtonTime;
	starTime_ = kStarTime;
	stageChangeInterval = kStageChangeTime;
	stageChangeTime = 0;

	isStarDraw_ = true;

	stageNum_ = 1;

	topPos_ = { 640.0f,-30.0f };
	nowPos_ = { 640,360 };
	underPos_ = { 640,750 };
	mainRad_= { 980.0f,420.0f };
	subRad_ = { 588.0f,216.0f };
}

void Select::Update()
{
	if (stageChangeInterval > 0)
	{
		stageChangeInterval -= kTimeCount;
	}

	if (changeStage == 1 || changeStage == -1)
	{
		StageSeleceUpdate();

		if (stageChangeTime < 1)
		{
			stageChangeTime += kStageChangeCo;
		}
		else
		{
			stageChangeTime = 0;
			changeStage = 0;
		}
	}

	StarUpdate();

	for (int i = 0; i < kStageNum; i++)
	{
		QuadVer(stage_[i].center, stage_[i].rad.x, stage_[i].rad.y, stage_[i].LT, stage_[i].RT, stage_[i].LB, stage_[i].RB);
	}
}

void Select::Draw()
{
	Novice::ScreenPrintf(0, 0, "%d", stageNum_);
	Novice::DrawQuad((int)bg_.LT.x, (int)bg_.LT.y,
		(int)bg_.RT.x, (int)bg_.RT.y,
		(int)bg_.LB.x, (int)bg_.LB.y,
		(int)bg_.RB.x, (int)bg_.RB.y,
		0, 0, (int)bg_.rad.x, (int)bg_.rad.y,
		bgTexture_, 0x191970ff);

	if (isStarDraw_)
	{
		Novice::DrawQuad((int)star_.LT.x, (int)star_.LT.y,
			(int)star_.RT.x, (int)star_.RT.y,
			(int)star_.LB.x, (int)star_.LB.y,
			(int)star_.RB.x, (int)star_.RB.y,
			0, 0, (int)star_.rad.x, (int)star_.rad.y,
			starTexture_, 0xffd700ff);
	}


	Novice::DrawQuad((int)stage_[0].LT.x, (int)stage_[0].LT.y,
		(int)stage_[0].RT.x, (int)stage_[0].RT.y,
		(int)stage_[0].LB.x, (int)stage_[0].LB.y,
		(int)stage_[0].RB.x, (int)stage_[0].RB.y,
		0, 0, (int)stage_[0].rad.x, (int)stage_[0].rad.y,
		stageTexture_[0], 0x4169e1ff);

	Novice::DrawQuad((int)stage_[1].LT.x, (int)stage_[1].LT.y,
		(int)stage_[1].RT.x, (int)stage_[1].RT.y,
		(int)stage_[1].LB.x, (int)stage_[1].LB.y,
		(int)stage_[1].RB.x, (int)stage_[1].RB.y,
		0, 0, (int)stage_[1].rad.x, (int)stage_[1].rad.y,
		stageTexture_[1], 0xff4500ff);



	/*Novice::DrawQuad((int)stage_[4].LT.x, (int)stage_[4].LT.y,
		(int)stage_[4].RT.x, (int)stage_[4].RT.y,
		(int)stage_[4].LB.x, (int)stage_[4].LB.y,
		(int)stage_[4].RB.x, (int)stage_[4].RB.y,
		0, 0, (int)stage_[4].rad.x, (int)stage_[4].rad.y,
		stageTexture_[4], 0x4169e1ff);*/



	for (int i=0; i < 2; i++)
	{
		Novice::DrawQuad((int)arrow_[i].LT.x, (int)arrow_[i].LT.y,
			(int)arrow_[i].RT.x, (int)arrow_[i].RT.y,
			(int)arrow_[i].LB.x, (int)arrow_[i].LB.y,
			(int)arrow_[i].RB.x, (int)arrow_[i].RB.y,
			0, 0, (int)arrow_[i].rad.x, (int)arrow_[i].rad.y,
			arrowTexture_[i], 0xb0c4deff);
	}

	Novice::DrawQuad((int)button_.LT.x, (int)button_.LT.y,
		(int)button_.RT.x, (int)button_.RT.y,
		(int)button_.LB.x, (int)button_.LB.y,
		(int)button_.RB.x, (int)button_.RB.y,
		0, 0, (int)button_.rad.x, (int)button_.rad.y,
		buttonTexture_, 0xffd700ff);
}

void Select::PlusStageNum()
{
	if (stageChangeInterval == 0)
	{
		stageNum_ += 1;
		stageChangeInterval = kStageChangeTime;
		changeStage = 1;
		if (stageNum_ == kStageNum + 1)
		{
			stageNum_ = 1;
		}
	}
}

void Select::MinasStageNum()
{
	if (stageChangeInterval == 0)
	{
		stageNum_ -= 1;
		stageChangeInterval = kStageChangeTime;
		changeStage = -1;
		if (stageNum_ == 0)
		{
			stageNum_ = kStageNum;
		}
	}
}

void Select::StageSeleceUpdate()
{
	if (changeStage == 1)
	{
		/*stage_[stageNum_ - 2].center = Lerp(nowPos_, topPos_, stageChangeTime);
		stage_[stageNum_ - 2].rad = Lerp(subRad_, mainRad_, stageChangeTime);*/

		stage_[stageNum_ - 1].center = Lerp(nowPos_, underPos_, stageChangeTime);
		stage_[stageNum_ - 1].rad = Lerp(subRad_, mainRad_, stageChangeTime);
		QuadVer(stage_[stageNum_ - 1].center, stage_[stageNum_ - 1].rad.x, stage_[stageNum_ - 1].rad.y, stage_[stageNum_ - 1].LT, stage_[stageNum_ - 1].RT, stage_[stageNum_ - 1].LB, stage_[stageNum_ - 1].RB);
	}

	if (changeStage == -1)
	{
		stage_[stageNum_-1].center = Lerp(nowPos_, topPos_, stageChangeTime);
		stage_[stageNum_ - 1].rad = Lerp(subRad_, mainRad_, stageChangeTime);
	}
}

void Select::StarUpdate()
{
	if (starTime_ >= 0)
	{
		starTime_ -= kTimeCount;
	}
	else if (isStarDraw_)
	{
		isStarDraw_ = false;
		starTime_ = kStarEraseTime;
	}
	else if (!isStarDraw_)
	{
		isStarDraw_ = true;
		starTime_ = kStarTime;
	}
}

Vector2 Select::Lerp(const Vector2& v1, const Vector2& v2, float t)
{
	Vector2 v = { v2.x - v1.x,v2.y - v2.y };

	v = { v.x * t,v.y * t };

	Vector2 result = { v1.x + v.x,v1.y + v.y };

	return result;
}

void Select::QuadVer(Vector2 pos, float width, float height, Vector2& lt, Vector2& rt, Vector2& lb, Vector2& rb)
{
	float halfwidth = width / 2;
	float halfheight = height / 2;

	lt = { pos.x - halfwidth, pos.y - halfheight };
	rt = { pos.x + halfwidth, pos.y - halfheight };
	lb = { pos.x - halfwidth, pos.y + halfheight };
	rb = { pos.x + halfwidth, pos.y + halfheight };
};
