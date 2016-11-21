#include "Info.h"



int Info::x;
int Info::y;
int Info::PLAYER_STATUS;

void Info::addPlayerStatus(int bitmask){
	PLAYER_STATUS |= bitmask;
}

void Info::removePlayerStatus(int bitmask){
	PLAYER_STATUS &= ~bitmask;
}

void Info::resetPlayerStatus(){
	PLAYER_STATUS = 0;
}
