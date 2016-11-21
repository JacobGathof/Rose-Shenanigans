#pragma once

#define FIRE 0x00000001
#define POISON 0x00000002
#define SLOWED 0x00000004
#define FROZEN 0x00000008

#define CURSED 0x00000010
#define BLEEDING 0x00000020



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

