#include "camera.h"

void system_move_camera(struct GameData* data) {
  float look_modifier = 10.0f;
  vec2 target;
  glm_vec2_scale(data->entities.entities[0].velocity, look_modifier, target);
  glm_vec2_add(data->entities.entities[0].position, target, data->camera.position);
}
