#include "weapon.h"

void system_weapon(struct GameData* data) {
  struct Entity* player = entity_pool_get(&data->entities, data->player_id);
  for (int i = 0; i < 1; ++i) {
    struct Weapon* weapon = &data->player.weapons[i];
    
    if (weapon->attack_timer < data->time) {
      weapon->attack_timer = data->time + weapon->time_between_attacks;
      
      // bullet 1
      entity_id id = entity_pool_add(&data->entities);
      struct Entity* entity = entity_pool_get(&data->entities, id);
      glm_vec2_copy(player->position, entity->position);
      
      entity->velocity[0] = 1.0f;
      entity->velocity[1] = 0.0f;
      glm_vec2_rotate(entity->velocity, -player->rotation, entity->velocity);
      glm_vec2_add(entity->velocity, player->velocity, entity->velocity);
      entity->uv_index = 2.0f;
      entity->rotation = player->rotation;
      entity->weight = 0.5f;
      entity->size = 2.0f;
      entity->type = ENTITY_BULLET;

      // bullet 2
      entity_id id_2 = entity_pool_add(&data->entities);
      struct Entity* entity_2 = entity_pool_get(&data->entities, id_2);
      glm_vec2_copy(player->position, entity_2->position);

      entity_2->velocity[0] = 1.0f;
      entity_2->velocity[1] = 0.0f;
      glm_vec2_rotate(entity_2->velocity, -player->rotation + GLM_PI, entity_2->velocity);
      glm_vec2_add(entity_2->velocity, player->velocity, entity_2->velocity);
      entity_2->uv_index = 2.0f;
      entity_2->rotation = player->rotation;
      entity_2->weight = 0.5f;
      entity_2->size = 2.0f;
      entity_2->type = ENTITY_BULLET;
    }
  }
}