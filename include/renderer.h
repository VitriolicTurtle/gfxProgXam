#include "constants.h"
#include "maploader.h"

class Renderer {
private:

public:
	Renderer() {}
	void drawMap(MapLoader* map);
	void drawObjModel(MapLoader* map);
};