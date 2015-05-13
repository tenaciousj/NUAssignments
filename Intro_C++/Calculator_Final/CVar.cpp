//
//  CVar.cpp
//  HW#5
//
//  Created by Jeanette Pranin on 2/20/14.
//  Copyright (c) 2014 Jeanette Pranin. All rights reserved.
//

#include "CVar.h"
#include <cstring>


//////////////////////////////////////////////////
// CVariable                                    //
//////////////////////////////////////////////////

//constructor
CVariable :: CVariable()
{
    m_sName = NULL;
    m_dValue = NULL;
}

//constructs a new CVariable with a name "name" and value "v"
CVariable :: CVariable(const char* name, const double& v)
{
    m_sName = str_dup_new(name);
    m_dValue = v;
}

//CVariable destructor
CVariable :: ~CVariable()
{
    _destroy();
}

//copy constructor
CVariable :: CVariable(const CVariable& var)
{
    _copy(var);
    _destroy();
    
    m_dValue = var.Value();
}

//operator overload
//assigns the content of CVariable being passed in into 'this' object
const CVariable& CVariable :: operator=(const CVariable& var)
{
    if (m_dValue != var.Value())
    {
        _destroy();
        _copy(var);
    }
    m_dValue = var.Value();
    
    return (*this);
}

//sets name of CVariable
bool CVariable :: SetName(const char* name)
{
    if (name == NULL) return false;
    
    _destroy();
    _copy(name);
    
    return true;
}

//helper function that copies the content in const char* data to temporary variable
char* str_dup_new(const char* data)
{
    int length = (int) strlen(data);
    char * temp = new char[length + 1];
    strcpy(temp, data);
    return temp;
}

//////////////////////////////////////////////////
// CVarDB                                       //
//////////////////////////////////////////////////

//CVariable database constructor
CVarDB :: CVarDB()
{
    Init();
}

//initialize first element of database to be "ans" with value 0
void CVarDB:: Init()
{
    m_pDB[0].SetName("ans");
    m_pDB[0].SetValue(0);
    m_nSize = 1;
}

//searches for a CVariable, returns it if found, otherwise return NULL
CVariable* CVarDB :: Search(const char*name)
{
    for (int i = 0; i < m_nSize; i++)
    {
        if(!strcmp(m_pDB[i].Name(),name))
        {
            return &m_pDB[i];
        }
    }
    return NULL;
}

//create a new CVariable to put into database
CVariable* CVarDB :: CreateANewVar(const char* name, double value)
{
    m_pDB[m_nSize].SetName(name);
    m_pDB[m_nSize].SetValue(value);
    
    m_nSize++; //increases size of database
    return &m_pDB[m_nSize-1];
}


//prints out everyone in the database
void CVarDB :: Dump()
{
    for (int i = 0; i < m_nSize; i++)
    {
        cout << m_pDB[i].Name() << "\t" << m_pDB[i].Value() << endl;
    }
}


//////////////////////////////////////////////////
// CALU                                         //
//////////////////////////////////////////////////


bool CALU :: Perform(const char* res_name, const char* operand_1_name, const char* operand_2_name)
{
    //placeholders for the values in res_name, operand_1_name, and operand_2_name, respectively
    double temp = 0;
    double temp_1 = 0;
    double temp_2 = 0;
    
    if((*m_pVarDB).Search(res_name) == NULL) //if the CVariable doesn't exist in the database, create it with arbitrary value 0
        m_pVarDB->CreateANewVar(res_name, 0);
    
    if(_ConvertAnOperand(operand_1_name, temp_1) == false || _ConvertAnOperand(operand_2_name, temp_2) == false) //checks to make sure the contents of operand_1_name and operand_2_name are valid (e.g. c = 3.2f3 will not be valid)
    {
        cout << "Sorry, do not understand!" << endl;
        return false;
    }
    
    _ConvertAnOperand(operand_1_name, temp_1); //retrieve the value in operand_1_name and put into temp_1
    _ConvertAnOperand(operand_2_name, temp_2); //retrieve the value in operand_2_name and put into temp_2
    _Operation(temp, temp_1, temp_2); //does calculation on temp_1 and temp_2 and puts into temp
    
    
    m_pVarDB->Search(res_name)->SetValue(temp); //set the value in temp to the value of the CVariable in the database
    
    return true;
}

//input two double variables, do the calculation and assign the result to 'res'
void CALU :: _Operation(double& res, double& operand_1, const double& operand_2)
{
    if(m_Type == asn) //if it is an assignment statement, the value in operand_1 is assigned to res
        res = operand_1;
    else if(m_Type == unary) //if it is a unary statement, increment/decrement the operand_1 accordingly and assign to res
    {
        if(m_OP == INC)
            res = operand_1+1; //increment
        else if(m_OP == DEC)
            res = operand_1-1; //decrement
    }
    else if(m_Type == binary) //if it is a unary statement, add/subtract/multiply/divide the operand_1 and operand_2 accordingly and assign to res
    {
        if(m_OP == ADD)
            res = operand_1 + operand_2; //addition
        else if(m_OP == MIN)
            res = operand_1 - operand_2; //subtraction
        else if(m_OP == MUL)
            res = operand_1 * operand_2; //multiplication
        else if(m_OP == DIV)
            res = operand_1 / operand_2; //division
    }
}

//Convert a symbolic operand to a numerical one
bool CALU :: _ConvertAnOperand(const char* operand_name, double& value)
{
    if((*m_pVarDB).Search(operand_name)) //if the CVariable is in database, assign its value to double& value
    {
        value = (*m_pVarDB).Search(operand_name)->Value();
        return true;
    }
    else //otherwise, check if operand_name is a number
    {
        int i = 0;
        while (IsCharADigit(operand_name[i])) i++;//checks if each element of operand_name composes a number (e.g. 3.2f3 is not a number but 3.2 is)
        if(i == strlen(operand_name))
        {
            value = atof(operand_name); //if operand_name is a number, assign its value to double& value
            return true;
        }
        return false; //otherwise, not a number
    }
}





///////////////////////////////
//////PARTITIONER//////////////
///////////////////////////////

// explain operators
void TranslateOP(const OP op)
{
	switch(op){
        case ASN:
            cout << "ASN" ;
            break;
        case ADD:
            cout << "ADD" ;
            break;
        case MIN:
            cout << "MIN" ;
            break;
        case MUL:
            cout << "MUL" ;
            break;
        case DIV:
            cout << "DIV" ;
            break;
        case INC:
            cout << "INC" ;
            break;
        case DEC:
            cout << "DEC" ;
            break;
        default:
            cout << "UNRECOGNIZED OPERATOR" ;
            break;
	}
}

// explain command line using the pre-defined pattern
void UnderstandAStatement(char* res_name, const OP &op, const OP_TYPE& type,
                          char* operand_1_name, char* operand_2_name)
{
	switch(type){
        case asn:
            TranslateOP(op);
            cout << " " << operand_1_name << " to " << res_name << endl;
            break;
        case unary:
            TranslateOP(op);
            cout <<" "<< res_name << endl;
            break;
        case binary:
            TranslateOP(op);
            cout << " " << operand_1_name << " AND "
			<< operand_2_name << " , THEN ASN to " << res_name << endl;
            break;
        default:
            cout << "Something must be wrong!" << endl;
            break;
	}
}





////////////////////////////////////////////////////////////////////////////////
// functions from MP#2
// read a piece from buffer from position pIndex
int ReadAPiece(const char* buffer, int& pIndex, char* piece)
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
			while( IsCharALetter(buffer[ed]) || IsCharADigit(buffer[ed]) ||  buffer[st]=='_')
				ed ++;
		}
		else if(IsCharADigit(buffer[st])){
			while(IsCharADigit(buffer[ed]) || buffer[st]=='.')
				ed ++;
		}
		else if(IsCharAOperator(buffer[st])){
			while(IsCharAOperator(buffer[ed]))
				ed ++;
		}
		else if(buffer[st]=='[')
		{
			ed = st+1;
			while(buffer[ed]!=']')
			{
				if(IsCharADigit(buffer[ed])||(buffer[ed]==',')||(buffer[ed]==';')||(buffer[ed]==' ')||(buffer[ed]=='.')||(buffer[ed]=='\r'))
				{
					ed++;
				}
				else
				{
					cout<<"Expect a ']' here."<<endl;
					err_code = 0;
					break;
				}
			}
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

bool ResolveAStatement(const char* state, char* res_name, OP &op, OP_TYPE& type,
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
				else							err_code = false;
			}
		}
		else
			break;
	}
    
	// second step: grammar check
	if(count!=2 && count!=3 && count!=5){
		err_code = false;
	}
	else{
		// the operators can only be the #2 or/and #4 piece in command line
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
            case 2: // unary operation (post increase and post decrease), e.g, a++
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
                    // if the command line is not valid
                    cout << "Sorry, don't understand!" << endl;
                    err_code = false;
                }
                break;
            default:
                cout << "Cannot be here!" << endl;
                break;
		}
	}
	return err_code;
}


//prints header
void PrintVersionInfo()
{
	cout << endl;
	cout << "\tWelcome to the EECS 211 MP#3: A Command Line Interpreter" << endl;
	cout << "\t\tJeanette Pranin, Northwestern University "<< endl;
	cout << "\t\t   Copyright, 2014   " << endl;
}



