#include "CPlayer.h"
#include "CScene.h"
#include "CWind.h"
#include "CSceneManager.h"
#include "CGameManager.h"
#include "CSmoothing.h"
#include "CEase.h"

// コントローラーを使う場合はtrueを指定
#define USE_CONTROLLER (true)

//明示的に親クラスのコンストラクタを呼び出す
CPlayer::CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
{
	// スケールの初期値を設定
	ini_scale = { transform.scale.x,transform.scale.y, 1.0f };

	// 初期スピード設定
	SetMoveSpeed(0.01f);
	smoothing = new CSmoothing();
	// 重力を初期値とする
	velocity.y = gravity;

	nockf = false;
	nockT = false;
	test = true;

	// ダメージエフェクトオブジェクト
	damageEffect = new CGameObject(vertexBufferEffect, CTextureLoader::GetInstance()->GetTex(TEX_ID::DAMAGE_FX), {0.2f, 0.5f});
	damageEffect->InitAnimParameter(false, 5, 2, ANIM_PATTERN::DAMAGE, 0.3f);
	damageEffect->transform.scale = { 120.0f * 0.0025f, 120.0f * 0.0025f, 1.0f };
	damageEffect->SetActive(false);

	// クラッカー
	kurakka_L = new CGameObject(vertexBufferEffect, CTextureLoader::GetInstance()->GetTex(TEX_ID::KURAKKA), { 0.125f, 1.0f });
	kurakka_L->transform.position = { -1.0f, -1.8f, -0.11f };
	kurakka_L->transform.scale = { 374.0f * 0.004f, 374.0f * 0.004f, 1.0f };
	kurakka_L->InitAnimParameter(false, 8, 1, ANIM_PATTERN::KURAKKA_L, 0.25f);
	kurakka_L->SetActive(false);
	// クラッカーのイージング
	kurakkaEase_L = new CEase;
	kurakkaEase_L->Init(&kurakka_L->transform.position.y, -0.45f, 0.8f, 0, EASE::easeOutCubic);

	// クラッカー右
	kurakka_R = new CGameObject(vertexBufferEffect, CTextureLoader::GetInstance()->GetTex(TEX_ID::KURAKKA_REVERSE), { 0.125f, 1.0f });
	kurakka_R->transform.position = { 1.0f, -1.8f, -0.11f };
	kurakka_R->transform.scale = { 374.0f * 0.004f, 374.0f * 0.004f, 1.0f };
	kurakka_R->InitAnimParameter(false, 8, 1, ANIM_PATTERN::KURAKKA_R, 0.25f);
	kurakka_R->SetActive(false);
	// クラッカー右のイージング
	kurakkaEase_R = new CEase;
	kurakkaEase_R->Init(&kurakka_R->transform.position.y, -0.45f, 0.8f, 0, EASE::easeOutCubic);

	// ゲームオーバー演出用背景
	gameoverBg = new CGameObject(vertexBufferEffect, CTextureLoader::GetInstance()->GetTex(TEX_ID::FADE));
	gameoverBg->transform.scale = { 1920.0f * 0.003f, 1080.0f * 0.003f, 1.0f };
	gameoverBg->SetActive(false);
	// ゲームオーバー演出用イージング
	gameoverEaseX = new CEase;
	gameoverEaseY = new CEase;
}

void CPlayer::PlayerInput()
{
	// ノックバック時、クリアまたはゲームオーバー時は入力を受け付けない
	if (nockf || clearFlg || gameOverFlg)
	{
		return;
	}

#if USE_CONTROLLER == true

	// スティックの入力を保存
	input_stickX = gInput->GetLeftStickX();
	input_stickY = gInput->GetLeftStickY();
	input_stickX2 = gInput->GetRightStickX();
	input_stickY2 = gInput->GetRightStickY();
	switch (State)
	{
	case PState::NORMAL: //通常状態
		if (anim->GetIsAnimation() == false)
		{
			// 前のフレームでめり込んだ方向でないなら移動量を適応する
			if ((input_stickX > 0.0f && prevFrameCorrect.x != -1) ||
				(input_stickX < 0.0f && prevFrameCorrect.x != 1))
			{
				dir.x = input_stickX;
			}
			// 前のフレームでめり込んだ方向に移動しようとしてるなら移動量を適応しない
			else
			{
				dir.x = 0;
			}
			if (input_stickX < 0.0f)
			{
				SetAnimationPattern(ANIM_PATTERN::LEFTWALK);// 左に歩くアニメーション再生
				FInput_dir.x = -1.0f;
			}
			else if (input_stickX > 0.0f)
			{
				SetAnimationPattern(ANIM_PATTERN::RIGHTWALK);// 右に歩くアニメーション再生
				FInput_dir.x = 1.0f;
			}

			if (input_stickX == 0)
			{
				// 最後に入力された方向に応じてアニメーションを変更
				if (FInput_dir.x == 1.0f)
				{
					SetAnimationPattern(ANIM_PATTERN::IDOL_R);// アイドルアニメーション再生
				}
				else
				{
					SetAnimationPattern(ANIM_PATTERN::IDOL_L);// アイドルアニメーション再生
				}
			}
			if ((input_stickY < 0.0f) && prevFrameCorrect.y == 1 && (input_stickY2 < 0.0f))
			{
				// 倒れる効果音再生
				XA_Play(SOUND_LABEL_FALL);
				SetState(PState::FALL);// 倒れる
				// 最後に入力された方向に応じてアニメーションを変更
				if (FInput_dir.x == 1.0f)
				{
					SetAnimationPattern(ANIM_PATTERN::FALLDOWN);// 倒れたアニメーション再生
				}
				else
				{
					SetAnimationPattern(ANIM_PATTERN::FALLDOWN_L);// 倒れたアニメーション再生
				}
				anim->SetIsAnimation(true);
			}
		}
		break;
	case PState::FALL:// 倒れた状態
		// 入力された、かつ起き上がれるなら起き上がる
		if ((input_stickY > 0.0f) && (input_stickY2 > 0.0f) && (old_input_stickY >= 0.0f) && !CheckStandCollision())
		{
			// 起き上がる効果音再生
			XA_Play(SOUND_LABEL_GETUP);
			SetState(PState::NORMAL);// 通常状態に戻す
			// 最後に入力された方向に応じてアニメーションを変更
			if (FInput_dir.x == 1.0f)
			{
				SetAnimationPattern(ANIM_PATTERN::GETUP);// 起き上がるアニメーション再生
			}
			else
			{
				SetAnimationPattern(ANIM_PATTERN::GETUP_L);// 起き上がるアニメーション再生
			}
			anim->SetIsAnimation(true);
		}
		if (input_stickX2 <= -1.0f && (old_input_stickX2 > -1.0f))
		{
			// 折れる音
			XA_Play(SOUND_LABEL_BREAK);
			SetState(PState::BREAKLEFT);// 左に折れる
			SetAnimationPattern(ANIM_PATTERN::BREAKLEFT);// 左に折れるアニメーション再生
			anim->SetIsAnimation(true);
		}
		if (input_stickX2 >= 1.0f && (old_input_stickX2 < 1.0f))
		{
			// 折れる音
			XA_Play(SOUND_LABEL_BREAK);
			SetState(PState::BREAKRIGHT);// 右に折れる
			SetAnimationPattern(ANIM_PATTERN::BREAKRIGHT);// 右に折れるアニメーション再生
			anim->SetIsAnimation(true);
		}
		// Bボタン入力でとりあえずのジャンプ操作
		if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A) && jumpCount != 2)
		{
			// ジャンプ音
			XA_Play(SOUND_LABEL_JUMP);
			isJump = true;
			jumpStrength = ini_jumpStrength;
			//ジャンプアニメーション
			SetAnimationPattern(ANIM_PATTERN::JAMP);
			anim->SetIsAnimation(true);
			jumpCount++;
		}

		if (prevFrameCorrect.y == 1 && !anim->GetIsAnimation())
		{
			SetAnimationPattern(ANIM_PATTERN::FALL);
		}

		break;
	case PState::BREAKLEFT:// 左に折れた状態
		if (anim->GetIsAnimation() == false)
		{
			if (input_stickX2 >= 1.0f && (old_input_stickX2 < 1.0f))
			{
				SetState(PState::FALL);// 倒れた状態に戻す
				SetAnimationPattern(ANIM_PATTERN::FIXLEFT);// 折れたのが直るアニメーション再生
				anim->SetIsAnimation(true);
				isWindLeft = true;    //  左向き
			}
		}
		break;
	case PState::BREAKRIGHT:// 右に折れた状態
		if (anim->GetIsAnimation() == false)
		{
			if (input_stickX2 <= -1.0f && (old_input_stickX2 < -1.0f))
			{
				SetState(PState::FALL);// 倒れた状態に戻す
				SetAnimationPattern(ANIM_PATTERN::FIXRIGHT);// 折れたのが直るアニメーション再生
				anim->SetIsAnimation(true);
			}
		}
		break;
	default:
		break;
	}
	old_input_stickX = input_stickX;
	old_input_stickY = input_stickY;
	old_input_stickX2 = input_stickX2;
	old_input_stickY2 = input_stickY2;


#else
	switch (State)
	{
	case PState::NORMAL:// 通常状態の処理
		//SetAnimationPattern(ANIM_PATTERN::NO_ANIM);
		//else if (gInput->GetKeyPress(VK_UP) && prevFrameCorrect.y != -1)
		//{
		//	if (!gInput->GetKeyPress(VK_DOWN))
		//	{
		//		//dir.y = 1.0f;
		//		prevFrameDir.y = dir.y;
		//	}
		//	else
		//	{
		//		dir.y = prevFrameDir.y;
		//	}
		//}
		if (anim->GetIsAnimation() == false)
		{
			if (gInput->GetKeyPress(VK_LEFT) && prevFrameCorrect.x != 1)
			{
				if (!gInput->GetKeyPress(VK_RIGHT))
				{
					dir.x = -1.0f;
					prevFrameDir.x = dir.x;
					SetAnimationPattern(ANIM_PATTERN::LEFTWALK);// 左に歩くアニメーション再生

				}
				else
				{
					fly = false;
					dir.x = prevFrameDir.x;
				}
			}
			else if (gInput->GetKeyPress(VK_RIGHT) && prevFrameCorrect.x != -1)
			{
				//dir.y = prevFrameDir.y;
				if (!gInput->GetKeyPress(VK_LEFT))
				{
					dir.x = 1.0f;
					prevFrameDir.x = dir.x;
					SetAnimationPattern(ANIM_PATTERN::RIGHTWALK);// 右に歩くアニメーション再生
				}
				else
				{
					dir.x = prevFrameDir.x;
				}
			}
			if (gInput->GetKeyPress(VK_DOWN) && prevFrameCorrect.y == 1)
			{
				if (!gInput->GetKeyPress(VK_UP))
				{
					/*dir.y = -1.0f;
					prevFrameDir.y = dir.y;*/

					SetState(PState::FALL);// 倒れた状態
					SetAnimationPattern(ANIM_PATTERN::FALLDOWN);// 倒れたアニメーション再生
					anim->SetIsAnimation(true);
					isWindUp = true;
				}
				else
				{
					/*dir.y = prevFrameDir.y;*/
				}
			}

			else if (!gInput->GetKeyPress(VK_RIGHT) && !gInput->GetKeyPress(VK_LEFT) && !gInput->GetKeyPress(VK_UP) && !gInput->GetKeyPress(VK_DOWN))
			{
				SetAnimationPattern(ANIM_PATTERN::NO_ANIM);// 動かないアニメーション再生
			}
		}
		break;

	case PState::FALL:// 倒れた状態の処理
		if (anim->GetIsAnimation() == false)
		{
			if (gInput->GetKeyPress(VK_UP))
			{
				if (!gInput->GetKeyPress(VK_DOWN))
				{
					SetState(PState::NORMAL);// 通常状態
					SetAnimationPattern(ANIM_PATTERN::GETUP);// 起き上がるアニメーション再生
					anim->SetIsAnimation(true);
					isWindLeft = false;
					isWindUp = false;	//	下からの風を受けない
					isWindRight = false;	//	風を受けない
				}
				else
				{

				}
			}
			if (gInput->GetKeyTrigger(VK_LEFT))
			{
				if (!gInput->GetKeyTrigger(VK_RIGHT))
				{
					SetState(PState::BREAKLEFT);// 左に折れる状態
					SetAnimationPattern(ANIM_PATTERN::BREAKLEFT);// 左に折れるアニメーション再生
					anim->SetIsAnimation(true);
					isWindRight = true;	//	風を受ける
					isWindUp = false;	//	上向きの風を受けない
				}
				else
				{

				}
			}
			else if (gInput->GetKeyTrigger(VK_RIGHT))
			{
				if (!gInput->GetKeyTrigger(VK_LEFT))
				{
					SetState(PState::BREAKRIGHT);// 右に折れる状態
					SetAnimationPattern(ANIM_PATTERN::BREAKRIGHT);// 右に折れるアニメーション再生
					anim->SetIsAnimation(true);
					isWindLeft = true;
					isWindUp = false;	//	上向きの風を受けない
				}
				else
				{

				}
			}

			else if (gInput->GetKeyTrigger(VK_TAB))
			{
				isJump = true;
				//--------------------------------
				//無限ジャンプ不可にしたい場合は下の１行を消してください
				jumpStrength = ini_jumpStrength;
				//--------------------------------

				SetAnimationPattern(ANIM_PATTERN::JAMP);
				anim->SetIsAnimation(true);
			}

			if (prevFrameCorrect.y == 1 && !anim->GetIsAnimation())
			{
				SetAnimationPattern(ANIM_PATTERN::FALL);
			}
		}
		break;

	case PState::BREAKLEFT:
		if (anim->GetIsAnimation() == false)
		{
			if (gInput->GetKeyTrigger(VK_RIGHT))
			{
				if (!gInput->GetKeyTrigger(VK_LEFT))
				{
					SetState(PState::FALL);// 倒れた状態
					SetAnimationPattern(ANIM_PATTERN::FIXLEFT);// 折れたのが直るアニメーション再生
					anim->SetIsAnimation(true);
					isWindRight = false;	//	風を受けない
					isWindUp = true;
				}
				else
				{

				}
			}
		}
		break;

	case PState::BREAKRIGHT:
		if (anim->GetIsAnimation() == false)
		{
			if (gInput->GetKeyTrigger(VK_LEFT))
			{
				if (!gInput->GetKeyTrigger(VK_RIGHT))
				{
					SetState(PState::FALL);// 倒れた状態
					SetAnimationPattern(ANIM_PATTERN::FIXRIGHT);// 折れたのが直るアニメーション再生
					anim->SetIsAnimation(true);
					isWindLeft = false;
					isWindUp = true;
				}
				else
				{

				}
			}
		}
		break;

	default:
		break;
	}
#endif
}

float CPlayer::Jump()
{
	// ジャンプ力を重力に従って更新
	jumpStrength = jumpStrength - gravity;
	velocity.y -= jumpStrength;
	if (jumpStrength <= 0.0f)
	{
		jumpStrength = 0.0f;
		isJump = false;
	}
	// 計算したジャンプ力を適応
	return velocity.y;
}

void CPlayer::ReceiveWind()
{
	// 左から右
	if (dir_wind.x == 1.0f)
	{
		// 風力を弱める
		receiveWindPower.x -= 0.001f;
		// 風力が0なら受けている方向を元に戻す
		if (receiveWindPower.x <= 0.0f)
		{
			dir_wind.x = 0.0f;
			receiveWindPower.x = 0.0f;
		}
		// 風の計算を移動量に加える
		this->transform.position.x += receiveWindPower.x;
	}
	// 右から左
	else if (dir_wind.x == -1.0f)
	{
		// 風力を弱める
		receiveWindPower.x -= 0.001f;
		// 風力が0なら受けている方向を元に戻す
		if (receiveWindPower.x <= 0.0f)
		{
			dir_wind.x = 0.0f;
			receiveWindPower.x = 0.0f;
		}
		// 風の計算を移動量に加える
		this->transform.position.x -= receiveWindPower.x;
	}
	// 下から上
	if (dir_wind.y == 1.0f)
	{
		// 風力を弱める
		receiveWindPower.y -= 0.001f;
		// 風力が0なら受けている方向を元に戻す
		if (receiveWindPower.y <= 0.0f)
		{
			dir_wind.y = 0.0f;
			receiveWindPower.y = 0.0f;
		}
		// 風の計算を移動量に加える
		this->transform.position.y += receiveWindPower.y;
	}
}

bool CPlayer::CheckStandCollision()
{
	// 上向きの風を受けているときは戻れるようにする
	if (dir_wind.y == 1.0f)
	{
		return false;
	}

	// 起き上がり後のコライダーの位置
	BoxCollider standBcol = this->Bcol;
	// 起き上がれるかどうかのフラグ
	bool notStand = false;
	// 大きくなった分だけ上にコライダーをずらす
	standBcol.centerY += 0.16f;
	standBcol.sizeY -= 0.2f;
	// 起き上がれるか判定
	for (auto it = CScene::map_object.begin(); it != CScene::map_object.end(); it++)
	{
		// 起き上がった後当たっている、かつ当たっているオブジェクトが普通のタイルなら
		if (CCollision::TestBoxCollision(standBcol, (*it)->Bcol) &&
			((*it)->GetObjectType() == OBJECT_TYPE::NORMAL))
		{
			notStand = true;
		}
	}
	return notStand;
}

void CPlayer::Update()
{
	// ダメージ時の透明度を元に戻す
	if (this->materialDiffuse.w != 1.0f && nockT == false)
	{
		this->materialDiffuse.w = 1.0f;
	}
	if (this->GetState() == PState::NORMAL)
	{
		this->Bcol.sizeY = 0.3f;
		this->Bcol.sizeX = 0.14f;
	}
	else if (this->GetState() != PState::NORMAL)
	{
		this->Bcol.sizeY = 0.14f;
	}

	// 風の影響を受けていないなら向きを戻す
	if (dir_wind.x == 0.0f)
	{
		// 向きを戻す
		dir.x = 0.0f;
	}
	 else if (dir_wind.x == 1.0f)
	{
		gInput->ControllerVibration(7, 10000);
	}
	 else if (dir_wind.x == -1.0f)
	{
		gInput->ControllerVibration(7, 10000);
	}


	if (dir_wind.y == 0.0f)
	{
		// 向きを戻す
		dir.y = -1.0f;
	}
	else if (dir_wind.y == 1.0f)
	{
		gInput->ControllerVibration(7, 10000);
	}
	if (Ddir.x == 0.0f)
	{
		dir.x = 0.0f;
	}
	// ダメージSEプレイ可能になるまでの時間を計測する
	damageSEplayCount = damageSEplayCount < 60 ? damageSEplayCount + 1 : damageSEplayCount;
  
	// ゲームマネージャから状態を取得して、ゲームオーバーならフラグを上げる
	if ((CGameManager::GetInstance()->GetGameState() == GAME_STATE::TIME_UP ||
		CGameManager::GetInstance()->GetGameState() == GAME_STATE::ZERO_HP) && !gameOverFlg)
	{
		gameOverFlg = true;
		// ゲームオーバー演出に使うイージングの初期化
		gameoverEaseX->Init(&transform.position.x, 0.0f, 3.0f, 0, EASE::easeOutSine);
		gameoverEaseY->Init(&transform.position.y, 0.3f, 3.0f, 0, EASE::easeOutSine);
	}
	PlayerInput();

	// ステートに応じてコライダーのサイズを変更
	if (this->GetState() == PState::NORMAL)
	{
		this->Bcol.sizeY = 0.25f;
	}
	else if (this->GetState() != PState::NORMAL)
	{
		this->Bcol.sizeY = 0.1f;
	}

	// 前フレームの補正方向を初期化
	prevFrameCorrect = { 0 };
	prevFrameCorrectY = { 0 };

	// 単位ベクトル化(矢印を１にする) = 正規化
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&dir);	// ベクトル計算用の型に入れる
	v = DirectX::XMVector3Normalize(v);					// 正規化する
	DirectX::XMStoreFloat3(&dir, v);					// 元の変数dirに戻す

	// 風の影響でのy方向の速度が限界値を超えないようにする
	if ((dir_wind.y == 1.0f || dir_wind.y == -1.0f) && velocity.y > velocityY_limit)
	{
		velocity.y = velocityY_limit;
	}

	// 重力の影響を受けてY軸方向の速度を更新
	// ジャンプ中ならジャンプ力の更新処理を行う
	velocity.y = isJump ? Jump() : velocity.y += gravity;

	//ノックバックオブジェクトに当たったのなら以下の処理をする
	if (nockf)
	{
		dir_wind.x = 0.0f;
		//プレイヤーがノックバックした先にカメラを追従させる
		smoothing->Update();
		//プレイヤーがすぐ入力できないようにするためのフレームカウンター
		flameCounter++;
		gInput->ControllerVibration(7, 35000);
		//---------------------------------------------------------//
		//プレイヤーを点滅させる
		if (this->materialDiffuse.w == 1.0f)
		{
			this->materialDiffuse.w = 0.2f;
		}
		else if (this->materialDiffuse.w == 0.2f)
		{
			this->materialDiffuse.w = 1.0f;
		}
		//-----------------------------------------------------------//
		//プレイヤーが入力できない時間を作ってる
		if (flameCounter == 20)
		{
			nockf = false;
			flameCounter = 0.0f;
			// ダメージエフェクトの初期化
			damageEffect->StopAnimation();
			damageEffect->ResetAnimation();
			damageEffect->SetActive(false);
		}
		//---------------------------------------------------------//
	}

	if (nockT == true)
	{
		if (this->GetState() != PState::NORMAL)
		{
			this->SetState(PState::NORMAL);
			SetAnimationPattern(ANIM_PATTERN::GETUP);// 起き上がるアニメーション再生
			anim->SetIsAnimation(true);
		}
		gInput->ControllerVibration(10, 35000);
		flameCounter++;
		//---------------------------------------------------------//
		//プレイヤーを点滅させる
		if (this->materialDiffuse.w == 1.0f)
		{
			this->materialDiffuse.w = 0.2f;
		}
		else if (this->materialDiffuse.w == 0.2f)
		{
			this->materialDiffuse.w = 1.0f;
		}
		//flameCounteMK2で無敵の時間を決めています（６０フレーム）
		if (flameCounter == 120 && nockT == true)
		{	
			//nockTがfalseになるとプレイヤーの当たり判定が復活（縦軸）
			nockT = false;
			flameCounter = 0.0f;
			// ダメージエフェクトの初期化
			damageEffect->StopAnimation();
			damageEffect->ResetAnimation();
			damageEffect->SetActive(false);
		}
	}

	// ゲーム開始状態の時以外は移動、当たり判定の処理をしない
	if (CGameManager::GetInstance()->GetGameState() == GAME_STATE::CLEAR ||
		CGameManager::GetInstance()->GetGameState() == GAME_STATE::TIME_UP ||
		CGameManager::GetInstance()->GetGameState() == GAME_STATE::ZERO_HP)
	{
		// リザルトに遷移するまでの時間を計測
		ResultShiftCount++;
		// ゲームオーバー時の処理
		if (gameOverFlg)
		{
			// 背景を有効化する
			gameoverBg->SetActive(true);
			// ゲームオーバー時の背景をプレイヤーの位置とカメラに合わせる
			gameoverBg->SetUseingCamera(this->useCamera);
			gameoverBg->transform.position = { this->useCamera->cameraPos.x, this-> useCamera->cameraPos.y };
			// 拡大率を変更
			gameoverPlayerUpperSize = gameoverPlayerUpperSize < 1.5f ? gameoverPlayerUpperSize + 0.01f : gameoverPlayerUpperSize;
			// プレイヤーの大きさを拡大する
			this->transform.scale = { ini_scale.x * gameoverPlayerUpperSize, ini_scale.y * gameoverPlayerUpperSize, 1.0f };
			gameoverEaseX->Update();
			gameoverEaseY->Update();

			// ダウンアニメーション再生
			SetAnimationPattern(ANIM_PATTERN::PLAYER_DOWN);
			SetAnimationSpeed(0.3f);
			// 180フレームたったら終了状態に設定
			if (ResultShiftCount >= 240)
			{
				this->SetState(PState::CLEAR_GAMEOVER);
			}
		}
		// クリア時の処理
		else if (clearFlg)
		{
			// クラッカーをアクティブに
			kurakka_L->SetActive(true);
			kurakka_R->SetActive(true);
			// クラッカーのイージングを更新
			kurakkaEase_L->Update();
			kurakkaEase_R->Update();
			// 60フレーム後に効果音とアニメーション再生
			if (ResultShiftCount == 60)
			{
				XA_Play(SOUND_LABEL_KURAKKA);
				kurakka_L->PlayAnimation();
				kurakka_R->PlayAnimation();
			}
			// 180フレームたったら終了状態に設定
			if (ResultShiftCount >= 180)
			{
				this->SetState(PState::CLEAR_GAMEOVER);
			}
		}
		// 親クラスのUpdate()を明示的に呼び出す
		// 全てのゲームオブジェクト共通の更新処理を行う
		CGameObject::Update();
	}
	// ゲームオーバー、またはクリアでは無いときに移動、当たり判定の処理をする
	else
	{
		// ベクトルに速度をかけて位置を変更
		this->transform.position.x += dir.x * velocity.x;
		this->transform.position.y -= velocity.y;

		// 風の計算を行う
		ReceiveWind();

		// 親クラスのUpdate()を明示的に呼び出す
		// 全てのゲームオブジェクト共通の更新処理を行う
		CGameObject::Update();

		// 地形との当たり判定と補正
		for (auto it = CScene::map_object.begin(); it != CScene::map_object.end(); it++)
		{
			if (CCollision::TestBoxCollision(this->Bcol, (*it)->Bcol))
			{
				// オブジェクトの種類に応じて処理を変更
				switch ((*it)->GetObjectType())
				{
				case OBJECT_TYPE::NORMAL:	//CSV　値１
					// コライダーの位置を補正し、補正した方向を受け取る
					prevFrameCorrect = CCollision::CorrectPosition(this->Bcol, (*it)->Bcol);
					// 天井にぶつかっていたならジャンプ力を0にする
					if (prevFrameCorrect.y == -1)
					{
						jumpStrength = 0;	// ジャンプ力を0にする
					}
					// 重力によって地面に衝突していたなら
					if (prevFrameCorrect.y == 1)
					{
						velocity.y = 0.0f;				// 速度Yを0に戻す
						jumpStrength = ini_jumpStrength;
						isJump = false;
						jumpCount = 0;
					}
					// オブジェクトの位置とコライダーの中心を合わせる
					this->transform.position.x = this->Bcol.centerX;
					this->transform.position.y = this->Bcol.centerY;
					break;

				case OBJECT_TYPE::SKELETON_TILE:	//CSV 50(透明なタイル)
					// コライダーの位置を補正し、補正した方向を受け取る
					prevFrameCorrect = CCollision::CorrectPosition(this->Bcol, (*it)->Bcol);
					// 天井にぶつかっていたならジャンプ力を0にする
					if (prevFrameCorrect.y == -1)
					{
						jumpStrength = 0;	// ジャンプ力を0にする
					}
					// 重力によって地面に衝突していたなら
					if (prevFrameCorrect.y == 1)
					{
						velocity.y = 0.0f;				// 速度Yを0に戻す
						jumpStrength = ini_jumpStrength;
						isJump = false;
						jumpCount = 0;
					}
					// オブジェクトの位置とコライダーの中心を合わせる
					this->transform.position.x = this->Bcol.centerX;
					this->transform.position.y = this->Bcol.centerY;
					break;

				case OBJECT_TYPE::WIND_RIGHT:	//CSV 値２
					//	アニメーションが終わったら……
					if (anim->GetIsAnimation() == false && this->GetState() == PState::BREAKLEFT)
					{
						// 右向きの風力を取得
						receiveWindPower.x = ((CWind*)(*it))->GetWindStrength();
						// 風を受けた方向と向き保存
						dir.x = 1.0f;
						dir_wind.x = 1.0f;
					}
					break;

				case OBJECT_TYPE::WIND_RIGHTS:	//CSV 値30
					if (this->GetState() == PState::BREAKLEFT)
					{
						// 右向きの風力を取得
						receiveWindPower.x = ((CWind*)(*it))->GetWindStrength();
						// 風を受けた方向と向き保存
						dir.x = 1.0f;
						dir_wind.x = 1.0f;
					}
					break;

				case OBJECT_TYPE::WIND_LEFT:	//CSV 値９
					if (anim->GetIsAnimation() == false && this->GetState() == PState::BREAKRIGHT)
					{
						// 右向きの風力を取得
						receiveWindPower.x = ((CWind*)(*it))->GetWindStrength();
						// 風を受けた方向と向き保存
						dir.x = -1.0f;
						dir_wind.x = -1.0f;
					}
					break;

				case OBJECT_TYPE::WIND_LEFTS:	//CSV 値40
					if (this->GetState() == PState::BREAKRIGHT)
					{
						// 右向きの風力を取得
						receiveWindPower.x = ((CWind*)(*it))->GetWindStrength();
						// 風を受けた方向と向き保存
						dir.x = -1.0f;
						dir_wind.x = -1.0f;
					}
					break;

				case OBJECT_TYPE::WIND_UP:	//CSV 値３
					if (anim->GetIsAnimation() == false && this->GetState() == PState::FALL)
					{
						if (FlyCount == 0)
						{
							//	サウンド再生
							XA_Play(SOUND_LABEL_FLY);
						}

						//	カウントを進めて再生しないようにする
						FlyCount++;

						SetAnimationPattern(ANIM_PATTERN::FLAYING);
						// 上向きの風力を取得
						receiveWindPower.y = ((CWind*)(*it))->GetWindStrengthY();
						// 風を受けた方向と向き保存
						dir.y = 1.0f;
						dir_wind.y = 1.0f;
					}
					break;

					//横向きのダメージタイル
				case OBJECT_TYPE::DAMAGE_TILE:	//CSV 値4
					//	サウンド再生
					XA_Play(SOUND_LABEL_DAMAGEHIT);
					prevFrameCorrect = CCollision::DtestCorrectPosition(this->Bcol, (*it)->Bcol);
					// オブジェクトの位置とコライダーの中心を合わせる
					this->transform.position.x = this->Bcol.centerX;
					this->transform.position.y = this->Bcol.centerY;

					// ノックバックの前にエフェクトをプレイヤーの位置に移動させる
					damageEffect->transform.position = { this->transform.position.x,this->transform.position.y, -0.3f };
					// エフェクトをアクティブに
					damageEffect->SetActive(true);

					//プレイヤーのノックバックの処理
					if (!nockf)
					{
						if (prevFrameCorrect.y == -1.0f)
						{
							moveF = this->transform.position.x - 0.5f;
						}
						//吹っ飛ばす計算式（右）
						if (prevFrameCorrect.x == 1.0f)
						{
							moveF = this->transform.position.x + 0.5f;
						}
						//吹っ飛ばす計算式（左）
						if (prevFrameCorrect.x == -1.0f)
						{
							moveF = this->transform.position.x - 0.5f;
						}
						//追従カメラの初期化
						smoothing->InitSmooth(&moveF, &this->transform.position.x, 0.05f);
						CGameManager::GetInstance()->AddDamage(1);
						nockf = true;

						// エフェクトの再生
						damageEffect->PlayAnimation();
					}
					break;

			case OBJECT_TYPE::DAMAGE_TILEY:	//CSV 値20
				// コライダーの位置を補正し、補正した方向を受け取る
				prevFrameCorrectY = CCollision::CorrectPosition(this->Bcol, (*it)->Bcol);

				//// ノックバックの前にエフェクトをプレイヤーの位置に移動させる
				//damageEffect->transform.position = { this->transform.position.x,this->transform.position.y - 0.15f, -0.3f };
				//// エフェクトをアクティブに
				//damageEffect->SetActive(true);

				// 天井にぶつかっていたならジャンプ力を0にする
				if (prevFrameCorrectY.y == -1)
				{
					jumpStrength = 0;	// ジャンプ力を0にする
				}
				// 重力によって地面に
				if (prevFrameCorrectY.y == 1)
				{
					velocity.y = 0.0f;				// 速度Yを0に戻す
					jumpStrength = ini_jumpStrength;
					isJump = false;
					//もしもプレイヤーの当たり判定がfalseならダメージを受ける
					if (nockT == false)
					{
						CGameManager::GetInstance()->AddDamage(1);
						//プレイヤーの当たり判定を受けないようにするためにtrue;
						//	サウンド再生
						// ノックバックの前にエフェクトをプレイヤーの位置に移動させる
						damageEffect->transform.position = { this->transform.position.x,this->transform.position.y - 0.15f, -0.3f };
						// エフェクトをアクティブに
						damageEffect->SetActive(true);
						XA_Play(SOUND_LABEL_DAMAGEHIT);
						nockT = true;
					}
				}
				// オブジェクトの位置とコライダーの中心を合わせる
				this->transform.position.x = this->Bcol.centerX;
				this->transform.position.y = this->Bcol.centerY;
				// エフェクトの再生
				damageEffect->PlayAnimation();
				break;

			case OBJECT_TYPE::DAMAGE_DOWN:
				prevFrameCorrect = CCollision::DtestCorrectPosition(this->Bcol, (*it)->Bcol);
				// オブジェクトの位置とコライダーの中心を合わせる
				this->transform.position.x = this->Bcol.centerX;
				this->transform.position.y = this->Bcol.centerY;

				// ノックバックの前にエフェクトをプレイヤーの位置に移動させる
				damageEffect->transform.position = { this->transform.position.x,this->transform.position.y, -0.3f };
				// エフェクトをアクティブに
				damageEffect->SetActive(true);

				//プレイヤーのノックバックの処理
				if (!nockf)
				{
					//	サウンド再生
					XA_Play(SOUND_LABEL_DAMAGEHIT);

					if (prevFrameCorrect.y == -1.0f)
					{
						moveF = this->transform.position.x - 0.5f;
					}
					//吹っ飛ばす計算式（右）
					if (prevFrameCorrect.x == 1.0f)
					{
						moveF = this->transform.position.x + 0.5f;
					}
					//吹っ飛ばす計算式（左）
					if (prevFrameCorrect.x == -1.0f)
					{
						moveF = this->transform.position.x - 0.5f;
					}
					//追従カメラの初期化
					smoothing->InitSmooth(&moveF, &this->transform.position.x, 0.05f);
					CGameManager::GetInstance()->AddDamage(1);
					nockf = true;

					// エフェクトの再生
					damageEffect->PlayAnimation();
				}
				break;

				case OBJECT_TYPE::GOAL:	//CSV 値99
					// ゲームクリアの信号を送る
					CGameManager::GetInstance()->SetGameClear();
					SetAnimationPattern(ANIM_PATTERN::IDOL_R);// 動かないアニメーション再生
					XA_Play(SOUND_LABEL_GAMECLEAR2);
					// クリアフラグを上げる
					clearFlg = true;
					break;

				case OBJECT_TYPE::ENEMY:	//CSV 値66
					//	再生可能ならサウンド再生
					if (damageSEplayCount >= 30)
					{
						XA_Play(SOUND_LABEL_DAMAGEHIT);
						damageSEplayCount = 0;
					}
					prevFrameCorrect = CCollision::DtestCorrectPosition(this->Bcol, (*it)->Bcol);
					// オブジェクトの位置とコライダーの中心を合わせる
					this->transform.position.x = this->Bcol.centerX;
					this->transform.position.y = this->Bcol.centerY;

					// ノックバックの前にエフェクトをプレイヤーの位置に移動させる
					damageEffect->transform.position = { this->transform.position.x,this->transform.position.y, -0.3f };
					// エフェクトをアクティブに
					damageEffect->SetActive(true);

					//プレイヤーのノックバックの処理
					if (!nockf)
					{
						if (prevFrameCorrect.y == 1.0f)
						{
							if (HitTy == true && prevFrameCorrect.y == 1.0f)
							{
								moveF = this->transform.position.x - 0.3f;
								HitTy = false;
							}
						}
						//吹っ飛ばす計算式（右）
						if (prevFrameCorrect.x == 1.0f)
						{
							if (HitTy == true && prevFrameCorrect.x == 1.0f)
							{
								moveF = this->transform.position.x + 0.5f;
								HitTy = false;
							}
						}
						//吹っ飛ばす計算式（左）
						if (prevFrameCorrect.x == -1.0f)
						{
							if (HitTy == true && prevFrameCorrect.x == -1.0f)
							{
								moveF = this->transform.position.x - 0.5f;
								HitTy = false;
							}
						}
						//追従カメラの初期化
						smoothing->InitSmooth(&moveF, &this->transform.position.x, 0.05f);
						CGameManager::GetInstance()->AddDamage(1);
						nockf = true;

						// エフェクトの再生
						damageEffect->PlayAnimation();
					}
				default:
					break;
				}

				//	サウンドの停止（ごり押し作戦）
				if ((anim->GetIsAnimation() != false && this->GetState() != PState::FALL) || (*it)->GetObjectType() == OBJECT_TYPE::DAMAGE_DOWN)
				{
					//	サウンドの停止
					XA_Stop(SOUND_LABEL_FLY);
					FlyCount = 0;
				}
			}
		}
	}

	HitTy = true;
	// プレイヤーが使っているカメラを使い、エフェクトを更新
	damageEffect->SetUseingCamera(this->useCamera);
	damageEffect->Update();

	kurakka_L->Update();
	kurakka_R->Update();
}

PState CPlayer::GetState()
{
	return State;
}

void CPlayer::SetState(PState state)
{
	State = state;
}

void CPlayer::Draw()
{
	gameoverBg->Draw();

	// 親クラスのDraw()を明示的に呼び出す
	// 全てのゲームオブジェクト共通の描画処理を行う
	CGameObject::Draw();

	// エフェクトの描画
	damageEffect->Draw();

	// クラッカーの描画
	kurakka_L->Draw();
	kurakka_R->Draw();
}

CPlayer::~CPlayer()
{
	// プレイヤー内オブジェクトの解放
	SAFE_RELEASE(vertexBufferEffect);
	delete damageEffect;
	delete gameoverBg;
	delete kurakka_L;
	delete kurakka_R;

	// イージングの解放
	delete smoothing;
	delete gameoverEaseX;
	delete gameoverEaseY;
	delete kurakkaEase_L;
	delete kurakkaEase_R;

	// 親クラスのコンストラクタを明示的に呼び出す
	// 頂点バッファの解放を行う
	CGameObject::~CGameObject();
}
