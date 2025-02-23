void scroll_mini_pinball_Cube_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 12;
	int height = 128 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(mini_pinball_Cube_mesh_layer_1_vtx_0);

	deltaY = (int)(4.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_actor_geo_mini_pinball() {
	scroll_mini_pinball_Cube_mesh_layer_1_vtx_0();
};
