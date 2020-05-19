#include "constants.h"
#include "wallobj.h"
#include "player.h"

class Renderer {
private:

public:
	Renderer() {}
	void loadMap(std::vector<WallObj>* wallVector, Player* player);	// Loads and updates the map.
};