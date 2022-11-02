#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <synge/synge.h>
#include <cglm/vec2.h>

#define MAX_ENTITIES 2000
#define MAX_BULLETS 800;

#define MAX_WEAPONS 5

#define MAX_RUSHES_PER_WAVE 5

#define ENTITY_FLAG_ACTIVE     0x0001 << 16
#define ENTITY_FLAG_COLLISION  0x0002 << 16

typedef int entity_id;
typedef int enemy_t;
typedef int wave_t;

enum EntityType {
  EntityPlayer,
  EntityEnemy,
  EntityBullet,
};

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

struct Entity {
  entity_id id;
  enum EntityType type;
  int flags;
  int health;
  float rotation;
  float weight;
  float size;
  float uv_index;
  vec2 velocity;
  vec2 position;
};

struct Entities {
  int entities_count;
  int entity_pool_length;
  struct Entity* entities;
  entity_id* entity_pool;
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
  struct Entities entities;
  struct EnemySpawner enemy_spawner;
  entity_id player_id;
  struct Player player;
};

struct GameData* game_data_new();
void game_data_destroy(struct GameData* data);

entity_id create_entity(struct Entities* entities);
void delete_entity(struct Entities* entities, entity_id id);
struct Entity* get_entity_data(struct Entities* entities, entity_id id);

int entity_get_flags(struct Entity* entity, int flags);
void entity_set_flags(struct Entity* entity, int flags);
void entity_remove_flags(struct Entity* entiity, int flags);

#endif