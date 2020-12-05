#ifndef __RENDER_H__
#define __RENDER_H__

#include "External/SDL/include/SDL.h"
#include "Point.h"
#include "Module.h"

class Render : public Module
{
public:

	Render();

	// Destructor
	virtual ~Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	// Blit
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	bool DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, bool flip = false, float speed = 1.0f, bool half = false, float newScale = 1.0f, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX) const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool useCamera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

public:

	SDL_Renderer*	renderer;
	SDL_Rect		camera;
	Point<int>   startingCamPos;
	SDL_Rect		viewport;
	SDL_Color		background;
};

#endif // __RENDER_H__