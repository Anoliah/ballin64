#include "src/game/envfx_snow.h"

const GeoLayout mini_mariokart_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mini_marioikart_Cube_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mini_marioikart_Cube_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
