#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "data/entity.h"

#include <synge/synge.h>
#include <cglm/vec2.h>

#define MAX_BULLETS 800;

#define MAX_WEAPONS 5

#define MAX_RUSHES_PER_WAVE 5

typedef int wave_t;

enum WeaponType {
  WeaponBasic,  
};

struct Weapon {
  enum WeaponType type;
  float time_between_attacks;
  float attack_timer;
};

struct EnemySpawner {
  float timer;
};

struct Player {
  struct Weapon weapons[MAX_WEAPONS];
};

struct GameData {
  struct SyngeCamera camera;
  struct SyngeCamera ui_camera;
  float delta_time;
  float time;
  int tick;
  int debug;
  struct EntityPool entities;
  struct EnemySpawner enemy_spawner;
  entity_id player_id;
  struct Player player;
};

struct GameData* game_data_new();
void game_data_destroy(struct GameData* data);

#endif