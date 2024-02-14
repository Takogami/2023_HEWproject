#include "CPlayer.h"
#include "CScene.h"
#include "CWind.h"
#include "CSceneManager.h"
#include "CGameManager.h"

// コントローラーを使う場合はtrueを指定
#define USE_CONTROLLER (true)

//明示的に親クラスのコンストラクタを呼び出す
CPlayer::CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
{
	// 初期スピード設定
	SetMoveSpeed(0.02f);
	smoothing = new CSmoothing();
	// 重力を初期値とする
	velocity.y = gravity;

	nockf = false;

	nockT = false;

	test = true;
}

void CPlayer::PlayerInput()
{
	if (nockf)
	{
		return;
	}
#if USE_CONTROLLER == true

	
	// スティックの入力を保存
	input_stickX = gInput->GetLeftStickX();
	input_stickY = gInput->GetLeftStickY();
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
			}
			else if (input_stickX > 0.0f)
			{
				SetAnimationPattern(ANIM_PATTERN::RIGHTWALK);// 右に歩くアニメーション再生
			}

			if (input_stickX == 0)
			{
				SetAnimationPattern(ANIM_PATTERN::NO_ANIM);// 動かないアニメーション再生
			}
			if ((input_stickY < 0.0f) && prevFrameCorrect.y == 1)
			{
				SetState(PState::FALL);// 倒れる
				SetAnimationPattern(ANIM_PATTERN::FALLDOWN);// 倒れたアニメーション再生
				anim->SetIsAnimation(true);
				if (!anim->GetIsAnimation())
				{

				}
			}
		}
		break;
	case PState::FALL:// 倒れた状態
		if ((input_stickY > 0.0f) && (old_input_stickY >= 0.0f))
		{
			SetState(PState::NORMAL);// 通常状態に戻す
			SetAnimationPattern(ANIM_PATTERN::GETUP);// 起き上がるアニメーション再生
			anim->SetIsAnimation(true);
		}
		if (input_stickX <= -1.0f && (old_input_stickX > -1.0f))
		{
			SetState(PState::BREAKLEFT);// 左に折れる
			SetAnimationPattern(ANIM_PATTERN::BREAKLEFT);// 左に折れるアニメーション再生
			anim->SetIsAnimation(true);
		}
		if (input_stickX >= 1.0f && (old_input_stickX < 1.0f))
		{
			SetState(PState::BREAKRIGHT);// 右に折れる
			SetAnimationPattern(ANIM_PATTERN::BREAKRIGHT);// 右に折れるアニメーション再生
			anim->SetIsAnimation(true);
		}
		// Bボタン入力でとりあえずのジャンプ操作
		if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A) && jumpCount != 5)
		{
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
			if (input_stickX >= 1.0f && (old_input_stickX < 1.0f))
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
			if (input_stickX < -1.0f && (old_input_stickX >= -1.0f))
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
	old_input_stickX= input_stickX;
	old_input_stickY= input_stickY;


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

void CPlayer::Update()
{
	if (this->materialDiffuse.w != 1.0f && nockT == false)
	{
		this->materialDiffuse.w = 1.0f;
	}

	if (this->GetState() == PState::NORMAL)
	{
		this->Bcol.sizeY = 0.25f;
		this->Bcol.sizeX = 0.2f;
	}
	else if (this->GetState() != PState::NORMAL)
	{
		this->Bcol.sizeY = 0.1f;
		this->Bcol.sizeX = 0.15f;
	}
	// 風の影響を受けていないなら向きを戻す
	if (dir_wind.x == 0.0f)
	{
		// 向きを戻す
		dir.x = 0.0f;
	}
	if (dir_wind.y == 0.0f)
	{
		// 向きを戻す
		dir.y = -1.0f;
	}
	if (Ddir.x == 0.0f)
	{
		dir.x = 0.0f;
	}
  
	// プレイヤー操作関連の入力処理
	PlayerInput();

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
		//プレイヤーがノックバックした先にカメラを追従させる
		smoothing->Update();
		//プレイヤーがすぐ入力できないようにするためのフレームカウンター
		flameCounter++;
		gInput->ControllerVibration(10, 35000);
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
		if (flameCounter == 20 && nockT == true)
		{
			CGameManager::GetInstance()->AddDamage(1);
			nockT = false;
			flameCounter = 0.0f;
		}
	}

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
				if (this->GetState() == PState::FALL)
				{
					SetAnimationPattern(ANIM_PATTERN::FLAYING);
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
				if (this->GetState() == PState::FALL)
				{
					SetAnimationPattern(ANIM_PATTERN::FLAYING);
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
				prevFrameCorrect = CCollision::CorrectPosition(this->Bcol, (*it)->Bcol);
				// オブジェクトの位置とコライダーの中心を合わせる
				this->transform.position.x = this->Bcol.centerX;
				this->transform.position.y = this->Bcol.centerY;
				//プレイヤーのノックバックの処理
				if (!nockf)
				{
					//吹っ飛ばす計算式（右）
					if (prevFrameCorrect.x == 1.0f)
					{
						moveF = this->transform.position.x + 0.5f;
						/*nockT = true;*/
					}
					//吹っ飛ばす計算式（左）
					if (prevFrameCorrect.x == -1.0f )
					{
						moveF = this->transform.position.x - 0.5f;
					}
					////追従カメラの初期化
					smoothing->InitSmooth(&moveF, &this->transform.position.x, 0.05f);
					CGameManager::GetInstance()->AddDamage(1);
					nockf = true;
				}
				break;
			case OBJECT_TYPE::DAMAGE_TILEY:	//CSV 値20
				// コライダーの位置を補正し、補正した方向を受け取る
				prevFrameCorrectY = CCollision::CorrectPosition(this->Bcol, (*it)->Bcol);
				// 天井にぶつかっていたならジャンプ力を0にする
				if (prevFrameCorrectY.y == -1)
				{
					jumpStrength = 0;	// ジャンプ力を0にする
				}
				// 重力によって地面に
				if (prevFrameCorrectY.y == 1 && nockT == false)
				{
					velocity.y = 0.0f;				// 速度Yを0に戻す
					jumpStrength = ini_jumpStrength;
					isJump = false;
					nockT = true;
				}
				// オブジェクトの位置とコライダーの中心を合わせる
				this->transform.position.x = this->Bcol.centerX;
				this->transform.position.y = this->Bcol.centerY;
				break;
			default:
				break;
			}
		}
	}
}

PState CPlayer::GetState()
{
	return State;
}

void CPlayer::SetState(PState state)
{
	State = state;
}

void CPlayer::Rknoc(DirectX::XMFLOAT3)
{

}

void CPlayer::Lknoc(DirectX::XMFLOAT3)
{

}

void CPlayer::Draw()
{
	// 親クラスのDraw()を明示的に呼び出す
	// 全てのゲームオブジェクト共通の描画処理を行う
	CGameObject::Draw();
}

CPlayer::~CPlayer()
{
	delete smoothing;
	// 親クラスのコンストラクタを明示的に呼び出す
	// 頂点バッファの解放を行う
	CGameObject::~CGameObject();
}
