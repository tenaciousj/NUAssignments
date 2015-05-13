
//
//  main.cpp
//  MP5_XCode_2
//
//  Copyright (c) 2014 Jeanette Pranin. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <string.h>
#include "CVar.h"

using namespace std;



#define SIZE_CL_BUFF 100

int main(int argc, char* argv[])
{
	string Buffer;
    
    char CL_BUFFER[SIZE_CL_BUFF];
    
	// welcome information
	PrintVersionInfo();
    
	// init system DB
	CVarDB	varDB;
	varDB.Init();
    
    
	// init ALU
	CALU	alu;
	alu.SetVarDB(&varDB);
    
    // read test cases from file
    ifstream TestFile("TestCase.txt");
    
	// main loop
    
    if(TestFile.is_open())
    {
        while(getline(TestFile, Buffer))
        {
            
            // parse the command line
            if(Buffer.compare("quit")==0){
                cout << "Thank you and Bye!" << endl;
                break;
            }
            else if(Buffer.compare("who")==0){
                cout<<"------------------------------"<<endl;
                varDB.Dump();
                cout<<"------------------------------"<<endl;
            }
            else{
                char res_name[50], operand_1_name[50], operand_2_name[50];
                OP	op;
                OP_TYPE type;
                int count;
                strncpy(CL_BUFFER, Buffer.c_str(), sizeof(Buffer));
                CL_BUFFER[sizeof(CL_BUFFER) - 1] = 0;
                if(!ResolveAStatement(CL_BUFFER,res_name,op,type, operand_1_name,operand_2_name, count))
                {
                    if(count!=0)	cout << "Sorry, don't understand!" << endl;
                }
                else
                {
                    alu.SetOP(op);
                    alu.SetOPType(type);
                    if(alu.Perform(res_name, operand_1_name, operand_2_name))
                    {
                        // self-check
                        CVariable	*p = varDB.Search(res_name);
                        cout << "  " << res_name << " = " << p->Value() << endl;
                    }
                }
            }
            
        }
        
    }
    else
    {
        cout<<"Unable to open file"<<endl;
    }
	return 0;
}





