#pragma once
class Camera
{
	float x, y, z;
	float xRot, zRot;

public:
	Camera();
	void Apply();
	void Rotate(float xAngle, float zAngle);
	void Move(int x1, int y1, float speeed);
	void MoveDirection(int forwardMove, int rightMove, float speed);
};