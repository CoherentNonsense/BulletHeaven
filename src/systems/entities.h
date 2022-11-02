#ifndef SYSTEM_ENTITIES_H
#define SYSTEM_ENTITIES_H

#include "../game_data.h"

void system_move_entities(struct GameData* data);
void system_entities_collide(struct GameData* data);
void system_draw_entities(struct GameData* data);

#endif