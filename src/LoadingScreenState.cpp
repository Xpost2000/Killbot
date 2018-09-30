#include "LoadingScreenState.h"
#include "StateMachine.h"

#include "constants.h"

#include "AnimationManager.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "SoundManager.h"

LoadingScreenState::LoadingScreenState(){
}

LoadingScreenState::~LoadingScreenState(){
}

bool LoadingScreenState::OnEnter(){
	return true;
}

bool LoadingScreenState::OnExit(){
	return true;
}

void LoadingScreenState::update(float dt){
	if(_drawScreenAlready){
			// this is also a code nightmare...
			/*
				It's very evident there are many things wrong with this code.
			*/
			SoundManager::instance()->addMusic("audio/music/boss_music.ogg");
			SoundManager::instance()->addMusic("audio/music/upgrade_music.ogg");
			SoundManager::instance()->addMusic("audio/music/main_menu_music.ogg");

			TextureManager::instance()->addTexture("tex/blocks/wall.png");
			TextureManager::instance()->addTexture("tex/blocks/tile_warning.png");
			TextureManager::instance()->addTexture("tex/blocks/tiletl_warning.png");
			TextureManager::instance()->addTexture("tex/blocks/tiletr_warning.png");
			TextureManager::instance()->addTexture("tex/ammo/gold_bullet.png");
			TextureManager::instance()->addTexture("tex/ammo/silver_bullet.png");
			TextureManager::instance()->addTexture("tex/ammo/lead_ball.png");

			AnimationGroup* basicEnemyAnimations = AnimationManager::instance()->addGroup(BasicEnemyAnimationGroupName);
			AnimationGroup* playerAnimations = AnimationManager::instance()->addGroup(PlayerAnimationGroupName);
			AnimationGroup* blasterEnemyAnimations = AnimationManager::instance()->addGroup(BlasterEnemyAnimationGroupName);
			AnimationGroup* machineBlasterEnemyAnimations = AnimationManager::instance()->addGroup(MachineBlasterEnemyAnimationGroupName);
			AnimationGroup* bossBlasterBot2 = AnimationManager::instance()->addGroup(Boss1AnimationGroupName);
			AnimationGroup* bossBlasterBot1 = AnimationManager::instance()->addGroup(Boss2AnimationGroupName);
			AnimationGroup* gameIntro = AnimationManager::instance()->addGroup(GameIntroAnimationGroupName);

			AnimationGroup* acid = AnimationManager::instance()->addGroup("acid");

			AnimationGroup* explosion = AnimationManager::instance()->addGroup(ExplosionAnimationGroupName);

			Animation* acidAnimation = acid->addAnimation("animation");
			Animation* explosionAnimation = explosion->addAnimation("animation");
			Animation* gameIntroAnimation = gameIntro->addAnimation("intro");

			// ADD INTRO SCREENS HERE
			gameIntroAnimation->addFrame(TextureManager::instance()->getTexture("tex/intro/intro_00.png"));
			gameIntroAnimation->addFrame(TextureManager::instance()->getTexture("tex/intro/intro_01.png"));
			gameIntroAnimation->addFrame(TextureManager::instance()->getTexture("tex/intro/intro_02.png"));
			gameIntroAnimation->addFrame(TextureManager::instance()->getTexture("tex/intro/intro_03.png"));
			gameIntroAnimation->addFrame(TextureManager::instance()->getTexture("tex/intro/intro_03_5.png"));
			gameIntroAnimation->addFrame(TextureManager::instance()->getTexture("tex/intro/intro_04.png"));
			// END INTRO SCREENS

			acidAnimation->addFrame(TextureManager::instance()->getTexture("tex/blocks/acid/acid_00.png"));
			acidAnimation->addFrame(TextureManager::instance()->getTexture("tex/blocks/acid/acid_01.png"));
			acidAnimation->addFrame(TextureManager::instance()->getTexture("tex/blocks/acid/acid_02.png"));
			acidAnimation->addFrame(TextureManager::instance()->getTexture("tex/blocks/acid/acid_01.png"));
			acidAnimation->addFrame(TextureManager::instance()->getTexture("tex/blocks/acid/acid_00.png"));

			explosionAnimation->addFrame(TextureManager::instance()->getTexture("tex/explosion_00.png"));
			explosionAnimation->addFrame(TextureManager::instance()->getTexture("tex/explosion_01.png"));
			explosionAnimation->addFrame(TextureManager::instance()->getTexture("tex/explosion_02.png"));
			explosionAnimation->addFrame(TextureManager::instance()->getTexture("tex/explosion_02.png"));

			Animation* basicEnemyIdle = basicEnemyAnimations->addAnimation("idle");
			Animation* basicEnemyWalk = basicEnemyAnimations->addAnimation("walk");
			Animation* basicEnemyAttack = basicEnemyAnimations->addAnimation("attack"); // you cannot use firing animations. It will CRASH for this enemy.

			Animation* pFire = playerAnimations->addAnimation("fire");
			Animation* pIdle = playerAnimations->addAnimation("idle");
			Animation* pWalk = playerAnimations->addAnimation("walk");
			Animation* pAttack = playerAnimations->addAnimation("attack");

			Animation* enemyBlasterWalk = blasterEnemyAnimations->addAnimation("walk");
			Animation* enemyBlasterIdle = blasterEnemyAnimations->addAnimation("idle");
			Animation* enemyBlasterFire = blasterEnemyAnimations->addAnimation("fire");

			Animation* mgEnemyBlasterWalk = machineBlasterEnemyAnimations->addAnimation("walk");
			Animation* mgEnemyBlasterIdle = machineBlasterEnemyAnimations->addAnimation("idle");
			Animation* mgEnemyBlasterFire = machineBlasterEnemyAnimations->addAnimation("fire");

			Animation* bossEnemyBlasterWalk1 = bossBlasterBot1->addAnimation("walk");
			Animation* bossEnemyBlasterIdle1 = bossBlasterBot1->addAnimation("idle");
			Animation* bossEnemyBlasterFire1 = bossBlasterBot1->addAnimation("fire");

			Animation* bossEnemyBlasterWalk2 = bossBlasterBot2->addAnimation("walk");
			Animation* bossEnemyBlasterIdle2 = bossBlasterBot2->addAnimation("idle");
			Animation* bossEnemyBlasterFire2 = bossBlasterBot2->addAnimation("fire");

			basicEnemyIdle->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_idle.png") );
			basicEnemyWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_walk_01.png") );
			basicEnemyWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_walk_02.png") );
			basicEnemyWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_walk_03.png") );
			basicEnemyWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_walk_04.png") );
			basicEnemyWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_walk_05.png") );
			basicEnemyWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_walk_06.png") );
			basicEnemyWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_walk_07.png") );
			basicEnemyWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_walk_08.png") );
			basicEnemyAttack->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_melee_00.png") );
			basicEnemyAttack->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_melee_01.png") );
			basicEnemyAttack->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_melee_02.png") );
			basicEnemyAttack->addFrame( TextureManager::instance()->getTexture("tex/killbot_evil/badkillbot_melee_03.png") );

			pIdle->addFrame( TextureManager::instance()->getTexture("tex/killbot_player/killbot_idle.png") );
			pIdle->addFrame( TextureManager::instance()->getTexture("tex/killbot_player/killbot_idle_01.png") );
			pIdle->addFrame( TextureManager::instance()->getTexture("tex/killbot_player/killbot_idle_02.png") );
			pIdle->addFrame( TextureManager::instance()->getTexture("tex/killbot_player/killbot_idle_01.png") );

			pFire->addFrame( TextureManager::instance()->getTexture("tex/killbot_player/killbot_fire01.png") );
			pFire->addFrame( TextureManager::instance()->getTexture("tex/killbot_player/killbot_fire02.png") );
			pFire->addFrame( TextureManager::instance()->getTexture("tex/killbot_player/killbot_fire03.png") );
			pFire->addFrame( TextureManager::instance()->getTexture("tex/killbot_player/killbot_fire02.png") );
			pFire->addFrame( TextureManager::instance()->getTexture("tex/killbot_player/killbot_fire01.png") );

			pWalk->addFrame(TextureManager::instance()->getTexture("tex/killbot_player/killbot_walk01.png"));
			pWalk->addFrame(TextureManager::instance()->getTexture("tex/killbot_player/killbot_walk02.png"));
			pWalk->addFrame(TextureManager::instance()->getTexture("tex/killbot_player/killbot_walk03.png"));
			pWalk->addFrame(TextureManager::instance()->getTexture("tex/killbot_player/killbot_walk04.png"));
			pWalk->addFrame(TextureManager::instance()->getTexture("tex/killbot_player/killbot_walk05.png"));
			pWalk->addFrame(TextureManager::instance()->getTexture("tex/killbot_player/killbot_walk06.png"));
			pWalk->addFrame(TextureManager::instance()->getTexture("tex/killbot_player/killbot_walk07.png"));

			pAttack->addFrame(TextureManager::instance()->getTexture("tex/killbot_player/killbot_melee00.png"));
			pAttack->addFrame(TextureManager::instance()->getTexture("tex/killbot_player/killbot_melee01.png"));
			pAttack->addFrame(TextureManager::instance()->getTexture("tex/killbot_player/killbot_melee02.png"));
			pAttack->addFrame(TextureManager::instance()->getTexture("tex/killbot_player/killbot_melee03.png"));

			mgEnemyBlasterIdle->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster.png"));
			mgEnemyBlasterIdle->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster.png"));
			mgEnemyBlasterIdle->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster.png"));
			mgEnemyBlasterIdle->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster.png"));

			mgEnemyBlasterFire->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster_fire00.png"));
			mgEnemyBlasterFire->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster_fire01.png"));
			mgEnemyBlasterFire->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster_fire02.png"));
			mgEnemyBlasterFire->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster_fire03.png"));
			mgEnemyBlasterFire->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster_fire02.png"));
			mgEnemyBlasterFire->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster_fire01.png"));
			mgEnemyBlasterFire->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster_fire00.png"));

			mgEnemyBlasterWalk->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster_walk00.png"));
			mgEnemyBlasterWalk->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster_walk01.png"));
			mgEnemyBlasterWalk->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster_walk02.png"));
			mgEnemyBlasterWalk->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster_walk03.png"));
			mgEnemyBlasterWalk->addFrame(TextureManager::instance()->getTexture("tex/killbot_blaster_mg_evil/badkillbot_blaster_walk04.png"));

			enemyBlasterIdle->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster.png") );
			enemyBlasterIdle->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster.png") );
			enemyBlasterIdle->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster.png") );
			enemyBlasterIdle->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster.png") );

			enemyBlasterFire->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster_fire00.png") );
			enemyBlasterFire->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster_fire01.png") );
			enemyBlasterFire->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster_fire02.png") );
			enemyBlasterFire->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster_fire03.png") );
			enemyBlasterFire->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster_fire02.png") );
			enemyBlasterFire->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster_fire01.png") );
			enemyBlasterFire->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster_fire00.png") );
			
			enemyBlasterWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster_walk00.png") );
			enemyBlasterWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster_walk01.png") );
			enemyBlasterWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster_walk02.png") );
			enemyBlasterWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster_walk03.png") );
			enemyBlasterWalk->addFrame( TextureManager::instance()->getTexture("tex/killbot_blaster_evil/badkillbot_blaster_walk04.png") );

			bossEnemyBlasterIdle1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster.png"));
			bossEnemyBlasterIdle1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster.png"));
			bossEnemyBlasterIdle1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster.png"));
			bossEnemyBlasterIdle1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster.png"));

			bossEnemyBlasterFire1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster_fire00.png"));
			bossEnemyBlasterFire1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster_fire01.png"));
			bossEnemyBlasterFire1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster_fire02.png"));
			bossEnemyBlasterFire1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster_fire03.png"));
			bossEnemyBlasterFire1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster_fire02.png"));
			bossEnemyBlasterFire1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster_fire01.png"));
			bossEnemyBlasterFire1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster_fire00.png"));

			bossEnemyBlasterWalk1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster_walk00.png"));
			bossEnemyBlasterWalk1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster_walk01.png"));
			bossEnemyBlasterWalk1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster_walk02.png"));
			bossEnemyBlasterWalk1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster_walk03.png"));
			bossEnemyBlasterWalk1->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss01/badkillbot_blaster_walk04.png"));

			bossEnemyBlasterIdle2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster.png"));
			bossEnemyBlasterIdle2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster.png"));
			bossEnemyBlasterIdle2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster.png"));
			bossEnemyBlasterIdle2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster.png"));

			bossEnemyBlasterFire2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster_fire00.png"));
			bossEnemyBlasterFire2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster_fire01.png"));
			bossEnemyBlasterFire2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster_fire02.png"));
			bossEnemyBlasterFire2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster_fire03.png"));
			bossEnemyBlasterFire2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster_fire02.png"));
			bossEnemyBlasterFire2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster_fire01.png"));
			bossEnemyBlasterFire2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster_fire00.png"));

			bossEnemyBlasterWalk2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster_walk00.png"));
			bossEnemyBlasterWalk2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster_walk01.png"));
			bossEnemyBlasterWalk2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster_walk02.png"));
			bossEnemyBlasterWalk2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster_walk03.png"));
			bossEnemyBlasterWalk2->addFrame(TextureManager::instance()->getTexture("tex/killbot_boss02/badkillbot_blaster_walk04.png"));

			_parent->getState("game")->init();
			_parent->setCurrent("intro");
	}
}

void LoadingScreenState::draw(Renderer2D* renderer){
	renderer->RenderText( Point{0, 0}, "Killbot : LOADING : Do not close the game while it is loading!", "ocr", Color{255, 0, 0, 255}, 30 );
	renderer->RenderText( Point{0, 35}, "Also game quality is likely representative of final version.", "ocr", Color{0, 255, 0, 255}, 25 );
	_drawScreenAlready = true;
}
