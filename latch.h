#pragma once
#include<string>
using namespace std;
class IF_ID
{
private://latch of IF_ID,ID_EX,EX_MEM,MEM_WB.
	string IR;
	unsigned long int NPC;
public:
	static unsigned long int R[32];//32 Rrg
	static unsigned long int PC;//PC
	//long type:32 bits
	//latchReg() {};
	IF_ID() :
		IR(""),///*/*00000000000000000000000000000000*/*/
		NPC(0)
	{}
	~IF_ID(){}

	void setIR(string ir)//IR
	{
		IR = ir;
	}
	string getIR()
	{
		return IR;
	}

	void setNPC(unsigned long int npc)//NPC
	{
		NPC = npc;

	}
	unsigned long int getNPC()
	{
		return NPC;
	}

};
//<静态变量的类型>  <类名> :: <类的静态成员变量名> <= 初始化值 >
unsigned long int IF_ID::R[32] = {};
unsigned long int IF_ID::PC = 0;

class ID_EX
{
private://latch of IF_ID,ID_EX,EX_MEM,MEM_WB.
	string IR;
	unsigned long int NPC;
	unsigned long int imm;
	unsigned long int A;//rs
	unsigned long int B;//rt
	unsigned long int rs;//十进制
	unsigned long int rt;
	unsigned long int rd;
	string OP;
	string RS;
	string RD;
	string RT;
	string SHAMT;
	string FUNCT;
	string IMM;
public:
	
	ID_EX() :
		IR(""),///*/*00000000000000000000000000000000*/*/
		OP(""),
		RS(""),
		RD(""),
		RT(""),
		SHAMT(""),
		FUNCT(""),
		IMM(""),
		NPC(0),
		imm(0),
		A(0),
		B(0),
		rs(0),//十进制
		rt(0),
		rd(0)
	{
	}
	~ID_EX() {}

	void setIR(string ir)//IR
	{
		IR = ir;
	}
	string getIR()
	{
		return IR;
	}

	void setNPC(unsigned long int npc)//NPC
	{
		NPC = npc;

	}
	unsigned long int getNPC()
	{
		return NPC;
	}

	//imm
	void setimm(unsigned long int imm_dec)//imm
	{
		imm = imm_dec;

	}
	unsigned long int getimm()
	{
		return imm;
	}
	//A
	void setA(unsigned long int A_value)
	{
		A = A_value;

	}
	unsigned long int getA()
	{
		return A;
	}

	//B
	void setB(unsigned long int B_value)
	{
		B = B_value;

	}
	unsigned long int getB()
	{
		return B;
	}

	void setrs(unsigned long int value)//rs
	{
		rs = value;
	}
	unsigned long int getrs()
	{
		return rs;
	}

	void setrt(unsigned long int value)//rt
	{
		rt = value;
	}
	unsigned long int getrt()
	{
		return rt;
	}

	void setrd(unsigned long int value)//rd
	{
		rd = value;
	}
	unsigned long int getrd()
	{
		return rd;
	}
	void setOP(string s1)//OP
	{
		OP = s1;
	}
	string getOP()
	{
		return OP;
	}

	void setRS(string s1)//RS
	{
		RS = s1;
	}
	string getRS()
	{
		return RS;
	}

	void setRD(string s1)//RD
	{
		RD = s1;
	}
	string getRD()
	{
		return RD;
	}

	void setRT(string s1)//RT
	{
		RT = s1;
	}
	string getRT()
	{
		return RT;
	}

	void setSHAMT(string s1)//SHAMT
	{
		SHAMT = s1;
	}
	string getSHAMT()
	{
		return SHAMT;
	}

	void setFUNCT(string s1)//FUNCT
	{
		FUNCT = s1;
	}
	string getFUNCT()
	{
		return FUNCT;
	}

	void setIMM(string s1)//IMM
	{
		IMM = s1;
	}
	string getIMM()
	{
		return IMM;
	}
};

class EX_MEM
{
private://latch of IF_ID,ID_EX,EX_MEM,MEM_WB.
	string IR;
	unsigned long int NPC;
	unsigned long int imm;
	unsigned long int A;//rs
	unsigned long int B;//rt
	unsigned long int ALUoutput;
	unsigned long int cond;
	unsigned long int rs;//十进制
	unsigned long int rt;
	unsigned long int rd;
	string OP;
	string RS;
	string RD;
	string RT;
	string SHAMT;
	string FUNCT;
	string IMM;
public:

	EX_MEM() :
		IR(""),///*/*00000000000000000000000000000000*/*/
		OP(""),
		RS(""),
		RD(""),
		RT(""),
		SHAMT(""),
		FUNCT(""),
		IMM(""),
		NPC(0),
		imm(0),
		A(0),
		B(0),
		ALUoutput(0),
		cond(0),
		rs(0),//十进制
		rt(0),
		rd(0)
	{
	}
	~EX_MEM() {}

	void setIR(string ir)//IR
	{
		IR = ir;
	}
	string getIR()
	{
		return IR;
	}

	void setNPC(unsigned long int npc)//NPC
	{
		NPC = npc;

	}
	unsigned long int getNPC()
	{
		return NPC;
	}

	//imm
	void setimm(unsigned long int imm_dec)//imm
	{
		imm = imm_dec;

	}
	unsigned long int getimm()
	{
		return imm;
	}
	//A
	void setA(unsigned long int A_value)
	{
		A = A_value;

	}
	unsigned long int getA()
	{
		return A;
	}

	//B
	void setB(unsigned long int B_value)
	{
		B = B_value;

	}
	unsigned long int getB()
	{
		return B;
	}

	//ALUoutput
	void setALUoutput(unsigned long int value)
	{
		ALUoutput = value;
	}
	unsigned long int getALUoutput()
	{
		return ALUoutput;
	}


	void setcond(bool value)//cond
	{
		cond = value;

	}
	bool getcond()
	{
		return cond;
	}

	void setrs(unsigned long int value)//rs
	{
		rs = value;
	}
	unsigned long int getrs()
	{
		return rs;
	}

	void setrt(unsigned long int value)//rt
	{
		rt = value;
	}
	unsigned long int getrt()
	{
		return rt;
	}

	void setrd(unsigned long int value)//rd
	{
		rd = value;
	}
	unsigned long int getrd()
	{
		return rd;
	}
	void setOP(string s1)//OP
	{
		OP = s1;
	}
	string getOP()
	{
		return OP;
	}

	void setRS(string s1)//RS
	{
		RS = s1;
	}
	string getRS()
	{
		return RS;
	}

	void setRD(string s1)//RD
	{
		RD = s1;
	}
	string getRD()
	{
		return RD;
	}

	void setRT(string s1)//RT
	{
		RT = s1;
	}
	string getRT()
	{
		return RT;
	}

	void setSHAMT(string s1)//SHAMT
	{
		SHAMT = s1;
	}
	string getSHAMT()
	{
		return SHAMT;
	}

	void setFUNCT(string s1)//FUNCT
	{
		FUNCT = s1;
	}
	string getFUNCT()
	{
		return FUNCT;
	}

	void setIMM(string s1)//IMM
	{
		IMM = s1;
	}
	string getIMM()
	{
		return IMM;
	}
};

class MEM_WB
{
private://latch of IF_ID,ID_EX,EX_MEM,MEM_WB.
	string IR;
	unsigned long int NPC;
	unsigned long int imm;
	unsigned long int A;//rs
	unsigned long int B;//rt
	unsigned long int ALUoutput;
	unsigned long int cond;
	unsigned long int LMD;
	unsigned long int rs;//十进制
	unsigned long int rt;
	unsigned long int rd;
	string OP;
	string RS;
	string RD;
	string RT;
	string SHAMT;
	string FUNCT;
	string IMM;
public:
	MEM_WB() :
		IR(""),///*/*00000000000000000000000000000000*/*/
		OP(""),
		RS(""),
		RD(""),
		RT(""),
		SHAMT(""),
		FUNCT(""),
		IMM(""),
		NPC(0),
		imm(0),
		A(0),
		B(0),
		ALUoutput(0),
		cond(0),
		LMD(0),
		rs(0),//十进制
		rt(0),
		rd(0)
	{
	}

	~MEM_WB() {}

	void setIR(string ir)//IR
	{
		IR = ir;
	}
	string getIR()
	{
		return IR;
	}

	void setNPC(unsigned long int npc)//NPC
	{
		NPC = npc;

	}
	unsigned long int getNPC()
	{
		return NPC;
	}

	//imm
	void setimm(unsigned long int imm_dec)//imm
	{
		imm = imm_dec;

	}
	unsigned long int getimm()
	{
		return imm;
	}
	//A
	void setA(unsigned long int A_value)
	{
		A = A_value;

	}
	unsigned long int getA()
	{
		return A;
	}

	//B
	void setB(unsigned long int B_value)
	{
		B = B_value;

	}
	unsigned long int getB()
	{
		return B;
	}

	//ALUoutput
	void setALUoutput(unsigned long int value)
	{
		ALUoutput = value;
	}
	unsigned long int getALUoutput()
	{
		return ALUoutput;
	}

	void setcond(bool value)//cond
	{
		cond = value;

	}
	bool getcond()
	{
		return cond;
	}

	void setLMD(unsigned long int value)//LMD
	{
		LMD = value;
	}
	unsigned long int getLMD()
	{
		return LMD;
	}

	void setrs(unsigned long int value)//rs
	{
		rs = value;
	}
	unsigned long int getrs()
	{
		return rs;
	}

	void setrt(unsigned long int value)//rt
	{
		rt = value;
	}
	unsigned long int getrt()
	{
		return rt;
	}

	void setrd(unsigned long int value)//rd
	{
		rd = value;
	}
	unsigned long int getrd()
	{
		return rd;
	}
	void setOP(string s1)//OP
	{
		OP = s1;
	}
	string getOP()
	{
		return OP;
	}

	void setRS(string s1)//RS
	{
		RS = s1;
	}
	string getRS()
	{
		return RS;
	}

	void setRD(string s1)//RD
	{
		RD = s1;
	}
	string getRD()
	{
		return RD;
	}

	void setRT(string s1)//RT
	{
		RT = s1;
	}
	string getRT()
	{
		return RT;
	}

	void setSHAMT(string s1)//SHAMT
	{
		SHAMT = s1;
	}
	string getSHAMT()
	{
		return SHAMT;
	}

	void setFUNCT(string s1)//FUNCT
	{
		FUNCT = s1;
	}
	string getFUNCT()
	{
		return FUNCT;
	}

	void setIMM(string s1)//IMM
	{
		IMM = s1;
	}
	string getIMM()
	{
		return IMM;
	}
};


//create object
/*static IF_ID if_id;
extern ID_EX id_ex;
extern EX_MEM ex_mem;
extern MEM_WB mem_wb;
*/
IF_ID if_id;
ID_EX id_ex;
EX_MEM ex_mem;
MEM_WB mem_wb;
