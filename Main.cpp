#include "Main.h"
#include "Character.h"
#include "Map.h"

int gpUpdateKey();
int KeyCalc_menu(int SelectNum);
void Draw_menu();
void KeyCalc(Character& c);
void Draw_game();

using namespace std;

int Key[256];// キーが押されているフレーム数を格納する


/*****
メイン関数
*****/
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

	// 画面に絵をロード
	Character myCharacter;
	myCharacter.handle = LoadGraph("images/mycharacter2.png"); // 画像をロード
	int a = myCharacter.handle;

	MapElement MapChips[2] = {
		{ LoadGraph("images/grass.png"), 0 }, //マップ番号１：草
		{ LoadGraph("images/tree.png"), 1 }, //マップ番号２：木
	};

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
			Draw_game();
			Draw_map(MapChips); //マップチップの描画
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


/*****
=====================================
キー入力を更新する関数
=====================================
引数
なし
=====================================
戻り値 0
=====================================
*****/
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


/*****
=====================================
メニュー画面のキー入力 : int KeyCalc_menu(int SelectNum)
=====================================
引数 
int SelectNum : 現在選択中のメニュー
=====================================
戻り値
1 : ゲームスタートが選択されたとき
-1 : ゲーム終了が選択されたとき
=====================================
*****/
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

/*****
=====================================
メニューの文字を表示 : void Draw_menu()
=====================================
引数
なし
=====================================
戻り値
なし
=====================================
*****/
void Draw_menu()
{
	SetFontSize(64); // 描画する文字列のサイズを設定
	SetFontThickness(3); // 描画する文字列の太さを設定
	for (int i = 0; i<2; i++) { // メニュー項目を描画
		if(MainMenu[i].flag == 0) DrawFormatString(MainMenu[i].x, MainMenu[i].y, GetColor(0, 0, 0), MainMenu[i].name);
		else if (MainMenu[i].flag == 1) DrawFormatString(MainMenu[i].x, MainMenu[i].y, GetColor(255, 0, 0), MainMenu[i].name);
	}
}

/*****
=====================================
自分のキャラクタを操作 : void KeyCalc(Character& c)
=====================================
引数
Character& c : 自分のキャラクタのオブジェクト
=====================================
戻り値
なし
=====================================
*****/

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

	if (c.pos.x <= 0) c.pos.x = 0;
	if (MAP_WIDTH*CHIP_SIZE <= (c.pos.x + CHIP_SIZE)) c.pos.x = MAP_WIDTH*CHIP_SIZE - CHIP_SIZE;
	if (c.pos.y <= 0) c.pos.y = 0;
	if (MAP_HEIGHT*CHIP_SIZE <= (c.pos.y + CHIP_SIZE)) c.pos.y = MAP_HEIGHT*CHIP_SIZE - CHIP_SIZE;
}


/*****
=====================================
ゲーム画面生成 : void Draw_game()
=====================================
引数
なし
=====================================
戻り値
なし
=====================================
*****/
void Draw_game()
{
	//ステータス画面用のウィンドウ
	DrawBox(MAP_WIDTH*CHIP_SIZE, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0,0,0), TRUE);

}
