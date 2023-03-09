#define _USE_MATH_DEFINES
#include "Camera.h"
#include <windows.h>
#include <math.h>
#include <gl/GL.h>
#include <stdio.h>



Camera::Camera() {
	x = 100;
	y = 50;
	z = 0;
	xRot = 0;
	zRot = 0;
}

void Camera::Apply() {
	glRotatef(-xRot, 1, 0, 0);
	glRotatef(-zRot, 0, 1, 0);
	glTranslatef(-x, -y, -z);
}

void Camera::Rotate(float xAngle, float zAngle) {
	zRot += zAngle;
	if (zRot < 0) zRot += 360;
	if (zRot > 360) zRot -= 360;

	xRot += xAngle;
	if (xRot < -180) xRot = -180;
	if (xRot > 180) xRot = 180;
}

void Camera::Move(int x1, int y1, float speed) {
	POINT cur;
	POINT base{ x1, y1 };
	GetCursorPos(&cur);

	Camera::Rotate((base.y - cur.y) * speed, (base.x - cur.x) * speed);
	SetCursorPos(base.x, base.y);

	if (GetKeyState(VK_CONTROL) < 0) y -= 0.5;  // 0.03 | 0.5
	if (GetKeyState(VK_SPACE) < 0) y += 0.5;

}


void Camera::MoveDirection(int forwardMove, int rightMove, float speed) {

	float angle = -zRot / 180 * M_PI;

	speed = 0.5;
	if (forwardMove > 0)
		angle += rightMove > 0 ? M_PI_4 : (rightMove < 0 ? -M_PI_4 : 0);
	if (forwardMove < 0)
		angle += M_PI + (rightMove > 0 ? -M_PI_4 : (rightMove < 0 ? M_PI_4 : 0));

	if (forwardMove == 0) {
		angle += rightMove > 0 ? M_PI_2 : -M_PI_2;
		if (rightMove == 0) speed = 0;
	}

	if (speed != 0) {
		x += sin(angle) * speed;
		z -= cos(angle) * speed;
	}
}


