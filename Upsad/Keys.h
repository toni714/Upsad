#pragma once

class Keys {
private:
	const int KEY_ID;
	Keys(const int& keyID);
public:
	static const Keys FORWARD;
	static const Keys BACKWARD;
	static const Keys LEFT;
	static const Keys RIGHT;
	static const Keys TURN_LEFT;
	static const Keys TURN_RIGHT;

	bool isPressed() const;
};