#pragma once
#include "Character.h"
class Command {
public:
	virtual ~Command() {}
	virtual void execute(Character& chara, int speed) = 0;
};
class MoveUpCommand : public Command {
	public:
		MoveUpCommand() {

		};
	virtual void execute(Character& chara, int speed) { moveUp(chara, speed); }
	void moveUp(Character& chara, int speed) {
		chara.move(0, -speed);
	};

};

class MoveDownCommand : public Command {
public:
	MoveDownCommand() {};
	virtual void execute(Character& chara, int speed) { moveDown(chara, speed); }
	void moveDown(Character& chara, int speed) {
		chara.move(0,speed);
	};
};

class MoveRightCommand : public Command {
public:
	MoveRightCommand() {};
	virtual void execute(Character& chara, int speed) { moveRight(chara, speed); }
	void moveRight(Character& chara, int speed) {
		chara.move(speed, 0);
	};
};

class MoveLeftCommand : public Command {
public:
	MoveLeftCommand() {};
	virtual void execute(Character& chara, int speed) { moveLeft(chara, speed); }
	void moveLeft(Character& chara, int speed) {
		chara.move(-speed, 0);
	};

};
class AttackCommand : public Command {
public:
	AttackCommand() {};
	virtual void execute(Character& chara, int speed) { attack(chara); }
	void attack(Character& chara) {};
};
class PowerUpCommand : public Command {
public:
	PowerUpCommand() {};
	virtual void execute(Character& chara, int speed) { powerup(chara); }
	void powerup(Character& chara) {};
};