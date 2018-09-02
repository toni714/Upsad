#pragma once

struct LimitBox {
	float top;
	float bottom;
	float left;
	float right;
	float front;
	float back;
	LimitBox(float top, float bottom, float left, float right, float front, float back)
		:top(top),bottom(bottom),left(left),right(right),front(front),back(back){}
};