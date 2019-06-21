#pragma once
#include "GameMode.h"

class EditorMode :
	public GameMode
{
public:
	EditorMode();
	virtual ~EditorMode();

	

	// GameMode��(��) ���� ��ӵ�
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

	// GameMode��(��) ���� ��ӵ�
	virtual void Initialize() override;

private:
	void ResetFieldMap();

	eObjectType mPutObjectType;
	unsigned int mCursorX;
	unsigned int mCursorY;

	// GameMode��(��) ���� ��ӵ�
	virtual void DrawObjectDescription() override;

	// GameMode��(��) ���� ��ӵ�
	virtual void DrawFieldMap() override;
};

