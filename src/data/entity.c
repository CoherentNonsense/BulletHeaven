#include "entity.h"

// entity
// ------
int entity_flag_get(const struct Entity* entity, const int flags) {
  return (entity->flags & flags) == flags;
}

void entity_flag_init(struct Entity* entity, const int flags) {
  entity->flags = flags;
}

void entity_flag_set(struct Entity* entity, const int flags) {
  entity->flags |= flags;
}

void entity_flag_remove(struct Entity* entity, const int flags) {
  entity->flags &= ~flags;
}


// entity pool
// -----------
struct EntityPool entity_pool_new() {
  struct EntityPool pool;
  pool.count = 0;
  pool.pool_count = 0;
  pool.entities = malloc(sizeof(struct Entity) * MAX_ENTITIES);
  pool.pool = malloc(sizeof(int) * MAX_ENTITIES);
  
  return pool;
}

void entity_pool_delete(const struct EntityPool* pool) {
  free(pool->entities);
  free(pool->pool);
}

entity_id entity_pool_add(struct EntityPool* pool) {
  entity_id id;
  if (pool->pool_count > 0) {
    pool->pool_count -= 1;
    id = pool->pool[pool->pool_count];
  } else {
    id = pool->count;
  }

  pool->count += 1;
  struct Entity* entity = entity_pool_get(pool, id);
  entity_flag_init(entity, ENTITY_FLAG_ACTIVE);

  return id;
}

void entity_pool_remove(struct EntityPool* pool, const entity_id id) {
  struct Entity* entity = entity_pool_get(pool, id);
  entity_flag_remove(entity, ENTITY_FLAG_ACTIVE);

  pool->pool[pool->pool_count] = id;
  pool->pool_count += 1;
  pool->count -= 1;
}

struct Entity* entity_pool_get(const struct EntityPool* pool, const entity_id id) {
  return &pool->entities[id];
}