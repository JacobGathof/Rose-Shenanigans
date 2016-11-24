#pragma once

#define FIRE 0x00000001
#define POISON 0x00000002
#define SLOWED 0x00000004
#define FROZEN 0x00000008

#define CURSED 0x00000010
#define BLEEDING 0x00000020
#define STRENGTHEN 0x00000040  // UP ATTACK
#define ENVIGORATE 0x00000080  // UP HEALTH

#define ENLIGHTENED 0x00000100 // UP MANA


class Info
{
public:
	static int x;
	static int y;
	static int PLAYER_STATUS;

	static void addPlayerStatus(int bitmask);
	static void removePlayerStatus(int bitmask);
	static void resetPlayerStatus();

};

