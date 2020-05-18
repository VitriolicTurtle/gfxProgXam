#include "constants.h"
#include "wallobj.h"
#include "player.h"

class Renderer {
private:

public:
	Renderer() {}
	void loadMap(WallObj* wallObj, Player player);	// Loads and updates the map.
};