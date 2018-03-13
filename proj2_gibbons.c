#include <stdio.h>
#include <string.h>

#define MAX_INSTRS 99
#define NUM_REGS 31

/////////////////////////
// Instruction opcodes //
/////////////////////////
#define ADD 32
#define SUB 34
#define LW 35
#define SW 43
#define SLL 0
#define ANDI 12
#define ORI 13
#define BNE 5
#define HALT 1
#define NOOP 0

/////////////////////
// Data structures //
/////////////////////
int instructions[MAX_INSTRS];
int regFile[NUM_REGS];
int dataMem[NUM_REGS];

typedef struct IFIDStruct {
		int instr;
		int pcPlus4;
} IFID_t;

typedef struct IDEXStruct {
		int instr;
		int pcPlus4;
		int readData1;
		int readData2;
		int rs;
		int rt;
		int rd;
		int branchTarget;
		int immed;
} IDEX_t;

typedef struct EXMEMStruct {
		int instr;
		int aluResult;
		int readData2;
		int writeReg;
} EXMEM_t;

typedef struct MEMWBStruct {
		int instr;
		int writeData;
} MEMWB_t;

typedef struct stateStruct {
		int pc;
		int instrMem[NUM_REGS];
		int dataMem[NUM_REGS];
		int reg[NUM_REGS];
		int numMemory;
		IFID_t IFID;
		IDEX_t IDEX;
		EXMEM_t EXMEM;
		MEMWB_t MEMWB;
		int numCycles;
} state_t;

///////////////////////////
// Function Declarations //
///////////////////////////
void printInstruction(int instr);
void printState(state_t *statePtr);
int rs(int instruction);
int rt(int instruction);
int rd(int instruction);
int opcode(int instruction);

int main() {
		return 0;
}

int rs(int instruction)
{
		return( (instruction >> 19) & 0x7);
}

int rt(int instruction)
{
		return( (instruction >> 16) & 0x7);
}

int rd(int instruction)
{
		return(instruction & 0xFFFF);
}

int opcode(int instruction)
{
		return(instruction >> 22);
}

void printInstruction(int instr) {
		char opcodeString[10];
		if (opcode(instr) == ADD) {
				strcpy(opcodeString, "add");
		} else if (opcode(instr) == SUB) {
				strcpy(opcodeString, "sub");
		} else if (opcode(instr) == LW) {
				strcpy(opcodeString, "lw");
		} else if (opcode(instr) == SW) {
				strcpy(opcodeString, "sw");
		} else if (opcode(instr) == ANDI) {
				strcpy(opcodeString, "andi");
		} else if (opcode(instr) == BNE) {
				strcpy(opcodeString, "bne");
		} else if (opcode(instr) == HALT) {
				strcpy(opcodeString, "halt");
		} else if (opcode(instr) == NOOP) {
				strcpy(opcodeString, "noop");
		} else if (opcode(instr) == ORI) {
				strcpy(opcodeString, "ori");
		} else if (opcode(instr) == SLL) {
				strcpy(opcodeString, "sll");
		} else {
				strcpy(opcodeString, "data");
		}

		printf("%s %d %d %d\n", opcodeString, rs(instr), rt(instr),
		       rd(instr));
}

void printState(state_t *statePtr) {
		int i;
		printf("\n********************\nState at the beginning of cycle %d: \n", statePtr->numCycles);
		printf("\tPC = %d\n", statePtr->pc);

		printf("\tData Memory:\n");
		for (i = 0; i < statePtr->numMemory; i++) {
				printf("\t\tdataMem[%d] %d\n", i, statePtr->dataMem[i]);
		}

		printf("\tRegisters:\n");
		for (i = 0; i < NUM_REGS; i++) {
				printf("\t\tregFile[%d] %d\n", i, statePtr->reg[i]);
		}

		printf("\tIF/ID:\n");
		printf("\t\tInstruction: ");
		printInstruction(statePtr->IFID.instr);
		printf("\t\tpcPlus4: %d\n", statePtr->IFID.pcPlus4);

		printf("\tID/EX:\n");
		printf("\t\tInstruction: ");
		printInstruction(statePtr->IDEX.instr);
		printf("\t\tpcPlus4: %d\n", statePtr->IDEX.pcPlus4);
		printf("\t\tbranchTarget: %d\n", statePtr->IDEX.branchTarget);
		printf("\t\treadData1: %d\n", statePtr->IDEX.readData1);
		printf("\t\treadData2: %d\n", statePtr->IDEX.readData2);
		printf("\t\timmed: %d\n", statePtr->IDEX.immed);
		printf("\t\trs: %d\n", statePtr->IDEX.rs);
		printf("\t\trt: %d\n", statePtr->IDEX.rt);
		printf("\t\trd: %d\n", statePtr->IDEX.rd);

		printf("\tEX/MEM:\n");
		printf("\t\tInstruction: ");
		printInstruction(statePtr->EXMEM.instr);
		printf("\t\taluResult: %d\n", statePtr->EXMEM.aluResult);
		printf("\t\twriteDataReg: %d\n", statePtr->EXMEM.readData2);
		printf("\t\twriteReg: %d\n", statePtr->EXMEM.writeReg);

		printf("\tMEM/WB:\n");
		printf("\t\tInstruction: ");
		printInstruction(statePtr->MEMWB.instr);
		printf("\t\twriteDataMem %d\n", statePtr->MEMWB.writeData);
		printf("\t\twriteDataALU %d\n", statePtr->MEMWB.writeData);
		printf("\t\twriteReg %d\n", statePtr->MEMWB.writeData);
}
