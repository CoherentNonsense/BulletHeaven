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
  
  if (input_key_down(SYNGE_KEY_X)) {
    glm_vec2_scale(player->velocity, 1.3f, player->velocity);
  }
  
  if (input_key(SYNGE_KEY_C)) {
    printf("Special 2\n");
  }
  
  if (input_key_down(SYNGE_KEY_Q)) {
    data->debug = 1 - data->debug;
  }
}