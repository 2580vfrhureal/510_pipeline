#include<iostream>
#include<string>
#include<algorithm>//fill()
#include<fstream>
#include<stdlib.h>//exit
#include<bitset>
#include"latch.h"
#include"functions.h"
using namespace std;

int instruction_number = 0;
int cycle_number = 0;

int main()
{
	fill(ins, ins + 512, "");//initial ins[]

	//choose mode
	cout << "choose the mode" << endl;
	int mode;//the choosed mode
	cout << "1.instruction mode" << endl << "2.cycly mode" << endl << "3.exit" << endl;
	cin >> mode;//input mode;

	string filename;

	string inputins;
	ifstream fin;
	int ins_counter = 0;
	//vector<string> ins;
	switch (mode)
	{
	case 1:
		cout << "you choose mode 1:instruction" << endl;


		cout << "input filename:";
		cin >> filename;
		cout << "how many instruction you want to run:" << endl;
		cin >> instruction_number;

		//ifstream fin;//create stream object.
		fin.open(filename, ios::in);//open file
		if (!fin.is_open()) //judge if successful
		{
			cout << "fail to open file" << endl;

		}
		else
		{
			cout << "file opened successfully" << endl;
		}

		while (getline(fin, inputins))
		{


			//ins.push_back(inputins);

			ins[ins_counter] = inputins;

			cout << "ins[" << ins_counter << "]" << ins[ins_counter] << endl;
			ins_counter++;
		}

		break;

	case 2:

		cout << "you choose mode 2:cycle" << endl;
		//readfile(filename);//read instructions from file;
		//string inputins;//


		cout << "input filename:" << endl;
		cin >> filename;
		cout << "how many cycle do you want to run:" << endl;
		cin >> cycle_number;
		//ifstream fin;//create stream object.
		fin.open(filename, ios::in);//open file
		if (!fin.is_open()) //judge if successful
		{
			cout << "fail to open file" << endl;

		}
		else
		{
			cout << "file opened successfully" << endl;
		}

		while (getline(fin, inputins))
		{


			//ins.push_back(inputins);

			ins[ins_counter] = inputins;

			cout << "ins[" << ins_counter << "]" << ins[ins_counter] << endl;
			ins_counter++;
		}

		break;
	case 3:
		cout << "you choose mode 3:exit;" << endl;
		cout<<"program finished"<<endl;
		break;
	default:
		cout << "invalid input" << endl;
		break;
	}
	/*for (int i = 0; i <ins_counter; i++)//显示ins内容
	{
		cout << "ins[" << i << "]" << ins[i] << endl;
	}
	*/

	//如果输入的是instruction模式 

	if (mode == 1) //instruction mode
	{
		while (instruction_number!= insnum)
		{
			WB();
			MEM();
			EX();
			ID();
			IF(ins);
		}
	}
	else if (mode == 2)//cycle mode
	{
		while (cycle_number != clock_WB)
		{
			WB();
			MEM();
			EX();
			ID();
			IF(ins);

		}

	}
	else
	{
		cout<<"exit"<<endl;
	}

	cout << "ins_counter=" << ins_counter << endl;
	//ins
	cout << endl;

	//	MEM_WB
	cout << "-------------------MEM_WB-----------------------" << endl;
	cout << "IR=" << mem_wb.getIR() << endl;
	cout << "ALUoutput=" << mem_wb.getALUoutput() << endl;

	cout << "LMD=" << mem_wb.getLMD() << endl;
	
	cout << "rt=" << mem_wb.getrt() << endl;
	cout << "RT=" << mem_wb.getRT() << endl;

	cout << "-------------------EX_MEM----------------------" << endl;
	cout << endl;
	cout << "IR=" << ex_mem.getIR() << endl;;
	cout << "NPC=" << ex_mem.getNPC() << endl;
	cout << "imm=" << ex_mem.getimm() << endl;
	cout << "A=" << ex_mem.getA() << endl;//rs
	cout << "B=" << ex_mem.getB() << endl;//rt
	cout << "ALUoutput=" << ex_mem.getALUoutput() << endl;
	cout << "cond=" << ex_mem.getcond() << endl;
	cout << "rt=" << ex_mem.getrt() << endl;//unsigned long int rt;
	cout << endl;
	cout << "-------------------ID_EX-----------------------" << endl;

	cout << "IR=" << id_ex.getIR() << endl;
	cout << "NPC=" << id_ex.getNPC() << endl;
	cout << "OP=" << id_ex.getOP() << endl;//string OP;
	cout << "RS=" << id_ex.getRS() << endl;//string RS;
	cout << "RD=" << id_ex.getRD() << endl;//string RD;
	cout << "RT=" << id_ex.getRT() << endl;//string RT;
	cout << "SHAMT=" << id_ex.getSHAMT() << endl;//string SHAMT;
	cout << "FUNCT=" << id_ex.getFUNCT() << endl;//string FUNCT;
	cout << "IMM=" << id_ex.getIMM() << endl;//string IMM;
	cout << "rs=" << id_ex.getrs() << endl;//unsigned long int rs;//十进制
	cout << "rt=" << id_ex.getrt() << endl;//unsigned long int rt;
	cout << "rd=" << id_ex.getrd() << endl;//unsigned long int rd;
	cout << "imm=" << id_ex.getimm() << endl;//unsigned long int imm;
	cout << endl;

	cout << "-------------------IF_ID-----------------------" << endl;
	cout << "PC=" << IF_ID::PC << endl;//static unsigned long int PC;//PC
	cout << "IR=" << if_id.getIR() << endl;//string IR;
	//cout << "NPC=" << if_id.getNPC() << endl;//unsigned long int NPC;
	cout << endl;

	cout << "-------------------Reg-----------------------" << endl;
	cout << endl;
	//display Reg
	for (int i = 0; i < 32; i++)
	{
		cout << "R[" << i << "]=" << IF_ID::R[i] << endl;

	}
	cout << endl;

	cout << "-------------------datamemory-----------------------" << endl;
	//display datamemory
	cout << endl;
	for (int i = 0; i < 512; i++)
	{
		cout << "d[" << i << "]=" << datamemory[i] << " ";//循环输出一维数组
		if ((i + 1) % 16 == 0)//做判定条件
		{
			cout << endl;
			cout << endl;
		}
	}
	cout << endl;

	
	//display utilization
	cout << "invalid_WB=" << invalid_WB << endl;
	cout << "invalid_MEM=" << invalid_MEM << endl;
	cout << "invalid_EX=" << invalid_EX << endl;
	cout << "invalid_ID=" << invalid_ID << endl;
	cout << "invalid_IF=" << invalid_IF << endl;

	cout << endl;
	cout << "clock_WB=" << clock_WB << endl;
	cout << "clock_MEM=" << clock_MEM << endl;
	cout << "clock_EX=" << clock_EX << endl;
	cout << "clock_ID=" << clock_ID << endl;
	cout << "clock_IF=" << clock_IF << endl;

	//cout << "nop_IF=" << nop_IF << endl;

	cout << endl;
	cout << "U_WB=" << ((float)(clock_WB-invalid_WB) / clock_WB) * 100 << "%" << endl;
	cout << "U_MEM=" << ((float)(clock_WB - invalid_MEM) / clock_MEM) * 100 << "%" << endl;
	cout << "U_EX=" << ((float)(clock_WB - invalid_EX) / clock_EX) * 100 << "%" << endl;
	cout << "U_ID=" << ((float)(clock_WB - invalid_ID) / clock_ID) * 100 << "%" << endl;
	cout << "U_IF=" << ((float)(clock_WB - invalid_IF) / clock_IF) * 100 << "%" << endl;

	//continue
	string continue_answer;
	cout << "continue?" << endl << "please input Y/N" << endl;
	cin >> continue_answer;
	if (continue_answer=="Y")
	{
		if (mode==1)
		{
			cout <<"please input the number of instructions want to execute:"<< endl;
			cin >> instruction_number;
			while (instruction_number != insnum)
			{
				WB();
				MEM();
				EX();
				ID();
				IF(ins);
			}
		}
		else if (mode==2)
		{
			cout << "please input the number of cycle want to execute:" << endl;
			cin >> cycle_number;
			while (cycle_number != clock_WB)
			{
				WB();
				MEM();
				EX();
				ID();
				IF(ins);

			}
		}
		

		//	MEM_WB
		cout << "-------------------MEM_WB-----------------------" << endl;
		cout << "IR=" << mem_wb.getIR() << endl;
		cout << "ALUoutput=" << mem_wb.getALUoutput() << endl;
		cout << "LMD=" << mem_wb.getLMD() << endl;
		
		cout << "rt=" << mem_wb.getrt() << endl;
		cout << "RT=" << mem_wb.getRT() << endl;
		
		cout << "-------------------EX_MEM----------------------" << endl;
		cout << endl;
		cout << "IR=" << ex_mem.getIR() << endl;;
		cout << "NPC=" << ex_mem.getNPC() << endl;
		cout << "imm=" << ex_mem.getimm() << endl;
		cout << "A=" << ex_mem.getA() << endl;//rs
		cout << "B=" << ex_mem.getB() << endl;//rt
		cout << "ALUoutput=" << ex_mem.getALUoutput() << endl;
		cout << "cond=" << ex_mem.getcond() << endl;
		cout << "rt=" << ex_mem.getrt() << endl;//unsigned long int rt;
		
		cout << endl;
		cout << "-------------------ID_EX-----------------------" << endl;

		cout << "IR=" << id_ex.getIR() << endl;
		cout << "NPC=" << id_ex.getNPC() << endl;
		cout << "OP=" << id_ex.getOP() << endl;//string OP;
		cout << "RS=" << id_ex.getRS() << endl;//string RS;
		cout << "RD=" << id_ex.getRD() << endl;//string RD;
		cout << "RT=" << id_ex.getRT() << endl;//string RT;
		cout << "SHAMT=" << id_ex.getSHAMT() << endl;//string SHAMT;
		cout << "FUNCT=" << id_ex.getFUNCT() << endl;//string FUNCT;
		cout << "IMM=" << id_ex.getIMM() << endl;//string IMM;
		cout << "rs=" << id_ex.getrs() << endl;//unsigned long int rs;//十进制
		cout << "rt=" << id_ex.getrt() << endl;//unsigned long int rt;
		cout << "rd=" << id_ex.getrd() << endl;//unsigned long int rd;
		cout << "imm=" << id_ex.getimm() << endl;//unsigned long int imm;
		cout << endl;

		cout << "-------------------IF_ID-----------------------" << endl;
		cout << "PC=" << IF_ID::PC << endl;//static unsigned long int PC;//PC
		cout << "IR=" << if_id.getIR() << endl;//string IR;
		cout << endl;

		cout << "-------------------Reg-----------------------" << endl;
		cout << endl;
		//display Reg
		for (int i = 0; i < 32; i++)
		{
			cout << "R[" << i << "]=" << IF_ID::R[i] << endl;

		}
		cout << endl;

		cout << "-------------------datamemory-----------------------" << endl;
		//display datamemory
		cout << endl;
		for (int i = 0; i < 512; i++)
		{
			cout << "d[" << i << "]=" << datamemory[i] << " ";//循环输出一维数组
			if ((i + 1) % 16 == 0)//做判定条件
			{
				cout << endl;
				cout << endl;
			}
		}
		cout << endl;


		//display utilization
		cout << "invalid_WB=" << invalid_WB << endl;
		cout << "invalid_MEM=" << invalid_MEM << endl;
		cout << "invalid_EX=" << invalid_EX << endl;
		cout << "invalid_ID=" << invalid_ID << endl;
		cout << "invalid_IF=" << invalid_IF << endl;

		cout << endl;
		cout << "clock_WB=" << clock_WB << endl;
		cout << "clock_MEM=" << clock_MEM << endl;
		cout << "clock_EX=" << clock_EX << endl;
		cout << "clock_ID=" << clock_ID << endl;
		cout << "clock_IF=" << clock_IF << endl;

		cout << endl;
		cout << "U_WB=" << ((float)(clock_WB - invalid_WB) / clock_WB) * 100 << "%" << endl;
		cout << "U_MEM=" << ((float)(clock_WB - invalid_MEM) / clock_MEM) * 100 << "%" << endl;
		cout << "U_EX=" << ((float)(clock_WB - invalid_EX) / clock_EX) * 100 << "%" << endl;
		cout << "U_ID=" << ((float)(clock_WB - invalid_ID) / clock_ID) * 100 << "%" << endl;
		cout << "U_IF=" << ((float)(clock_WB - invalid_IF) / clock_IF) * 100 << "%" << endl;


	}
	else 
	{
		cout << "program finished" << endl;
	}



	system("pause");
	return 0;



}