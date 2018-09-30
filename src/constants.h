#ifndef CONSTANTS_H
#define CONSTANTS_H
	/*
		Sadly since I didn't design the original game with CEF in mind
		so I can't exactly refactor everything.
	
		I mean the best way would be to make all variables of every class
		a value in a map.

		Then I would easily do all the scripting from javascript.
		Except I can't so I need to group somethings into functions.
	*/

	const std::string EngineRequestDisplayModes = "ENGINERequestDisplayModes";
	const std::string EngineApplySettings = "ENGINEApplySettings";

	const std::string WriteFileMessageId = "CEFWriteMessage";
	const std::string StateMachineSetCurrent = "GAMESetCurrentState";
	const std::string UpgradeScreenPlayGame = "GAMEUpgradeScreenStart";
	const std::string GetBossVariableUpgrade = "GAMEUpgradeGetBossFightStatus";

	const std::string IsThereABoss = "GAMESTATEInBossFight?";
	
	const std::string CurrentPlayerCurrentHealth = "GAMESTATEPlayerCurrentHealth";
	const std::string CurrentPlayerMaxHealth = "GAMESTATEPlayerMaxHealth";

	const std::string RestorePointsToPlayerHP = "GAMESTATERestorePlayerHP";
	const std::string AddMaxHealthToPlayer = "GAMESTATEUPGRADEMAXHPPLAYER";

	const std::string AddToBullet = "GAMESTATEAddBulletCount";
	const std::string SubtractGameScore = "GAMESTATESubtractGameScore";
	const std::string AddGameScore = "GAMESTATEAddGameScore";
	const std::string GetGameScore = "GAMESTATEGetGameScore";

	const std::string GetPlayerLives = "GAMESTATEGetPlayerLives";

	const std::string CurrentBossMaxHealth = "GAMESTATEBossMAXHP";
	const std::string CurrentBossCurrentHealth = "GAMESTATEBossCurrentHealth";

	const std::string RequestCurrentGameRound = "GAMESTATECurrentRound";
	const std::string RequestBulletIndexPlayer = "GAMESTATEPlayerBulletIndex";
	const std::string RequestBulletCountForIndex = "GAMESTATEPlayerBulletIndexCountOf";
	const std::string RequestCurrentBulletCount = "GAMESTATECurrentPlayerBulletCount"; 

	const std::string RequestMessageBarMessage = "GAMESTATERequestMSGBARTXT";

	const std::string UpgradeDeveloperCheat1 = "GAMECHEATForceBossFight";
	
	const float GravityLimit = 720;
	const float GravityStrength = 600;
	const int GameObjectTypeBlock = -1;
	const int GameObjectTypePlayer = 0;
	const int GameObjectTypeEnemy = 1;
	const int GameObjectTypeBullet = 4;
	const int GameObjectTypeProp = 8;
	const int GameObjectTypeSpawner = 16;
	const int GameObjectTypePickup = 32; // TODO

	const int GameModeStandard = 1;
	const int GameModeBossGauntlet = 2;

	const std::string ExplosionAnimationGroupName = "explosion";

	const std::string PlayerAnimationGroupName = "player";
	const std::string BlasterEnemyAnimationGroupName = "blasterEnemy";
	const std::string MachineBlasterEnemyAnimationGroupName = "mgBlasterEnemy";
	const std::string BasicEnemyAnimationGroupName = "basicEnemy";
	const std::string Boss0AnimationGroupName = "basicEnemy"; // tbd
	const std::string Boss1AnimationGroupName = "bossBlasterBot1";
	const std::string Boss2AnimationGroupName = "bossBlasterBot2";
	const std::string GameIntroAnimationGroupName = "gameIntro";

	enum{
		GameVersionPreview,
		GameVersionFinal,
		GameVersionDeveloper
	};

	const std::string GameVersionString = "GamePreviewVersion 0.1";
	const int         GameVersionId = GameVersionPreview; // 1 preview, 0 final game, everything else is developer.
#endif
