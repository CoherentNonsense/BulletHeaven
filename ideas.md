## Weapons/Effects

### format examples (maybe)

```
weapon: magic_missiles
name: Magic Missiles
type: basic_shot
  firerate: 2.0
  bullets_per_shot: 1
  bullet_type: basic
    sprite:
      uv: (0, 0)
      size: (8, 8)
    lifetime: 10.0
    on_expire: explode
      damage: 2
      radius: 16
    on_hit: explode
      damage: 2
      radius: 16
```

```
weapon: magic_beans extends magic_missiles
name: Magic Beans
type: extends magic_missiles
  bull
```

### Base Weapon

```
weapon: string
name: string
damage: int
firerate: float
cooldown_time: float
active_time: float
type: weapon_type
```

### Weapon Types

#### position_shot

Spawns a bullet at a position (cycles through spawn points in order)

```
type: position_shot
  bullets_per_shot: int
  accuracy: [0.0-1.0]
  spawn_points: vec2[]
  bullet_type: *
```

#### target_shot

Spawns a bullet towards an enemy

```
type: position_shot
  bullets_per_shot: int
  accuracy: [0.0-1.0]
  bullet_type: *
```

#### area_effect

```
type: area_effect
  radius: float
```

#### minion

```
type: minion
  health: int
  speed: float
  type: *
```

### Bullet Types

#### basic_bullet

Basic bullet (maybe just for testing)

```
bullet_type: basic_bullet
  sprite:
    uv: vec2
    size: vec2
  lifetime: float
  on_expire: special_bullet
  on_hit: special_bullet
```

#### lightning

Creates a chain of lightning that hits n enemies

```
type: lightning
  color_1: vec3
  color_2: vec3
  chain: int
```