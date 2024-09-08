#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "Vector2.h"
#include "BrockEmitter.h"
#include "MoveEmitter.h"

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

const char kWindowTitle[] = "LE2A_01_イイオカ_イサミ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	


	BrockEmitter* brockEmit = new BrockEmitter();
	brockEmit->BrockEmitterInitialize();

	Vector2 pos = { 700,300 };
	

	int timer = 60;


	MoveEmitter* moveEmitter = new MoveEmitter();
	moveEmitter->MoveEmitterInitialize();

	Emit emitter2 =
	{
		0,
		0,
		{0,0},
	};

	Vector2 vel = {};

	Vector2 Lt, Lb, Rt, Rb, rad = { 20.0f,20.0f };

	unsigned int currenttime = (unsigned int)time(nullptr);
	srand(currenttime);

	int particlegh = Novice::LoadTexture("./NoviceResources/kamata.ico");

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
		

		timer--;


		// フラグが立った時にbrockEmit->Emit(pos)を呼び出す
		if (timer==0)
		{
			brockEmit->Emit(pos, { 50.0f,50.0f });
			timer = 60;
		}

		// アップデート
		brockEmit->Update();



		if (keys[(DIK_W)])
		{
			vel.y = -3.0f;
			emitter2.emit.y += vel.y;
			
		}
		if (keys[(DIK_S)])
		{
			vel.y = 3.0f;
			emitter2.emit.y += vel.y;
			
		}
		if (keys[(DIK_A)])
		{
			vel.x = -3.0f;
			emitter2.emit.x += vel.x;
			
		}
		if (keys[(DIK_D)])
		{
			vel.x = 3.0f;
			emitter2.emit.x += vel.x;
			
		}

		moveEmitter->Update(emitter2.emit, vel, rad);

		QuadVer(emitter2.emit, rad.x, rad.y, Lt, Rt, Lb, Rb);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		brockEmit->Draw();
		Novice::DrawEllipse((int)pos.x, (int)pos.y, 10, 10, 0.0f, WHITE, kFillModeSolid);

		Novice::DrawQuad((int)Lt.x, (int)Lt.y, (int)Rt.x, (int)Rt.y, (int)Lb.x, (int)Lb.y, (int)Rb.x, (int)Rb.y, 0, 0, 80, 80, particlegh, WHITE);
		moveEmitter->Draw();

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


	delete brockEmit;
	delete moveEmitter;


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
