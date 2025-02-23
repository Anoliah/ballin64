void scroll_sa_dl_Plane_mesh_layer_1_vtx_2() {
	int i = 0;
	int count = 107;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(sa_dl_Plane_mesh_layer_1_vtx_2);

	deltaX = (int)(-0.20000000298023224 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_sa_dl_Plane_mesh_layer_1_vtx_4() {
	int i = 0;
	int count = 4;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(sa_dl_Plane_mesh_layer_1_vtx_4);

	deltaY = (int)(3.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_sa() {
	scroll_sa_dl_Plane_mesh_layer_1_vtx_2();
	scroll_sa_dl_Plane_mesh_layer_1_vtx_4();
};
