#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "Vector2.h"
#include "BrockEmitter.h"
#include "MoveEmitter.h"
#include "Select.h"

const int number = 8;

struct Matrix2x2
{
	float m[2][2];
};

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

//void Test()

const char kWindowTitle[] = "LE2A_01_イイオカ_イサミ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	

	Select* select = new Select();
	select->Initialize();


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
			select->GetStageNum();
		}

		
		select->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		select->Draw();


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


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
