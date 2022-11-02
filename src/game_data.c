#include "game_data.h"
#include <assert.h>

struct GameData* game_data_new() {
  struct GameData* data = malloc(sizeof(struct GameData));
  
  data->entities.entities = malloc(sizeof(struct Entity) * MAX_ENTITIES);
  data->entities.entity_pool = malloc(sizeof(entity_id) * MAX_ENTITIES);
  data->entities.entity_pool_length = 0;
  data->entities.entities_count = 0;
  data->tick = 0;
  data->delta_time = 0.0f;
  data->time = 0.0f;
  data->debug = 0;
  data->enemy_spawner.timer = 0.0f;
  
  for (int i = 0; i < MAX_ENTITIES; ++i) {
    data->entities.entities[i].flags = 0;
  }

  return data;
}

void game_data_destroy(struct GameData* data) {
  free(data->entities.entities);
  free(data->entities.entity_pool);
  free(data);
}

entity_id create_entity(struct Entities* entities) {
  assert(entities->entities_count < MAX_ENTITIES);
  entity_id id;
  if (entities->entity_pool_length > 0) {
    entities->entity_pool_length -= 1;
    id = entities->entity_pool[entities->entity_pool_length];
  } else {
    id = entities->entities_count;
  }
  
  entities->entities_count += 1;
  entity_set_flags(get_entity_data(entities, id), ENTITY_FLAG_ACTIVE);

  return id;
}

void delete_entity(struct Entities* entities, entity_id id) {
  entity_remove_flags(get_entity_data(entities, id), ENTITY_FLAG_ACTIVE);
  
  entities->entity_pool[entities->entity_pool_length] = id;
  entities->entity_pool_length += 1;
  
  entities->entities_count -= 1;
}

struct Entity* get_entity_data(struct Entities* entities, entity_id id) {
  return &entities->entities[id];
}

int entity_get_flags(struct Entity* entity, int flags) {
  return entity->flags & flags;
}

void entity_set_flags(struct Entity* entity, int flags) {
  entity->flags |= flags;
}

void entity_remove_flags(struct Entity* entity, int flags) {
  entity->flags &= ~flags;
}

