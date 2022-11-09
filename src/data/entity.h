#ifndef DATA_ENTITY_H
#define DATA_ENTITY_H

#include <cglm/vec2.h>

#define MAX_ENTITIES 2000

#define ENTITY_FLAG_ACTIVE      0x1 << 0
#define ENTITY_FLAG_RIGID_BODY  0x1 << 1
#define ENTITY_FLAG_ENEMY       0x1 << 2
#define ENTITY_FLAG_ONE         0x1 << 3
#define ENTITY_FLAG_TWO         0x1 << 4
#define ENTITY_FLAG_THREE       0x1 << 5
#define ENTITY_FLAG_FOUR        0x1 << 6
#define ENTITY_FLAG_FIVE        0x1 << 7

typedef int entity_id;

enum EntityType {
  ENTITY_PLAYER,
  ENTITY_ENEMY,
  ENTITY_BULLET,
};

struct Entity {
  enum EntityType type;
  int flags;
  float rotation;
  float weight;
  float size;
  float uv_index;
  vec2 velocity;
  vec2 position;
};

struct EntityPool {
  struct Entity* entities;
  int count;
  entity_id* pool;
  int pool_count;
};


// entity
// ------
int entity_flag_get(const struct Entity* entity, const int flags);
void entity_flag_init(struct Entity* entity, const int flags);
void entity_flag_set(struct Entity* entity, const int flags);
void entity_flag_remove(struct Entity* entity, const int flags);


// entity pool
// -----------
struct EntityPool entity_pool_new();
void entity_pool_delete(const struct EntityPool* pool);

entity_id entity_pool_add(struct EntityPool* pool);
void entity_pool_remove(struct EntityPool* pool, const entity_id id);
struct Entity* entity_pool_get(const struct EntityPool* pool, const entity_id id);

#endif