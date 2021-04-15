#pragma once
#include<string>
#include"latch.h"
using namespace std;

static string ins[512];//2048bytes/4bytes如果出现问题把数组改小；
static unsigned long int datamemory[512];

static bool beq_flag=0;
static bool data_flag = 0;
static bool R_flag[32] = {};

extern int insnum = 0;//the number of already excute instruction number 
extern int clock_WB = 0;//总cycle
extern int clock_MEM = 0;
extern int clock_EX = 0;
extern int clock_ID = 0;
extern int clock_IF = 0;


extern int invalid_WB = 0;//WB被调用的次数
extern int invalid_MEM = 0;
extern int invalid_EX = 0;
extern int invalid_ID = 0;
extern int invalid_IF = 0;



//tool functions
unsigned long int bin_to_dec(string bin)//change string type binary number to int type decimal
{
	//将传入的二进制字符串转换成十进制，并返回十进制数字。
	//在此处调用判断一个字符串有多长的函数
	unsigned long int size = bin.length();

	//将二进制数字转换为十进制
	unsigned long int parseBinary = 0;
	for (unsigned long int i = 0; i < size; ++i) {
		if (bin[i] == '1') {
			parseBinary += pow(2.0, size - i - 1);
		}
	}

	return parseBinary;
}

unsigned long int OrOperator(unsigned long int& a, unsigned long int& b) //or
{
	return a | b;
}

unsigned long int AndOperator(unsigned long int& a, unsigned long int& b) //&
{
	return a & b;
}

//sign extend
void signExtend(string IMM)
{
	string s=IMM;
	string imme;
	imme = s.substr(0, 1);
	if (imme == "0")
	{
		id_ex.setIMM("0000000000000000" + s);
	}
	else if (imme == "1")
	{
		id_ex.setIMM("1111111111111111" + s);
	}

}

//zero extend
void zeroExtend(string IMM)
{
	string s=IMM;
	string imme;
	id_ex.setIMM("0000000000000000" + s);
}


//IF()
void IF(string ins[])
{
	if_id.setIR(ins[IF_ID::PC]);
	string s= if_id.getIR();
	if (s != "")
	{
		if (beq_flag == 1)//last instruction is beq
		{
			//stall
		}
		else if(beq_flag==0)
		{
			if (ex_mem.getcond()==1)
			{
				ex_mem.setcond(0);
				IF_ID::PC = ex_mem.getNPC();
				if_id.setIR(ins[IF_ID::PC]);
			}
			else//cond=0 
			{
				IF_ID::PC++;
				if_id.setNPC(IF_ID::PC);

			}
		}
	}
	else
	{
		invalid_IF++;
	}

	clock_IF++;
}




//ID()
void ID()
{
	
	//
	id_ex.setNPC(if_id.getNPC());
	id_ex.setIR(if_id.getIR());
		string s = "0";
		string s1 = "0";
		s = if_id.getIR();//current instruction
		if ((s!="")&&(data_flag==0))
		{
			s1 = s.substr(0, 6);
			id_ex.setOP(s1);//OP
			if (id_ex.getOP() == "000000")//R type
			{
				string s2 = "0";
				s2 = s.substr(6, 5);//RS
				id_ex.setRS(s2);
				id_ex.setrs(bin_to_dec(id_ex.getRS()));//把RS转为rs
				//id_ex.setA(IF_ID::R[id_ex.getrs()]);//将R[rs]存入A

				s2 = s.substr(11, 5);//RT
				id_ex.setRT(s2);
				id_ex.setrt(bin_to_dec(id_ex.getRT()));//把RT转为rt
				//id_ex.setB(IF_ID::R[id_ex.getrt()]);//将R[rt]存入B


				s2 = s.substr(16, 5);//RD
				id_ex.setRD(s2);
				id_ex.setrd(bin_to_dec(id_ex.getRD()));//把RD转为rd


				s2 = s.substr(21, 5);//SHAMT
				id_ex.setSHAMT(s2);

				s2 = s.substr(26, 6);//FUNCT
				id_ex.setFUNCT(s2);

				s2 = "0";//IMM寄存器清零
				id_ex.setIMM(s2);
			}
			else//I type
			{
				string s3 = "0";
				s3 = s.substr(6, 5);//RS
				id_ex.setRS(s3);
				id_ex.setrs(bin_to_dec(id_ex.getRS()));//把RS转为rs
				//id_ex.setA(IF_ID::R[id_ex.getrs()]);//将R[rs]存入A

				s3 = s.substr(11, 5);//RT
				id_ex.setRT(s3);
				id_ex.setrt(bin_to_dec(id_ex.getRT()));

				s3 = s.substr(16, 16);//IMM
				id_ex.setIMM(s3);
				id_ex.setimm(bin_to_dec(id_ex.getIMM()));//IMM转dec imm

				s3 = "0";//其他寄存器清零
				id_ex.setRD(s3);
				id_ex.setSHAMT(s3);
				id_ex.setFUNCT(s3);

			}

			//hazard detect

				
				if (id_ex.getOP() == "000100")//beq
				{
					beq_flag = 1;//control hazard

				}
				else 
				{
					if (id_ex.getOP() == "000000")//R type
					{
						if ((id_ex.getRS() == ex_mem.getRD() || id_ex.getRT() == ex_mem.getRD()))
							//||((id_ex.getRS() == mem_wb.getRD() || id_ex.getRT() == mem_wb.getRD()))
							//)
						
						{
							//execute stall
							id_ex.setIR("");
							IF_ID::PC--;
							data_flag = 1;
						}
						
					}
					else//I type 
					{
						if ((id_ex.getOP() != "101011"))//I type except sw
						{
							
						    if ((id_ex.getRS() == ex_mem.getRT()))
								//||((id_ex.getRS() == mem_wb.getRT()))(no)
							
								
							{
								id_ex.setIR("");
								IF_ID::PC--;
								data_flag = 1;
							}
							
						}
						
					}
				}
			
		}
		else
		{ 
		invalid_ID++;
        }

		
	
	clock_ID++;
}

//EX()
void EX()
{

		unsigned long int a = 0;//&|
		unsigned long int b = 0;
		ex_mem.setIR(id_ex.getIR());
		ex_mem.setA(id_ex.getA());//unsigned long int A;//rs
		ex_mem.setB(id_ex.getB());//rt
		ex_mem.setrs(id_ex.getrs());//十进制
		ex_mem.setrt(id_ex.getrt());
		ex_mem.setrd(id_ex.getrd());
		ex_mem.setimm(id_ex.getimm());
		ex_mem.setOP(id_ex.getOP());
		ex_mem.setRS(id_ex.getRS());
		ex_mem.setRT(id_ex.getRT());
		ex_mem.setRD(id_ex.getRD());
		ex_mem.setSHAMT(id_ex.getSHAMT());
		ex_mem.setFUNCT(id_ex.getFUNCT());
		ex_mem.setIMM(id_ex.getIMM());
		string s = id_ex.getIR();
		if (s != "")
		{
			if (id_ex.getOP() == "000000")//R type
			{

				if (id_ex.getFUNCT() == "100000")//add
				{
					id_ex.setA(IF_ID::R[id_ex.getrs()]);
					id_ex.setB(IF_ID::R[id_ex.getrt()]);
					ex_mem.setALUoutput(id_ex.getA() + id_ex.getB());//int ALUoutput=A+B
				}
				else if (id_ex.getFUNCT() == "100010")//sub
				{
					id_ex.setA(IF_ID::R[id_ex.getrs()]);
					id_ex.setB(IF_ID::R[id_ex.getrt()]);
					ex_mem.setALUoutput(id_ex.getA() - id_ex.getB());//int ALUoutput=A-B
				}
				else if (id_ex.getFUNCT() == "100101")//or
				{
					id_ex.setA(IF_ID::R[id_ex.getrs()]);
					id_ex.setB(IF_ID::R[id_ex.getrt()]);
					a = id_ex.getA();
					b = id_ex.getB();
					ex_mem.setALUoutput(OrOperator(a, b));//or
				}

				else if (id_ex.getFUNCT() == "011000")//mul
				{
					id_ex.setA(IF_ID::R[id_ex.getrs()]);
					id_ex.setB(IF_ID::R[id_ex.getrt()]);
					unsigned long int c = 0;
					//id_ex.setA(40960);//test
					//id_ex.setB(40960);
					c = id_ex.getA() * id_ex.getB();
					ex_mem.setALUoutput(c);

				}

			}
			//I type
			else if (id_ex.getOP() == "000100")//beq
			{
				id_ex.setA(IF_ID::R[id_ex.getrs()]);
				id_ex.setB(IF_ID::R[id_ex.getrt()]);
				beq_flag = 0;//stall a instruction
				//bool(R[rs]==R[rt])
				ex_mem.setALUoutput(0);//beq not WB()
				ex_mem.setcond(bool(id_ex.getA() == id_ex.getB()));//相等 cond=1;


				ex_mem.setNPC(id_ex.getNPC() + id_ex.getimm());//NPC ->branch instruction number
			}
			else if (id_ex.getOP() == "001100")//andi
			{
				id_ex.setA(IF_ID::R[id_ex.getrs()]);
				a = id_ex.getA();
				//latch.setimm(bin_to_dec(latch.getIMM()));//IMM转dec imm
				b = id_ex.getimm();
				ex_mem.setALUoutput(AndOperator(a, b));//and
			}
			else if (id_ex.getOP() == "001101")//ori
			{
				id_ex.setA(IF_ID::R[id_ex.getrs()]);
				a = id_ex.getA();
				//latch.setimm(bin_to_dec(latch.getIMM()));//IMM转dec imm
				b = id_ex.getimm();
				ex_mem.setALUoutput(OrOperator(a, b));
			}
			else if (id_ex.getOP() == "001111")//lui
			{

				unsigned long int a = 0;
				a = 65536;
				//latch.setimm(bin_to_dec(latch.getIMM()));//IMM转dec imm
				ex_mem.setALUoutput(a * id_ex.getimm());

			}
			else if (id_ex.getOP() == "100011")//lw
			{
				//R[rs]*16
				//imm/4
				id_ex.setA(IF_ID::R[id_ex.getrs()]);
				//latch.setimm(bin_to_dec(latch.getIMM()));//IMM转dec imm
				a = id_ex.getA() * 16 + id_ex.getimm() / 4;//address=R[rs]*16+imm/4
				ex_mem.setALUoutput(a);//ALUoutput=address
				//datamemory[latch.getALUoutput()]=66;//for test
			}
			else if (id_ex.getOP() == "101011")//sw
			{
				//R[rs]*16

				//imm/4
				id_ex.setA(IF_ID::R[id_ex.getrs()]);
				//latch.setimm(bin_to_dec(latch.getIMM()));//IMM转dec imm
				a = (id_ex.getA() * 16) + (id_ex.getimm() / 4);//address=R[rs]*16+imm/4
				ex_mem.setALUoutput(a);//ALUoutput=address

			}
			else if (id_ex.getOP() == "001010" || id_ex.getOP() == "001011")//
			{
			int result;
			if (IF_ID::R[id_ex.getrt()] < id_ex.getimm())
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			ex_mem.setALUoutput(result);
			}

			else
			{
				ex_mem.setALUoutput(0);

			}
}
		else {
			invalid_EX++;
		}
	clock_EX++;
}

//MEM()
void MEM()
{
	mem_wb.setIR(ex_mem.getIR());
	mem_wb.setALUoutput(ex_mem.getALUoutput());
	//cond;
	mem_wb.setimm(ex_mem.getimm());//ex_mem.setimm(id_ex.getimm());
	mem_wb.setA(ex_mem.getA());//unsigned long int A;//rs
	mem_wb.setB(ex_mem.getB());//ex_mem.setB(id_ex.getB());//rt
	mem_wb.setrs(ex_mem.getrs());//十进制
	mem_wb.setrt(ex_mem.getrt());
	mem_wb.setrd(ex_mem.getrd());
	mem_wb.setOP(ex_mem.getOP());
	mem_wb.setRS(ex_mem.getRS());

	mem_wb.setRT(ex_mem.getRT());
	mem_wb.setRD(ex_mem.getRD());
	mem_wb.setSHAMT(ex_mem.getSHAMT());
	mem_wb.setFUNCT(ex_mem.getFUNCT());
	mem_wb.setIMM(ex_mem.getIMM());
	string s = ex_mem.getIR();
	if (s != "")
	{
		//sw M[ALUoutput]=R[rt]

		if (ex_mem.getOP() == "101011")//sw
		{
			datamemory[ex_mem.getALUoutput()] = ex_mem.getB();
			ex_mem.setALUoutput(0);//no WB

		}

		//lw LMD=M[address]
		else if (ex_mem.getOP() == "100011")//lw
		{

			mem_wb.setLMD(datamemory[ex_mem.getALUoutput()]);

		}
		else 
		{
			invalid_MEM++;
		}
	
	}
	else 
	{
		invalid_MEM++;
	}
	clock_MEM++;
}

//WB()
void WB()
{

	string s = mem_wb.getIR();
	if (s != "")
	{
		if (data_flag ==1)
		{
			data_flag = 0;
		}

		if (mem_wb.getOP() == "100011")//lw
		{
			IF_ID::R[mem_wb.getrt()] = mem_wb.getLMD();
		}

		else
		{
			if (mem_wb.getOP() == "101011")//sw
			{
				//no WB
			}
			else
			{
				if (mem_wb.getOP() == "000100")//beq
				{
					//no WB

				}
				else
				{

					if (mem_wb.getOP() == "000010")//mul
					{
						bitset<64> b1(mem_wb.getALUoutput());
						//cout << b1 << endl;
						string s;
						string s1;
						string s2;
						s = b1.to_string();
						s1 = s.substr(0, 32);
						s2 = s.substr(32, 32);
						//cout << "s1=" << s1 << endl;
						//cout << "s2=" << s2 << endl;

						IF_ID::R[mem_wb.getrd()] = bin_to_dec(s2);//低32位存rd
						IF_ID::R[mem_wb.getrd() + 1] = bin_to_dec(s1);//高32位存rd+1

					}
					else
					{

						if (mem_wb.getOP() == "000000")//R type
						{

							IF_ID::R[mem_wb.getrd()] = mem_wb.getALUoutput();
						
						}
						else //I type
						{

							IF_ID::R[mem_wb.getrt()] = mem_wb.getALUoutput();
						
						}

					}
					
				}
			}
		}
		
			insnum++;
		
	}
	else
	{
		invalid_WB++;
	}
	clock_WB++;
}
