#include "enemy.h"

void system_enemy_move(struct GameData* data) {
  struct Entity* player = &data->entities.entities[0];
  vec2 dir;
  float speed = 0.3f;
  for (int i = 1; i < MAX_ENTITIES; ++i) {
    struct Entity* entity = &data->entities.entities[i];
    if (!entity_flag_get(entity, ENTITY_FLAG_ACTIVE) || entity->type != ENTITY_ENEMY) {
      continue;
    }

    glm_vec2_sub(player->position, entity->position, dir);
    if (glm_vec2_distance(player->position, entity->position) > 800.0f) {
      entity_pool_remove(&data->entities, i);
      continue;
    }

    glm_vec2_normalize(dir);
    glm_vec2_scale(dir, speed * data->delta_time, dir);
    
    entity->rotation = -atan2(entity->velocity[1], entity->velocity[0]) + GLM_PI / 2.0f;
    
    glm_vec2_add(entity->velocity, dir, entity->velocity);
  }
}

void system_enemy_spawn(struct GameData* data) {
  if (data->time > data->enemy_spawner.timer) {
    data->enemy_spawner.timer = data->time + 0.08f;
    entity_id id = entity_pool_add(&data->entities);
    struct Entity* entity = entity_pool_get(&data->entities, id);
    struct Entity* player = entity_pool_get(&data->entities, data->player_id);
    vec2 offset;
    glm_vec2_normalize_to(
      (vec2){(float)(rand() - RAND_MAX / 2), (float)(rand() - RAND_MAX / 2)},
      offset
    );
    glm_vec2_scale(offset, 300.0f, offset);
    entity_flag_set(entity, ENTITY_FLAG_RIGID_BODY);
    entity->position[0] = player->position[0] + offset[0];
    entity->position[1] = player->position[1] + offset[1];
    entity->velocity[0] = 0.0f;
    entity->velocity[1] = 0.0f;
    entity->size = 8.0f;
    entity->uv_index = 1.0f;
    entity->weight = 0.0f;
    entity->type = ENTITY_ENEMY;
  }
}
