#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "Vector2.h"
#include "BrockEmitter.h"
#include "MoveEmitter.h"
#include "Select.h"
#include "Result.h"

const int number = 8;


struct Matrix3x3
{
	float m[3][3];
};

struct Emit
{
	int x;
	int y;

	Vector2 emit;
};

struct Particle
{
	// 中心、半径
	Vector2 pos[number];
	float radius[number];

	// 向き、加速、速さ
	Vector2 moveDir[number];
	Vector2 acc[number];
	Vector2 vel[number];

	// フラグ、タイマー
	bool isLive[number];
	int timer[number];

	// 四つ角
	Vector2 Lt[number];
	Vector2 Rt[number];
	Vector2 Lb[number];
	Vector2 Rb[number];

	unsigned int color[number];
	unsigned int alpha[number];
};

void normalize(Vector2& vec)
{
	float length = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (length != 0)
	{
		vec.x = vec.x / length;
		vec.y = vec.y / length;
	}
}

void QuadVer(Vector2 pos, float width, float height, Vector2& lt, Vector2& rt, Vector2& lb, Vector2& rb)
{
	float halfwidth = width / 2;
	float halfheight = height / 2;

	lt = { pos.x - halfwidth, pos.y - halfheight };
	rt = { pos.x + halfwidth, pos.y - halfheight };
	lb = { pos.x - halfwidth, pos.y + halfheight };
	rb = { pos.x + halfwidth, pos.y + halfheight };
};


const char kWindowTitle[] = "LE2A_01_イイオカ_イサミ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	

	Select* select = new Select();
	select->Initialize();

	int stage = 0;

	Result* result = new Result();
	result->Initialize();

	int scene = 0;

	BrockEmitter* brockEmit = new BrockEmitter();
	brockEmit->BrockEmitterInitialize();

	Vector2 pos = { 700,300 };


	int timer = 60;



	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		if (keys[(DIK_RETURN)])
		{
			if (scene == 0)
			{
				scene = 1;
			}
			else if (scene == 1)
			{
				scene = 0;
			}
		}

		if (scene == 0)
		{



			if (keys[(DIK_W)])
			{
				select->MinasStageNum();
			}
			if (keys[(DIK_S)])
			{
				select->PlusStageNum();

			}


			if (keys[(DIK_SPACE)])
			{
				// スペース押したらSutageNum（ステージ番号）取得
				stage = select->GetStageNum();
			}


			select->Update();
		}
		else if (scene == 1)
		{
			if (keys[(DIK_W)] && !preKeys[(DIK_W)])
			{
				result->ChangeNext();
			}
			if (keys[(DIK_S)] && !preKeys[(DIK_S)])
			{
				result->ChangeNext();
			}

			// 評価の切り替えテスト
			if (keys[(DIK_1)] && !preKeys[(DIK_1)])
			{
				result->SetEvaluation(0);
			}
			if (keys[(DIK_2)] && !preKeys[(DIK_2)])
			{
				result->SetEvaluation(1);
			}
			if (keys[(DIK_3)] && !preKeys[(DIK_3)])
			{
				result->SetEvaluation(2);
			}

			// スコアの切り替えテスト
			if (keys[(DIK_4)] && !preKeys[(DIK_4)])
			{
				result->SetScore(623);
			}

			if (keys[(DIK_5)] && !preKeys[(DIK_5)])
			{
				result->SetScore(129);
			}
			if (keys[(DIK_6)] && !preKeys[(DIK_6)])
			{
				result->SetScore(0);
			}

			if (keys[(DIK_7)] && !preKeys[(DIK_7)])
			{
				result->SetScore(12);
			}


			result->Update();
		}


		timer--;


		// フラグが立った時にbrockEmit->Emit(pos)を呼び出す
		if (timer == 0)
		{
			brockEmit->Emit(pos, { 50.0f,50.0f });
			timer = 60;
		}

		// アップデート
		brockEmit->Update();



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		if (scene == 0)
		{
			select->Draw();
		}
		else if (scene == 1)
		{
			result->Draw();
		}


		Novice::DrawEllipse((int)pos.x, (int)pos.y, 10, 10, 0.0f, WHITE, kFillModeSolid);
		brockEmit->Draw();


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete select;
	delete result;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
