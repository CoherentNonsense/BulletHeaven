#include "entities.h"
#include <stdio.h>

static int entity_in_view(struct Entity* entity_a, struct Entity* entity_b) {
  if (glm_vec2_distance2(entity_a->position, entity_b->position) > glm_pow2(300.0f)) {
    return 0;
  }
  
  return 1;
}

void system_move_entities(struct GameData* data) {
  float drag = 0.8f;
  vec2 friction;
  for (int i = 0; i < MAX_ENTITIES; ++i) {
    struct Entity* entity = &data->entities.entities[i];
    if (!entity_get_flags(entity, ENTITY_FLAG_ACTIVE)) {
      continue;
    }

    glm_vec2_scale(entity->velocity, drag * data->delta_time, friction);
    glm_vec2_sub(entity->velocity, friction, entity->velocity);
    glm_vec2_add(entity->position, entity->velocity, entity->position);

  }
}

void system_entities_collide(struct GameData* data) {  
  vec2 repulsion;
  for (int i = 0; i < MAX_ENTITIES; ++i) {
    struct Entity* entity = &data->entities.entities[i];
    if (!entity_get_flags(entity, ENTITY_FLAG_ACTIVE)) {
      continue;
    }
    
    if (!entity_get_flags(entity, ENTITY_FLAG_COLLISION)) {
      continue;
    }
    
    struct Entity* player = get_entity_data(&data->entities, data->player_id);
    if (!entity_in_view(player, entity)) {
      continue;
    }

    glm_vec2_copy((vec2){0.0f, 0.0f}, repulsion);
    for (int j = 0; j < MAX_ENTITIES; ++j) {
      struct Entity* other = &data->entities.entities[j];
      if (!entity_get_flags(other, ENTITY_FLAG_ACTIVE)) {
        continue;
      }

      if (!entity_get_flags(other, ENTITY_FLAG_COLLISION)) {
        continue;
      }

      if (i != j && entity->weight <= other->weight) {
        vec2 dir;
        glm_vec2_sub(entity->position, other->position, dir);
        float dist = glm_vec2_distance(entity->position, other->position);
        if (dist < entity->size + other->size) {
          glm_vec2_normalize(dir);
          // glm_vec2_scale(dir, entity->size + other->size - dist, dir);
          glm_vec2_scale(dir, (entity->size + other->size - dist) * 0.8f, dir);
          glm_vec2_add(dir, repulsion, repulsion);
        }
      }
    }
    glm_vec2_add(entity->position, repulsion, entity->position);
  }
}

void system_draw_entities(struct GameData* data) {
  struct Entity* player = get_entity_data(&data->entities, data->player_id);
  for (int i = 0; i < MAX_ENTITIES; ++i) {
    struct Entity* entity = &data->entities.entities[i];
    if (!entity_get_flags(entity, ENTITY_FLAG_ACTIVE) || !entity_in_view(player, entity)) {
      continue;
    }

    graphics_draw(entity->position, (vec2){16.0f * entity->uv_index, 0.0f}, (vec2){16.0f, 16.0f}, -entity->rotation);    
  }
}
