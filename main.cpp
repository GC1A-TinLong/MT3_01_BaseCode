#include <Novice.h>
#include <Function.h>

const char kWindowTitle[] = "GC2A_08_チョウ_テンロウ_AL3";

static void CameraControl(char* keys, Vector3& cameraPosition, Vector3& cameraRotate) {
	if (cameraPosition.z < 0) {
		if (keys[DIK_Q]) {
			cameraPosition.y += 0.05f;
		}
		if (keys[DIK_E]) {
			cameraPosition.y -= 0.05f;
		}
		if (keys[DIK_A]) {
			cameraPosition.x -= 0.05f;
		}
		if (keys[DIK_D]) {
			cameraPosition.x += 0.05f;
		}
		if (keys[DIK_W]) {
			cameraPosition.z += 0.05f;
		}
		if (keys[DIK_S]) {
			cameraPosition.z -= 0.05f;
		}
		if (keys[DIK_LSHIFT] && keys[DIK_W]) {
			cameraRotate.x -= 0.02f;
		}
		if (keys[DIK_LSHIFT] && keys[DIK_S]) {
			cameraRotate.x += 0.02f;
		}
		if (keys[DIK_LSHIFT] && keys[DIK_A]) {
			cameraRotate.y -= 0.02f;
		}
		if (keys[DIK_LSHIFT] && keys[DIK_D]) {
			cameraRotate.y += 0.02f;
		}
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 rotate{};
	Vector3 cameraRotate{ 0.26f,0,0 };
	Vector3 translate{ 0,0,0 };
	Vector3 cameraPosition{ 0.0f,2.0f,-6.8f };
	Sphere sphere{};
	uint32_t color = BLACK;

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
		Matrix4x4 viewProjectionMatrix = viewMatrix * projectionMatrix;
		Matrix4x4 worldViewProjectionMatrix = worldMatrix * viewMatrix * projectionMatrix;
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		CameraControl(keys, cameraPosition, cameraRotate);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, color);

#ifdef _DEBUG

#endif // _DEBUG


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
