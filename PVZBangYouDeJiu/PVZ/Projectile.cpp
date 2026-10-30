#include "Projectile.h"
#include <stdint.h>

ProjectileDefinition* gProjectileDefinition = (ProjectileDefinition*)0x69F1C0;

void Projectile::Die()
{
	uintptr_t func = 0x46EB20;

	_asm
	{
		mov eax, this;
		call func;
	}
}

void Projectile::DoImpact(Zombie* theZombie)
{
	uintptr_t func = 0x46E000;

	_asm
	{
		mov eax, theZombie;
		mov ecx, this;
		call func;
	}
}

ProjectileDefinition& Projectile::GetProjectileDef()
{
	ProjectileDefinition& aProjectileDef = *(ProjectileDefinition*)(0x69F1C0 + sizeof(ProjectileDefinition) * mProjectileType);
	return aProjectileDef;
}

Sexy::Rect Projectile::GetProjectileRect()
{
	uintptr_t func = 0x46EBC0;
	Sexy::Rect result;
	Sexy::Rect* pResult = &result;
	_asm
	{
		mov ecx, pResult;
		mov esi, this;
		call func;
	}
	return result;
}

Plant* Projectile::FindCollisionTargetPlant()
{
	uintptr_t func = 0x46CAA0;
	Plant* result;
	_asm
	{
		push this;
		call func;
		mov result, eax;
	}
	return result;
}

void Projectile::ConvertToFireball(int theGridX)
{
	uintptr_t func = 0x46ECB0;

	_asm
	{
		mov eax, theGridX;
		mov ecx, this;
		call func;
	}
}
