#include "Main.h"
#include "Character.h"
#include "Map.h"

int gpUpdateKey();
int KeyCalc_menu(int SelectNum, int bgm_handle[], int se_handle[]);
void Draw_menu();
void KeyCalc(Character& c, Enemy e[],MapElement map[]);
void Draw_game(Character& c,int time, int gameovercount,int point, int tips);
int KeyCalc_ending(int SelectNum, int bgm_handle[], int se_handle[]);
void Draw_ending();
int KeyCalc_gameover(int SelectNum, int bgm_handle[], int se_handle[]);
void Draw_gameover();
void Draw_result(Character& c, int durability, int point, int minusp, int timing, int se_handle[]);

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


//画面用画像をロード
	 int screen[4] =
	{
		LoadGraph("images/title.png"),
		LoadGraph("images/gameover.png"),
		LoadGraph("images/result.png"),
		LoadGraph("images/ending.png"),
	};

	int bgm_handle[2] =
	{
		LoadSoundMem("musics/bgm/bgm_maoudamashii_fantasy10.mp3"),//タイトルBGM
		LoadSoundMem("musics/bgm/bgm_maoudamashii_fantasy13.mp3"),//ゲーム内BGM
	};

	int se_handle[11] =
	{
		LoadSoundMem("musics/se/cursor10.mp3"), //メニュー選択音
		LoadSoundMem("musics/se/decision24.mp3"), //メニュー決定音
		LoadSoundMem("musics/se/sen_ge_byun02.mp3"),//弓を打つ音
		LoadSoundMem("musics/se/sen_ge_ya_sasaru04.mp3"),//弓が当たる音
		LoadSoundMem("musics/se/down1.mp3"),//敵が倒れる音
		LoadSoundMem("musics/se/se_maoudamashii_se_stairs.mp3"),//敵に突破されるときの音
		LoadSoundMem("musics/se/se_maoudamashii_jingle13.mp3"),//ゲームオーバー
		LoadSoundMem("musics/se/drum-japanese1.mp3"),//結果発表
		LoadSoundMem("musics/se/drum-japanese2.mp3"),//最終結果発表
		LoadSoundMem("musics/se/jingle06.mp3"),//クリア
		LoadSoundMem("musics/se/kick-low1.mp3"),//最終結果発表
	};

	// 絵をロード

	//キャラクタ
	Character myCharacter(LoadGraph("images/mycharacter2.png"));

	
	//敵
	Enemy enemy[ENEMY_TYPE_NUM*ENEMY_NUM] = { 0,0,0,0,0, 0,0,0,0,0, 1,1,1,1,1, 1,1,1,1,1, 2,2,2,2,2, 2,2,2,2,2};

	//ボス
	Enemy boss[1] = {3};
	boss[0].handle = LoadGraph("images/boss1.png");

	//プレイヤーの技
	Skill arrow_1[100];
	int arrow_handle = LoadGraph("images/normal_arrow.png");

	//ボスが使う技
	Skill boss_atk_1[100];
	int boss_atk_1_handle = LoadGraph("images/boss_atk_1.png");


	MapElement MapChips[4] = {
		{ LoadGraph("images/grass.png"), 0 }, //マップ番号１：草
//		{ LoadGraph("images/tree.png"), 1 }, //マップ番号２：木
		{ LoadGraph("images/floor.png"), 0 }, //マップ番号３：床
		{ LoadGraph("images/wall.png"), 1 }, //マップ番号４：城壁
		{ LoadGraph("images/stairs.png"), 0 }, //マップ番号５：階段
	};

	int enemy_hitflag = 0;//0ならヒットなし,1ならヒット
	int charge_count = 0;//チャージした時間


	//ゲームモード選択フラグ
	int WinFlag = 0;
	int frame_count = 0;
	int clear_flag = 0;//クリアしたら1
	int gameover_count = 0;
	int time = 0;
	int base_time[100];//処理の時間差
	int start_time = 0;
	int durability = 10;//耐久度
	int totalpoint = 0;//総合ポイント
	int minuspoint = 0;//マイナスポイント
	int cleartime = GetNowCount();
	int tips = 0;//負けたタイミングのTIPS
	int resultcount = 0;//結果を表示するときのカウント
	/*****メインループ*****/	
	while (WinFlag >= 0) {//終了が押されるまで
		/***毎ループで必要な処理***/
		frame_count++;
		if (frame_count == 60) frame_count = 0;
		if (ScreenFlip() != 0) break;//裏画面を表画面に反映
		if (ProcessMessage() != 0) break;//メッセージ処理
		if (ClearDrawScreen() != 0) break;  // 画面を消す
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break; //escキーが押されたとき
		gpUpdateKey();
		/*************************/
		switch (WinFlag) {
		case 0://メニュー画面
			if (CheckSoundMem(bgm_handle[0]) == 0) {
				PlaySoundMem(bgm_handle[0], DX_PLAYTYPE_BACK | DX_PLAYTYPE_LOOP);
				// 音量の設定
				ChangeVolumeSoundMem(255 * 50 / 100, bgm_handle[0]);
			}
			DrawGraph(0, 0, screen[0], FALSE); //タイトル画面の描画
			WinFlag = KeyCalc_menu(SelectNum, bgm_handle, se_handle);//メニュー選択
			Draw_menu();//メニュー描画

			if (WinFlag == 1) {//ゲーム画面に遷移するときに初期化
				myCharacter.pos = { 5 * CHIP_SIZE, 8 * CHIP_SIZE };
				myCharacter.move_v = 0;
				myCharacter.chargeflag = 0;
				myCharacter.aliveflag = 1;
				myCharacter.HP = 10;
				myCharacter.shootcount = 0;
				myCharacter.cancharge = 1;
				myCharacter.shootflag = 0;

				for (int i = 0; i < ENEMY_TYPE_NUM*ENEMY_NUM; i++) {
					switch (enemy[i].enemytype) {
					case 0:
						enemy[i].handle = LoadGraph("images/enemy1.png");
						enemy[i].speed = 1;
						enemy[i].MAXHP = 3;
						enemy[i].point = 100;
						break;
					case 1:
						enemy[i].handle = LoadGraph("images/enemy2.png");
						enemy[i].speed = 2;
						enemy[i].MAXHP = 3;
						enemy[i].point = 300;
						break;
					case 2:
						enemy[i].handle = LoadGraph("images/enemy3.png");
						enemy[i].speed = 5;
						enemy[i].MAXHP = 1;
						enemy[i].point = 200;
						break;
					default:
						break;
					}
					enemy[i].move_pattern = 0;
					enemy[i].aliveflag = 0;
					enemy[i].enemy_clearflag = 0;
					enemy[i].bossflag = 0;
				}

				boss[0].handle = LoadGraph("images/boss1.png");
				boss[0].pos = { 4 * CHIP_SIZE, CHIP_SIZE };
				boss[0].speed = 2;
				boss[0].aliveflag = 0;
				boss[0].bossflag = 1;
				boss[0].enemy_clearflag = 0;
				boss[0].move_pattern = 0;
				boss[0].MAXHP = 15;
				boss[0].point = 1000;


				for (int i = 0; i < 100; i++) {
					arrow_1[i].speed = 16;
					arrow_1[i].intervalflag = 0;
					arrow_1[i].handle = arrow_handle;
					arrow_1[i].drawinterval = 10;
					arrow_1[i].intervalcount = 0;
					arrow_1[i].shootflag = 0;
					arrow_1[i].distance = 0;
					arrow_1[i].range = 0;
					arrow_1[i].chargetime = 0;
					arrow_1[i].damage = 1;
				}

				for (int i = 0; i < 100; i++) {
					boss_atk_1[i].speed = 8;
					boss_atk_1[i].intervalflag = 0;
					boss_atk_1[i].handle = boss_atk_1_handle;
					boss_atk_1[i].drawinterval = 10;
					boss_atk_1[i].intervalcount = 0;
					boss_atk_1[i].shootflag = 0;
					boss_atk_1[i].distance = 0;
					boss_atk_1[i].range = 0;
					boss_atk_1[i].chargetime = 0;
					boss_atk_1[i].damage = 3;
				}
				Init_map();
				clear_flag = 0;
				gameover_count = 0;
				for (int i = 0; i < 100; i++) {
					base_time[i] = 0;
				}
				SRand(GetNowCount());//乱数の初期化
				start_time = GetNowCount();//ゲーム開始した時刻を基準にする
				totalpoint = 0;
				minuspoint = 0;
				resultcount = 0;
				StopSoundMem(bgm_handle[0]);
				PlaySoundMem(bgm_handle[1], DX_PLAYTYPE_BACK | DX_PLAYTYPE_LOOP);
				// 音量の設定
				ChangeVolumeSoundMem(255 * 50 / 100, bgm_handle[1]);
			}

			break;
		case 1://ゲーム画面
			if (clear_flag == 0) {
				/*********************計算部***********************/
				time = GetNowCount() - start_time;
				KeyCalc(myCharacter, enemy, MapChips); //自キャラのキー入力
				if (time < 60000) {
					if (time - base_time[0] >= 3000) {//3秒ごと
						int random_enemytype = GetRand(2);//0~2までのランダムな数値を算出（登場するモンスターの種類）
						base_time[0] = time;
						for (int i = 0; i < ENEMY_TYPE_NUM*ENEMY_NUM; i++) {
							if (enemy[i].aliveflag == 0 && enemy[i].enemytype == random_enemytype) {
								enemy[i].HP = enemy[i].MAXHP;
								enemy[i].aliveflag = 1;
								int random_enemydisppos = GetRand(9);//0~9までのランダムな数値を算出（モンスターの登場する座標を指定）
								enemy[i].pos = { random_enemydisppos*CHIP_SIZE, 0 };
								break;
							}
						}
					}
				}
				else if (60000 <= time && time < 90000) {
					if (time - base_time[0] >= 3000) {//3秒ごと
						base_time[0] = time;
						for (int i = 0; i < ENEMY_TYPE_NUM*ENEMY_NUM; i++) {
							if (enemy[i].aliveflag == 0 && enemy[i].enemytype == 0) {
								enemy[i].HP = enemy[i].MAXHP;
								enemy[i].aliveflag = 1;

								int random_enemydisppos = GetRand(9);//0~9までのランダムな数値を算出（モンスターの登場する座標を指定）
								enemy[i].pos = { random_enemydisppos*CHIP_SIZE, 0 };
								break;
							}
						}
						for (int i = 0; i < ENEMY_TYPE_NUM*ENEMY_NUM; i++) {
							if (enemy[i].aliveflag == 0 && enemy[i].enemytype == 2) {
								enemy[i].HP = enemy[i].MAXHP;
								enemy[i].aliveflag = 1;
								int random_enemydisppos = GetRand(9);//0~9までのランダムな数値を算出（モンスターの登場する座標を指定）
								enemy[i].pos = { random_enemydisppos*CHIP_SIZE, 0 };
								break;
							}
						}
					}
				}
				else if (time >= 90000) {
					if (boss[0].aliveflag == 0) {
						boss[0].aliveflag = 1;
						boss[0].HP = boss[0].MAXHP;
						boss[0].pos = { 4 * CHIP_SIZE, CHIP_SIZE };
					}

					if (time - base_time[0] >= 7000) {//7秒ごと
						int random_enemytype = GetRand(2);//0~2までのランダムな数値を算出（登場するモンスターの種類）
						base_time[0] = time;
						for (int i = 0; i < ENEMY_TYPE_NUM*ENEMY_NUM; i++) {
							if (enemy[i].aliveflag == 0 && enemy[i].enemytype == random_enemytype) {
								enemy[i].HP = enemy[i].MAXHP;
								enemy[i].aliveflag = 1;
								int random_enemydisppos = GetRand(9);//0~9までのランダムな数値を算出（モンスターの登場する座標を指定）
								enemy[i].pos = { random_enemydisppos*CHIP_SIZE, 0 };
								break;
							}
						}
					}

					if (time - base_time[1] >= 2000) {//3秒ごと
						base_time[1] = time;
						for (int i = 0; i < 100; i++)//描画に使用されていない敵の弾を選ぶ
						{
							if (boss_atk_1[i].shootflag == 0) {
								boss_atk_1[i].shootflag = 1;
								boss_atk_1[i].pos = { boss[0].pos.x + 32, boss[0].pos.y + 50 };
								break;
							}
						}
					}
				}

				for (int i = 0; i < ENEMY_TYPE_NUM*ENEMY_NUM; i++) {//敵とのあたり判定
					if (myCharacter.pos.y < 10 * CHIP_SIZE) {
						if (Hit_Enemy(myCharacter, enemy[i]) == 1 && enemy[i].aliveflag == 1) {
							PlaySoundMem(se_handle[10], DX_PLAYTYPE_BACK);
							enemy[i].aliveflag = 0;
							myCharacter.HP--;

						}
					}
					if (myCharacter.HP <= 0) {
						myCharacter.aliveflag = 0;
					}
				}


				for (int i = 0; i < ENEMY_TYPE_NUM*ENEMY_NUM; i++) {//敵のタイプごとに座標を決定
					if (enemy[i].aliveflag == 1) {
						Move_enemy(enemy[i]);//敵の移動先を決める
					}
				}
				if (boss[0].aliveflag == 1)
					Move_enemy(boss[0]);

				//矢のチャージ可能か
				if (time - base_time[2] >= 500 && myCharacter.cancharge == 0 && charge_count == 0 && myCharacter.shootflag == 0 && myCharacter.chargeflag == 0) {//前に矢を打ってから500msで再度打てる
					myCharacter.cancharge = 1;
				}

				//矢のチャージ
				if (Key[KEY_INPUT_Z] >= 1 && myCharacter.cancharge == 1) {
					myCharacter.chargeflag = 1;
					charge_count = Key[KEY_INPUT_Z];
					if (charge_count >= 100) charge_count = 100;
				}

				////矢の発射
				if (Key[KEY_INPUT_Z] == 0 && myCharacter.chargeflag == 1) {//Zキーが押されたとき技の発動フラグを立てる
					PlaySoundMem(se_handle[2], DX_PLAYTYPE_BACK);
					base_time[2] = time;//発動タイミングを保存
					minuspoint++;
					myCharacter.cancharge = 0;
					myCharacter.chargeflag = 0;
					myCharacter.shootflag = 1;
					if (charge_count < 60) {
						myCharacter.shootcount = 0;
					}
					else if (60 <= charge_count && charge_count < 80) {
						myCharacter.shootcount = 2;
					}
					else if (80 <= charge_count && charge_count < 100) {
						myCharacter.shootcount = 3;
					}
					else if (100 == charge_count) {
						myCharacter.shootcount = 5;
					}
					charge_count = 0;
				}

				if (myCharacter.shootflag == 1) {
					for (int i = 0; i < 100; i++)//描画に使用されていない矢を選ぶ
					{
						if (arrow_1[i].shootflag == 0) {
							if (myCharacter.shootcount == 0) {
								myCharacter.cancharge = 0;
								myCharacter.shootflag = 0;
								arrow_1[i].shootflag = 1;
								arrow_1[i].pos = { myCharacter.pos.x + 16, myCharacter.pos.y - 64 };
								break;
							}
							else {
								if (time - base_time[3] >= 100) {//100msごとに発射
									base_time[3] = time;
									myCharacter.shootcount--;
									if (myCharacter.shootcount == 0) {
										myCharacter.shootflag = 0;
									}
									arrow_1[i].shootflag = 1;
									arrow_1[i].pos = { myCharacter.pos.x + 16, myCharacter.pos.y - 64 };
									break;
								}
							}
						}
					}
				}
				//矢と敵のあたり判定
				for (int i = 0; i < 100; i++) {
					if (arrow_1[i].shootflag == 1) {//技の発動フラグが立っているとき当たり判定
						arrow_1[i].pos.x += cos(270 * PI / 180)*arrow_1[i].speed;
						arrow_1[i].pos.y += sin(270 * PI / 180)*arrow_1[i].speed;
						arrow_1[i].distance += sqrt(pow(cos(270 * PI / 180)*arrow_1[i].speed, 2.0) + pow(sin(270 * PI / 180)*arrow_1[i].speed, 2.0));
						for (int j = 0; j < ENEMY_TYPE_NUM*ENEMY_NUM; j++) {
							if (enemy[j].aliveflag == 1) {//敵が生きていればあたり判定
								if (Hit_Skill(enemy[j], arrow_1[i]) == 1) {
									PlaySoundMem(se_handle[3], DX_PLAYTYPE_BACK);
									enemy[j].HP -= arrow_1[i].damage;
									arrow_1[i].shootflag = 0;
								}
								if (enemy[j].HP <= 0) {
									PlaySoundMem(se_handle[4], DX_PLAYTYPE_BACK);
									enemy[j].aliveflag = 0;//HPが0になったとき
									totalpoint += enemy[j].point;//ポイントを加算
								}
							}
						}
						if (boss[0].aliveflag == 1) {//ボスが生きていればあたり判定
							if (Hit_Skill(boss[0], arrow_1[i]) == 1) {
								PlaySoundMem(se_handle[3], DX_PLAYTYPE_BACK);
								boss[0].HP -= arrow_1[i].damage;
								arrow_1[i].shootflag = 0;
							}
							if (boss[0].HP <= 0) {
								PlaySoundMem(se_handle[4], DX_PLAYTYPE_BACK);
								clear_flag = 1;
								boss[0].aliveflag = 0;
								totalpoint += boss[0].point;
							}
						}
						//矢がゲーム画面外から出たら消す
						if (arrow_1[i].pos.x <= -30 || MAP_WIDTH * CHIP_SIZE <= arrow_1[i].pos.x || arrow_1[i].pos.y <= -CHIP_SIZE) {
							arrow_1[i].shootflag = 0;
						}
					}
				}

				//敵の弾とキャラクターのあたり判定
				for (int i = 0; i < 100; i++) {
					if (boss_atk_1[i].shootflag == 1) {//技の発動フラグが立っているとき当たり判定
						boss_atk_1[i].pos.x += cos(90 * PI / 180)*boss_atk_1[i].speed;
						boss_atk_1[i].pos.y += sin(90 * PI / 180)*boss_atk_1[i].speed;
						if (Hit_Attack(myCharacter, boss_atk_1[i]) == 1) {
							myCharacter.HP -= boss_atk_1[i].damage;
							boss_atk_1[i].shootflag = 0;
						}
						if (myCharacter.HP <= 0) {
							myCharacter.aliveflag = 0;
						}
						//矢がゲーム画面外から出たら消す
						if (boss_atk_1[i].pos.x <= -64 || MAP_WIDTH * CHIP_SIZE <= boss_atk_1[i].pos.x || boss_atk_1[i].pos.y >= (MAP_HEIGHT + 1)*CHIP_SIZE) {
							boss_atk_1[i].shootflag = 0;
						}
					}
				}


				for (int i = 0; i < ENEMY_TYPE_NUM*ENEMY_NUM; i++) {
					if (enemy[i].enemy_clearflag == 1) {
						PlaySoundMem(se_handle[5], DX_PLAYTYPE_BACK);
						gameover_count++;
						enemy[i].enemy_clearflag = 0;
					}
				}
			}

			/************************描画部**************************/
			Draw_game(myCharacter, time, gameover_count, totalpoint, tips);//ゲーム画面の描画
			Draw_map(MapChips); //マップチップの描画

			myCharacter.Draw(myCharacter.pos, myCharacter.handle); //自キャラの描画
			for (int i = 0; i < ENEMY_TYPE_NUM*ENEMY_NUM; i++)
			{
				if (enemy[i].aliveflag == 1) {//敵が生きていれば描画
					enemy[i].Draw(enemy[i].pos, enemy[i].handle); //敵の描画
					switch (enemy[i].enemytype) {
					case 0:
						DrawBox(enemy[i].pos.x, enemy[i].pos.y - 5, enemy[i].pos.x + 64 / enemy[i].MAXHP*enemy[i].HP, enemy[i].pos.y, GetColor(255, 0, 0), TRUE);
						break;
					case 1:
						DrawBox(enemy[i].pos.x, enemy[i].pos.y - 5, enemy[i].pos.x + 64 / enemy[i].MAXHP*enemy[i].HP, enemy[i].pos.y, GetColor(255, 0, 0), TRUE);
						break;
					case 2:
						DrawBox(enemy[i].pos.x, enemy[i].pos.y - 5, enemy[i].pos.x + 64 / enemy[i].MAXHP*enemy[i].HP, enemy[i].pos.y, GetColor(255, 0, 0), TRUE);
						break;
					case 3:
						DrawBox(enemy[i].pos.x, enemy[i].pos.y - 5, enemy[i].pos.x + 64 / enemy[i].MAXHP*enemy[i].HP, enemy[i].pos.y, GetColor(255, 0, 0), TRUE);
						break;
					default: break;
					}
				}
			}
			if (boss[0].aliveflag == 1) {
				boss[0].Draw(boss[0].pos, boss[0].handle);
				DrawBox(boss[0].pos.x, boss[0].pos.y - 5, boss[0].pos.x + 128 / boss[0].MAXHP*boss[0].HP, boss[0].pos.y, GetColor(255, 0, 0), TRUE);
			}
			//チャージ中のみチャージ時間の描画
			if (myCharacter.chargeflag == 1) {
				DrawBox(myCharacter.pos.x - CHIP_SIZE / 4, myCharacter.pos.y + CHIP_SIZE, myCharacter.pos.x + CHIP_SIZE * 5 / 4, myCharacter.pos.y + CHIP_SIZE * 5 / 4, GetColor(0, 0, 0), TRUE);
				if (charge_count < 50)
					DrawBox(myCharacter.pos.x - CHIP_SIZE / 4 + 2, myCharacter.pos.y + CHIP_SIZE + 3, myCharacter.pos.x - CHIP_SIZE / 4 + charge_count - 3, myCharacter.pos.y + CHIP_SIZE * 5 / 4 - 3, GetColor(charge_count * 255 / 50, 255, 0), TRUE);
				else if (50 <= charge_count && charge_count < 100)
					DrawBox(myCharacter.pos.x - CHIP_SIZE / 4 + 2, myCharacter.pos.y + CHIP_SIZE + 3, myCharacter.pos.x - CHIP_SIZE / 4 + charge_count - 3, myCharacter.pos.y + CHIP_SIZE * 5 / 4 - 3, GetColor(255, 255 - charge_count * 255 / 50, 0), TRUE);
				else if (charge_count >= 100)
					DrawBox(myCharacter.pos.x - CHIP_SIZE / 4 + 2, myCharacter.pos.y + CHIP_SIZE + 3, myCharacter.pos.x + CHIP_SIZE * 5 / 4 - 2, myCharacter.pos.y + CHIP_SIZE * 5 / 4 - 3, GetColor(255, 0, 0), TRUE);
			}

			for (int i = 0; i < 100; i++) {//矢の描画
				if (arrow_1[i].shootflag == 1) {
					arrow_1[i].Draw({ arrow_1[i].pos.x, arrow_1[i].pos.y }, arrow_1[i].handle, arrow_1[i].drawinterval); //矢の描画
				}
			}


			for (int i = 0; i < 100; i++) {//敵の攻撃描画
				if (boss_atk_1[i].shootflag == 1) {
					boss_atk_1[i].Draw({ boss_atk_1[i].pos.x, boss_atk_1[i].pos.y }, boss_atk_1[i].handle, boss_atk_1[i].drawinterval); //矢の描画

				}
			}

			if (myCharacter.aliveflag == 0) {
				WinFlag = 3; SelectNum = 0; tips = 1;
				StopSoundMem(bgm_handle[1]);
				PlaySoundMem(se_handle[6], DX_PLAYTYPE_BACK);
			} //キャラクタが死んでいればゲームオーバー
			if (gameover_count >= 10) {
				WinFlag = 3;
				SelectNum = 0;
				tips = 2;
				StopSoundMem(bgm_handle[1]);
				PlaySoundMem(se_handle[6], DX_PLAYTYPE_BACK);
			} //ゲームオーバー
			if (clear_flag == 1) {
				if (CheckSoundMem(se_handle[9]) == 0 && CheckSoundMem(bgm_handle[1]) == 1) {
					StopSoundMem(bgm_handle[1]);
					PlaySoundMem(se_handle[9], DX_PLAYTYPE_BACK);
				}
				int a = CheckSoundMem(se_handle[9]);
				if (CheckSoundMem(se_handle[9]) == 0) {
					WinFlag = 4;
					SelectNum = 0;
					cleartime = GetNowCount();
				}
			}//ボスが倒れたらクリア

			break;
		case 2:
			DrawGraph(0, 0, screen[3], FALSE); //エンディング画像の描画
			WinFlag = KeyCalc_ending(SelectNum, bgm_handle, se_handle);//メニュー選択
			Draw_ending();
			break;
		case 3:
			DrawGraph(0, 0, screen[1], FALSE); //ゲームオーバー画像の描画
			WinFlag = KeyCalc_gameover(SelectNum, bgm_handle, se_handle);//メニュー選択
			Draw_gameover();
			if (WinFlag == 1) {//ゲーム画面に遷移するときに初期化
				myCharacter.pos = { 5 * CHIP_SIZE, 8 * CHIP_SIZE };
				myCharacter.move_v = 0;
				myCharacter.chargeflag = 0;
				myCharacter.aliveflag = 1;
				myCharacter.HP = 10;
				myCharacter.shootcount = 0;
				myCharacter.cancharge = 1;
				myCharacter.shootflag = 0;

				for (int i = 0; i < ENEMY_TYPE_NUM*ENEMY_NUM; i++) {
					switch (enemy[i].enemytype) {
					case 0:
						enemy[i].handle = LoadGraph("images/enemy1.png");
						enemy[i].speed = 1;
						enemy[i].MAXHP = 3;
						enemy[i].point = 100;
						break;
					case 1:
						enemy[i].handle = LoadGraph("images/enemy2.png");
						enemy[i].speed = 2;
						enemy[i].MAXHP = 3;
						enemy[i].point = 300;
						break;
					case 2:
						enemy[i].handle = LoadGraph("images/enemy3.png");
						enemy[i].speed = 5;
						enemy[i].MAXHP = 1;
						enemy[i].point = 200;
						break;
					default:
						break;
					}
					enemy[i].move_pattern = 0;
					enemy[i].aliveflag = 0;
					enemy[i].enemy_clearflag = 0;
					enemy[i].bossflag = 0;
				}

				boss[0].handle = LoadGraph("images/boss1.png");
				boss[0].pos = { 4 * CHIP_SIZE, CHIP_SIZE };
				boss[0].speed = 2;
				boss[0].aliveflag = 0;
				boss[0].bossflag = 1;
				boss[0].enemy_clearflag = 0;
				boss[0].move_pattern = 0;
				boss[0].MAXHP = 15;
				boss[0].point = 1000;


				for (int i = 0; i < 100; i++) {
					arrow_1[i].speed = 16;
					arrow_1[i].intervalflag = 0;
					arrow_1[i].handle = arrow_handle;
					arrow_1[i].drawinterval = 10;
					arrow_1[i].intervalcount = 0;
					arrow_1[i].shootflag = 0;
					arrow_1[i].distance = 0;
					arrow_1[i].range = 0;
					arrow_1[i].chargetime = 0;
					arrow_1[i].damage = 1;
				}

				for (int i = 0; i < 100; i++) {
					boss_atk_1[i].speed = 8;
					boss_atk_1[i].intervalflag = 0;
					boss_atk_1[i].handle = boss_atk_1_handle;
					boss_atk_1[i].drawinterval = 10;
					boss_atk_1[i].intervalcount = 0;
					boss_atk_1[i].shootflag = 0;
					boss_atk_1[i].distance = 0;
					boss_atk_1[i].range = 0;
					boss_atk_1[i].chargetime = 0;
					boss_atk_1[i].damage = 3;
				}
				Init_map();
				clear_flag = 0;
				gameover_count = 0;
				for (int i = 0; i < 100; i++) {
					base_time[i] = 0;
				}
				SRand(GetNowCount());//乱数の初期化
				start_time = GetNowCount();//ゲーム開始した時刻を基準にする
				totalpoint = 0;
				minuspoint = 0;
				PlaySoundMem(bgm_handle[1], DX_PLAYTYPE_BACK | DX_PLAYTYPE_LOOP);
			}
			break;
		case 4:
			DrawGraph(0, 0, screen[2], FALSE); //リザルト画像の描画
			time = GetNowCount() - cleartime;
			Draw_result(myCharacter, durability, totalpoint, minuspoint, resultcount, se_handle);
			if (time - base_time[4] >= 1000 && CheckSoundMem(se_handle[7]) == 0 && resultcount < 4) { //1000msごとに処理
				base_time[4] = time;
				resultcount++;
				PlaySoundMem(se_handle[7], DX_PLAYTYPE_BACK);
			}
			if (time - base_time[4] >= 1000 && CheckSoundMem(se_handle[7]) == 1 && resultcount == 4) { //1000msごとに処理
				resultcount++;
				StopSoundMem(se_handle[7]);
				PlaySoundMem(se_handle[8], DX_PLAYTYPE_BACK);
			}
			if (time - base_time[4] >= 1500 && CheckSoundMem(se_handle[7]) == 1) {
				base_time[5] = time;
				StopSoundMem(se_handle[7]);
			}

			if (time >= 7000) {
				if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_SPACE] == 1) { //スペースキーまたはエンターキーが押されたとき
					WinFlag = 2; //終了画面へ
					tips = 0;
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
int KeyCalc_menu(int SelectNum, int bgm_handle[], int se_handle[])
{
	if (Key[KEY_INPUT_DOWN] == 1) { // 上キーが押された瞬間だけ処理

		SelectNum = (SelectNum + 1) % 2; // 現在の選択項目を一つ上にずらす(逆ループする)
		PlaySoundMem(se_handle[0], DX_PLAYTYPE_BACK); 
	}
	if (Key[KEY_INPUT_UP] == 1) { // 上キーが押された瞬間だけ処理

		SelectNum = SelectNum % 2; // 現在の選択項目を一つ上にずらす(逆ループする)
		PlaySoundMem(se_handle[0], DX_PLAYTYPE_BACK);
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
		if (MainMenu[0].flag == 1) { PlaySoundMem(se_handle[1], DX_PLAYTYPE_BACK); return 1; } //"ゲームスタート"が選択されている
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
		if (Hit_map(map, c) == 1) c.pos.x = oldp.x;

	}
    if (Key[KEY_INPUT_DOWN] >= 1) {
		c.move_v = 1;
		c.pos.y += 6;
		if (Hit_map(map, c) == 1) c.pos.y = oldp.y;
	}
	if (Key[KEY_INPUT_LEFT] >= 1) {
		c.move_v = 2;
		c.pos.x -= 6;
		if (Hit_map(map, c) == 1) c.pos.x = oldp.x;
	}
	if (Key[KEY_INPUT_UP] >= 1) {
		c.move_v = 3;
		c.pos.y -= 6;
		if (Hit_map(map, c) == 1) c.pos.y = oldp.y;
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
void Draw_game(Character& c, int time, int gameover_count, int point, int tips)
{

	SetFontSize(20); // 描画する文字列のサイズを設定
	SetFontThickness(3); // 描画する文字列の太さを設定
	//ステータス画面用のウィンドウ
	DrawBox(MAP_WIDTH*CHIP_SIZE, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0,0,0), TRUE);

	DrawFormatString(Status[0].x, Status[0].y, GetColor(255, 255, 255), Status[0].name.c_str());
	if(c.HP >= 7) DrawBox(650, 150, 650 + 30*c.HP, 200, GetColor(0, 255, 0), TRUE);
	else if(4 <= c.HP && c.HP < 7)  DrawBox(650, 150, 650 + 30 * c.HP, 200, GetColor(255, 255, 0), TRUE);
	else if ( c.HP < 4)  DrawBox(650, 150, 650 + 30 * c.HP, 200, GetColor(255, 0, 0), TRUE);

	DrawFormatString(Status[1].x, Status[1].y, GetColor(255, 255, 255), Status[1].name.c_str());
	if ((10- gameover_count) >= 7) DrawBox(650, 250, 650 + 30 * (10-gameover_count), 300, GetColor(0, 255, 0), TRUE);
	else if (4 <= (10 - gameover_count) && (10 - gameover_count) < 7)  DrawBox(650, 250, 650 + 30 * (10 - gameover_count), 300, GetColor(255, 255, 0), TRUE);
	else if ((10 - gameover_count) < 4)  DrawBox(650, 250, 650 + 30 * (10 - gameover_count), 300, GetColor(255, 0, 0), TRUE);

	ostringstream score;
	score << Status[2].name.c_str() << point;
	DrawFormatString(Status[2].x, Status[2].y, GetColor(255, 255, 255), score.str().c_str());

	DrawFormatString(manual[0].x, manual[0].y, GetColor(255, 255, 255), manual[0].name.c_str());
	DrawFormatString(manual[1].x, manual[1].y, GetColor(255, 255, 255), manual[1].name.c_str());
	DrawFormatString(manual[2].x, manual[2].y, GetColor(255, 255, 255), manual[2].name.c_str());
	DrawFormatString(manual[3].x, manual[3].y, GetColor(255, 255, 255), manual[3].name.c_str());
	if (tips == 0) DrawFormatString(manual[4].x, manual[4].y, GetColor(255, 255, 255), manual[4].name.c_str());
	else if (tips == 1) DrawFormatString(manual[5].x, manual[5].y, GetColor(255, 255, 255), manual[5].name.c_str());
	else if (tips == 2) DrawFormatString(manual[6].x, manual[6].y, GetColor(255, 255, 255), manual[6].name.c_str());

	////でばっぐ用に座標を出力
	//ostringstream position;
	//position << debug[0].name.c_str() << c.pos.x << "," << c.pos.y << ")";
	//ostringstream key;
	//key << debug[1].name.c_str() << endl << "↑ " << Key[KEY_INPUT_UP] << " ↓ " << Key[KEY_INPUT_DOWN] << "→ " << Key[KEY_INPUT_RIGHT] << " ← " << Key[KEY_INPUT_LEFT] << " Z " << Key[KEY_INPUT_Z];
	////debug[0].name = position.str();
	//ostringstream timer;
	//timer << debug[2].name.c_str() << time/1000 << " s";
	//ostringstream gameovercounter;
	//gameovercounter << debug[3].name.c_str() << gameover_count;
	//DrawFormatString(debug[0].x, debug[0].y, GetColor(255, 255, 255), position.str().c_str());
	//DrawFormatString(debug[1].x, debug[1].y, GetColor(255, 255, 255), key.str().c_str());
	//DrawFormatString(debug[2].x, debug[2].y, GetColor(255, 255, 255), timer.str().c_str());
	//DrawFormatString(debug[3].x, debug[3].y, GetColor(255, 255, 255), gameovercounter.str().c_str());

}

/*****
=====================================
エンディング画面のキー入力 : int KeyCalc_ending(int SelectNum)
=====================================
引数
int SelectNum : 現在選択中のメニュー
=====================================
戻り値
0 : ゲームスタートが選択されたとき
-1 : ゲーム終了が選択されたとき
2 : エンディング画面の維持
=====================================
*****/
int KeyCalc_ending(int SelectNum, int bgm_handle[], int se_handle[])
{
	if (Key[KEY_INPUT_DOWN] == 1) { // 上キーが押された瞬間だけ処理

		SelectNum = (SelectNum + 1) % 2; // 現在の選択項目を一つ上にずらす(逆ループする)
		PlaySoundMem(se_handle[0], DX_PLAYTYPE_BACK);
	}
	if (Key[KEY_INPUT_UP] == 1) { // 上キーが押された瞬間だけ処理

		SelectNum = SelectNum % 2; // 現在の選択項目を一つ上にずらす(逆ループする)
		PlaySoundMem(se_handle[0], DX_PLAYTYPE_BACK);
	}
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_UP] == 1) { // 下キーが押された瞬間だけ処理
		for (int i = 0; i < 2; i++) {              // メニュー項目数である2個ループ処理
			if (i == SelectNum) {          // 今処理しているのが、選択番号と同じ要素なら
				Ending[i].flag = 1;      //選択されているものを1にする
			}
			else {                       // 今処理しているのが、選択番号以外なら
				Ending[i].flag = 0;// 選択されているものを0にする
			}
		}
	}

	if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_SPACE] == 1) { //スペースキーまたはエンターキーが押されたとき
		if (Ending[0].flag == 1) { PlaySoundMem(se_handle[1], DX_PLAYTYPE_BACK); return 0; } //"タイトルに戻る"が選択されている
		if (Ending[1].flag == 1) return -1; //"ゲーム終了"が選択されている
	}

	return 2;
}



/*****
=====================================
ゲームエンディング画面 : void Draw_ending()
=====================================
引数
なし
=====================================
戻り値
なし
=====================================
*****/
void Draw_ending()
{
	SetFontSize(64); // 描画する文字列のサイズを設定
	SetFontThickness(3); // 描画する文字列の太さを設定
	for (int i = 0; i < 2; i++) { // メニュー項目を描画
		if (Ending[i].flag == 0) DrawFormatString(Ending[i].x, Ending[i].y, GetColor(0, 0, 0), Ending[i].name.c_str());
		else if (Ending[i].flag == 1) DrawFormatString(Ending[i].x, Ending[i].y, GetColor(255, 0, 0), Ending[i].name.c_str());
	}
}

/*****
=====================================
ゲームオーバー画面のキー入力 : int KeyCalc_gameover(int SelectNum)
=====================================
引数
int SelectNum : 現在選択中のメニュー
=====================================
戻り値
0 : リトライ(再びゲームを再開する)が選択されたとき
-1 : タイトルに戻るが選択されたとき
3 : ゲームオーバー画面の維持
=====================================
*****/
int KeyCalc_gameover(int SelectNum, int bgm_handle[], int se_handle[])
{

	if (Key[KEY_INPUT_DOWN] == 1) { // 上キーが押された瞬間だけ処理

		SelectNum = (SelectNum + 1) % 2; // 現在の選択項目を一つ上にずらす(逆ループする)
		PlaySoundMem(se_handle[0], DX_PLAYTYPE_BACK);
	}
	if (Key[KEY_INPUT_UP] == 1) { // 上キーが押された瞬間だけ処理

		SelectNum = SelectNum % 2; // 現在の選択項目を一つ上にずらす(逆ループする)
		PlaySoundMem(se_handle[0], DX_PLAYTYPE_BACK);
	}
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_UP] == 1) { // 下キーが押された瞬間だけ処理
		for (int i = 0; i < 2; i++) {              // メニュー項目数である2個ループ処理
			if (i == SelectNum) {          // 今処理しているのが、選択番号と同じ要素なら
				Gameover[i].flag = 1;      //選択されているものを1にする
			}
			else {                       // 今処理しているのが、選択番号以外なら
				Gameover[i].flag = 0;// 選択されているものを0にする
			}
		}
	}

	if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_SPACE] == 1) { //スペースキーまたはエンターキーが押されたとき
		PlaySoundMem(se_handle[1], DX_PLAYTYPE_BACK);
		if (Gameover[0].flag == 1) return 1; //"リトライ"が選択されている
		if (Gameover[1].flag == 1) return 0; //"タイトルに戻る"が選択されている
	}
	return 3;
}

/*****
=====================================
ゲームオーバー画面 : void Draw_gameover()
=====================================
引数
なし
=====================================
戻り値
なし
=====================================
*****/
void Draw_gameover()
{
	SetFontSize(64); // 描画する文字列のサイズを設定
	SetFontThickness(3); // 描画する文字列の太さを設定
	for (int i = 0; i < 2; i++) { // メニュー項目を描画
		if (Gameover[i].flag == 0) DrawFormatString(Gameover[i].x, Gameover[i].y, GetColor(0, 0, 0), Gameover[i].name.c_str());
		else if (Gameover[i].flag == 1) DrawFormatString(Gameover[i].x, Gameover[i].y, GetColor(255, 0, 0), Gameover[i].name.c_str());
	}
}

/*****
=====================================
結果画面 : void Draw_result()
=====================================
引数
なし
=====================================
戻り値
なし
=====================================
*****/
void Draw_result(Character& c, int durability, int point, int minusp, int timing, int se_handle[])
{
	int total = point + c.HP * 100 + durability * 100 - minusp * 10;

	SetFontSize(30); // 描画する文字列のサイズを設定
	SetFontThickness(20); // 描画する文字列の太さを設定
	ostringstream result;
/*
	if (timing < 1000) {
		result << "Result" << endl << endl;
		if (CheckSoundMem(se_handle[7]) == 0) {
			PlaySoundMem(se_handle[7], DX_PLAYTYPE_BACK);
		}
	}
	if (1000 <= timing && timing < 2000) {
		result << "Result" << endl << endl << "Score" << endl;
	}
	if (2000 <= timing && timing < 3000) {
		result << "Result" << endl << endl << "Score" << endl << "Base : " << point << endl;
	if (CheckSoundMem(se_handle[7]) == 0) {
			PlaySoundMem(se_handle[7], DX_PLAYTYPE_BACK);
		}
	}
	if (3000 <= timing && timing < 4000) {
		result << "Result" << endl << endl << "Score" << endl << "Base : " << point << endl << "Bonus : " << c.HP * 100 << "(HP×100) " << durability * 100 << "(防衛度×100)";
		if (CheckSoundMem(se_handle[7]) == 0) {
			PlaySoundMem(se_handle[7], DX_PLAYTYPE_BACK);
		}
	}
	if (4000 <= timing && timing < 6000){
		result << "Result" << endl << endl << "Score" << endl << "Base : " << point << endl << "Bonus : " << c.HP * 100 << "(HP×100) " << durability * 100 << "(防衛度×100)" << endl << "Minus : " << minusp * 10 << "(矢の発射数×10)" << endl;
		if (CheckSoundMem(se_handle[7]) == 0) {
			PlaySoundMem(se_handle[7], DX_PLAYTYPE_BACK);
		}
	}
	if (6000 <= timing) {
		result << "Result" << endl << endl << "Score" << endl << "Base : " << point << endl << "Bonus : " << c.HP * 100 << "(HP×100) " << durability * 100 << "(防衛度×100)" << endl << "Minus : " << minusp * 10 << "(矢の発射数×10)" << endl << "Total : " << total;
		PlaySoundMem(se_handle[7], DX_PLAYTYPE_BACK);
	}
*/
	switch (timing) {
	case 0:
		result << "Result" << endl << endl;
/*
		if (CheckSoundMem(se_handle[7]) == 0) {
			PlaySoundMem(se_handle[7], DX_PLAYTYPE_BACK);
		}*/
		break;
	case 1:
		result << "Result" << endl << endl << "Score" << endl;
		break;
	case 2:
		result << "Result" << endl << endl << "Score" << endl << "Base : " << point << endl;
		/*if (CheckSoundMem(se_handle[7]) == 0) {
			PlaySoundMem(se_handle[7], DX_PLAYTYPE_BACK);
		}*/
		break;
	case 3:
		result << "Result" << endl << endl << "Score" << endl << "Base : " << point << endl << "Bonus : " << c.HP * 100 << "(HP×100) " << durability * 100 << "(防衛度×100)";
		/*if (CheckSoundMem(se_handle[7]) == 0) {
			PlaySoundMem(se_handle[7], DX_PLAYTYPE_BACK);
		}*/
		break;
	case 4:
		result << "Result" << endl << endl << "Score" << endl << "Base : " << point << endl << "Bonus : " << c.HP * 100 << "(HP×100) " << durability * 100 << "(防衛度×100)" << endl << "Minus : " << minusp * 10 << "(矢の発射数×10)" << endl;
		/*if (CheckSoundMem(se_handle[7]) == 0) {
			PlaySoundMem(se_handle[7], DX_PLAYTYPE_BACK);
		}*/
		break;
	case 5:
		result << "Result" << endl << endl << "Score" << endl << "Base : " << point << endl << "Bonus : " << c.HP * 100 << "(HP×100) " << durability * 100 << "(防衛度×100)" << endl << "Minus : " << minusp * 10 << "(矢の発射数×10)" << endl << "Total : " << total;
		//PlaySoundMem(se_handle[8], DX_PLAYTYPE_BACK);
		break;
	default:
		break;
	}
	DrawFormatString(190, 300, GetColor(0, 0, 0), result.str().c_str());

	ostringstream message;
	message << "Press Enter or Space";
	if ( timing == 5) {
		DrawFormatString(330, 600, GetColor(0, 0, 0), message.str().c_str());
	}


}
