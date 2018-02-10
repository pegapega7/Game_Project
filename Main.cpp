#include "Main.h"
#include "Character.h"

int gpUpdateKey();
int KeyCalc_menu(int SelectNum);
void Draw_menu();
void KeyCalc(Character& c);
using namespace std;

int Key[256];// キーが押されているフレーム数を格納する
MenuElement_t MainMenu[2] = {
	{ 500, 500, "ゲームスタート", 1 }, // タグの中身の順番で格納される。xに80が、yに100が、nameに"ゲームスタート"が
    { 500, 550, "ゲーム終了", 0 },
};

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*****初期設定*****/
	ChangeWindowMode(TRUE); // ウィンドウモードに設定(TRUE:ウィンドウ FALSE)
	SetBackgroundColor(255, 255, 255);//画面の色を白に
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);

	int SelectNum = 0; // 現在の選択メニュー番号


	// 画面に絵を表示
	Character myCharacter;
	myCharacter.handle = LoadGraph("images/mycharacter.png"); // 画像をロード

	//ゲームモード選択フラグ
	int WinFlag = 0;

	/*****メインループ*****/	
	while (WinFlag >= 0) {//終了が押されるまで
		/***毎ループで必要な処理***/
		if(ScreenFlip() != 0) break;//裏画面を表画面に反映
		if(ProcessMessage() != 0) break;//メッセージ処理
		if(ClearDrawScreen() != 0) break;  // 画面を消す
		if(CheckHitKey(KEY_INPUT_ESCAPE) == 1) break; //escキーが押されたとき
		gpUpdateKey();
		/*************************/
		switch (WinFlag) {
		case 0://メニュー画面
			WinFlag = KeyCalc_menu(SelectNum);//メニュー選択
			Draw_menu();//メニュー描画
			break;
		case 1://ゲーム画面
			KeyCalc(myCharacter); //自キャラのキー入力
			myCharacter.Draw(myCharacter.pos, myCharacter.handle); //自キャラの描画
			break;
		default:
			break;

		}
	}


	/*****終了処理*****/
	DxLib_End();				// ＤＸライブラリ使用の終了処理	
	return 0;				// ソフトの終了 
}


// キーの入力状態を更新する
int gpUpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}

int KeyCalc_menu(int SelectNum)
{
	if (Key[KEY_INPUT_DOWN] == 1) { // 上キーが押された瞬間だけ処理

		SelectNum = (SelectNum + 1) % 2; // 現在の選択項目を一つ上にずらす(逆ループする)
	}
	if (Key[KEY_INPUT_UP] == 1) { // 上キーが押された瞬間だけ処理

		SelectNum = SelectNum % 2; // 現在の選択項目を一つ上にずらす(逆ループする)
	}
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_UP] == 1) { // 下キーが押された瞬間だけ処理
		for (int i = 0; i < 2; i++) {              // メニュー項目数である2個ループ処理
			if (i == SelectNum) {          // 今処理しているのが、選択番号と同じ要素なら
				MainMenu[i].flag = 1;      //選択されているものを1にする
			}
			else {                       // 今処理しているのが、選択番号以外なら
				MainMenu[i].flag = 0;// 選択されているものを0にする
			}
		}
	}

	if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_SPACE] == 1) { //スペースキーまたはエンターキーが押されたとき
		if (MainMenu[0].flag == 1) return 1; //"ゲームスタート"が選択されている
		if (MainMenu[1].flag == 1) return -1; //"ゲーム終了"が選択されている
	}

	return 0;
}

void Draw_menu()
{
	for (int i = 0; i<2; i++) { // メニュー項目を描画
		if(MainMenu[i].flag == 0) DrawFormatString(MainMenu[i].x, MainMenu[i].y, GetColor(0, 0, 0), MainMenu[i].name);
		else if (MainMenu[i].flag == 1) DrawFormatString(MainMenu[i].x, MainMenu[i].y, GetColor(255, 0, 0), MainMenu[i].name);
	}
}

//キーの入力処理
void KeyCalc(Character& c) {
	if (Key[KEY_INPUT_RIGHT] >= 1) {
		c.pos.x += 5;
	}
	if (Key[KEY_INPUT_DOWN] >= 1) {
		c.pos.y += 5;
	}
	if (Key[KEY_INPUT_LEFT] >= 1) {
		c.pos.x -= 5;
	}
	if (Key[KEY_INPUT_UP] >= 1) {
		c.pos.y -= 5;
	}
}
