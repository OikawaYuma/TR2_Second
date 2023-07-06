#include <Novice.h>
#include"ImGuiManager.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"Vector2.h"
struct QuadPos {
	Vector2 LeftTop;
	Vector2 RightTop;
	Vector2 LeftBottom;
	Vector2 RightBottom;
};


const char kWindowTitle[] = "LE2B_05_オイカワユウマ";
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	bool carMove = false;

	Vector2 pos = { 440,700 };
	int width = 90;
	int height = 150;


	//car pos
	QuadPos carPos;
	carPos.LeftTop = { pos.x - width / 2,pos.y - height / 2 };
	carPos.RightTop = { pos.x + width / 2,pos.y - height / 2 };
	carPos.LeftBottom = { pos.x - width / 2,pos.y + height / 2 };
	carPos.RightBottom = { pos.x + width / 2,pos.y + height / 2 };

	//rotate
	QuadPos carRotate;
	carRotate.LeftTop;
	carRotate.RightTop;
	carRotate.LeftBottom;
	carRotate.RightBottom;


	//car size
	QuadPos cark;
	cark.LeftTop = { (float)-width / 2,(float)-height / 2 };
	cark.RightTop = { (float)width / 2,(float)-height / 2 };;
	cark.LeftBottom = { (float)-width / 2,(float)height / 2 };;
	cark.RightBottom = { (float)width / 2,(float)height / 2 };;


	float curveRadius = 25.0f; //カーブの大きさ
	float mass86 = 1000;  //940kgが86の重さ
	
	float staticFrictionCoefficient = 0.8f; //静止摩擦係数　初期値は乾いた道路を参照
	float gravity = 9.8f;
	
	float veloMaxMs = sqrtf(staticFrictionCoefficient*gravity*curveRadius );
	float veloMs = 14.0f;
	float velo = 14.0f/60;
	float radian = 0.0f;
	int radius =180;
	int posx = 790;
	int posy = 510;

	// curve;
	/*float theta = (radian / 2.0f) * (float)M_PI;
	Vector2 move = { cosf(theta),sinf(theta) };*/
	// ウィンドウの×ボタンが押されるまでループ

	int carPng = Novice::LoadTexture("./Resources/hachir.png");
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		
		//ImGuiで変数の変更
		ImGui::Begin("Parameter");
		ImGui::SliderFloat("mass", &mass86, 940, 1000);
		
		ImGui::SliderFloat("posX", &pos.x, 0, 440);
		ImGui::SliderFloat("posY", &pos.y, 0, 720);
		ImGui::SliderFloat("radian", &radian, 0.0f, 4.0f);
		ImGui::SliderFloat("staticFrictionCoefficient[%f]", &staticFrictionCoefficient, 0.2f, 0.8f);
		ImGui::SliderFloat("curve", &curveRadius,25,100);
		ImGui::Text("MaxVelo[%f][%f]", veloMaxMs, veloMaxMs *3600 / 1000);
		ImGui::SliderFloat("Velocity", &veloMs, 10, 50);
		ImGui::Text("m/frame[%f][%f][%f]", velo, veloMs,veloMs * 3600/1000);

		/*ImGui::SliderInt("radius", &radius, 100, 300);
		ImGui::SliderInt("posx", &posx, 500, 1100);
		ImGui::SliderInt("posy", &posy, 300, 600);*/

		if (ImGui::Button("Reset")) {
			carMove = false;
			velo = 1;
			pos = { 440,700 };
			radian = 0.0f;
			carPos.LeftTop = { pos.x - width / 2,pos.y - height / 2 };
			carPos.RightTop = { pos.x + width / 2,pos.y - height / 2 };
			carPos.LeftBottom = { pos.x - width / 2,pos.y + height / 2 };
			carPos.RightBottom = { pos.x + width / 2,pos.y + height / 2 };
		
			
		}
		ImGui::End();

		
		if (keys[DIK_R] && preKeys[DIK_R] == 0) {
			carMove = false;
			velo = 1;
			pos = { 600,700 };
			radian = 0.0f;
			carPos.LeftTop = { pos.x - width/2,pos.y - height / 2 };
			carPos.RightTop = { pos.x + width / 2,pos.y - height / 2 };
			carPos.LeftBottom = { pos.x - width / 2,pos.y + height / 2 };
			carPos.RightBottom = { pos.x + width / 2,pos.y + height / 2 };
		}

		veloMaxMs = sqrtf(staticFrictionCoefficient * gravity * curveRadius);
		velo = veloMs / 60 * 5;

		if (keys[DIK_SPACE]&&preKeys[DIK_SPACE]==0) {
			carMove = true;
		}
		
		if (carMove && veloMs >= veloMaxMs && radian != 0.0f) {
				float theta = (radian / 2.0f) * (float)M_PI;
				Vector2 move = { cosf(theta),sinf(theta) };
				carRotate.LeftTop = {
				cark.LeftTop.x * cosf(theta) - cark.LeftTop.y * sinf(theta),
				cark.LeftTop.y * cosf(theta) + cark.LeftTop.x * sinf(theta) };
				carRotate.RightTop = {
					cark.RightTop.x * cosf(theta) - cark.RightTop.y * sinf(theta),
					cark.RightTop.y * cosf(theta) + cark.RightTop.x * sinf(theta) };
				carRotate.LeftBottom = {
					cark.LeftBottom.x * cosf(theta) - cark.LeftBottom.y * sinf(theta),
					cark.LeftBottom.y * cosf(theta) + cark.LeftBottom.x * sinf(theta)
				};;
				carRotate.RightBottom = {
					cark.RightBottom.x * cosf(theta) - cark.RightBottom.y * sinf(theta),
					cark.RightBottom.y * cosf(theta) + cark.RightBottom.x * sinf(theta)
				};;
				pos.x += velo * move.y * -1;
				pos.y -= velo * move.x;
				carPos.LeftTop = { carRotate.LeftTop.x + pos.x,carRotate.LeftTop.y + pos.y };
				carPos.RightTop = { carRotate.RightTop.x + pos.x,carRotate.RightTop.y + pos.y };
				carPos.LeftBottom = { carRotate.LeftBottom.x + pos.x,carRotate.LeftBottom.y + pos.y };
				carPos.RightBottom = { carRotate.RightBottom.x + pos.x,carRotate.RightBottom.y + pos.y };

		}
		else if (carMove) {

			if (keys[DIK_A]) {
				radian -= 0.01f;
			}
			else if (keys[DIK_D]) {
				radian += 0.01f;
			}

			float theta = (radian / 2.0f) * (float)M_PI;
			Vector2 move = { cosf(theta),sinf(theta) };


			carRotate.LeftTop = {
				cark.LeftTop.x * cosf(theta) - cark.LeftTop.y * sinf(theta),
				cark.LeftTop.y * cosf(theta) + cark.LeftTop.x * sinf(theta) };
			carRotate.RightTop = {
				cark.RightTop.x * cosf(theta) - cark.RightTop.y * sinf(theta),
				cark.RightTop.y * cosf(theta) + cark.RightTop.x * sinf(theta) };
			carRotate.LeftBottom = {
				cark.LeftBottom.x * cosf(theta) - cark.LeftBottom.y * sinf(theta),
				cark.LeftBottom.y * cosf(theta) + cark.LeftBottom.x * sinf(theta)
			};;
			carRotate.RightBottom = {
				cark.RightBottom.x * cosf(theta) - cark.RightBottom.y * sinf(theta),
				cark.RightBottom.y * cosf(theta) + cark.RightBottom.x * sinf(theta)
			};;
			pos.x += velo * move.y;
			pos.y -= velo * move.x;
			carPos.LeftTop = { carRotate.LeftTop.x + pos.x,carRotate.LeftTop.y + pos.y };
			carPos.RightTop = { carRotate.RightTop.x + pos.x,carRotate.RightTop.y + pos.y };
			carPos.LeftBottom = { carRotate.LeftBottom.x + pos.x,carRotate.LeftBottom.y + pos.y };
			carPos.RightBottom = { carRotate.RightBottom.x + pos.x,carRotate.RightBottom.y + pos.y };

		}
		
			
		//float x = sqrtf(49);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		/*Novice::DrawBox(
			(int)pos.x, (int)pos.y,
			162, 421,
			radian,
			0xFFFFFFFF,
			kFillModeSolid
		);*/
		Novice::DrawBox(0, 0, 1280, 1280, 0.0f, 0x5D6562FF, kFillModeSolid);
		

		Novice::DrawEllipse(640, 360, 320,320 ,0.0f, WHITE, kFillModeSolid);
		Novice::DrawBox(320, 360, 20, 920, 0.0f, WHITE, kFillModeSolid);
		Novice::DrawEllipse(640, 360, 300, 300, 0.0f, 0x5D6562FF, kFillModeSolid);
		Novice::DrawBox(340, 360, 300, 920, 0.0f, 0x5D6562FF, kFillModeSolid);
		Novice::DrawBox(640, 60, 300, 300, 0.0f, 0x5D6562FF, kFillModeSolid);
		Novice::DrawBox(640, 250, 320, 430, 0.0f, 0x5D6562FF, kFillModeSolid);
		Novice::DrawBox(640, 40, 640, 20, 0.0f,WHITE, kFillModeSolid);
		Novice::DrawEllipse(posx, posy, radius,radius, 0.0f, WHITE, kFillModeSolid);
		Novice::DrawEllipse(posx, posy, radius-20, radius-20, 0.0f, 0x5D6562FF, kFillModeSolid);
		Novice::DrawBox(posx-radius, posy, radius*2, radius*2, 0.0f, 0x5D6562FF, kFillModeSolid);
		Novice::DrawBox(posx , posy-radius+20, radius * 2, radius * 2, 0.0f, 0x5D6562FF, kFillModeSolid);
		Novice::DrawBox(posx - radius, posy, 20, 500, 0.0f, WHITE, kFillModeSolid);
		Novice::DrawBox(posx , posy-radius, 500, 20, 0.0f, WHITE, kFillModeSolid);
		Novice::DrawQuad(
			(int)carPos.LeftTop.x, (int)carPos.LeftTop.y,
			(int)carPos.RightTop.x, (int)carPos.RightTop.y,
			(int)carPos.LeftBottom.x, (int)carPos.LeftBottom.y,
			(int)carPos.RightBottom.x, (int)carPos.RightBottom.y,
			0, 0,
			width, height,
			carPng,
			WHITE

		);
		
		Novice::ScreenPrintf(0, 0, "pos : %f,%f", pos.x, pos.y);

		Novice::ScreenPrintf(0, 20, "ltp : %f,%f", carPos.LeftTop.x, carPos.LeftTop.y);
		Novice::ScreenPrintf(0, 40, "ltp : %f,%f", carPos.RightTop.x, carPos.RightTop.y);

		Novice::ScreenPrintf(0, 60, "ltp : %f,%f", carPos.LeftBottom.x, carPos.LeftBottom.y);
		Novice::ScreenPrintf(0, 40, "ltp : %f,%f", carPos.RightBottom.x, carPos.RightBottom.y);
		Novice::ScreenPrintf(500, 0, "%d  %d ",posx-radius-340,posy -radius -60);

		Novice::ScreenPrintf(9, 100, "%f  %f ", velo, velo*3600.0f/1000);

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

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
