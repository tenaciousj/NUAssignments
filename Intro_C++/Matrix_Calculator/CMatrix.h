//
//  CMatrix.h
//  HW#6
//
//  Created by Jeanette Pranin on 3/6/14.
//  Copyright (c) 2014 Jeanette Pranin. All rights reserved.
//

#ifndef __HW_6__CMatrix__
#define __HW_6__CMatrix__

#include <iostream>

using namespace std;

#define	SIZE_DB 100

enum OP {ASN, ADD, MIN, MUL, DIV, INC, DEC, ADDASN, MINASN, MULASN, DIVASN};
enum OP_TYPE {chk, asn, unary, binary}; // chk just mean check

void PrintVersionInfo();
void PrintPrompt();

////////////////////////////////////////
// functions to check the characters  //
////////////////////////////////////////
bool IsCharALetter(const char& c);
bool IsCharADigit(const char& c);
bool IsCharAOperator(const char& c);

///////////////////////////////////////////////////
//		Class CMatrix                            //
///////////////////////////////////////////////////

class CMatrix
{
	double	*m_pData;
	int		m_nNRow;
	int		m_nNCol;
    
public:
	// default constructor
	CMatrix(int nrow = 1, int ncol = 1); //done
	// copy constructor
	CMatrix(const CMatrix& m); //copy constructor
	// destructor
	~CMatrix(); //done
    
	// getting and setting
	int		NRow() const { return m_nNRow; }; //return number of rows
	int		NCol() const { return m_nNCol; };//return number of columns
	int		Size() const { return m_nNRow*m_nNCol; };//returns size of matrix
    
	// operator overloading
	// assignment
	const CMatrix& operator=(const CMatrix& m);//overload =
	const CMatrix& operator=(const double& k);//overload =
	// compare equal
	bool		   operator==(const CMatrix& m) const; //overload ==
	bool		   operator==(const double& v) const;//overload ==
	// not equal
	bool		   operator!=(const CMatrix &m) const { return !(*this==m); };
	bool		   operator!=(const double& v) const { return !(*this==v); };
	// indexing get CMatrix(i, j)
	double&		   operator()(int, int);
	const double&  operator()(int, int) const;
	// +/-/*
    //operations with other matrices
	CMatrix		operator+(const CMatrix& m);
	CMatrix		operator-(const CMatrix& m);
	CMatrix		operator*(const CMatrix& m); // MATRIX MULTIPLICATION
	CMatrix		operator/(const CMatrix& m);
    
    //operations with scalars
	CMatrix		operator+(const double& t);
	CMatrix		operator-(const double& t);
	CMatrix		operator*(const double& t);
	CMatrix		operator/(const double& t);
    
    //operations with other matrices
	CMatrix&	operator+=(const CMatrix& m);
	CMatrix&	operator-=(const CMatrix& m);
	CMatrix&	operator*=(const CMatrix& m);
	CMatrix&	operator/=(const CMatrix& m);
    
    //operations with scalars
	CMatrix&	operator+=(const double& t);
	CMatrix&	operator-=(const double& t);
	CMatrix&	operator*=(const double& t);
	CMatrix&	operator/=(const double& t);

    
    
	CMatrix&	Neg(); // this is for matrix subtraction, to get the negative value of every element in the matrix //done
    
	// stream I/O
	friend	ostream &operator<<( ostream &, const CMatrix &);//done
    
};

//////////////////////////////////////////////////
//	Class CVariable                             //
//////////////////////////////////////////////////

class CVariable
{
	CMatrix	m_xValue;		// matrix version
	char*	m_sName;
public:
	// constructors and destructor
	CVariable();
	CVariable(const char* name, const CMatrix& m = 0.0);	// matrix version
	~CVariable();
	CVariable(const CVariable& var); // copy constructor
	const CVariable& operator=(const CVariable& var); // overload =
    
	// getting and setting
	// matrix version
	CMatrix&	Value() { return m_xValue; };
	const CMatrix& Value() const { return m_xValue; };
    
	char*	Name() const { return m_sName; };
	void	SetValue(const CMatrix& m) { m_xValue = m; }; // matrix version
	void	SetValue(const double& v) { m_xValue = v; } // matrix version should also include this
	bool	SetName(const char* name);
};



//////////////////////////////////////////////////
//	Class CVarDB                                //
//////////////////////////////////////////////////

class CVarDB
{
	CVariable	m_pDB[SIZE_DB];
	int			m_nSize;		// size of the database
public:
	CVarDB();
	~CVarDB(){};
    
	void		Init();
	CVariable*	Search(const char*name);	// return a valid ptr if found, else a NULL
	CVariable*	CreateANewVar(const char*name); // return a ptr of the new one, else a NULL
    void	    print();
};


/////////////////////////////////////////////////
// Class CALU                                  //
/////////////////////////////////////////////////

enum MATRIX_INPUT {NUM, SEP, END, ERR};

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
	void	_Operation(CMatrix& res, CMatrix& operand_1, CMatrix& operand_2);
	bool	_ConvertAnOperand(const char* operand_name, CMatrix& m);
	bool	_CheckValidMatrixInput(const char* mat_data, int& row, int& col);
    
};

MATRIX_INPUT MatrixPiece(const char *buffer, int &st, char *piece);

///////////////////////////////////////////////////////
// functions related to the command line interpreter //
///////////////////////////////////////////////////////

bool ResolveAStatement(string& state, char* res_name, OP &op, OP_TYPE& type,
                       char* operand_1_name, char* operand_2_name, int& count);

// read a piece from buffer from position pIndex
int ReadAPiece(const string& buffer, int& pIndex, char* piece);

#endif