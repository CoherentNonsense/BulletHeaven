#include "player.h"
#include <stdio.h>

void system_player_move(struct GameData* data) {
  // movement
  float speed = 0.8f;
  float break_speed = 3.0f;
  float rotation_speed = 5.0f;
  struct Entity* player = &data->entities.entities[0];
  if (input_key(SYNGE_KEY_UP)) {
    player->velocity[0] += sin(player->rotation) * (data->delta_time * speed);  
    player->velocity[1] += cos(player->rotation) * (data->delta_time * speed);  
  }
  if (input_key(SYNGE_KEY_LEFT)) {
    player->rotation -= data->delta_time * rotation_speed;
  }
  if (input_key(SYNGE_KEY_Z) && glm_vec2_distance2(GLM_VEC2_ZERO, player->velocity) > 0.1f) {
    vec2 break_force;
    glm_vec2_normalize_to(player->velocity, break_force);
    glm_vec2_scale(break_force, break_speed * data->delta_time, break_force);
    glm_vec2_sub(player->velocity, break_force, player->velocity);
  }
  if (input_key(SYNGE_KEY_RIGHT)) {
    player->rotation += data->delta_time * rotation_speed;
  }
  
  if (input_key(SYNGE_KEY_X)) {
    printf("Special 1\n");
  }
  
  if (input_key(SYNGE_KEY_C)) {
    printf("Special 2\n");
  }
  
  if (input_key_down(SYNGE_KEY_Q)) {
    data->debug = 1 - data->debug;
  }
}

void system_player_attack(struct GameData* data) {
  struct Entity* player = get_entity_data(&data->entities, data->player_id);
  for (int i = 0; i < 1; ++i) {
    struct Weapon* weapon = &data->player.weapons[i];
    if (weapon->attack_timer < data->time) {
      weapon->attack_timer = data->time + weapon->time_between_attacks;
      entity_id id = create_entity(&data->entities);
      struct Entity* entity = get_entity_data(&data->entities, id);
      glm_vec2_copy(player->position, entity->position);

      entity_remove_flags(entity, ENTITY_FLAG_COLLISION);
      entity->velocity[0] = 1.0f;
      entity->velocity[1] = 0.0f;
      entity->uv_index = 2.0f;
      entity->rotation = 0.0f;
      entity->weight = 0.5f;
      entity->size = 2.0f;
      entity->type = EntityBullet;
    }
  }
}
