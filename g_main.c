/*
 * Copyright(c) 1997-2001 Id Software, Inc.
 * Copyright(c) 2002 The Quakeforge Project.
 * Copyright(c) 2006 Quake2World.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

//#include "g_local.h"
//#include <string.h>
//#include <unistd.h>


#include "g_types.h"
#include "game.h"
#include "g_main.h"



#define GAME_NAME "railarena"

#define Debug(...) Debug_(__func__, __VA_ARGS__)
#define Warn(...) Warn_(__func__, __VA_ARGS__)
#define Error(...) Error_(__func__, __VA_ARGS__)

g_import_t gi;
g_export_t ge;

g_game_t g_game;
g_level_t g_level;

uint32_t means_of_death;

cvar_t *g_ammo_respawn_time;
cvar_t *g_auto_join;
cvar_t *g_capture_limit;
cvar_t *g_cheats;
cvar_t *g_ctf;
cvar_t *g_frag_limit;
cvar_t *g_friendly_fire;
cvar_t *g_gameplay;
cvar_t *g_gravity;
cvar_t *g_match;
cvar_t *g_max_entities;
cvar_t *g_motd;
cvar_t *g_mysql;
cvar_t *g_mysql_db;
cvar_t *g_mysql_host;
cvar_t *g_mysql_password;
cvar_t *g_mysql_user;
cvar_t *g_player_projectile;
cvar_t *g_random_map;
cvar_t *g_respawn_protection;
cvar_t *g_round_limit;
cvar_t *g_rounds;
cvar_t *g_spawn_farthest;
cvar_t *g_spectator_chat;
cvar_t *g_show_attacker_stats;
cvar_t *g_teams;
cvar_t *g_time_limit;
cvar_t *g_voting;
cvar_t *g_weapon_respawn_time;

cvar_t *password;

cvar_t *sv_max_clients;
cvar_t *sv_hostname;
cvar_t *dedicated;

g_team_t g_team_good, g_team_evil;

g_map_list_t g_map_list;


/*
 * @brief
 */
void G_ResetTeams(void) {
	
}

/*
 * @brief
 */
void G_ResetVote(void) {
	
}

/*
 * @brief Reset all items in the level based on gameplay, ctf, etc.
 */
static void G_ResetItems(void) {
	
}

/*
 * @brief For normal games, this just means reset scores and respawn.
 * For match games, this means cancel the match and force everyone
 * to ready again. Teams are only reset when teamz is true.
 */
static void G_RestartGame(_Bool teamz) {
	
}

/*
 * @brief
 */
static void G_MuteClient(char *name, _Bool mute) {
	
}

/*
 * @brief
 */
static void G_BeginIntermission(const char *map) {
	
}

/*
 * @brief
 */
static void G_CheckVote(void) {
	
}

/*
 * @brief The time limit, frag limit, etc.. has been exceeded.
 */
static void G_EndLevel(void) {
	//G_BeginIntermission(G_SelectNextmap());
}

/*
 * @brief
 */
static void G_CheckRoundStart(void) {
	
}

/*
 * @brief
 */
static void G_CheckRoundLimit() {
	
}

/*
 * @brief
 */
static void G_CheckRoundEnd(void) {
	
}

/*
 * @brief
 */
static void G_CheckMatchEnd(void) {
	
}

/*
 * @brief
 */
//static char *G_FormatTime(uint32_t time) {
	//return 
//}

/*
 * @brief
 */
static void G_CheckRules(void) {
	
}

/*
 * @brief
 */
static void G_ExitLevel(void) {
	
}

#define INTERMISSION (10.0 * 1000) // intermission duration
/*
 * @brief The main game module "think" function, called once per server frame.
 * Nothing would happen in Quake land if this weren't called.
 */
static void G_Frame(void) {
	/*
	int32_t i;
	g_edict_t *ent;

	g_level.frame_num++;
	g_level.time = g_level.frame_num * gi.frame_millis;

	// check for level change after running intermission
	if (g_level.intermission_time) {
		if (g_level.time > g_level.intermission_time + INTERMISSION) {
			G_ExitLevel();
			return;
		}
	}

	// treat each object in turn
	// even the world gets a chance to think
	ent = &g_game.edicts[0];
	for (i = 0; i < ge.num_edicts; i++, ent++) {

		if (!ent->in_use)
			continue;

		g_level.current_entity = ent;

		// update old origin for interpolation
		if (!(ent->s.effects & EF_LIGHTNING))
			VectorCopy(ent->s.origin, ent->s.old_origin);

		if (ent->locals.ground_entity) {

			// check for ground entities going away
			if (ent->locals.ground_entity->link_count != ent->locals.ground_entity_link_count)
				ent->locals.ground_entity = NULL;
		}

		if (i > 0 && i <= sv_max_clients->integer)
			G_ClientBeginFrame(ent);
		else
			G_RunEntity(ent);
	}

	// see if a vote has passed
	G_CheckVote();

	// inspect and enforce gameplay rules
	G_CheckRules();

	// see if a match should end
	G_CheckMatchEnd();

	// see if an arena round should start
	G_CheckRoundStart();

	// see if an arena round should end
	G_CheckRoundEnd();

	// build the player_state_t structures for all players
	G_EndClientFrames();
	*/
}

/*
 * @brief
 */
static void G_InitMapList(void) {
	/*
	int32_t i;

	memset(&g_map_list, 0, sizeof(g_map_list));

	for (i = 0; i < MAX_MAP_LIST_ELTS; i++) {
		g_map_list_elt_t *map = &g_map_list.maps[i];
		map->gravity = -1;
		map->gameplay = 0;
		map->teams = map->ctf = map->match = -1;
		map->frag_limit = map->round_limit = map->capture_limit = -1;
		map->time_limit = -1;
		map->weight = 1.0;
	}
	*/
}

/*
 * @brief Populates a g_map_list_t from a text file. See default/maps.lst
 */
static void G_ParseMapList(const char *file_name) {
	
}

/*
 * @brief
 */
const char *G_SelectNextmap(void) {
	
}

/*
 * @brief Returns the game name advertised by the server in info strings.
 */
const char *G_GameName(void) {
	/*
	static char name[64];

	sprintf(name, "%s", G_GameplayName(g_level.gameplay));

	if (g_level.ctf) {
		strcat(name, " / CTF");
	} else if (g_level.teams) {
		strcat(name, " / TDM");
	}

	return name;
	*/
}

/*
 * @brief This will be called when the game module is first loaded.
 */
void G_Init(void) {

	//gi.Print("  Game initialization...\n");
	/*
	memset(&g_game, 0, sizeof(g_game));

	gi.Cvar("game_name", GAME_NAME, CVAR_SERVER_INFO | CVAR_NO_SET, NULL);
	gi.Cvar("game_date", __DATE__, CVAR_SERVER_INFO | CVAR_NO_SET, NULL);

	g_ammo_respawn_time = gi.Cvar("g_ammo_respawn_time", "20.0", CVAR_SERVER_INFO,
			"Ammo respawn interval in seconds");
	g_auto_join = gi.Cvar("g_auto_join", "1", CVAR_SERVER_INFO,
			"Automatically assigns players to teams");
	g_capture_limit = gi.Cvar("g_capture_limit", "8", CVAR_SERVER_INFO,
			"The capture limit per level");
	g_cheats = gi.Cvar("g_cheats", "0", CVAR_SERVER_INFO, NULL);
	g_ctf = gi.Cvar("g_ctf", "0", CVAR_SERVER_INFO, "Enables capture the flag gameplay");
	g_frag_limit = gi.Cvar("g_frag_limit", "30", CVAR_SERVER_INFO, "The frag limit per level");
	g_friendly_fire = gi.Cvar("g_friendly_fire", "1", CVAR_SERVER_INFO, "Enables friendly fire");
	g_gameplay = gi.Cvar("g_gameplay", "0", CVAR_SERVER_INFO,
			"Selects deathmatch, arena, or instagib combat");
	g_gravity = gi.Cvar("g_gravity", "800", CVAR_SERVER_INFO, NULL);
	g_match = gi.Cvar("g_match", "0", CVAR_SERVER_INFO,
			"Enables match play requiring players to ready");
	g_max_entities = gi.Cvar("g_max_entities", "1024", CVAR_LATCH, NULL);
	g_motd = gi.Cvar("g_motd", "", CVAR_SERVER_INFO,
			"Message of the day, shown to clients on initial connect");
	g_mysql = gi.Cvar("g_mysql", "0", 0, NULL);
	g_mysql_db = gi.Cvar("g_mysql_db", "quake2world", 0, NULL);
	g_mysql_host = gi.Cvar("g_mysql_host", "localhost", 0, NULL);
	g_mysql_password = gi.Cvar("g_mysql_password", "", 0, NULL);
	g_mysql_user = gi.Cvar("g_mysql_user", "quake2world", 0, NULL);
	g_player_projectile = gi.Cvar("g_player_projectile", "1.0", CVAR_SERVER_INFO,
			"Scales player velocity to projectiles");
	g_random_map = gi.Cvar("g_random_map", "0", 0, "Enables map shuffling");
	g_respawn_protection = gi.Cvar("g_respawn_protection", "0.0", 0,
			"Respawn protection in seconds");
	g_round_limit = gi.Cvar("g_round_limit", "30", CVAR_SERVER_INFO,
			"The number of rounds to run per level");
	g_rounds = gi.Cvar("g_rounds", "0", CVAR_SERVER_INFO,
			"Enables rounds-based play, where last player standing wins");
	g_show_attacker_stats = gi.Cvar("g_show_attacker_stats", "1", CVAR_SERVER_INFO, NULL);
	g_spawn_farthest = gi.Cvar("g_spawn_farthest", "1", CVAR_SERVER_INFO, NULL);
	g_spectator_chat = gi.Cvar("g_spectator_chat", "1", CVAR_SERVER_INFO,
			"If enabled, spectators can only talk to other spectators");
	g_teams = gi.Cvar("g_teams", "0", CVAR_SERVER_INFO, "Enables teams-based play");
	g_time_limit = gi.Cvar("g_time_limit", "20.0", CVAR_SERVER_INFO,
			"The time limit per level in minutes");
	g_voting = gi.Cvar("g_voting", "1", CVAR_SERVER_INFO, "Activates voting");
	g_weapon_respawn_time = gi.Cvar("g_weapon_respawn_time", "5.0", CVAR_SERVER_INFO,
			"Weapon respawn interval in seconds");

	password = gi.Cvar("password", "", CVAR_USER_INFO, "The server password");

	sv_max_clients = gi.Cvar("sv_max_clients", "8", CVAR_SERVER_INFO | CVAR_LATCH, NULL);
	sv_hostname = gi.Cvar("sv_hostname", "Quake2World", CVAR_SERVER_INFO, NULL);
	dedicated = gi.Cvar("dedicated", "0", CVAR_NO_SET, NULL);


	G_ParseMapList("maps.lst");

	// initialize entities and clients for this game
	g_game.edicts = gi.Malloc(g_max_entities->integer * sizeof(g_edict_t), Z_TAG_GAME);
	g_game.clients = gi.Malloc(sv_max_clients->integer * sizeof(g_client_t), Z_TAG_GAME);

	ge.edicts = g_game.edicts;
	ge.max_edicts = g_max_entities->integer;
	ge.num_edicts = sv_max_clients->integer + 1;

	// set these to false to avoid spurious game restarts and alerts on init
	g_gameplay->modified = g_teams->modified = g_match->modified = g_rounds->modified
			= g_ctf->modified = g_cheats->modified = g_frag_limit->modified
					= g_round_limit->modified = g_capture_limit->modified = g_time_limit->modified
							= false;
	*/
	//gi.Print("  Game initialized\n");
}

/*
 * @brief Shuts down the game module. This is called when the game is unloaded
 * (complements G_Init).
 */
void G_Shutdown(void) {

	//gi.Print("  Game shutdown...\n");

	gi.FreeTag(Z_TAG_GAME_LEVEL);
	gi.FreeTag(Z_TAG_GAME);
}

_Bool G_ClientConnect(g_edict_t *ent, char *user_info) {
	return true;
}

void G_ClientDisconnect(g_edict_t *ent) {
}

void G_ClientBegin(g_edict_t *ent) {
}

void G_ClientCommand(g_edict_t *ent) {
}

void G_ClientThink(g_edict_t *ent, user_cmd_t *cmd) {
}

void G_ClientUserInfoChanged(g_edict_t *ent, const char *user_info) {
}

void G_SpawnEntities(const char *name, const char *entities) {
}

/*
 * @brief This is the entry point responsible for aligning the server and game module.
 * The server resolves this symbol upon successfully loading the game library,
 * and invokes it. We're responsible for copying the import structure so that
 * we can call back into the server, and returning a populated game export
 * structure.
 */
g_export_t *G_LoadGame(g_import_t *import) {

	gi = *import;

	memset(&ge, 0, sizeof(ge));

	ge.api_version = GAME_API_VERSION;

	ge.Init = G_Init;
	ge.Shutdown = G_Shutdown;
	ge.SpawnEntities = G_SpawnEntities;

	ge.ClientThink = G_ClientThink;
	ge.ClientConnect = G_ClientConnect;
	ge.ClientUserInfoChanged = G_ClientUserInfoChanged;
	ge.ClientDisconnect = G_ClientDisconnect;
	ge.ClientBegin = G_ClientBegin;
	ge.ClientCommand = G_ClientCommand;

	ge.Frame = G_Frame;

	ge.GameName = G_GameName;

	ge.edict_size = sizeof(g_edict_t);

	return &ge;
}
