#pragma once
#include "GameMode.h"

class StartMode :
	public GameMode
{
public:
	StartMode();
	~StartMode();

	// GameMode을(를) 통해 상속됨
	virtual void Draw() override;

	virtual bool ActionLeft() override;

	virtual bool ActionUp() override;

	virtual bool ActionDown() override;

	virtual bool ActionRight() override;

	virtual bool ActionEnter() override;

	virtual bool ActionEscape() override;

	virtual bool ActionSpace() override;

	virtual bool ActionNum1() override;

	virtual bool ActionNum2() override;

	virtual bool ActionNum3() override;

	virtual bool ActionNum4() override;

	virtual bool ActionNum5() override;


	// GameMode을(를) 통해 상속됨
	virtual void Initialize() override;


	// GameMode을(를) 통해 상속됨
	virtual void DrawObjectDescription() override;


	// GameMode을(를) 통해 상속됨
	virtual void DrawFieldMap() override;

};

