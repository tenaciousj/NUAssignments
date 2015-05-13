//
//  CMatrix.cpp
//  HW#6
//
//  Created by Jeanette Pranin on 3/6/14.
//  Copyright (c) 2014 Jeanette Pranin. All rights reserved.
//

#include "CMatrix.h"

#include <assert.h>
#include <iostream>
#include <iomanip>

using namespace std;


/////////////////////////////////////////////////////////
// Implementation of Class CMatrix                     //
/////////////////////////////////////////////////////////

//copy constructor
CMatrix:: CMatrix(const CMatrix &m)
{
    if (m.Size() <= 0) //makes the matrix null if nRow or nCol is not valid, i.e. <=0
    {
        m_nNRow = m_nNCol = 0;
        m_pData = 0;
    }
    else
    {
        m_nNRow = m.NRow();
        m_nNCol = m.NCol();
        m_pData = new double[m_nNRow*m_nNCol]; //allocate memory based on size of CMatrix m
        for (int i = 0; i < m_nNRow*m_nNCol; i++)
            m_pData[i] = m.m_pData[i]; //copy contents of CMatrix m to this CMatrix
    }
}

CMatrix::CMatrix(int nrow, int ncol)
: m_nNRow(nrow), m_nNCol(ncol), m_pData(new double[nrow*ncol])
{
	for (int i = 0; i < m_nNRow*m_nNCol; ++i)
			m_pData[i] = 0; //make nrow by ncol matrix will value 0
}

//destructor
CMatrix::~CMatrix()
{
    delete [] m_pData;
}

const CMatrix& CMatrix :: operator=(const CMatrix& var)
{
    int size = m_nNRow*m_nNCol;
    //make sure you are not destroying yourself
    if(&var != this){
        if(m_nNRow != var.m_nNRow || m_nNCol != var.m_nNCol){
            delete [] m_pData;
            m_nNRow = var.m_nNRow;
            m_nNCol = var.m_nNCol;
            size = m_nNRow*m_nNCol;
            m_pData = new double[size]; //allocate new memory based on var's size
            assert(m_pData);//make sure m_pData has its own location in memory
        }
        for (int i = 0; i < size; i++)
            m_pData[i] = var.m_pData[i]; //copy contents of var to this
    }
    return *this;
}

//= overload
const CMatrix& CMatrix::operator=(const double& k)
{
    delete [] m_pData;
    m_pData = new double[1]; //allocate memory to create 1 by 1 matrix with value k
    assert(m_pData);
    m_pData[0] = k;
    return *this;
}

//== overload
//returns true if the given CMatrix is the same size and contains all of the same values as this matrix (false otherwise)
bool CMatrix::operator==(const CMatrix& m) const
{
    if((m_pData == m.m_pData) && m_nNRow == m.NRow() && m_nNCol == m.NCol())
        return true;
    return false;
}

//== overload
//returns true if the given double variable is the same size and contains the same value as this matrix (false otherwise)
bool CMatrix::operator==(const double& v) const
{
    if(this == NULL){
        if(v==0)
            return true;
    }
    else if(Size() == 1){
        if(m_pData[0] == v)
            return true;
    }
    return false;
}

//() overload
//returns the value in the indicated row and column
double&	CMatrix::operator()(int i, int j)
{
    assert((i >= 0) && (i < m_nNRow));
	assert((j >= 0) && (j < m_nNCol));
    return m_pData[i*m_nNCol + j];
}

//() overload
//returns the value in the indicated row and column, takes const input values
const double& CMatrix::operator()(int i, int j) const
{
    assert((i >= 0) && (i < m_nNRow));
	assert((j >= 0) && (j < m_nNCol));
    return m_pData[i*m_nNCol + j];
}

//+ overload
//returns the result of adding two matrices; result is a null matrix if input matrices are not the same size
CMatrix CMatrix:: operator+(const CMatrix& m)
{
    if(m_nNRow == m.NRow() && m_nNCol == m.NCol()){
        for(int i = 0; i < m_nNRow; i++){
            for(int j = 0; j < m_nNCol; j++)
                m_pData[i*m_nNCol + j] += m(i, j);
        }
    }
    //if "matrix" is 1 by 1 matrix with a number, treat it like a scalar
    else if(m.Size() == 1){
        for(int i = 0; i < Size(); i++)
            m_pData[i] += m(0, 0);
    }
    else
        return NULL;
    return (*this);
}

//- overload
//returns the result of subtracting one matrix from another; result is a null matrix if input matrices are not the same size
CMatrix	CMatrix::operator-(const CMatrix& m)
{
    if(m_nNRow == m.NRow() && m_nNCol == m.NCol())
    {
        for(int i = 0; i < m_nNRow; i++){
            for(int j = 0; j < m_nNCol; j++)
                m_pData[i*m_nNCol + j] -= m(i, j);
        }
    }
    //if "matrix" is 1 by 1 matrix with a number, treat it like a scalar
    else if(m.Size() == 1){
        for(int i = 0; i < Size(); i++)
            m_pData[i] -= m(0, 0);
    }
    else
        return NULL;
    return (*this);
}

//*overload
//MATRIX MULTIPLICATION
CMatrix	CMatrix::operator*(const CMatrix& m)
{
    if(m_nNCol == m.NRow()) //matrix multiplication only works when the number of cols in first matrix = the number of rows in second matrix
    {
        double* temp = new double[m_nNRow*m.NCol()];
        for(int i = 0; i < m_nNRow; i++){
            for(int j = 0; j < m.NCol(); j++){
                temp[i*m_nNCol + j] = 0;
                for(int k = 0; k < m_nNCol; k++)
                    temp[i*m_nNCol + j] += m_pData[i*m.NCol() + k] * m(k, j);
            }
        }
        delete [] m_pData;
        m_pData = new double[m_nNRow*m.NCol()];
        for(int pos = 0; pos < Size(); pos++)
            m_pData[pos] = temp[pos];
        delete [] temp;
    }
    else if(m.Size() == 1)
    {
        //if "matrix" is 1 by 1 matrix with a number, treat it like a scalar
        for(int i = 0; i < Size(); i++)
            m_pData[i] *= m(0, 0);
    }
    else{
        return NULL;
    }
    return (*this);
}

// / overload
//returns the result of dividing this matrix by corresponding element of another matrix
CMatrix	CMatrix::operator/(const CMatrix& m)
{
    if(m(0,0) == 0)
        return NULL;
    if(m_nNRow == m.NRow() && m_nNCol == m.NCol())
    {
        for(int i = 0; i < m_nNRow; i++){
            for(int j = 0; j < m_nNCol; j++){
                if(m(i, j) != 0)
                    m_pData[i*m_nNCol + j] /= m(i, j);
                else{
                    cout << "Div. by 0!!" << endl;
                    return NULL;
                }
            }
        }
    }
    //if "matrix" is 1 by 1 matrix with a number, treat it like a scalar
    else if(m.Size() == 1)
    {
        if(m(0,0) == 0)
            return NULL;
        for(int i = 0; i < Size(); i++)
            m_pData[i] += m(0, 0);
    }
    else
        return NULL;
    return (*this);
}

//returns the result of adding one scalar number to each element in the matrix
CMatrix	CMatrix::operator+(const double& t)
{
    for(int i = 0; i < Size(); i++)
        m_pData[i]+= t;
    return (*this);
}

//returns the result of subtracting one scalar number to each element in the matrix
CMatrix	CMatrix::operator-(const double& t)
{
    for(int i = 0; i < Size(); i++)
        m_pData[i]-= t;
    return (*this);
}

//returns the result of multiplying one scalar number to each element in the matrix
CMatrix	CMatrix::operator*(const double& t)
{
    for(int i = 0; i < Size(); i++)
        m_pData[i]*= t;
    return (*this);
}

//returns the result of dividing each element in the matrix by a scalar
CMatrix	CMatrix::operator/(const double& t)
{
    if (t==0){
        cout << "Div. by 0!!" << endl;
        return NULL;
    }
    for(int i = 0; i < Size(); i++)
        m_pData[i]/= t;
    return (*this);
}

//returns the result of adding two matrices; result is a null matrix if input matrices are not the same size
CMatrix& CMatrix::operator+=(const CMatrix& m)
{
    CMatrix *null = NULL;
    if(m_nNRow == m.NRow() && m_nNCol == m.NCol()){
        for(int i = 0; i < m_nNRow; i++){
            for(int j = 0; j < m_nNCol; j++)
                m_pData[i*m_nNCol + j] += m(i, j);
        }
    }
    //treat it like a scalar
    else if(m.Size() == 1)
    {
        for(int i = 0; i < Size(); i++)
            m_pData[i] += m(0, 0);
    }
    else
        return *null;
    return (*this);
}

//returns the result of subtracting one matrix from another; result is a null matrix if input matrices are not the same size
CMatrix& CMatrix::operator-=(const CMatrix& m)
{
    CMatrix *null = NULL;
    if(m_nNRow == m.NRow() && m_nNCol == m.NCol())
    {
        for(int i = 0; i < m_nNRow; i++){
            for(int j = 0; j < m_nNCol; j++)
                m_pData[i*m_nNCol + j] -= m(i, j);
        }
    }
    //treat it like a scalar
    else if(m.Size() == 1)
    {
        for(int i = 0; i < Size(); i++)
            m_pData[i] -= m(0, 0);
    }
    else
        return *null;
    return (*this);
    
}

//return the result of matrix multiplication
CMatrix& CMatrix::operator*=(const CMatrix& m)
{
    CMatrix *null = NULL;
    if(m_nNCol == m.NRow())
    {
        double* temp = new double[m_nNRow*m.NCol()];
        for(int i = 0; i < m_nNRow; i++){
            for(int j = 0; j < m.NCol(); j++)
            {
                temp[i*m_nNCol + j] = 0;
                for(int k = 0; k < m_nNCol; k++)
                    temp[i*m_nNCol + j] += m_pData[i*m.NCol() + k] * m(k, j);
            }
        }
        delete [] m_pData;
        m_pData = new double[m_nNRow*m.NCol()];
        for(int pos = 0; pos < Size(); pos++)
            m_pData[pos] = temp[pos];
        delete [] temp;
    }
    //treat it like a scalar
    else if(m.Size() == 1)
    {
        for(int i = 0; i < Size(); i++)
            m_pData[i] *= m(0, 0);
    }
    else
        return *null;
    return (*this);
}

//returns the result of dividing this matrix by corresponding element of another matrix
CMatrix& CMatrix::operator/=(const CMatrix& m)
{
    CMatrix *null = NULL;
    if(m_nNRow == m.NRow() && m_nNCol == m.NCol())
    {
        for(int i = 0; i < m_nNRow; i++){
            for(int j = 0; j < m_nNCol; j++)
            {
                if(m(i, j) != 0)
                    m_pData[i*m_nNCol + j] /= m(i, j);
                else{
                    cout << "Div. by 0!!" << endl;
                    return *null;
                }
            }
        }
    }
    //treat it as a scalar
    else if(m.Size() == 1)
    {
        if(m(0,0)==0)
            return *null;
        for(int i = 0; i < Size(); i++)
            m_pData[i] /= m(0, 0);
    }
    else
        return *null;
    return (*this);
}

//returns the result of adding one scalar number to each element in the matrix
CMatrix& CMatrix::operator+=(const double& t)
{
    for(int i = 0; i < Size(); i++)
        m_pData[i] += t;
    return (*this);
}

//returns the result of subtracting one scalar number to each element in the matrix
CMatrix& CMatrix::operator-=(const double& t)
{
    for(int i = 0; i < Size(); i++)
        m_pData[i] -= t;
    return (*this);
}

//returns the result of multiplying one scalar number to each element in the matrix
CMatrix& CMatrix::operator*=(const double& t)
{
    for(int i = 0; i < Size(); i++)
        m_pData[i] *= t;
    return (*this);
}

//returns the result of dividing one scalar number to each element in the matrix
CMatrix& CMatrix::operator/=(const double& t)
{
    CMatrix *null = NULL;
    if(t==0)
        return *null;
    for(int i = 0; i < Size(); i++)
            m_pData[i] /= t;
    return (*this);
}

//makes every element in the matrix negative
CMatrix& CMatrix:: Neg()
{
    for(int i = 0; i < m_nNRow; i++){
        for(int j = 0; j < m_nNCol; j++){
            if(m_pData[i*m_nNCol + j] > 0)
                m_pData[i*m_nNCol + j] *= -1;
        }
    }
    return (*this);
}

// << overload
//makes << compatible to print out matrix
ostream &operator<<(ostream & out, const CMatrix &c)
{
    //if the matrix is invalid
    if (c.Size() == 0)
		out << "\tnull matrix" <<endl;
	else{
		// row by row
		for (int i = 0; i < c.NRow(); ++i){
			out << "\t";
			for (int j = 0; j < c.NCol(); ++j)
				out << c.m_pData[i*c.NCol() + j] << "\t";
			out << endl;
		}
	}
    return out;
}


/////////////////////////////////////////////////////////
// Implementation of Class CVariable                   //
/////////////////////////////////////////////////////////

//constructor
CVariable::CVariable() :
m_xValue(0.0),
m_sName(NULL)
{
	// empty
}

//constructs a new CVariable with a name "name" and value "v"
CVariable::CVariable(const char* name, const CMatrix& v)
{
	m_xValue = v;
	m_sName = new char[strlen(name)+1];
	strcpy(m_sName, name);
}

//copy constructor
CVariable::CVariable(const CVariable& var)
{
	m_xValue = var.m_xValue;
	m_sName = new char[strlen(var.m_sName)+1];
	strcpy(m_sName, var.m_sName);
}

//operator overload
//assigns the content of CVariable being passed in into 'this' object
const CVariable& CVariable::operator=(const CVariable& var)
{
	if(&var != this){ // check for self-assignment
		m_xValue = var.m_xValue;
		SetName(var.m_sName);
	}
	return *this;
}

//destructor
CVariable::~CVariable()
{
	if(m_sName!=NULL){
		delete [] m_sName;
	}
}

//sets name of CVariable
bool CVariable::SetName(const char* name)
{
	bool	code = true;
	if(m_sName!=NULL)	delete [] m_sName;
	m_sName = new char [strlen(name) + 1];
	if(m_sName){
		strcpy(m_sName, name);
	}
	else
		code = false;
    
	return code;
}

//////////////////////////////////////////////////
//  Implementation of Class CVarDB              //
//////////////////////////////////////////////////

//CVariable database constructor
CVarDB::CVarDB()
{
	Init();
}

//initialize first element of database to be "ans" with value 0
void
CVarDB::Init()
{
    CMatrix temp(1,1);
	m_nSize = 1;
	m_pDB[0].SetName("ans");
    
    m_pDB[0].SetValue(temp);
}

// NOTE: return a ptr of the variable if found
//searches for a CVariable, returns it if found, otherwise return NULL
CVariable* CVarDB::Search(const char* name)
{
	CVariable *pVar = NULL;
	for(int i=0; i<m_nSize; i++){
		if(!strcmp(m_pDB[i].Name(), name)){
			pVar = &(m_pDB[i]);
			break;
		}
	}
	return pVar;
}

//create a new CVariable to put into database
CVariable*
CVarDB::CreateANewVar(const char*name)
{
	CVariable *pVar = NULL;
	if(m_nSize < SIZE_DB){
		m_nSize ++;
		m_pDB[m_nSize-1].SetName(name);
		m_pDB[m_nSize-1].SetValue(0.0);
		pVar = &(m_pDB[m_nSize-1]);
	}
	return pVar;
}

//prints out everyone in the database
void
CVarDB::print()
{
	cout.setf(ios::left, ios::adjustfield);
    cout<<"\n----------------VarDB Starts---------------------\n"<<endl;
	for(int i=0; i<m_nSize; i++){
        cout << "  " << m_pDB[i].Name() << m_pDB[i].Value() << endl;
	}
    cout<<"\n----------------VarDB Ends-----------------------\n"<<endl;
}


////////////////////////////////////////////////////////
//// Implementataion of Class CALU                    //
////////////////////////////////////////////////////////

//input two CMatrices, do the calculation and assign the result to 'res'
void
CALU::_Operation(CMatrix& res, CMatrix& operand_1, CMatrix& operand_2)
{
	switch(m_OP){
        case ASN:
            res = operand_1;
            break;
        case ADD:
            res = operand_1 + operand_2;
            break;
        case MIN:
            res = operand_1 - operand_2;
            break;
        case MUL:
            res = operand_1 * operand_2;
            break;
        case DIV:
            if(operand_2 != 0.0)	res = operand_1/operand_2;
            else	cout << "Div. by 0!!" << endl;
            break;
        case INC:
            res = operand_1 + 1;
            break;
        case DEC:
            res = operand_1 - 1;
            break;
        case ADDASN:
            res = operand_1 + operand_2;
            break;
        case MINASN:
            res = operand_1 - operand_2;
            break;
        case MULASN:
            res = operand_1 * operand_2;
            break;
        case DIVASN:
            res = operand_1 / operand_2;
            break;
        default:
            break;
	}
    
}

// Convert a symbolic operand to a numercial one
bool
CALU::_ConvertAnOperand(const char* operand_name, CMatrix& value)
{
	bool err_code = true;
	CVariable *p = NULL;
	if(IsCharADigit(operand_name[0]))
		value = atof(operand_name);
    else if(operand_name[0] == '[')
    {
        int nrow, ncol;
        if(_CheckValidMatrixInput(operand_name, nrow, ncol)){
            CMatrix tmp(nrow, ncol);
            char piece[50];
            int index =1;
            for(int i=0;i<nrow;i++){
                for(int j=0; j<ncol;j++){
                    ReadAPiece(operand_name, index, piece);
                    tmp(i, j) = atof(piece);
                }
                index+=2;
            }
            value = tmp;
        }
        else{
            cout << operand_name << " is an invalid matrix!\n" << endl;
            err_code = false;
        }
    }
	else{
		// search the variable DB
		p = m_pVarDB->Search(operand_name);
		if(p!=NULL){ // if found in system var DB
			value = p->Value();
		}
		else {
			err_code = false;	// if not found, return false
			cout << " ?? " << operand_name << " doesn't exist!" << endl;
		}
	}
	return err_code;
}

//splits matrix into segments to check if valid matrix
MATRIX_INPUT MatrixPiece(const char *buffer, int &st, char *piece)
{
	while (buffer[st] == ' ')
		st++;
    
	if (((buffer[st] <= '9') && (buffer[st] >= '0')) || (buffer[st] == '.'))
	{
		int ed = st;
		while (((buffer[ed] <= '9') && (buffer[ed] >= '0')) || (buffer[ed] == '.'))
		{
			piece[ed-st] = buffer[ed];
			ed++;
		}
		piece[ed-st] = 0;
		st = ed;
		return NUM;
	}
	else if (buffer[st] == ']')
	{
		++st;
		return END;
	}
	else if (buffer[st] == ';')
	{
		++st;
		return SEP;
	}
	else
		return ERR;
}

//validates matrix, returns true if valid matrix, false if not
bool
CALU::_CheckValidMatrixInput(const char* mat_data, int& row, int& col)
{
    row = 0;
	col = 0;
    
	// should start with a '['
	if (mat_data[0] != '[')
		return false;
    
	char piece[100];
	int column = 0, st = 1;
	for (;;)
        switch (MatrixPiece(mat_data, st, piece))
	{
		case SEP: // new row
			if ((row != 0) && (column != col))
				return false;
			col = column;
			++row;
			column = 0;
			break;
		case NUM: // new number
			++column;
			break;
		case END:
			if ((row != 0) && (column != col))
				return false;
			col = column;
			++row;
			return true;
		case ERR:
			return false;
		default:
			return false;
	}
	return false;
}

//performs calculation on given operand inputs
bool
CALU::Perform(const char* res_name, const char* operand_1_name, const char* operand_2_name)
{
	bool err_code = true;
	CMatrix res, operand_1, operand_2;
	
	// setting the input to ALU
	switch(m_Type){
        case asn:
        case unary:
            if(!_ConvertAnOperand(operand_1_name, operand_1)){
                err_code = false;
            }
            break;
        case binary:
            if(!_ConvertAnOperand(operand_1_name, operand_1)){
                err_code = false;
            }
            else if(!_ConvertAnOperand(operand_2_name, operand_2)){
                err_code = false;
            }
            break;
        default:
            break;
	}
    
	CVariable	*pRes = NULL;
	if(err_code){
		// check the res_name to see if it is in DB
		// otherwise, create a new variable in DB
		if(IsCharALetter(res_name[0])){
			pRes = m_pVarDB->Search(res_name);
			if(pRes==NULL){
				pRes = m_pVarDB->CreateANewVar(res_name);
				if(!pRes){
					cout << " !!! System runs of out memory !!!" << endl;
					err_code = false;
				}
			}
		}
		else{
			cout << "  " << res_name << " is not a valid name for a variable!" << endl;
			err_code = false;
		}
        
		if(err_code){
			// doing ALU operation
			_Operation(res,operand_1,operand_2);
			// grabbing the results from ALU
			pRes->SetValue(res);
		}
	}
	return err_code;
}

///////////////////////////////
//////PARTITIONER//////////////
///////////////////////////////




// read a piece from buffer from position pIndex
int ReadAPiece(const string& buffer, int& pIndex, char* piece)
{
	int err_code = 1;
	int st = pIndex;
	
	// ignore all space before the piece
	// after that, st is positioned at the first char which is not a space
	while((buffer[st]==' ' || buffer[st] == '\r') && buffer[st]!=0)	st++;
    
	int ed = st;
	if(buffer[st] == 0){	// at the end
		err_code = 0;
	}
	else{
		if(IsCharALetter(buffer[st])){
			while(IsCharALetter(buffer[ed]) || IsCharADigit(buffer[ed]))
				ed ++;
		}
		else if(IsCharADigit(buffer[st])){
			while(IsCharADigit(buffer[ed]))
				ed ++;
		}
		else if(IsCharAOperator(buffer[st])){
			while(IsCharAOperator(buffer[ed]))
				ed ++;
		}
        else if(buffer[st] == '['){
            ed++;
            while(buffer[ed] != ']'){
                ed++;}
            ed++;
        }
		else{
			err_code = 0;
		}
        
		// reset pIndex
		pIndex = ed;
        
		// let ed points to the last char of the piece
		ed --;
        
		// set piece
		for(int i=st;i<=ed;i++)
			piece[i-st] = buffer[i];
		piece[ed-st+1]= '\0';
	}
    
	return err_code;
}




/////////////////////////////////////////////////////////////////////
// functions to check the characters
bool IsCharALetter(const char& c)
{
	return( (c>='A' && c<='Z') || (c>='a' && c<='z') || (c=='_') );
}

bool IsCharADigit(const char& c)
{
	return( (c>='0' && c<='9') || c=='.');
}

bool IsCharAOperator(const char& c)
{
	return( c=='+' || c=='-' || c=='*' || c=='/' || c=='=');
}


////////////////////////////////////////////////////////////////////////////////
// functions related to the command line interpreter

// We only allow:
// type asn:   e.g., a = b              (iSeg = 3)
// type unary: e.g., a++                (iSeg = 2)
// type binary:e.g., a + b or c = a+b   (iSeg = 3 or 5)

bool ResolveAStatement(string& state, char* res_name, OP &op, OP_TYPE& type,
                       char* operand_1_name, char* operand_2_name, int& count)
{
	bool err_code = true;
    
	// first step: scanning determine the # of pieces
	// we only allow 2/3/5
	count = 0;
	int pIndex = 0;
	char	piece[5][50];
	bool	pisop[5] = {false,false,false,false,false};
	OP		pop[5];
	for(int i=0;i<5;i++){
		if(ReadAPiece(state,pIndex,piece[i])){
			count++;
			if(IsCharAOperator(piece[i][0])){
				pisop[i] = true;
				if(!strcmp(piece[i],"="))		pop[i] = ASN;
				else if(!strcmp(piece[i],"+"))	pop[i] = ADD;
				else if(!strcmp(piece[i],"-"))	pop[i] = MIN;
				else if(!strcmp(piece[i],"*"))	pop[i] = MUL;
				else if(!strcmp(piece[i],"/"))	pop[i] = DIV;
				else if(!strcmp(piece[i],"++"))	pop[i] = INC;
				else if(!strcmp(piece[i],"--"))	pop[i] = DEC;
                else if(!strcmp(piece[i],"+=")) pop[i] = ADDASN;
                else if(!strcmp(piece[i],"-=")) pop[i] = MINASN;
                else if(!strcmp(piece[i],"*=")) pop[i] = MULASN;
                else if(!strcmp(piece[i],"/=")) pop[i] = DIVASN;
				else							err_code = false;
			}
		}
		else
			break;
	}
    
	// second step: grammer check
	if(count!=2 && count!=3 && count!=5){
		err_code = false;
	}
	else{
		// the operators can only be -*--- or -*-*-
		if( !(pisop[0]==false && pisop[1]==true && pisop[2]==false
              && pisop[3]==false && pisop[4]==false) &&
           !(pisop[0]==false && pisop[1]==true && pisop[2]==false
             && pisop[3]==true && pisop[4]==false)){
               err_code = false;
           }
	}
    
	// third step: assigning symbolic operands and operators
	if(err_code){
		switch(count){
            case 2: // unary, e.g, a++
                type = unary;
                op = pop[1];
                strcpy(res_name,piece[0]);
                strcpy(operand_1_name, piece[0]);
                break;
            case 3:
                if(pop[1]==ASN){
                    type = asn;
                    op = pop[1];
                    strcpy(res_name,piece[0]);
                    strcpy(operand_1_name, piece[2]);
                }
                else if(pop[1]==ADDASN){
                    type = binary;
                    op = pop[1];
                    strcpy(res_name,piece[0]);
                    strcpy(operand_1_name, piece[0]);
                    strcpy(operand_2_name, piece[2]);
                }
                else if(pop[1]==MINASN){
                    type = binary;
                    op = pop[1];
                    strcpy(res_name,piece[0]);
                    strcpy(operand_1_name, piece[0]);
                    strcpy(operand_2_name, piece[2]);
                }
                else if(pop[1]==MULASN){
                    type = binary;
                    op = pop[1];
                    strcpy(res_name,piece[0]);
                    strcpy(operand_1_name, piece[0]);
                    strcpy(operand_2_name, piece[2]);
                }
                else if(pop[1]==DIVASN){
                    type = binary;
                    op = pop[1];
                    strcpy(res_name,piece[0]);
                    strcpy(operand_1_name, piece[2]);
                    strcpy(operand_2_name, piece[4]);
                }
                else{
                    type = binary;
                    op = pop[1];
                    strcpy(res_name,"ans");
                    strcpy(operand_1_name, piece[0]);
                    strcpy(operand_2_name, piece[2]);
                }
                break;
            case 5:
                if(pop[1]==ASN){
                    type = binary;
                    op = pop[3];
                    strcpy(res_name, piece[0]);
                    strcpy(operand_1_name, piece[2]);
                    strcpy(operand_2_name, piece[4]);
                }
                else{
                    // doesn't allow
                    cout << "Sorry, don't understand!" << endl;
                    err_code = false;
                }
                break;
            default:
                cout << "Can't be here!" << endl;
                break;
		}
	}
	return err_code;
}

///////////////////////////////////////////////////////////////////////
// helper functions
void PrintVersionInfo()
{
	cout << endl;
	cout << "\tWelcome to the MP#6 Programmable Calc With Matrices (C++ version)" << endl;
	cout << "\t\tJeanette Pranin, Northwestern Univ. "<< endl;
	cout << "\t\t   Copyright, 2014.   \n" << endl;
}