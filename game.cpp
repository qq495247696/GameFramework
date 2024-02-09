/*==============================================================================

   �Q�[������ [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "game.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "meshfield.h"
#include "meshsky.h"
#include "meshmountain.h"
#include "EnemyBullet.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "camera.h"
#include "shadow.h"
#include "polyline.h"
#include "Home.h"
#include "Wall.h"
#include "sprite.h"
#include "Texture.h"
#include "select.h"
#include "tower.h"
#include "Ui.h"



/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static int g_BGMNo = 0;


/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
static Ui *g_ui;
void InitGame(void)
{
	// �J�����̏�����
	InitCamera();

	// �e�̏�����
	InitShadow();

	// �|�����C���̏�����
	InitPolyLine();
	g_ui = new Ui();
	// �n�ʂ̏�����
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, 180.0f, 180.0f);

	// ��̏�����
	InitMeshSky(D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10000.0f, 16, 8);

	// �R�̏�����
	InitMeshMountain(D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 1, 8000.0f, 300.0f);

	// �v���C���[�̏�����
	InitPlayer();
	InitEnemyBullet();

	InitWall();
	InitHome();
	// �G�l�~�[�̏�����
	InitEnemy();
	InitTower();
	InitSelect();

	// �e�̏�����
	InitBullet();

	// �X�R�A�̏�����
	InitScore();

	SetLightEnable(true);

	SetAlphaTestEnable(true);

	g_BGMNo = LoadSound((char*)"data/BGM/sample001.wav");

	SetVolume(g_BGMNo, 1.0f);
	PlaySound(g_BGMNo, -1);
}


void UninitGame()
{
	//�������Ƃ͋t���ɏI���������s��
	UninitScore();
	UninitPolyLine();
	UninitShadow();
	UninitBullet();
	UninitTower();
	UninitSelect();
	UninitEnemy();
	UninitEnemyBullet();
	UninitPlayer();
	delete g_ui;
	UninitHome();
	UninitMeshMountain();
	UninitMeshSky();
	UninitMeshField();
}

void UpdateGame(void)
{
	// �J�����X�V
	UpdateCamera();

	// �n�ʂ̍X�V����
	UpdateMeshField();
	UpdateMeshSky();
	UpdateMeshMountain();
	g_ui->Update();
	// �v���C���[�̍X�V����
	UpdatePlayer();
	UpdateEnemyBullet();
	UpdateHome();

	// �G�l�~�[�̍X�V����
	UpdateEnemy();
	UpdateTower();
	UpdateSelect();

	// �e�̍X�V����
	UpdateBullet();

	// �e�̍X�V����
	UpdateShadow();

	// �|�����C���̍X�V����
	UpdatePolyLine();

	// �X�R�A�̍X�V����
	UpdateScore();

	// �����蔻��̍X�V����
	UpdateCollision();


	//�X�y�[�X�L�[��������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE) 
	{
		SetVolume(g_BGMNo, 0.1f);

		//RESULT�ֈڍs����
		SceneTransition(SCENE_RESULT);
	}
}


void DrawGame(void)
{
	// �v���C���[���_
	D3DXVECTOR3 pos = GetPlayer()->pos;
	auto cam = GetCamera();
	UpdateCameraPos(cam->pos);
	pos.y = 0.0f;			// �J����������h�����߂ɃN���A���Ă���
	SetCamera();
	SetLightEnable(true);
	// �[�x�e�X�g�L��
	SetDepthEnable(true);
	// ���C�e�B���O�L��
	
	// �n�ʂ̕`�揈��
	DrawMeshSky();
	DrawMeshField();
	DrawMeshMountain();

	// �e�̕`�揈��
	DrawShadow();

	// �G�l�~�[�̕`�揈��
	DrawEnemy();

	DrawTower();
	DrawSelect();
	DrawEnemyBullet();
	DrawWall();
	DrawPlayer();
	DrawHome();

	// �e�̕`�揈��
	DrawBullet();

	// �|�����C���̕`�揈��
	DrawPolyLine();

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	g_ui->Draw();
	// �X�R�A�̕`�揈��
	DrawScore();
}