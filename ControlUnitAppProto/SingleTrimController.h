#pragma once

// SingleTrimController コマンド ターゲット

class SingleTrimController : public CObject
{
public:
	SingleTrimController();
	virtual ~SingleTrimController();


	BOOL CheckInTrim(void);
	BOOL CheckOutTrim(void);


};


