	/* 

	The project is developed as part of Computer Architecture class
	Project Name: Functional Simulator for subset of ARM Processor

	Developer's Name: Kaustav Vats, Shravika Mittal, Meghna Gupta.

	*/
	#include <stdio.h>
	#include <stdlib.h>

	// Registers
	static int R[16];
	// Register[15] = PC
	// Instructions Memory
	static char MEM[4000];

	// Intermediate Datapath.
	static unsigned int rn;
	static unsigned int op2;
	static unsigned int inst;
	static unsigned int rd;
	static unsigned int immediate;
	static int Instruction_Type;
	static unsigned int opcode;
	static int Binary[32];

	void reset_proc();
	void load_program_memory(char *file_name);
	int read_word(char *mem, unsigned int address);
	void Run_ARMSim();
	void Fetch();
	void Decode();
	void Execute();
	void Memory();
	void Write_Back();
	void swi_exit();
	void write_word(char *mem, unsigned int address, unsigned int data);
	void write_data_memory();
	int read_word(char *mem, unsigned int address);


	int main()
	{
		reset_proc();
		load_program_memory("input.mem");
		Run_ARMSim();
		return 0;
	}
	// Resets all Arrays & Variables to 0.
	void reset_proc() 
	{
		for ( int i=0; i<16; i++ )
		{
			R[i] = 0;
		}
		for ( int i=0; i<4000; i++ )
		{
			MEM[i] = '0';
		}
		for ( int i=0; i<32; i++ ) 
		{
			Binary[i] = 0;
		}
		rn = 0;
		op2 = 0;
		Instruction_Type = -1;
	}
	void Run_ARMSim()
	{
		while( 1 )
		{
			Fetch();
			Decode();
			Execute();
			Memory();
			Write_Back();
		}
	}
	void Fetch()
	{
		inst = read_word(MEM, R[15]);
		printf("Fetch: Instruction 0x%x from Address 0x%x\n", inst, R[15]);
		R[15] = R[15] + 4;
	}
	void Decode()
	{
		unsigned int a = (inst>>26);
	  a = (a<<30);
		a = (a>>30);
	  unsigned int f = a ;
	  unsigned int cond = (inst>>28); // check
	  if(f==0)
	  {
	    unsigned int b = (inst<<6);
	    immediate = (b>>31);
	    unsigned int c = (inst<<7);
	    opcode = (c>>28);
	    rn = (inst>>16)&(0xF);
			unsigned int e = (inst<<16);
			rd = (e>>28);
	    if(immediate == 0)
	    {
	      op2 = ((inst)&(0xF));
	      switch(opcode)
	      {
	        case 4:
	          printf("DECODE: Operation is ADD, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	        case 2:
	          printf("DECODE: Operation is SUB, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	        case 1:
	          printf("DECODE: Operation is XOR, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	        case 15:
	          printf("DECODE: Operation is MNV, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	        case 13:
	          printf("DECODE: Operation is MOV, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	        case 10:
	          printf("DECODE: Operation is CMP, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	        case 5:
	          printf("DECODE: Operation is ADC, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	        case 12:
	          printf("DECODE: Operation is ORR, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	        case 0:
	          printf("DECODE: Operation is AND, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	        case 3:
	          printf("DECODE: Operation is RSB, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	        case 6:
	          printf("DECODE: Operation is SBC, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	        case 7:
	          printf("DECODE: Operation is SRC, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	        case 14:
	          printf("DECODE: Operation is BIC, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", rn, op2, rd, rn, R[rn], op2, R[op2]);
	          break;
	      }
	  }
	      else if(immediate == 1)
	      {
	        op2 = ((inst)&(0xFF));
	        switch(opcode)
	        {
	          case 4:
	            printf("DECODE: Operation is ADD, First Operand is R%d, (immediate) second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	          case 2:
	            printf("DECODE: Operation is SUB, First Operand is R%d, (immediate) second  Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	          case 1:
	            printf("DECODE: Operation is XOR, First Operand is R%d, (immediate) second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	          case 15:
	            printf("DECODE: Operation is MNV, First Operand is R%d, (immediate) second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	          case 13:
	            printf("DECODE: Operation is MOV, First Operand is R%d, (immediate) second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	          case 10:
	            printf("DECODE: Operation is CMP, First Operand is R%d, (immediate) second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	          case 5:
	            printf("DECODE: Operation is ADC, First Operand is R%d, (immediate) second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	          case 12:
	            printf("DECODE: Operation is ORR, First Operand is R%d, (immediate) second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	          case 0:
	            printf("DECODE: Operation is AND, First Operand is R%d, (immediate) second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	          case 3:
	            printf("DECODE: Operation is RSB, First Operand is R%d, (immediate) second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	          case 6:
	            printf("DECODE: Operation is SBC, First Operand is R%d, (immediate) Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	          case 7:
	            printf("DECODE: Operation is SRC, First Operand is R%d, (immediate) Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	          case 14:
	            printf("DECODE: Operation is BIC, First Operand is R%d, (immediate) Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d\n", rn, op2, rd, rn, R[rn]);
	            break;
	        }
	      }
	    }

		// ldr str - Data Transfer
	  else if(f==1)
	  {
			unsigned int a = (inst<<6);
			opcode = (a>>26);
			if(opcode == 25)
			{
				rn = (inst>>16)&(0xF);
				unsigned int e = (inst<<16);
				rd = (e>>28);
				op2 = ((inst)&(0xFFF));
				printf("DECODE: Operation is LDR, Base Register is R%d, Offset is %d, Destination Register is R%d\n",rn, op2, rd);
			}
			else if(opcode == 24)
			{
				rn = (inst>>16)&(0xF);
				unsigned int e = (inst<<16);
				rd = (e>>28);
				op2 = ((inst)&(0xFFF));
				printf("DECODE: Operation is STR, Base Register is R%d, Offset is %d, Destination Register is R%d\n",rn, op2, rd);
			}
	  }

		// branch
	  else if(f==2)
	  {
			unsigned int a = (inst<<6);
			opcode = (a>>30);
			offset = (inst&(0xFFFFFF));
			if(opcode == 2)
			{
				switch (cond) {
					case 0:
						printf("DECODE: Operation is Branch Equals\n");
						break;
					case 13:
						printf("DECODE: Operation is Branch less than Equals\n");
						break;
					case 10:
						printf("DECODE: Operation is Branch greater than Equals\n");
						break;
					case 1:
						printf("DECODE: Operation is Branch Not Equals\n");
						break;
					case 14:
						printf("DECODE: Operation is Branch and Link\n");
						break;
					case 12:
						printf("DECODE: Operation is Branch Greater Than\n");
						break;
					case 11:
						printf("DECODE: Operation is Branch Less Than\n");
						break;
				}
			}
	  }
	}
	void Execute()
	{

	}
	void Memory()
	{

	}
	void Write_Back()
	{

	}
	void swi_exit() 
	{
	  	write_data_memory();
	  	exit(0);
	}
	void load_program_memory(char *file_name) 
	{
		FILE *fp;
	  	unsigned int address, instruction;
	  	fp = fopen(file_name, "r");
	  	if(fp == NULL) 
	  	{
	    	printf("Error opening input mem file\n");
	    	exit(1);
	  	}
	  	while(fscanf(fp, "%x %x", &address, &instruction) != EOF) 
	  	{
	    	write_word(MEM, address, instruction);
	  	}
	  	fclose(fp);
	}
	void write_word(char *mem, unsigned int address, unsigned int data) 
	{
	  	int *data_p;
	  	data_p = (int*) (mem + address);
	  	*data_p = data;
	}

	//writes the data memory in "data_out.mem" file
	void write_data_memory() 
	{
	  	FILE *fp;
	  	unsigned int i;
	  	fp = fopen("data_out.mem", "w");
	  	if(fp == NULL) 
	  	{
	    	printf("Error opening dataout.mem file for writing\n");
	    	return;
	  	}
	  
	  	for(i=0; i < 4000; i = i+4)
	  	{
	    	fprintf(fp, "%x %x\n", i, read_word(MEM, i));
	  	}
	  	fclose(fp);
	}
	int read_word(char *mem, unsigned int address) 
	{
	  	int *data;
	  	data =  (int*) (mem + address);
	  	return *data;
	}
