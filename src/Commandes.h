#pragma once
#include "Character.h"
#include <iostream>
class Command {
public:
	virtual ~Command() {}
	virtual void execute(Character& chara, double speed) = 0;
};
class MoveUpCommand : public Command {
	public:
		MoveUpCommand() {

		};
	virtual void execute(Character& chara, double speed) { moveUp(chara, speed); }
	void moveUp(Character& chara, double speed) {
		chara.move(0, -speed);
	};

};

class MoveDownCommand : public Command {
public:
	MoveDownCommand() {};
	virtual void execute(Character& chara, double speed) { moveDown(chara, speed); }
	void moveDown(Character& chara, double speed) {
		chara.move(0,speed);
	};
};

class MoveRightCommand : public Command {
public:
	MoveRightCommand() {};
	virtual void execute(Character& chara, double speed) { moveRight(chara, speed); }
	void moveRight(Character& chara, double speed) {
		chara.move(speed, 0);
	};
};

class MoveLeftCommand : public Command {
public:
	MoveLeftCommand() {};
	virtual void execute(Character& chara, double speed) { moveLeft(chara, speed); }
	void moveLeft(Character& chara, double speed) {
		chara.move(-speed, 0);
	};

};
class AttackCommand : public Command {
public:
	AttackCommand() {};
	virtual void execute(Character& chara, double speed) { attack(chara); }
	void attack(Character& chara) {

		chara.attack();
		
	};
};
class PowerUpCommand : public Command {
public:
	PowerUpCommand() {};
	virtual void execute(Character& chara, double speed) { powerup(chara); }
	void powerup(Character& chara) {};
};