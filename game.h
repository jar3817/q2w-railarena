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

//#include "shared.h"

#define GAME_API_VERSION 1

// edict->sv_flags
#define SVF_NO_CLIENT 1  // don't send entity to clients
// edict->solid values
typedef enum {
	SOLID_NOT, // no interaction with other objects
	SOLID_TRIGGER, // only touch when inside, after moving
	SOLID_BOX, // touch on edge
	SOLID_MISSILE, // touch on edge
	SOLID_BSP
// bsp clip, touch on edge
} solid_t;

// link_t is only used for entity area links now
typedef struct link_s {
	struct link_s *prev, *next;
} link_t;

#define MAX_ENT_CLUSTERS 16

/*
 * This is the server's definition of the client and edict structures. The
 * game module is free to add additional members to these structures, provided
 * they communicate the actual size of them at runtime through the game export
 * structure.
 */

/*
typedef struct {
	void *opaque;
} g_client_locals_t;

typedef struct {
	void *opaque;
} g_edict_locals_t;

typedef struct g_client_s g_client_t;
typedef struct g_edict_s g_edict_t;
*/

struct g_client_s {
	player_state_t ps; // communicated by server to clients
	uint32_t ping;

	g_client_locals_t locals; // game-local data members
};

struct g_edict_s {
	const char *class_name;
	const char *model;

	// the entity state is delta-compressed based on what each client last
	// received for a given entity
	entity_state_t s;
	_Bool in_use;

	uint32_t sv_flags; // SVF_NO_CLIENT, etc

	link_t area; // linked to a division node or leaf
	uint32_t link_count;

	// the following variables facilitate PVS and PHS culling
	int32_t num_clusters; // if -1, use head_node instead
	int32_t clusters[MAX_ENT_CLUSTERS];
	int32_t head_node; // unused if num_clusters != -1
	int32_t area_num, area_num2;

	// the following variables facilitate tracing and basic physics interactions
	vec3_t mins, maxs;
	vec3_t abs_mins, abs_maxs, size;
	solid_t solid;
	uint32_t clip_mask; // e.g. MASK_SHOT, MASK_PLAYER_SOLID, ..
	g_edict_t *owner; // projectiles are not clipped against their owner

	// the client struct, as a pointer, because it is both optional and variable sized
	g_client_t *client;

	g_edict_locals_t locals; // game-local data members
};

// functions provided by the main engine
typedef struct {

	uint32_t frame_rate; // server frames per second
	uint32_t frame_millis;
	vec_t frame_seconds; // seconds per frame

	void (*Print)(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
	void (*Debug_)(const char *func, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
	void (*Warn_)(const char *func, const char *fmr, ...) __attribute__((format(printf, 2, 3)));
	void (*Error_)(const char *func, const char *fmt, ...) __attribute__((noreturn, format(printf, 2, 3)));

	void (*BroadcastPrint)(const int32_t level, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
	void (*ClientPrint)(const g_edict_t *ent, const int32_t level, const char *fmt, ...) __attribute__((format(printf, 3, 4)));

	// config_strings are used to transmit arbitrary tokens such
	// as model names, skin names, team names, and weather effects
	void (*ConfigString)(const uint16_t index, const char *string);

	// create config_strings and some internal server state
	uint16_t (*ModelIndex)(const char *name);
	uint16_t (*SoundIndex)(const char *name);
	uint16_t (*ImageIndex)(const char *name);

	void (*SetModel)(g_edict_t *ent, const char *name);
	void (*Sound)(const g_edict_t *ent, const uint16_t index, const uint16_t atten);
	void (*PositionedSound)(const vec3_t origin, const g_edict_t *ent, const uint16_t index,
			const uint16_t atten);

	// collision detection
	c_trace_t (*Trace)(const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end,
			const g_edict_t *passent, const int32_t mask);
	int32_t (*PointContents)(const vec3_t point);
	_Bool (*inPVS)(const vec3_t p1, const vec3_t p2);
	_Bool (*inPHS)(const vec3_t p1, const vec3_t p2);
	void (*SetAreaPortalState)(int32_t portal_num, _Bool open);
	_Bool (*AreasConnected)(int32_t area1, int32_t area2);
	void (*Pmove)(pm_move_t *pm_state); // player movement code common with client prediction

	// an entity will never be sent to a client or used for collision
	// if it is not passed to linkentity. if the size, position, or
	// solidity changes, it must be relinked.
	void (*LinkEntity)(g_edict_t *ent);
	void (*UnlinkEntity)(g_edict_t *ent); // call before removing an interactive edict
	int32_t (*AreaEdicts)(const vec3_t mins, const vec3_t maxs, g_edict_t **area_edicts,
			const int32_t max_area_edicts, const int32_t area_type);

	// network messaging
	void (*Multicast)(const vec3_t origin, multicast_t to);
	void (*Unicast)(const g_edict_t *ent, const _Bool reliable);
	void (*WriteData)(const void *data, size_t len);
	void (*WriteChar)(const int32_t c);
	void (*WriteByte)(const int32_t c);
	void (*WriteShort)(const int32_t c);
	void (*WriteLong)(const int32_t c);
	void (*WriteString)(const char *s);
	void (*WritePosition)(const vec3_t pos); // some fractional bits
	void (*WriteDir)(const vec3_t pos); // single byte encoded, very coarse
	void (*WriteAngle)(const vec_t v);

	// managed memory allocation
	void *(*Malloc)(size_t size, z_tag_t tag);
	void (*Free)(void *ptr);
	void (*FreeTag)(z_tag_t tag);

	// filesystem interaction
	int64_t (*LoadFile)(const char *file_name, void **buffer);
	void (*FreeFile)(void *buffer);

	// console variable interaction
	cvar_t *(*Cvar)(const char *name, const char *value, uint32_t flags, const char *desc);

	// command function parameter access
	int32_t (*Argc)(void);
	const char *(*Argv)(int32_t n);
	const char *(*Args)(void); // concatenation of all argv >= 1

	// add commands to the server console as if they were typed in
	// for map changing, etc
	void (*AddCommandString)(const char *text);
} g_import_t;

// functions exported by the game subsystem
typedef struct {
	int32_t api_version;

	// the init function will only be called when a game starts,
	// not each time a level is loaded. Persistent data for clients
	// and the server can be allocated in init
	void (*Init)(void);
	void (*Shutdown)(void);

	// each new level entered will cause a call to SpawnEntities
	void (*SpawnEntities)(const char *name, const char *entities);

	_Bool (*ClientConnect)(g_edict_t *ent, char *user_info);
	void (*ClientBegin)(g_edict_t *ent);
	void (*ClientUserInfoChanged)(g_edict_t *ent, const char *user_info);
	void (*ClientDisconnect)(g_edict_t *ent);
	void (*ClientCommand)(g_edict_t *ent);
	void (*ClientThink)(g_edict_t *ent, user_cmd_t *cmd);

	void (*Frame)(void);

	const char *(*GameName)(void);

	// global variables shared between game and server

	// The edict array is allocated in the game dll so it
	// can vary in size from one game to another.
	//
	// The size will be fixed when ge->Init() is called
	struct g_edict_s *edicts;
	size_t edict_size;
	uint16_t num_edicts; // current number, <= max_edicts
	uint16_t max_edicts;
} g_export_t;

