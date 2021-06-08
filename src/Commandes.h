#pragma once
#include "Character.h"
class Command {
public:
	virtual ~Command() {}
	virtual void execute(Hero& chara, int speed) = 0;
};
class MoveUpCommand : public Command {
	public:
		MoveUpCommand() {

		};
	virtual void execute(Hero& chara, int speed) { moveUp(chara, speed); }
	void moveUp(Hero& chara, int speed) {
		chara.move(0, -speed);
	};

};

class MoveDownCommand : public Command {
public:
	virtual void execute(Character chara, int speed) { moveDown(chara, speed); }
	void moveDown(Character chara, int speed) {
		chara.move(0,speed);
	};
};

class MoveRightCommand : public Command {
public:
	virtual void execute(Character chara, int speed) { moveRight(chara, speed); }
	void moveRight(Character chara, int speed) {
		chara.move(speed, 0);
	};
};

class MoveLeftCommand : public Command {
public:
	virtual void execute(Character chara) { moveLeft(chara); }
	void moveLeft(Character chara);

};
class AttackCommand : public Command {
public:
	virtual void execute(Character chara) { attack(chara); }
	void attack(Character chara);
};
class PowerUpCommand : public Command {
public:
	virtual void execute(Character chara) { powerup(chara); }
	void powerup(Character chara);
};