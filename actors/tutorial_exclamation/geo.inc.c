#include "src/game/envfx_snow.h"

const GeoLayout tutorial_exclamation_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tutorial_exclamation_Text_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
