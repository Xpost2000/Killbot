#ifndef PLAYER_DATA_STRUCT_H
#define PLAYER_DATA_STRUCT_H

enum AmmoTypes{
	LeadBall,
	SilverBullet,
	GoldBullet,
	MaxAmmoTypes // everything above is for the player.
};

//TODO: Use Observer pattern for this
//but I don't need this yet since the game 
//isn't in the stage where this is needed
struct PlayerStatisticsStruct{
	int deaths;
	int kills;

	int shots_fired;
	int shots_missed;
	int shots_hit;
};

//TODO: Use in the PlayerAI class.
struct PlayerDataStruct{
	bool ammo_type_unlocked[MaxAmmoTypes];
	int ammo_types[MaxAmmoTypes];
	int current_ammo_type;
};

#endif
