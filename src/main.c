#include "game_data.h"
#include "systems/player.h"
#include "systems/entities.h"
#include "systems/enemy.h"
#include "systems/camera.h"
#include "systems/weapon.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <synge/synge.h>
#include <cglm/vec2.h>

void draw_text(vec2 position, char* text) {
  vec2 cursor;
  glm_vec2_copy(position, cursor);
  while (*text != 0) {
    int c = (int)*text++;
    int x = (c % 16) * 8;
    int y = ((c / 16) + 16) * 8;
    graphics_draw(cursor, (vec2){(float)x, (float)y}, (vec2){8.0f, 8.0f}, 0);
    cursor[0] += 8.0f;
  }
}

float max_fps = 0.0f;
float min_fps = 0.0f;
void system_debug(struct GameData* data) {
  float fps = 1.0f / data->delta_time;
  if (fps > max_fps) {
    max_fps = fps;
  } else if (fps < min_fps) {
    min_fps = fps;
  }
  if (data->tick % 200 == 0) {
    max_fps = fps;
    min_fps = fps;
  }
  
  if (!data->debug) {
    return;
  }
  
  struct Entity* player = get_entity_data(&data->entities, data->player_id);
  
  char buffer[50];
  sprintf(buffer, "POS: (%.2f, %.2f)", player->position[0], player->position[1]);
  draw_text((vec2){-230.0f, -70.0f}, buffer);
  sprintf(buffer, "VEL: (%.2f, %.2f)", player->velocity[0], player->velocity[1]);
  draw_text((vec2){-230.0f, -90.0f}, buffer);
  sprintf(buffer, "ROT: %.2f", player->rotation);
  draw_text((vec2){-230.0f, -80.0f}, buffer);
  sprintf(buffer, "FPS: %.2f", fps);
  draw_text((vec2){-230.0f, -120.0f}, buffer);
  sprintf(buffer, "MIN: %.2f", min_fps);
  draw_text((vec2){-230.0f, -130.0f}, buffer);
  sprintf(buffer, "TIME: %.2f", data->time);
  draw_text((vec2){-230.0f, -110.0f}, buffer);
  sprintf(buffer, "ENT: %d", data->entities.entities_count);
  draw_text((vec2){-230.0f, -100.0f}, buffer);
}

int main() {
  srand(time(NULL));
  
  const vec2 game_size = {480.0f, 270.0f};
  synge_init("Bullet Heaven", game_size);

  unsigned int texture = graphics_load_texture("resources/textures/spritesheet.png");
  graphics_use_texture(texture);

  struct GameData* game_data = game_data_new();
  game_data->camera = synge_camera_new(game_size);
  game_data->ui_camera = synge_camera_new(game_size);
    
  game_data->player_id = create_entity(&game_data->entities);
  struct Entity* player = get_entity_data(&game_data->entities, game_data->player_id);
  player->size = 4.0f;
  player->weight = 1.0f;
  player->uv_index = 0.0f;
  player->rotation = 0.0f;
  entity_set_flags(player, ENTITY_FLAG_COLLISION);
  glm_vec2_copy(GLM_VEC2_ZERO, player->position);
  glm_vec2_copy(GLM_VEC2_ZERO, player->velocity);

  game_data->player.weapons[0].type = WeaponBasic;
  game_data->player.weapons[0].attack_timer = 0.0f;
  game_data->player.weapons[0].time_between_attacks = 1.0f;
  
  while (synge_is_running()) {
    float current_time = synge_get_time();
    game_data->delta_time = current_time - game_data->time;
    game_data->time = current_time;
    game_data->tick += 1;
    
    system_player_move(game_data);
    system_player_attack(game_data);
    system_enemy_spawn(game_data);
    system_enemy_move(game_data);
    system_move_entities(game_data);
    system_entities_collide(game_data);
    system_weapon(game_data);
    system_move_camera(game_data);
        
    // Drawing
    synge_start_draw(game_data->camera);
    graphics_clear();    

    system_draw_entities(game_data);
    // system_debug_background(game_data);

    graphics_flush();

    synge_start_draw(game_data->ui_camera);
    system_debug(game_data);
    
    synge_end_draw();
    
    
    synge_poll();
  }
  
  game_data_destroy(game_data);  
  synge_terminate();
  
  return 0;
}