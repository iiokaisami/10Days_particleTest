#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "Vector2.h"
#include "Emitter.h"

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
	


	Emitter* emit = new Emitter();
	
	Vector2 pos = { 700,300 };
	

	bool isStart = false;


	Emit emitter2 =
	{
		0,
		0,
		{0,0},
	};

	Particle particle2;
	for (int i = 0; i < number; i++) {
		particle2.pos[i] = { 0,0 };
		particle2.radius[i] = 5;

		particle2.moveDir[i] = { 0,0 };
		particle2.acc[i] = { 0,0.1f };
		particle2.vel[i] = {};

		particle2.isLive[i] = 0;
		particle2.timer[i] = 0;

		particle2.Lt[i] = { 0,0 };
		particle2.Rt[i] = { 0,0 };
		particle2.Lb[i] = { 0,0 };
		particle2.Rb[i] = { 0,0 };

		particle2.color[i] = 0xffffff90;
		particle2.alpha[i] = 0x00000002;
	}

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
		

		if (keys[(DIK_SPACE)])
		{
			if (!isStart)
			{
				isStart = true;
			}
			else if (isStart)
			{
				isStart=false;
			}
		}



		emit->Update(pos, isStart);



		if (keys[(DIK_W)])
		{
			emitter2.emit.y -= 3.0f;
			for (int i = 0; i < number; i++)
			{
				particle2.moveDir[i].y = 1;
			}
		}
		if (keys[(DIK_S)])
		{
			emitter2.emit.y += 3.0f;
			for (int i = 0; i < number; i++)
			{
				particle2.moveDir[i].y = -1;
			}
		}
		if (keys[(DIK_A)])
		{
			emitter2.emit.x -= 3.0f;
			for (int i = 0; i < number; i++)
			{
				particle2.moveDir[i].x = 1;
			}
		}
		if (keys[(DIK_D)])
		{
			emitter2.emit.x += 3.0f;
			for (int i = 0; i < number; i++)
			{
				particle2.moveDir[i].x = -1;
			}
		}

		QuadVer(emitter2.emit, rad.x, rad.y, Lt, Rt, Lb, Rb);

		for (int i = 0; i < number; i++)
		{
			if (!particle2.isLive[i])
			{
				particle2.pos[i] = { emitter2.emit.x,emitter2.emit.y };

				if (particle2.moveDir[i].x != 0 or particle2.moveDir[i].y != 0)
				{
					particle2.moveDir[i].x = float(rand() % 500 - 250);
				}
				if (particle2.moveDir[i].y != 0 or particle2.moveDir[i].x != 0)
				{
					particle2.moveDir[i].y = float(rand() % 500 - 250);
				}


				normalize(particle2.moveDir[i]);

				particle2.color[i] = 0xfffffff0;

				particle2.isLive[i] = true;
				particle2.timer[i] = 20;

				break;
			}

			if (particle2.isLive[i])
			{
				if (particle2.timer[i] > 0)
				{
					particle2.timer[i]--;
				}
				else
				{
					particle2.moveDir[i] = {0,0};
					particle2.isLive[i] = false;
					particle2.timer[i] = 20;
				}


				// 動かす
				particle2.pos[i].x += particle2.moveDir[i].x * 5;
				particle2.pos[i].y += particle2.moveDir[i].y * 5;

				// 中心から角4点求める
				QuadVer(particle2.pos[i], particle2.radius[i], particle2.radius[i], particle2.Lt[i], particle2.Rt[i], particle2.Lb[i], particle2.Rb[i]);
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		emit->Draw();
		Novice::DrawEllipse((int)pos.x, (int)pos.y, 10, 10, 0.0f, WHITE, kFillModeSolid);

		Novice::DrawQuad((int)Lt.x, (int)Lt.y, (int)Rt.x, (int)Rt.y, (int)Lb.x, (int)Lb.y, (int)Rb.x, (int)Rb.y, 0, 0, 80, 80, particlegh, WHITE);

		for (int i = 0; i < number; i++)
		{
			Novice::DrawQuad((int)particle2.Lt[i].x, (int)particle2.Lt[i].y,
				(int)particle2.Rt[i].x, (int)particle2.Rt[i].y,
				(int)particle2.Lb[i].x, (int)particle2.Lb[i].y,
				(int)particle2.Rb[i].x, (int)particle2.Rb[i].y,
				0, 0, 80, 80, particlegh, particle2.color[i]);
		}

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


	delete emit;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
