#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:

	void CheckLevelProgress();
	void SetUp(int level);
	void DebugKeys();

public:

	int		currentLevel;

	bool	levelCompleted; //used to check if the player has collected all the pickups

	SDL_Rect		cameraRect;
	

private:

	SDL_Rect		backgroundRect;
	SDL_Texture*	background;

};

#endif // __SCENE_H__