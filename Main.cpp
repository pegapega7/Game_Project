#include "Main.h"
#include "Character.h"
#include "Map.h"

int gpUpdateKey();
int KeyCalc_menu(int SelectNum);
void Draw_menu();
void KeyCalc(Character& c, Enemy e[],MapElement map[]);
void Draw_game(Character& c);

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
	//キャラクタ
	Character myCharacter(LoadGraph("images/mycharacter2.png"));
	myCharacter.pos = { 5 * CHIP_SIZE, 9 * CHIP_SIZE };
	myCharacter.move_v = 0;
	myCharacter.chargeflag = 0;

	//敵
	Enemy enemy[1] = {
		{LoadGraph("images/enemy1.png")},
	};
	for (int i = 0; i < 1; i++) {
		enemy[i].pos = { 5 * CHIP_SIZE, 3 * CHIP_SIZE };
	}

	//技
	Skill arrow_1[100];
	int arrow_handle = LoadGraph("images/normal_arrow.png");
	for (int i=0; i < 100; i++) {
		arrow_1[i].handle = arrow_handle;
		arrow_1[i].drawinterval = 10;
		arrow_1[i].intervalcount = 0;
		arrow_1[i].shootflag = 0;
		arrow_1[i].distance = 0;
		arrow_1[i].range = 0;
		arrow_1[i].chargetime = 0;
	}

	MapElement MapChips[2] = {
		{ LoadGraph("images/grass.png"), 0 }, //マップ番号１：草
		{ LoadGraph("images/tree.png"), 1 }, //マップ番号２：木
	};

	//ゲームモード選択フラグ
	int WinFlag = 0;
	int frame_count = 0;

	int enemy_hitflag = 0;//0ならヒットなし,1ならヒット
	int charge_count = 0;//チャージした時間

	/*****メインループ*****/	
	while (WinFlag >= 0) {//終了が押されるまで
		/***毎ループで必要な処理***/
		frame_count++;
		if (frame_count == 60) frame_count = 0;
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
			Draw_map(MapChips); //マップチップの描画
			KeyCalc(myCharacter, enemy, MapChips); //自キャラのキー入力
			
			if (Key[KEY_INPUT_Z] >= 1) {
				//ステータス画面用のウィンドウ
				DrawBox(myCharacter.pos.x - CHIP_SIZE / 4, myCharacter.pos.y + CHIP_SIZE, myCharacter.pos.x + CHIP_SIZE * 5 / 4, myCharacter.pos.y + CHIP_SIZE * 5 / 4, GetColor(0, 0, 0), TRUE);
				if (Key[KEY_INPUT_Z] < 50)
					DrawBox(myCharacter.pos.x - CHIP_SIZE / 4 + 2, myCharacter.pos.y + CHIP_SIZE + 3, myCharacter.pos.x - CHIP_SIZE / 4 + Key[KEY_INPUT_Z]-3, myCharacter.pos.y + CHIP_SIZE * 5 / 4 - 3, GetColor(Key[KEY_INPUT_Z] * 255 / 50, 255, 0), TRUE);
				else if ( 50 <= Key[KEY_INPUT_Z] && Key[KEY_INPUT_Z] < 100)
					DrawBox(myCharacter.pos.x - CHIP_SIZE / 4 + 2, myCharacter.pos.y + CHIP_SIZE + 3, myCharacter.pos.x - CHIP_SIZE / 4 + Key[KEY_INPUT_Z]-3, myCharacter.pos.y + CHIP_SIZE * 5 / 4 - 3, GetColor(255, 255- Key[KEY_INPUT_Z] * 255 / 50, 0), TRUE);
				else if (Key[KEY_INPUT_Z] >= 100)
					DrawBox(myCharacter.pos.x - CHIP_SIZE / 4 + 2, myCharacter.pos.y + CHIP_SIZE + 3, myCharacter.pos.x + CHIP_SIZE * 5 / 4 - 2, myCharacter.pos.y + CHIP_SIZE * 5 / 4 - 3, GetColor(255, 0, 0), TRUE);
				myCharacter.chargeflag = 1;
				charge_count = Key[KEY_INPUT_Z];
				if (Key[KEY_INPUT_Z] >= 100) charge_count = 100 ;
			}


			if (Key[KEY_INPUT_Z] == 0  && myCharacter.chargeflag == 1) {//Zキーが押されたとき技の発動フラグを立てる
				myCharacter.chargeflag = 0;
				for (int i = 0; i < 100; i++)//描画に使用されていない矢を選ぶ
				{
					if (arrow_1[i].shootflag == 0) {
						arrow_1[i].shootflag = 1;
						arrow_1[i].pos = { myCharacter.pos.x + 16, myCharacter.pos.y - 64 };
						arrow_1[i].range = charge_count;//チャージ時間を射出される矢の飛距離として保存
						break;
					}
				}
			}
			Draw_game(myCharacter);//ゲーム画面の描画
			myCharacter.Draw(myCharacter.pos, myCharacter.handle); //自キャラの描画
			for (int i = 0; i < 1; i++)
			{
				enemy[i].Draw(enemy[i].pos, enemy[i].handle); //敵の描画
			}
			
			for (int i = 0; i < 100; i++) {
				if (arrow_1[i].shootflag == 1) {
					arrow_1[i].Draw({ arrow_1[i].pos.x, arrow_1[i].pos.y }, arrow_1[i].handle, arrow_1[i].drawinterval); //矢の描画
					for (int j = 0; j < 1; j++) {
						if (arrow_1[i].Hit(enemy[j].pos,  arrow_1[i].pos) == 1) {//技の発動フラグが立っているとき描画と当たり判定
							enemy[j].~Enemy();
							arrow_1[i].shootflag = 0;
							arrow_1[i].range = 0;
							arrow_1[i].distance = 0;
						}
					}
					arrow_1[i].pos.x += cos(270*PI/180)*arrow_1[i].speed;
					arrow_1[i].pos.y += sin(270*PI/180)*arrow_1[i].speed;
					arrow_1[i].distance += sqrt(pow(cos(270 * PI / 180)*arrow_1[i].speed, 2.0) + pow(sin(270 * PI / 180)*arrow_1[i].speed ,2.0));
					//矢が射程圏外に出たら消す
					if (3*CHIP_SIZE + arrow_1[i].range*4*CHIP_SIZE/100 < arrow_1[i].distance) {
						arrow_1[i].shootflag = 0;
						arrow_1[i].range = 0;
						arrow_1[i].distance = 0;

					}
					//矢がゲーム画面外から出たら消す
					if (arrow_1[i].pos.x <= -30 || MAP_WIDTH * CHIP_SIZE <= arrow_1[i].pos.x || arrow_1[i].pos.y <= -CHIP_SIZE) {
						arrow_1[i].shootflag = 0;
						arrow_1[i].range = 0;
						arrow_1[i].distance = 0;
					}
				}
			}
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
		if(MainMenu[i].flag == 0) DrawFormatString(MainMenu[i].x, MainMenu[i].y, GetColor(0, 0, 0), MainMenu[i].name.c_str());
		else if (MainMenu[i].flag == 1) DrawFormatString(MainMenu[i].x, MainMenu[i].y, GetColor(255, 0, 0), MainMenu[i].name.c_str());
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

void KeyCalc(Character& c, Enemy e[], MapElement map[]) {

	//自キャラクタの移動
	//移動可能かどうか判定
	Pos oldp = c.pos;//移動計算前の座標保存
	int hitenemyflag = 0;//敵との当たり判定(0:当たり判定なし, 1: 当たり判定あり)
	if (Key[KEY_INPUT_RIGHT] >= 1) { //右キーを押されたとき
		c.move_v = 0;
	    c.pos.x += 6;
		for (int i = 0; i < 3; i++) {
			if (Hit_Enemy(c.pos, e[i].pos) == 1) {
				hitenemyflag = 1;
				break;
			}
		}
		if (Hit_map(map, c.move_v, c.pos, oldp) == 1 || hitenemyflag == 1) {//マップとの当たり判定を計算(１なら進めないようにする)
			c.pos.x = oldp.x;
		}
	}
    if (Key[KEY_INPUT_DOWN] >= 1) {
		c.move_v = 1;
		c.pos.y += 6;
		for (int i = 0; i < 3; i++) {
			if (Hit_Enemy(c.pos, e[i].pos) == 1) {
				hitenemyflag = 1;
				break;
			}
		}
		if (Hit_map(map, c.move_v, c.pos, oldp) == 1 || hitenemyflag == 1) {//マップとの当たり判定を計算(１なら進めないようにする)
		 	c.pos.y = oldp.y;
		}
	}
	if (Key[KEY_INPUT_LEFT] >= 1) {
		c.move_v = 2;
		c.pos.x -= 6;
		for (int i = 0; i < 3; i++) {
			if (Hit_Enemy(c.pos, e[i].pos) == 1) {
				hitenemyflag = 1;
				break;
			}
		}
		if (Hit_map(map, c.move_v, c.pos, oldp) == 1 || hitenemyflag == 1) {//マップとの当たり判定を計算(１なら進めないようにする)
			c.pos.x = oldp.x;
		}
	}
	 if (Key[KEY_INPUT_UP] >= 1) {
		c.move_v = 3;
		c.pos.y -= 6;
		for (int i = 0; i < 3; i++) {
			if (Hit_Enemy(c.pos, e[i].pos) == 1) {
				hitenemyflag = 1;
				break;
			}
		}
		if (Hit_map(map, c.move_v, c.pos, oldp) == 1 || hitenemyflag == 1) {//マップとの当たり判定を計算(１なら進めないようにする)
			c.pos.y = oldp.y;
		}
	}


	//自分のキャラクタがゲーム画面内から出さない処理
	if (c.pos.x <= 0) c.pos.x = 0;
	if ((MAP_WIDTH-1)*CHIP_SIZE <= c.pos.x) c.pos.x = (MAP_WIDTH-1)*CHIP_SIZE;
	if (c.pos.y <= 8*CHIP_SIZE) c.pos.y = 8*CHIP_SIZE; //移動できる高さを制限
	if (WINDOW_HEIGHT-CHIP_SIZE/4 <= (c.pos.y + CHIP_SIZE)) c.pos.y = (MAP_HEIGHT-1)*CHIP_SIZE- CHIP_SIZE / 4;
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
void Draw_game(Character& c)
{
	//ステータス画面用のウィンドウ
	DrawBox(MAP_WIDTH*CHIP_SIZE, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0,0,0), TRUE);

	//でばっぐ用に座標を出力
	ostringstream position;
	position << debug[0].name.c_str() << c.pos.x << "," << c.pos.y << ")";
	ostringstream key;
	key << debug[1].name.c_str() << endl << "↑ " << Key[KEY_INPUT_UP] << " ↓ " << Key[KEY_INPUT_DOWN] << "→ " << Key[KEY_INPUT_RIGHT] << " ← " << Key[KEY_INPUT_LEFT] << " Z " << Key[KEY_INPUT_Z];
	//debug[0].name = position.str();
	SetFontSize(20); // 描画する文字列のサイズを設定
	SetFontThickness(3); // 描画する文字列の太さを設定
	DrawFormatString(debug[0].x, debug[0].y, GetColor(255, 255, 255), position.str().c_str());
	DrawFormatString(debug[1].x, debug[1].y, GetColor(255, 255, 255), key.str().c_str());
}
