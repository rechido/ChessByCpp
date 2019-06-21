#pragma once
#include "eModeType.h"

class ModeType
{
public:
	ModeType();
	~ModeType();

	void SetStartMode();
	void SetEditorMode();
	void SetPlayMode();
	void SetExitMode();

	eModeType GetGameMode();

private:
	eModeType mMode;
};

