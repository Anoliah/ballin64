void scroll_vcutm_dl_Lanuchpipe_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 32;
	int width = 32 * 0x20;
	int height = 128 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(vcutm_dl_Lanuchpipe_mesh_layer_1_vtx_0);

	deltaX = (int)(4.0 * 0x20) % width;
	deltaY = (int)(-2.0 * 0x20) % height;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}
	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
		vertices[i].n.tc[1] += deltaY;
	}
	currentX += deltaX;	currentY += deltaY;
}

void scroll_vcutm_dl_Logo_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 8;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(vcutm_dl_Logo_mesh_layer_1_vtx_0);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_vcutm_dl_Main_mesh_layer_1_vtx_2() {
	int i = 0;
	int count = 12;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(vcutm_dl_Main_mesh_layer_1_vtx_2);

	deltaY = (int)(-2.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_vcutm_dl_Main_mesh_layer_1_vtx_7() {
	int i = 0;
	int count = 8;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(vcutm_dl_Main_mesh_layer_1_vtx_7);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_vcutm_dl_Sign2_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 8;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(vcutm_dl_Sign2_mesh_layer_1_vtx_0);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_vcutm_dl_Slot_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 12;
	int height = 128 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(vcutm_dl_Slot_mesh_layer_1_vtx_0);

	deltaY = (int)(-4.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_vcutm() {
	scroll_vcutm_dl_Lanuchpipe_mesh_layer_1_vtx_0();
	scroll_vcutm_dl_Logo_mesh_layer_1_vtx_0();
	scroll_vcutm_dl_Main_mesh_layer_1_vtx_2();
	scroll_vcutm_dl_Main_mesh_layer_1_vtx_7();
	scroll_vcutm_dl_Sign2_mesh_layer_1_vtx_0();
	scroll_vcutm_dl_Slot_mesh_layer_1_vtx_0();
};
