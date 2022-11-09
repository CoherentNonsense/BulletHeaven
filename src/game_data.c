#include "game_data.h"
#include <assert.h>

struct GameData* game_data_new() {
  struct GameData* data = malloc(sizeof(struct GameData));

  data->entities = entity_pool_new();  
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
  entity_pool_delete(&data->entities);
  free(data);
}
