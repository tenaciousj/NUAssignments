//
//  CVar.h
//  HW#5
//
//  Created by Jeanette Pranin on 2/20/14.
//  Copyright (c) 2014 Jeanette Pranin. All rights reserved.
//

//
//  Calculator.h
//  MP5
//
//  Copyright (c) 2014 Jeanette Pranin. All rights reserved.
//

#ifndef __HW_5__CVar__
#define __HW_5__CVar__

#include <iostream>
#include <string.h>


#define	SIZE_DB 100

using namespace std;

enum OP {ASN, ADD, MIN, MUL, DIV, INC, DEC};
enum OP_TYPE {asn, unary, binary};

void PrintVersionInfo(); //prints header

///////////////////////////////////////////////////////
// functions related to the command line interpreter //
///////////////////////////////////////////////////////

bool ResolveAStatement(const char* state, char* res_name, OP &op, OP_TYPE& type, char* operand_1_name, char* operand_2_name, int& count); // segment the command line into the five variables
void TranslateOP(const OP op); // explain operator
void UnderstandAStatement(char* res_name, const OP &op, const OP_TYPE& type,  // explain command line using the pre-defined pattern
                          char* operand_1_name, char* operand_2_name);

////////////////////////////////////////
// functions from previous project  //
////////////////////////////////////////
int ReadAPiece(const char* buffer, int& pIndex, char* piece);// read a piece from buffer from position pIndex

bool IsCharALetter(const char& c);
bool IsCharADigit(const char& c);
bool IsCharAOperator(const char& c);


//////////////////////////////////////////////////
//	Class CVariable                             //
//////////////////////////////////////////////////

char* str_dup_new(const char* data); //helper function that copies the content in const char* data to temporary variable

class CVariable
{
private:
	double	m_dValue;
	char*	m_sName;
public:
	// constructors and destructors
	CVariable();
	CVariable(const char*name, const double& v = 0.0);
	~CVariable();
	CVariable(const CVariable& var); // copy constructor
	const CVariable& operator=(const CVariable& var); // overload =
    
	// getting and setting
	double&	Value() { return m_dValue; };   // reference return creates a lvalue
	const double&	Value() const { return m_dValue; }; // const ref reture creates a rvalue
	char*	Name() const { return m_sName; }; //returns the name of the CVariable
	void	SetValue(const double& v) { m_dValue = v; }; //sets the value of the CVariable to the value of input v
	bool	SetName(const char* name); //sets the name of the CVariable to the name of input name
private:
    void _copy(const CVariable &s) {m_sName = str_dup_new(s.Name());}; //copies the name of input CVariable to into "this" CVariable
    void _destroy() {delete [] m_sName;}; //destroys the allocated memory
};



//////////////////////////////////////////////////
//	Class CVarDB                                //
//////////////////////////////////////////////////

class CVarDB
{
private:
	CVariable	m_pDB[SIZE_DB]; //array that holds database
	int			m_nSize;		// size of the database
public:
    //constructors and destructors
	CVarDB();
	~CVarDB(){};
    
	void		Init(); //makes a CVariable with name "ans" and value 0
	CVariable*	Search(const char*name);	// return a valid ptr if found, else a NULL
	CVariable*	CreateANewVar(const char*name, double v); // return a ptr of the new one, else a NULL
    void	Dump(); //prints out everyone in the database
};



/////////////////////////////////////////////////
// Class CALU                                  //
/////////////////////////////////////////////////

class CALU
{
	OP			m_OP;
	OP_TYPE		m_Type;
	CVarDB*		m_pVarDB;
    
	bool		m_bIsVarDBSet;
    
public:
	CALU() : m_bIsVarDBSet(false) {};
	~CALU(){};
    
	//setting ALU
	void	SetOP(const OP& op) { m_OP = op; };
	void	SetOPType(const OP_TYPE& type) { m_Type = type;};
	void	SetVarDB(CVarDB*	db) { m_pVarDB = db; m_bIsVarDBSet = true; };
    
	bool	Perform(const char* res_name, const char* operand_1_name, const char* operand_2_name);
    
private:
	// numerical operation
	void	_Operation(double& res, double& operand_1, const double& operand_2); //input two double variables, do the calculation and assign the result to 'res'
	bool	_ConvertAnOperand(const char* operand_name, double& value); //Convert a symbolic operand to a numerical one
};

#endif /* defined(__HW_5__CVar__) */


