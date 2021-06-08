#include "Commandes.h"

class Command {
public:
	virtual ~Command() {}
	virtual void execute(Character& chara) = 0;
};
class MoveUpCommand : public Command {
	virtual void execute(Character chara) { moveup( chara); }
	void moveup(Character chara) {
		
	}
};

class MoveDownCommand : public Command {
	virtual void execute() { movedown(); }
};

class MoveRightCommand : public Command {
	virtual void execute() { moveright(); }
};

class MoveLeftCommand : public Command {
	virtual void execute() { moveleft(); }
};
class AttackCommand : public Command {
	virtual void execute() { attack(); }
};
class PowerUpCommand : public Command {
	virtual void execute() { powerup(); }
};


