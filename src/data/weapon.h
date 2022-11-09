#ifndef DATA_WEAPON_H
#define DATA_WEAPON_H

#define MAX_WEAPONS 5
#define MAX_EFFECTS 5

enum WeaponType {
  WEAPON_BASIC,
};

enum EffectType {
  EFFECT_DASH,
};

struct Weapon {
  enum WeaponType type;
  float time_between_attacks;
  float timer;
};

struct Effect {
  enum EffectType type;
  float time_between_uses;
  float use_timer;
};

struct Weapons {
  struct Weapon weapons[MAX_WEAPONS];
  struct Effect effects[MAX_EFFECTS];
};

#endif