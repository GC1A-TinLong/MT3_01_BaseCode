#include <Novice.h>
#include <Function.h>

const char kWindowTitle[] = "GC2A_08_チョウ_テンロウ_AL3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 rotate{};
	Vector3 cameraRotate{};
	Vector3 translate{};
	Vector3 cameraPosition{ 0.0f,0.0f,-5.0f };
	int rotateReverse = 0;

	Vector3 v1{};
	Vector3 v2{};
	Vector3 cross{};
	float isFront = 0;

	const Vector3 kLocalVertics[3] = {
		{0.0f,0.5f,0.0f},
		{0.5f,-0.5f,0.0f},
		{-0.5f,-0.5f,0.0f},
	};

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = worldMatrix * viewMatrix * projectionMatrix;
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		if (rotateReverse == 0) {
			rotate.y -= 0.08f;
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
				rotateReverse = 1;
		}
		else if (rotateReverse == 1) {
			rotate.y += 0.08f;
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
				rotateReverse = 0;
		}
		if (keys[DIK_A]) {
			translate.x -= 0.05f;
		}
		else if (keys[DIK_D]) {
			translate.x += 0.05f;
		}
		if (keys[DIK_W]) {
			translate.z += 0.05f;
		}
		else if (keys[DIK_S]) {
			translate.z -= 0.05f;
		}
		//Camera
		if (keys[DIK_LEFTARROW]) {
			cameraPosition.x -= 0.05f;
		}
		else if (keys[DIK_RIGHTARROW]) {
			cameraPosition.x += 0.05f;
		}
		if (keys[DIK_UPARROW]) {
			cameraPosition.y += 0.05f;
		}
		else if (keys[DIK_DOWNARROW]) {
			cameraPosition.y -= 0.05f;
		}


		Vector3 screenVertics[3]{};
		for (uint32_t i = 0; i < 3; i++) {
			Vector3 ndcVertex = Transform(kLocalVertics[i], worldViewProjectionMatrix);
			screenVertics[i] = Transform(ndcVertex, viewportMatrix);
		}
		v1.x = screenVertics[1].x - screenVertics[0].x;
		v1.y = screenVertics[1].y - screenVertics[0].y;
		v1.z = screenVertics[1].z - screenVertics[0].z;
		v2.x = screenVertics[2].x - screenVertics[1].x;
		v2.y = screenVertics[2].y - screenVertics[1].y;
		v2.z = screenVertics[2].z - screenVertics[1].z;
		cross = Cross(v1, v2);
		isFront = Dot(cameraPosition, cross);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		if (isFront <= 0) {
			Novice::DrawTriangle(int(screenVertics[0].x), (int)screenVertics[0].y, int(screenVertics[1].x), int(screenVertics[1].y),
				int(screenVertics[2].x), int(screenVertics[2].y), 0xBB0000FF, kFillModeSolid);
		}
		VectorScreenPrintf(0, kRowHeight * 0, cross, "       Cross");
		Novice::ScreenPrintf(0, 20, "isFront = %f", isFront);

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
