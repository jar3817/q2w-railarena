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

#ifndef __SHARED_H__
#define __SHARED_H__

#include "quake2world.h"

// math and trigonometry functions
int32_t Random(void); // 0 to (2^32)-1
vec_t Randomf(void); // 0.0 to 1.0
vec_t Randomc(void); // -1.0 to 1.0

void ClearBounds(vec3_t mins, vec3_t maxs);
void AddPointToBounds(const vec3_t v, vec3_t mins, vec3_t maxs);

_Bool VectorCompare(const vec3_t v1, const vec3_t v2);
_Bool VectorNearer(const vec3_t v1, const vec3_t v2, const vec3_t comp);

vec_t VectorNormalize(vec3_t v);  // returns vector length
vec_t VectorLength(const vec3_t v);
void VectorMix(const vec3_t v1, const vec3_t v2, const vec_t mix, vec3_t out);
void VectorMA(const vec3_t veca, const vec_t scale, const vec3_t vecb, vec3_t vecc);
void CrossProduct(const vec3_t v1, const vec3_t v2, vec3_t cross);

void ConcatRotations(vec3_t in1[3], vec3_t in2[3], vec3_t out[3]);

void VectorAngles(const vec3_t vector, vec3_t angles);
void AngleVectors(const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);

void VectorLerp(const vec3_t from, const vec3_t to, const vec_t frac, vec3_t out);
void AngleLerp(const vec3_t from, const vec3_t to, const vec_t frac, vec3_t out);

byte SignBitsForPlane(const c_bsp_plane_t *plane);
int32_t BoxOnPlaneSide(const vec3_t emins, const vec3_t emaxs, const c_bsp_plane_t *plane);

void ProjectPointOnPlane(vec3_t dst, const vec3_t p, const vec3_t normal);
void PerpendicularVector(vec3_t dst, const vec3_t src);
void TangentVectors(const vec3_t normal, const vec3_t sdir, const vec3_t tdir, vec4_t tangent, vec3_t bitangent);
void RotatePointAroundVector(vec3_t dst, const vec3_t dir, const vec3_t point, vec_t degrees);

void PackPosition(const vec3_t in, int16_t *out);
void UnpackPosition(const int16_t *in, vec3_t out);
#define PackAngle(x) ((uint16_t)((x) * 65536 / 360.0) & 65535)
void PackAngles(const vec3_t in, int16_t *out);
#define UnpackAngle(x) ((x) * (360.0 / 65536.0))
#define Radians(d) ((d * M_PI) / 180.0)
void UnpackAngles(const int16_t *in, vec3_t out);
void ClampAngles(vec3_t angles);

// color functions
#define EFFECT_COLOR_RED 232
#define EFFECT_COLOR_GREEN 201
#define EFFECT_COLOR_BLUE 119
#define EFFECT_COLOR_YELLOW 219
#define EFFECT_COLOR_ORANGE 225
#define EFFECT_COLOR_WHITE 216
#define EFFECT_COLOR_PINK 247
#define EFFECT_COLOR_PURPLE 187
#define EFFECT_COLOR_DEFAULT 0

#define TEAM_COLOR_RED 242
#define TEAM_COLOR_BLUE 243

vec_t ColorNormalize(const vec3_t in, vec3_t out);
void ColorFilter(const vec3_t in, vec3_t out, vec_t brightness, vec_t saturation, vec_t contrast);
int32_t ColorByName(const char *s, int32_t def);

// string functions
_Bool GlobMatch(const char *pattern, const char *text);
_Bool MixedCase(const char *s);
char *CommonPrefix(GList *words);
void Lowercase(const char *in, char *out);
char *Trim(char *s);
const char *Basename(const char *path);
void Dirname(const char *in, char *out);
void StripExtension(const char *in, char *out);
void StripColor(const char *in, char *out);
int32_t StrColorCmp(const char *s1, const char *s2);
char *ParseToken(const char **data_p);
char *va(const char *format, ...) __attribute__((format(printf, 1, 2)));
char *vtos(const vec3_t v);

// key / value info strings
#define MAX_USER_INFO_KEY		64
#define MAX_USER_INFO_VALUE		64
#define MAX_USER_INFO_STRING	512

char *GetUserInfo(const char *s, const char *key);
void DeleteUserInfo(char *s, const char *key);
void SetUserInfo(char *s, const char *key, const char *value);
_Bool ValidateUserInfo(const char *s);

#endif /* __SHARED_H__ */

