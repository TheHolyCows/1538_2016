//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_CONSTANTS_H__
#define __COW_CONSTANTS_H__

#include <unistd.h>
#include <WPILib.h>
#include <fstream>
#include <string>
#include <map>
#include "Declarations.h"
#include "CowLib/CowLib.h"

// Short way to access a constant.  There's probably a better way to do this.
#define CONSTANT CowConstants::GetInstance()->GetValueForKey

using namespace std;

class CowConstants
{	
private:
	// Converting from a std::string to a double is expensive,
	// and almost every constant will be a double, so we cast
	// at load time instead of continuously
	typedef struct
	{
		string value;
		double numeric;
	} st_CowConstant;
	
	map<string, st_CowConstant> m_Data;
	static CowConstants *m_SingletonInstance;
	
	CowLib::CowLexer *m_Lexer;
	
	void GrammarError(const char *expectedTokenDescription, string value, string receivedToken);
	void ParseINI(string data, const char *filename);
	
	CowConstants();
public:
	void RestoreData(const char *filename = COWCONSTANTS_DEFAULT_FILE);

	static CowConstants *GetInstance();
	
	double GetValueForKey(const char *key);
	template <typename T>
	T GetValueForKey(const char *key);
	
	void SetValueForKey(string key, string value);
	
	bool DoesKeyExist(string key);	
};

#endif
