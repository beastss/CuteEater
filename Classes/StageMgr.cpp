#include "StageMgr.h"
int stacount[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
float tim[] = { 720, 600, 480, 360, 300, 240, 180, 120 };
int food[] = { 10, 200, 200, 200, 100, 100, 100, 100 };
int cstage = 1;
int gho[] = { 10, 11, 12, 13, 14, 15, 16, 17 };
std::string  map[] = { "game_scene/map_01.png", "game_scene/map_02.png", "game_scene/map_03.png", "game_scene/map_04.png", "game_scene/map_05.png", "game_scene/map_06.png", "game_scene/map_07.png", "game_scene/map_08.png" };


StageMgr * StageMgr::getIter()
{
	static StageMgr  iter;

	return &iter;
}

void StageMgr::reset()
{
	for (int i = 0; i < sizeof(stagecount) / sizeof(int); i++)
	{
		stagecount[i] = stacount[i];
	}

	for (int i = 0; i < sizeof(time) / sizeof(float); i++)
	{
		time[i] = tim[i];
	}

	for (int i = 0; i < sizeof(foods) / sizeof(int); i++)
	{
		foods[i] = food[i];

	}

	for (int i = 0; i < sizeof(ghost) / sizeof(int); i++)
	{
		ghost[i] = gho[i];
	}
	currentstage = 1;
}
 StageMgr::StageMgr()
{
	 for (int i = 0; i < sizeof(stagecount)/sizeof(int); i++)
	 {
		 stagecount[i] = stacount[i];
	 }

	 for (int i = 0; i < sizeof(time) / sizeof(float); i++)
	 {
		 time[i] = tim[i];
	 }

	 for (int i = 0; i < sizeof(foods) / sizeof(int); i++)
	 {
		 foods[i] = food[i];

	 }
		 
	 for (int i = 0; i < sizeof(ghost) / sizeof(int); i++)
	 {
		 ghost[i] = gho[i];
	 }
		 
	 /*for (int i = 0; i < sizeof(mapnames) / sizeof(string); i++)
	 {
		 mapnames[i] = map[i];
	 }*/

}