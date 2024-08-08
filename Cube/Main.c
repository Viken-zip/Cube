#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

//NOTE: this is not tought trou because distance i bsicly max of how far away a corner can be! so mac distance value is basicly in your face!

typedef struct{
	int r;
	int g;
	int b;
} RGB;

typedef struct vector {
	double x;
	double z;
	double y;
} vector;

typedef struct{
	struct vector corner1;
	struct vector corner2;
	struct vector corner3;
	struct vector corner4;
	struct vector corner5;
	struct vector corner6;
	struct vector corner7;
	struct vector corner8;
} cube;

cube* createCube() {
	cube* newCube;

	newCube = (cube*)malloc(sizeof(cube));
	if (newCube == NULL) {
		printf("Failed to give cube memory upon it's creation of the divine createCube function!");
		return NULL;
	}

	// vision it from a flat face of a cube.
	// vector's here are like vector3(x, z, y);
	// x is from back to front, z is from left to right, y is from top to bottom.
	newCube->corner1 = (struct vector){ 0,  10, 5  };	//back top left.
	newCube->corner2 = (struct vector){ 0,  10, 10 };	//back bottom left.
	newCube->corner3 = (struct vector){ 0,  20, 5  };	//back top right.
	newCube->corner4 = (struct vector){ 0,  20, 10 };	//back bottom right.
	newCube->corner5 = (struct vector){ 10, 20, 5  };	//front top right.
	newCube->corner6 = (struct vector){ 10, 20, 10 };	//front bottom right.
	newCube->corner7 = (struct vector){ 10, 10, 5  };	//front top left.
	newCube->corner8 = (struct vector){ 10, 10, 10 };	//front bottom left.

	return newCube;
}

vector* getMatchingCorner(cube* Cube, int x, int y) {
	
	//this is bad! it will just check in one order!
	vector* closestVector = NULL; // max vector distance.

	if (round(Cube->corner1.z) == x && round(Cube->corner1.y) == y && (!closestVector || Cube->corner1.x > closestVector->x)) closestVector = &Cube->corner1;
	if (round(Cube->corner2.z) == x && round(Cube->corner2.y) == y && (!closestVector || Cube->corner2.x > closestVector->x)) closestVector = &Cube->corner2;
	if (round(Cube->corner3.z) == x && round(Cube->corner3.y) == y && (!closestVector || Cube->corner3.x > closestVector->x)) closestVector = &Cube->corner3;
	if (round(Cube->corner4.z) == x && round(Cube->corner4.y) == y && (!closestVector || Cube->corner4.x > closestVector->x)) closestVector = &Cube->corner4;
	if (round(Cube->corner5.z) == x && round(Cube->corner5.y) == y && (!closestVector || Cube->corner5.x > closestVector->x)) closestVector = &Cube->corner5;
	if (round(Cube->corner6.z) == x && round(Cube->corner6.y) == y && (!closestVector || Cube->corner6.x > closestVector->x)) closestVector = &Cube->corner6;
	if (round(Cube->corner7.z) == x && round(Cube->corner7.y) == y && (!closestVector || Cube->corner7.x > closestVector->x)) closestVector = &Cube->corner7;
	if (round(Cube->corner8.z) == x && round(Cube->corner8.y) == y && (!closestVector || Cube->corner8.x > closestVector->x)) closestVector = &Cube->corner8;

	// Return a default vector if no match is found.
	return closestVector;
	//return (vector) { -1, -1, -1 };
}

int isCornerMatch(cube* Cube, int x, int y) {
	// Check if any corner of the cube matches the current x and y.
	if ((Cube->corner1.x == x && Cube->corner1.y == y) ||
		(Cube->corner2.x == x && Cube->corner2.y == y) ||
		(Cube->corner3.x == x && Cube->corner3.y == y) ||
		(Cube->corner4.x == x && Cube->corner4.y == y) ||
		(Cube->corner5.x == x && Cube->corner5.y == y) ||
		(Cube->corner6.x == x && Cube->corner6.y == y) ||
		(Cube->corner7.x == x && Cube->corner7.y == y) ||
		(Cube->corner8.x == x && Cube->corner8.y == y)) {
		return 1;
	}
	return 0;
}

RGB* distanceToRGB(int distance) {
	int maxXAxisDistance = 13;
	RGB* newRGB = (RGB*)malloc(sizeof(RGB));

	newRGB->r = ((255 / maxXAxisDistance) * distance);
	newRGB->g = ((255 / maxXAxisDistance) * distance);
	newRGB->b = ((255 / maxXAxisDistance) * distance);

	return newRGB;
}

void drawFrame(cube* Cube) {

	// dont get confused from the cubes X, Z, Y here! they are not the same! this is from a flat view.
	system("cls");
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 40; x++) {
			vector* matchingVector = getMatchingCorner(Cube, x, y);
			if (matchingVector != NULL) {
				RGB* newRGB = distanceToRGB(matchingVector->x);
				//printf("x: %d, z: %d y: %d", matchingVector->x, matchingVector->z, matchingVector->y);
				printf("\x1b[38;2;%d;%d;%dmC\x1b[0m", newRGB->r, newRGB->g, newRGB->b);
				free(newRGB);
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}

}

rotateVector(struct vector* vector, double thetaX, double thetaZ, double thetaY) {
	// rotates like a microwave (you know).
	double x, z, y;
	double cosX = cos(thetaX), sinX = sin(thetaX);
	double cosY = cos(thetaY), sinY = sin(thetaY);
	double cosZ = cos(thetaZ), sinZ = sin(thetaZ);

	// im not even gona pretend i know how this shit works.

	// rotates on X axis
	y = vector->y * cosX - vector->z * sinX;
	z = vector->y * sinX + vector->z * cosX;
	vector->y = y;
	vector->z = z;

	// rotate Y axis
	x = vector->x * cosY + vector->z * sinY;
	z = -vector->x * sinY + vector->z * cosY;
	vector->x = x;
	vector->z = z;

	// roatate Z axis
	x = vector->x * cosZ - vector->y * sinZ;
	y = vector->x * sinZ + vector->y * cosZ;
	vector->x = x;
	vector->y = y;
}

vector calculateCenter(cube* Cube) {
	return (struct vector) {
		(Cube->corner1.x + Cube->corner6.x) / 2,
		(Cube->corner1.z + Cube->corner6.z) / 2,
		(Cube->corner1.y + Cube->corner6.y) / 2
	};
}

void translateVector(struct vector* vector, struct vector* translate) {
	vector->x += translate->x;
	vector->z += translate->z;
	vector->y += translate->y;
}

rotateCube(cube* Cube, double thetaX, double thetaZ, double thetaY) {
	struct vector center = calculateCenter(Cube);
	struct vector negativeCenter = {-center.x, -center.z, -center.y}; // we need this for temporarly movine cube center to 0 0 0 for the rotation calculation.

	//these are ugly but hey, they get the job done and dont need to be added again for multiple cubes.
	//moving cube to have 0 0 0 to center.
	translateVector(&Cube->corner1, &negativeCenter);
	translateVector(&Cube->corner2, &negativeCenter);
	translateVector(&Cube->corner3, &negativeCenter);
	translateVector(&Cube->corner4, &negativeCenter);
	translateVector(&Cube->corner5, &negativeCenter);
	translateVector(&Cube->corner6, &negativeCenter);
	translateVector(&Cube->corner7, &negativeCenter);
	translateVector(&Cube->corner8, &negativeCenter);

	//rotate around the origin wich is 0 0 0.
	rotateVector(&Cube->corner1, thetaX, thetaY, thetaZ);
	rotateVector(&Cube->corner2, thetaX, thetaY, thetaZ);
	rotateVector(&Cube->corner3, thetaX, thetaY, thetaZ);
	rotateVector(&Cube->corner4, thetaX, thetaY, thetaZ);
	rotateVector(&Cube->corner5, thetaX, thetaY, thetaZ);
	rotateVector(&Cube->corner6, thetaX, thetaY, thetaZ);
	rotateVector(&Cube->corner7, thetaX, thetaY, thetaZ);
	rotateVector(&Cube->corner8, thetaX, thetaY, thetaZ);

	// move cube to the original position.
	translateVector(&Cube->corner1, &center);
	translateVector(&Cube->corner2, &center);
	translateVector(&Cube->corner3, &center);
	translateVector(&Cube->corner4, &center);
	translateVector(&Cube->corner5, &center);
	translateVector(&Cube->corner6, &center);
	translateVector(&Cube->corner7, &center);
	translateVector(&Cube->corner8, &center);
}

int main() {
	cube* Cube = createCube();

	// M_PI = 180 degrees so M_PI / 2 is 90 degrees.
	double thetaX = 0;
	double thetaZ = M_PI / 10;
	double thetaY = 0;

	rotateCube(Cube, 0, 0, 0);
	drawFrame(Cube);

	for (int i = 0; i < 20; i++) {
		Sleep(400L);
		rotateCube(Cube, thetaX, thetaZ, thetaY);
		drawFrame(Cube);
	}

	free(Cube);
	return 0;
}