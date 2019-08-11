void transformPoints(float points[], unsigned int length, float matrix[]) {
	
	float x, y, z;
	for (int i = 0; i < length; i += 3) {
		x = points[i];
		y = points[i + 1];
		z = points[i + 2];
		points[i] = matrix[0] * x + matrix[1] * y + matrix[2] * z + matrix[3];
		points[i + 1] = matrix[4] * x + matrix[5] * y + matrix[6] * z + matrix[7];
		points[i + 2] = matrix[8] * x + matrix[9] * y + matrix[10] * z + matrix[11];
	}
}