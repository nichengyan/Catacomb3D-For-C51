#pragma once

#include <stdint.h>
#include "Entity.h"
#include "Defines.h"
#include "Draw.h"
/*x
enum class EnemyType : uint8_t
{
	Skeleton,
	Mage,
	Bat,
	Spider,
	NumEnemyTypes,
	None = NumEnemyTypes
};

enum class EnemyState : uint8_t
{
	Idle,
	Moving,
	Attacking,
	Stunned,
	Dying,
	Dead
};
*/
class EnemyType
{
    public:
        enum Value{
            Skeleton,
            Mage,
            Bat,
            Spider,
            NumEnemyTypes,
            None = NumEnemyTypes
        };
};        
/*       
}
        static const uint8_t Skeleton=0;
	static const uint8_t Mage=1;
	static const uint8_t Bat=2;
	static const uint8_t Spider=3;
	static const uint8_t NumEnemyTypes=4;
	static const uint8_t None = 24;//NumEnemyTypes
};
*/
class EnemyState
{
    public:
        enum Value{
            Idle,
            Moving,
            Attacking,
            Stunned,
            Dying,
            Dead
        };
};
/*
{
	static const uint8_t Idle=0;
	static const uint8_t Moving=1;
	static const uint8_t Attacking=2;
	static const uint8_t Stunned=3;
	static const uint8_t Dying=4;
	static const uint8_t Dead=5;
};
*/
struct EnemyArchetype//µ–»À‘≠–Õ
{
	const uint16_t* spriteData;

	uint8_t hp;
	uint8_t movementSpeed;
	uint8_t attackStrength;
	uint8_t attackDuration;
	uint8_t stunDuration;
	uint8_t isRanged;
	uint8_t spriteScale;
	//x AnchorType spriteAnchor;
        AnchorType::Value spriteAnchor;

	uint16_t* GetSpriteData() const		{ return (uint16_t*) pgm_read_ptr(&spriteData); }
	uint8_t GetHP() const				{ return pgm_read_byte(&hp); }
	uint8_t GetMovementSpeed() const	{ return pgm_read_byte(&movementSpeed); }
	uint8_t GetAttackStrength() const	{ return pgm_read_byte(&attackStrength); }
	uint8_t GetAttackDuration() const	{ return pgm_read_byte(&attackDuration); }
	uint8_t GetStunDuration() const		{ return pgm_read_byte(&stunDuration); }
	bool GetIsRanged() const			{ return pgm_read_byte(&isRanged) != 0; }
	uint8_t GetSpriteScale() const		{ return pgm_read_byte(&spriteScale); }
	//x AnchorType GetSpriteAnchor() const	{ return (AnchorType) pgm_read_byte(&spriteAnchor); }
        AnchorType::Value GetSpriteAnchor() const	{ return (AnchorType::Value) pgm_read_byte(&spriteAnchor); }
};

class Enemy : public Entity
{
public:
	//x void Init(EnemyType type, int16_t x, int16_t y);
        void Init(EnemyType::Value type, int16_t x, int16_t y);
	void Tick();
	bool IsValid() const { return type != EnemyType::None; }
	void Damage(uint8_t amount);
	void Clear() { type = EnemyType::None; }
	const EnemyArchetype* GetArchetype() const;
        EnemyState::Value GetState() const { return state; }
        EnemyType::Value GetType() const { return type; }

private:
	static const EnemyArchetype archetypes[(int)EnemyType::NumEnemyTypes];

	bool ShouldFireProjectile() const;
	bool FireProjectile(uint8_t angle);
	bool TryMove();
	void StunMove();
	bool TryFireProjectile();
	void PickNewTargetCell();
	bool TryPickCells(int8_t deltaX, int8_t deltaY);
	bool TryPickCell(int8_t newX, int8_t newY);
	uint8_t GetPlayerCellDistance() const;

        EnemyType::Value type ;
        EnemyState::Value state ;
	uint8_t frameDelay ;
	uint8_t hp;
	uint8_t targetCellX, targetCellY;
};

class EnemyManager
{
public:
	static constexpr int maxEnemies = 24; //24;
	static Enemy enemies[maxEnemies];
	
	static void Spawn(EnemyType::Value enemyType, int16_t x, int16_t y);
	static void SpawnEnemies();

	static Enemy* GetOverlappingEnemy(Entity& entity);
	static Enemy* GetOverlappingEnemy(int16_t x, int16_t y);
	
	static void Init();
	static void Draw();
	static void Update();
};
