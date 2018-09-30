#include "GameState.h"
#include "GameObjectFactory.h"
#include "TextureManager.h"
#include "StateMachine.h"
#include "SoundManager.h"
#include "GameUpgradeScreenState.h"

//#include "spawn_macros.h" This doesn't do anything!!!!!!

#include "CefManager.h"

// Yes I know the hard coded levels aren't good
// but this isn't a big game project so to speak
// so I will permit this one piece of horrible
// code in a sea of so far decent code.

std::string GameState::_msg = "";

int bossMap[24][32]={
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int defaultMap[24][32]={
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,3,2,2,2,2,2,2,2,4,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2,2,4,0,0,0,0,0,0,0,0,0,0,1},
	{1,9,9,9,9,9,9,9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

GameState::GameState(InputManager* input) : _input(input){
}

GameState::~GameState(){
	delete GameObjectFactory::instance();
}

void GameState::init(){
	GameObjectFactory::instance();

	if (player == nullptr){
		player = GameObjectFactory::instance()->createPlayer(Point{ 40, 768 - 150 }, Point{ 75, 75 }, _input);
		world.AddEntity(player);
	}
	else{
		//TODO Figure out how to reset the player completely.
		//actually reset the game state
		player->getPosition() = Point{ 40, 768 - 150 };
		player->getSize() = Point{ 75, 75 };
		player->getHealth() = 50;
		player->getMaxHealth() = 50;

		_gameRound = 1;
		_gameRoundWaitTime = 5;
		_gameWaitTilBackToMenu = 5;
		_gameScore = 0;
		_roundComplete = false;
	}
}

bool GameState::OnEnter(){
	SoundManager::instance()->haltMusic();
	CefManager::instance()->GetCefBrowser()->GetMainFrame()->LoadURL(std::string("file://" + std::string(SDL_GetBasePath()) + "htmlui/IngameUI.html"));
	return true;
}

bool GameState::OnExit(){
	SoundManager::instance()->haltMusic();
	return true;
}

// not hard reset.
void GameState::reset(){
	_gameWaitTilBackToMenu = 5;
	_currentBossOnRoster = 0;
	GameUpgradeScreenState* ptr = (GameUpgradeScreenState*)_parent->getState("upgradeScreen");
	ptr->canFightBoss = false;
	_gameRound = 1; // reset game state cause you suck.
}
// the hard reset.
void GameState::gameOverReset(){
	reset();
	_playerLives = 3;
	_gameScore = 0;
	PlayerAI* ptr = (PlayerAI*)player->getAI();
	ptr->reset();
	player->setMaxHealth(35);
	player->setHealth(35);
}

void GameState::update(float dt){
	/*
	*/
	// player dies here cause the health is either zero or less than zero.
	if(player->getHealth() <= 0){
		if (_gameWaitTilBackToMenu <= 0){
			player->getPosition() = Point{ 0, 0 }; // it'll glue the player to a wall.
			SoundManager::instance()->haltMusic();
			SoundManager::instance()->haltChannel(-1);
			reset();
			player->getHealth() = player->getMaxHealth(); // default value and stuff.
			if ((_gameScore - 50 * _gameRound >= 0)){
				_gameScore -= 50 * _gameRound; // half the score you had last time to penalized
			}
			_playerLives--;
			// Yeah I bet this'll work. (I'm just guessing.)
			if (_playerLives < 0){
				// hard reset here.
				// cause game over.
				_parent->setCurrent("gameOver");
				// thinking.....
			}
			else{
				_parent->setCurrent("upgradeScreen");
			}
		}
		else{
			_gameWaitTilBackToMenu -= dt;
		}
	}
	
	// check if the spawner spawned everything and all enemies are dead.
	if (_currentBossOnRoster > 2){
		_parent->setCurrent("endGame");
	}
	else{
		if (world.areAllSpawnersEmpty() && world.getEnemyCount() == 0){
			if (_gameWaitTilBackToMenu > 0){
				_gameWaitTilBackToMenu -= dt;
				_roundComplete = true;
			}
			else{
				_gameWaitTilBackToMenu = 5;
				_gameRound++;
				_gameScore += 250 + (100 * _gameRound);
				if (_gameMode != GameModeBossGauntlet){
					if ((_gameRound % 5) == 0){
						// allow the boss gauntlet to work.
						GameUpgradeScreenState* ptr = (GameUpgradeScreenState*)_parent->getState("upgradeScreen");
						ptr->canFightBoss = true;
					}
				}
				else{
					GameUpgradeScreenState* ptr = (GameUpgradeScreenState*)_parent->getState("upgradeScreen");
					ptr->canFightBoss = false;
					_currentBossOnRoster++;
					// boss round bonus to actually make higher tier ammo affordable... Cause it's so f**king expensive.
					_gameScore += 500 + (float)8 * (_gameRound / 5);
				}
				SoundManager::instance()->haltChannel(-1);
				SoundManager::instance()->haltMusic();
				_parent->setCurrent("upgradeScreen");
			}
		}
		else{
			_roundComplete = false;
			if (_gameMode == GameModeStandard){
				if (!SoundManager::instance()->isMusicPlaying())
					SoundManager::instance()->playMusic("audio/music/game_music.ogg", 100, -1);
			}
			else{
				if (!SoundManager::instance()->isMusicPlaying())
					SoundManager::instance()->playMusic("audio/music/boss_music.ogg", 100, -1);
			}
		}
	}
	if (player->getHealth() >= 0){
		world.update(dt);
	}
}

void GameState::draw(Renderer2D* renderer){
	renderer->SpritebatchBegin(TextureManager::instance()->getTexture("tex/blocks/wall.png"));
	for(int y = 0; y < 10; ++y){
		for(int x = 0; x < 10; ++x){
			renderer->SpritebatchDraw(Point{x*100, y*100}, Point{100, 100}, Color{128/2, 128/2, 128/2, 255});
		}
	}
	for(int y = 0; y < 10; ++y){
		for(int x = 0; x < 10; ++x){
			renderer->SpritebatchDraw(Point{x*100, y*100+200}, Point{100, 100}, Color{128/2, 128/2, 128/2, 255});
		}
	}
	for(int y = 0; y < 10; ++y){
		for(int x = 0; x < 10; ++x){
			renderer->SpritebatchDraw(Point{x*100, y*100+400}, Point{100, 100}, Color{128/2, 128/2, 128/2, 255});
		}
	}
	for(int y = 0; y < 10; ++y){
		for(int x = 0; x < 10; ++x){
			renderer->SpritebatchDraw(Point{x*100, y*100+400}, Point{100, 100}, Color{128/2, 128/2, 128/2, 255});
		}
	}
	renderer->SpritebatchEnd();
	world.draw(renderer);
	// HUD HERE
	PlayerAI* ai = (PlayerAI*)player->getAI();
//	renderer->RenderText(Point{ 0, 150 }, "Current Bullet Type : " + std::to_string(ai->getBulletIndex()) + " with " + std::to_string(ai->getBulletCountForCurrentIndex()) + " bullets left.", "ocr", Color{ 255, 0, 0, 255 }, 25);
	if(_gameMode == GameModeStandard){
	}else{
	}
	if (player->getHealth() <= 0){
		// I know this isn't fade out, so fix that once I verify.
		renderer->RenderRectangle(Point{ 0, 0 }, Point{ 1024, 768 }, Color{0, 0, 0, (255 / (_gameWaitTilBackToMenu*1.24))});
	}
	renderer->RenderRectangle(CefManager::instance()->GetRenderHandler()->getTexture(), Point{ 0, 0 }, Point{ renderer->getWidth(), renderer->getHeight() }, UV{ 0, 0, 1, 1 }, Color{ 255, 255, 255, 255 });
}
void GameState::parseMap(int map[24][32]){
	// spawn lists.
	// obviously in a more well structured game you would not use
	// lambdas for this purpose.
	SpawnList spawnList;

	// every 5 rounds uses a different spawnlist.
	if (_gameRound < 5){
		spawnList.push_back(std::make_pair([&](Point position){world.AddEntity(GameObjectFactory::instance()->createBasicEnemy(position, Point{ 75 * 1, 75 * 1 }, 85, 75, 15)); }, 70));
		spawnList.push_back(std::make_pair([&](Point position){world.AddEntity(GameObjectFactory::instance()->createBasicEnemy(position, Point{ 75 * 1.25, 75 * 1.25 }, 85, 85, 20)); }, 50));
		spawnList.push_back(std::make_pair([&](Point position){world.AddEntity(GameObjectFactory::instance()->createBlasterEnemy(position, Point{ 75 * 1.0, 75 * 1.0 }, 105, 76, GameObjectFactory::instance()->generateRubberBullet(GameObjectTypeEnemy))); }, 5));
	}
	else if (_gameRound < 10){
		spawnList.push_back(std::make_pair([&](Point position){world.AddEntity(GameObjectFactory::instance()->createBasicEnemy(position, Point{ 75 * 1.45, 75 * 1.45 }, 125, 135, 35)); }, 50));
		spawnList.push_back(std::make_pair([&](Point position){world.AddEntity(GameObjectFactory::instance()->createBlasterEnemy(position, Point{ 75 * 1.25, 75 * 1.25 }, 120, 100, GameObjectFactory::instance()->generateLeadBullet(GameObjectTypeEnemy))); }, 45));
		spawnList.push_back(std::make_pair([&](Point position){world.AddEntity(GameObjectFactory::instance()->createBlasterEnemy(position, Point{ 75 * 1.25, 75 * 1.25 }, 120, 100, GameObjectFactory::instance()->generateSilverBullet(GameObjectTypeEnemy))); }, 25));
		spawnList.push_back(std::make_pair([&](Point position){world.AddEntity(GameObjectFactory::instance()->createMGBlasterEnemy(position, Point{ 75 * 1, 75 * 1 }, 90, 150, GameObjectFactory::instance()->generateMGBullet(GameObjectTypeEnemy))); }, 5));
	}
	else{
		spawnList.push_back(std::make_pair([&](Point position){world.AddEntity(GameObjectFactory::instance()->createBasicEnemy(position, Point{ 75 * 1.45, 75 * 1.45 }, 125, 135, 35)); }, 20));
		spawnList.push_back(std::make_pair([&](Point position){world.AddEntity(GameObjectFactory::instance()->createBlasterEnemy(position, Point{ 75 * 1.25, 75 * 1.25 }, 120, 150, GameObjectFactory::instance()->generateLeadBullet(GameObjectTypeEnemy))); }, 45));
		spawnList.push_back(std::make_pair([&](Point position){world.AddEntity(GameObjectFactory::instance()->createBlasterEnemy(position, Point{ 75 * 1.25, 75 * 1.25 }, 120, 150, GameObjectFactory::instance()->generateSilverBullet(GameObjectTypeEnemy))); }, 45));
		spawnList.push_back(std::make_pair([&](Point position){world.AddEntity(GameObjectFactory::instance()->createMGBlasterEnemy(position, Point{ 75 * 1.25, 75 * 1.25 }, 120, 200, GameObjectFactory::instance()->generateMGBullet(GameObjectTypeEnemy))); }, 35));
		spawnList.push_back(std::make_pair([&](Point position){world.AddEntity(GameObjectFactory::instance()->createMGBlasterEnemy(position, Point{ 75 * 1.15, 75 * 1.15 }, 145, 300, GameObjectFactory::instance()->generateMGBullet(GameObjectTypeEnemy), Boss1AnimationGroupName)); }, 5));
	}

	for(int y = 0; y < 24; ++y){
		for(int x = 0; x < 32; ++x){
			switch(map[y][x]){
				case 0: break;
				case 1:
					world.AddEntity(GameObjectFactory::instance()->createWall(Point{x*32, y*32}, Point{32, 32}, TextureManager::instance()->getTexture("tex/blocks/wall.png")));
					break;
				case 2:
					world.AddEntity(GameObjectFactory::instance()->createWall(Point{x*32, y*32}, Point{32, 32}, TextureManager::instance()->getTexture("tex/blocks/tile_warning.png")));
					break;
				case 3:
					world.AddEntity(GameObjectFactory::instance()->createWall(Point{x*32, y*32}, Point{32, 32}, TextureManager::instance()->getTexture("tex/blocks/tiletl_warning.png")));
					break;
				case 4:
					world.AddEntity(GameObjectFactory::instance()->createWall(Point{x*32, y*32}, Point{32, 32}, TextureManager::instance()->getTexture("tex/blocks/tiletr_warning.png")));
					break;
				case 5:
					world.AddEntity(GameObjectFactory::instance()->createSpawner(Point{x*32, y*32}, 16, 3.2, spawnList));
					break;
				case 6:
					// player spawn
					player->getPosition().x = x*32;
					player->getPosition().y = y*32;
					break;
				case 9:
					world.AddEntity(GameObjectFactory::instance()->createAcid(Point{ x * 32, y * 32 }, Point{ 32, 32 }, TextureManager::instance()->getTexture("tex/blocks/acid.png")));
					break;
			}
		}
	}
}

void GameState::setUpGameMode(){
	// idk why I have to do this, but I know I have to.
	for(int i = 0; i < 35; ++i)
		world.ClearNonPlayerEntities();
	switch(_gameMode){
		case GameModeStandard:	
			parseMap(defaultMap);
			//_bcurrentSpawned = 0;	
			//_maxEntities = 16;
			break;
		case GameModeBossGauntlet:
			parseMap(bossMap);
			// in the more complete version I'd probably have another setUpBossGauntlet mode
			// that checks the wave your on and sets the boss scenario. For now just spawn the giant kill bot :D.
			if (_currentBossOnRoster == 0){
				_currentBoss = GameObjectFactory::instance()->createBasicEnemy(Point{ 500, 300 }, Point{ 175, 175 }, 90, 550, 50);
			}
			if (_currentBossOnRoster == 1){
				_currentBoss = GameObjectFactory::instance()->createBlasterEnemy(Point{ 500, 300 }, Point{ 125, 125 }, 65, 1250, GameObjectFactory::instance()->generateGoldBullet(GameObjectTypeEnemy), Boss1AnimationGroupName);
				world.AddEntity(GameObjectFactory::instance()->createBlasterEnemy(Point{ 550, 300 }, Point{ 90, 90 }, 65, 350, GameObjectFactory::instance()->generateRubberBullet(GameObjectTypeEnemy)));
				world.AddEntity(GameObjectFactory::instance()->createBlasterEnemy(Point{ 470, 300 }, Point{ 90, 90 }, 65, 350, GameObjectFactory::instance()->generateRubberBullet(GameObjectTypeEnemy)));
			}
			if (_currentBossOnRoster == 2){
				_currentBoss = GameObjectFactory::instance()->createBlasterEnemy(Point{ 500, 300 }, Point{ 75, 75 }, 145, 3000, GameObjectFactory::instance()->generateGoldBullet(GameObjectTypeEnemy), Boss2AnimationGroupName);
			}
			world.AddEntity(_currentBoss);
			break;
	}
}
