#pragma once

// SingleTrimController �R�}���h �^�[�Q�b�g

class SingleTrimController : public CObject
{
public:
	SingleTrimController();
	virtual ~SingleTrimController();


	BOOL CheckInTrim(void);
	BOOL CheckOutTrim(void);


};


