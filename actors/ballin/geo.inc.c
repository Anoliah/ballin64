#include "src/game/envfx_snow.h"

const GeoLayout ballin_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 200),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, ballin_Sphere_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
