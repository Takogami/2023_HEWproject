#include "CPlayer.h"
#include "CScene.h"

// コントローラーを使う場合はtrueを指定
#define USE_CONTROLLER (false)

//明示的に親クラスのコンストラクタを呼び出す
CPlayer::CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
{
	// 初期スピード設定
	SetMoveSpeed(0.05f);
	// 重力を初期値とする
	velocity.y = gravity;
}

void CPlayer::PlayerInput()
{
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
			}
			// Aボタン入力でとりあえずのジャンプ操作
			if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A))
			{
				isJump = true;
				/*	this->transform.position.y = -0.2f;*/
			}
		}
		break;
	case PState::FALL:// 倒れた状態
		if (anim->GetIsAnimation() == false)
		{
			if ((input_stickY > 0.0f) && (old_input_stickY <= 0.0f))
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
			if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A))
			{
				isJump = true;
				/*	this->transform.position.y = -0.2f;*/
			}
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

			if (gInput->GetKeyPress(VK_TAB))
			{
				isJump = true;
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
				}
				else
				{

				}
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
	// 向きを上にする
	dir.y = 1.0f;
	// ジャンプ力を重力に従って更新
	jumpStrength -= gravity;
	// 計算したジャンプ力を適応
	return jumpStrength;
}


void CPlayer::Update()
{

	// 向きを戻す
	dir.x = 0.0f;
	dir.y = -1.0f;

	// プレイヤー操作関連の入力処理
	PlayerInput();

	// 前フレームの補正方向を初期化
	prevFrameCorrect = { 0 };

	// 単位ベクトル化(矢印を１にする) = 正規化
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&dir);	// ベクトル計算用の型に入れる
	v = DirectX::XMVector3Normalize(v);					// 正規化する
	DirectX::XMStoreFloat3(&dir, v);					// 元の変数dirに戻す
	
	// 重力の影響を受けてY軸方向の速度を更新
	// ジャンプ中ならジャンプ力の更新処理を行う
	velocity.y = isJump ? Jump() : velocity.y += gravity;

	// ベクトルに速度をかけて位置を変更
	this->transform.position.x += dir.x * velocity.x;
	this->transform.position.y += dir.y * velocity.y;

	// 親クラスのUpdate()を明示的に呼び出す
	// 全てのゲームオブジェクト共通の更新処理を行う
	CGameObject::Update();

	// 地形との当たり判定と補正
	for (auto it = CScene::map_object.begin(); it != CScene::map_object.end(); it++)
	{
		if (CCollision::TestBoxCollision(this->Bcol, (*it)->Bcol))
		{
			switch ((*it)->GetObjectType())
			{
			case OBJECT_TYPE::NORMAL:
				// コライダーの位置を補正し、補正した方向を受け取る
				prevFrameCorrect = CCollision::CorrectPosition(this->Bcol, (*it)->Bcol);

				// 天井にぶつかっていたならジャンプ力を0にする
				if (prevFrameCorrect.y == -1)
				{
					dir.y = -1.0f;		// 向きを下にする
					jumpStrength = 0;	// ジャンプ力を0にする
				}
				// 重力によって地面に衝突していたなら
				if (prevFrameCorrect.y == 1)
				{
					dir.y = -1.0f;
					velocity.y = 0.0f;				// 速度Yを0に戻す
					jumpStrength = ini_jumpStrength;
					isJump = false;
				}

				// オブジェクトの位置とコライダーの中心を合わせる
				this->transform.position.x = this->Bcol.centerX;
				this->transform.position.y = this->Bcol.centerY;
				break;

			case OBJECT_TYPE::WIND:
				//	オブジェクトに当たったらtrue
				isWind = true;

				
				break;

			default:
				break;
			}
		}
	}
}

void CPlayer::Wind()
{
	//	プレイヤーの状態が折れていて風が吹いてるオブジェクトに当たったら…
	if (isWind == true && (State == PState::BREAKLEFT || State == PState::BREAKRIGHT))
	{
		//	右向きベクトル
		dir.x = 1.0f;

		//	風が起きてるような計算
		this->transform.position.x += dir.x * velocity.x * 1.1f;

		//	地面に当たったら…
		if (prevFrameCorrect.y == 1)
		{
			//	移動を終了
			isWind = false;
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

void CPlayer::Draw()
{
	// 親クラスのDraw()を明示的に呼び出す
	// 全てのゲームオブジェクト共通の描画処理を行う
	CGameObject::Draw();
}

CPlayer::~CPlayer()
{
	// 親クラスのコンストラクタを明示的に呼び出す
	// 頂点バッファの解放を行う
	CGameObject::~CGameObject();
}
