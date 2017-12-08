#include<iostream>
#include<string>
#include<vector>
#include<bitset>
#include<fstream>
using namespace std;
#define ADDU 1
#define SUBU 3
#define AND 4
#define OR  5
#define NOR 7
#define MemSize 65536 // memory size, in reality, the memory size should be 2^32, but for this lab, for the space resaon, we keep it as this large number, but the memory is still 32-bit addressable.


class RF
{
    public:
        bitset<32> ReadData1, ReadData2; 
     	RF()
    	{ 
          Registers.resize(32);  
          Registers[0] = bitset<32> (0);  
        }
	
        void ReadWrite(bitset<5> RdReg1, bitset<5> RdReg2, bitset<5> WrtReg, bitset<32> WrtData, bitset<1> WrtEnable)
        {   
            // implement the funciton by you.
            if(WrtEnable.to_string() == "0")
            {
                ReadData1 = Registers[RdReg1.to_ulong()];
                ReadData2 = Registers[RdReg2.to_ulong()];
            }
            
            if(WrtEnable.to_string() == "1")
            {
                Registers[WrtReg.to_ulong()] = WrtData;
                //cout<<"wrtreg--"<<Registers[WrtReg.to_ulong()]<<"--";
            }
         }
		 
	void OutputRF()
             {
               ofstream rfout;
                  rfout.open("RFresult.txt",std::ios_base::app);
                  if (rfout.is_open())
                  {
                    rfout<<"A state of RF:"<<endl;
                  for (int j = 0; j<32; j++)
                      {        
                        rfout << Registers[j]<<endl;
                      }
                     
                  }
                  else cout<<"Unable to open file";
                  rfout.close();
               
               }     
	private:
            vector<bitset<32> >Registers;
	
};

class ALU
{
      public:
             bitset<32> ALUresult;
             bitset<32> ALUOperation (bitset<3> ALUOP, bitset<32> oprand1, bitset<32> oprand2)
             {   
                 // implement the ALU operations by you.
                 
                 // ADDU
                 if(ALUOP.to_string() == "001")
                 {
                     ALUresult = bitset<32>(oprand1.to_ulong() + oprand2.to_ulong());
                 }
                 
                 // SUBU
                 if(ALUOP.to_string() == "011")
                 {
                     ALUresult = bitset<32>(oprand1.to_ulong() - oprand2.to_ulong());
                 }
                 
                 // AND
                 if(ALUOP.to_string() == "100")
                 {
                     ALUresult = oprand1 & oprand2;
                 }
                 
                 // OR
                 if(ALUOP.to_string() == "101")
                 {
                     ALUresult = oprand1 | oprand2;
                 }
                 
                 // NOR
                 if(ALUOP.to_string() == "111")
                 {
                     ALUresult = ~(oprand1 | oprand2);
                 }
                 
                 return ALUresult;
               }            
};

class INSMem
{
      public:
          bitset<32> Instruction;
          INSMem()
          {       IMem.resize(MemSize); 
                  ifstream imem;
                  string line;
                  int i=0;
                  imem.open("C:\\Users\\Desktop\\imem.txt");
                  if (imem.is_open())
                  {
                  while (getline(imem,line))
                     {      
                        IMem[i] = bitset<8>(line);
                        i++;
                     }
                     
                  }
                  else cout<<"Unable to open file";
                  imem.close();
                     
                  }
                  
          bitset<32> ReadMemory (bitset<32> ReadAddress) 
              { 
              
//              for(int i=0;IMem[i]!=NULL;i++)
//              {
//                  cout<<IMem[i];
//              }
              
              string temp_instruction = "";
               // implement by you. (Read the byte at the ReadAddress and the following three byte).
               int instruction_line = ReadAddress.to_ulong();
               for(int i = instruction_line;i < instruction_line + 4;i++)
               {
                   temp_instruction = temp_instruction + IMem[i].to_string();
               }
               //cout<<"xx"<<temp_instruction<<"xx";
               
               bitset<32> Instruction (temp_instruction);
               //return temp_instruction;
               return Instruction;     
              }     
      
      private:
           vector<bitset<8> > IMem;
      
};
      
class DataMem    
{
      public:
          bitset<32> readdata;  
          DataMem()
          {
             DMem.resize(MemSize); 
             ifstream dmem;
                  string line;
                  int i=0;
                  dmem.open("C:\\Users\\Desktop\\dmem.txt");
                  if (dmem.is_open())
                  {
                  while (getline(dmem,line))
                       {      
                        DMem[i] = bitset<8>(line);
                        i++;
                       }
                  }
                  else cout<<"Unable to open file";
                  dmem.close();
          
          }  
          bitset<32> MemoryAccess (bitset<32> Address, bitset<32> WriteData, bitset<1> readmem, bitset<1> writemem) 
          {    
              if(readmem.to_ulong() == 1 && writemem.to_ulong() == 0)
              {
                  string temp_data = "";
                  int data_line = Address.to_ulong();
                  for(int i = data_line;i < data_line + 4; i++)
                  {
                    temp_data = temp_data + DMem[i].to_string();
                  }
                  bitset<32> readdata (temp_data);
                  cout<<"\n"<<readdata<<"\n";
                  
             
               // implement by you.
               return readdata;     
              }
              
              if(readmem.to_ulong() == 0 && writemem.to_ulong() == 1)
              {
                
                  bitset<8> DMem_write[MemSize];
                  
//                  for(int i = 0;DMem[i]!="";i++)
//                  {
//                      DMem_write[i] = DMem[i];
//                  }
                  int i=0;
                  while(DMem[i]!=NULL)
                  {
                      DMem_write[i] = DMem[i];
                      i++;
                  }
                  
                  ofstream outfile;
                  string Write_Data = WriteData.to_string();
                  outfile.open("C:\\Users\\Desktop\\dmem.txt", std::ios_base::out);
                  //outfile << bitset<8> (Write_Data.substr(0,8)); 
                  //outfile << bitset<8> (Write_Data.substr(8,8)); 
                  //outfile << bitset<8> (Write_Data.substr(16,8)); 
                  //outfile << bitset<8> (Write_Data.substr(24,8)); 
                  int address_int = Address.to_ulong();
                  DMem_write[address_int] =bitset<8> (Write_Data.substr(0,8));
                  DMem_write[address_int + 1] =bitset<8> (Write_Data.substr(8,8));
                  DMem_write[address_int + 2] =bitset<8> (Write_Data.substr(16,8)); 
                  DMem_write[address_int + 3] =bitset<8> (Write_Data.substr(24,8));
                  
                  if(outfile.is_open())
                    {
//                        for(int i = 0; DMem_write[i]!= ""; i++)
//                        {
//                            outfile<<DMem_write[i]<<endl;
//                        }
                      i=0;
                      while(DMem_write[i].to_ulong())
                      {
                          if(DMem_write[i].to_string() == ""){break;}
                          outfile<<DMem_write[i]<<endl;
                          //cout<<"\n";
                          i++;
                      }
                      
                    }
                    else
                    {
                        cout<<"Unable to open file for writing";
                    }
//                  int data_line = Address.to_ulong();
//                  
//                  DMem[data_line] = bitset<8> R1 (WriteData.substr(0,8));
//                  DMem[data_line + 1] = bitset<8> R2 (WriteData.substr(8,8));
//                  DMem[data_line + 2] = bitset<8> R3 (WriteData.substr(16,8));
//                  DMem[data_line + 3] = bitset<8> R4 (WriteData.substr(24,8));
               
               return 0;     
              }
              
          }   
                     
          void OutputDataMem()
          {
               ofstream dmemout;
                  dmemout.open("dmemresult.txt");
                  if (dmemout.is_open())
                  {
                  for (int j = 0; j< 1000; j++)
                       {     
                        dmemout << DMem[j]<<endl;
                       }
                     
                  }
                  else cout<<"Unable to open file";
                  dmemout.close();
               
               }             
      
      private:
           vector<bitset<8> > DMem;
      
};  

int main() {
    RF myRF;
    ALU myALU;
    INSMem myInsMem;
    DataMem myDataMem;
    int instruction_number = 0;
    bitset<32> PC = 00000000000000000000000000000000;
    //bitset<32> counter = 00000000000000000000000000000100;
    bitset<32> Instruction_bits;
    string instruction;
    string line;
    string inst[40];
    bitset<32> Result;

    while (1) {
        
        cout<<"\n";
        Instruction_bits = myInsMem.ReadMemory(PC);
        instruction = Instruction_bits.to_string();
     
        if (instruction == "11111111111111111111111111111111") {
            cout << "break" << endl;
            break;
        } else {
            string op_type = instruction.substr(0, 6);
            //cout << "\nxx" << op_type << "xx\n";

            if (op_type == "000000") {
                //cout << "r-type";
                string func_type = instruction.substr(29, 3);
                
                bitset<5> RS (instruction.substr(6,5));
                bitset<5> RT (instruction.substr(11,5));
                bitset<5> RD (instruction.substr(16,5));
   
                //cout << "\n" << func_type << "\n";
                
                bitset<3> funct (func_type);
                int function_int = funct.to_ulong();
                
                switch(function_int)
                {
                    case 1:
                    {
                        cout<<"addu";
                        myRF.ReadWrite(RS,RT,0,0,0);
                        Result = myALU.ALUOperation(001,myRF.ReadData1,myRF.ReadData2);
                        myRF.ReadWrite(0,0,RD,Result,1); 
                        PC = bitset<32> (PC.to_ulong()+4);
                        break;
                    }
                    case 3:
                    {
                        cout<<"subu";
                        myRF.ReadWrite(RS,RT,0,0,0);
                        Result = myALU.ALUOperation(011,myRF.ReadData1,myRF.ReadData2);
                        myRF.ReadWrite(0,0,RD,Result,1);
                        PC = bitset<32> (PC.to_ulong()+4);
                        break;
                    }
                    case 4:
                    {
                        cout<<"and";
                        myRF.ReadWrite(RS,RT,0,0,0);
                        Result = myALU.ALUOperation(100,myRF.ReadData1,myRF.ReadData2);
                        myRF.ReadWrite(0,0,RD,Result,1);
                        PC = bitset<32> (PC.to_ulong()+4);
                        break;
                    }
                    case 5:
                    {
                        cout<<"or";
                        myRF.ReadWrite(RS,RT,0,0,0);
                        Result = myALU.ALUOperation(101,myRF.ReadData1,myRF.ReadData2);
                        myRF.ReadWrite(0,0,RD,Result,1);
                        PC = bitset<32> (PC.to_ulong()+4);
                        break;
                    }
                    case 7:
                    {
                        cout<<"nor";
                        myRF.ReadWrite(RS,RT,0,0,0);
                        Result = myALU.ALUOperation(111,myRF.ReadData1,myRF.ReadData2);
                        myRF.ReadWrite(0,0,RD,Result,1);
                        PC = bitset<32> (PC.to_ulong()+4);
                        break;
                    }
                }

            }
            
            else if(op_type == "100011")
            {
                cout<<"lw";
                                
                bitset<5> RS (instruction.substr(6,5));
                bitset<5> RT (instruction.substr(11,5));
                bitset<32> IMM (instruction.substr(16,16));
                bitset<3> add (string("001"));
                
                //int RS_int = RS.to_ulong();

                myRF.ReadWrite(RS,RS,0,0,0);

                bitset<32> final_address = myALU.ALUOperation(add,myRF.ReadData1,IMM);

                bitset<32> read_data_mem = myDataMem.MemoryAccess(final_address,0,1,0);
                
                myRF.ReadWrite(0,0,RT,read_data_mem,1);
                PC = bitset<32> (PC.to_ulong()+4);
            }
            else if(op_type == "101011")
            {
                cout<<"sw";
                                
                bitset<5> RS (instruction.substr(6,5));
                bitset<5> RT (instruction.substr(11,5));
                bitset<32> IMM (instruction.substr(16,16));
                //bitset<3> add (string("001"));
                
                //int RS_int = RS.to_ulong();

                myRF.ReadWrite(RS,RT,0,0,0);

                bitset<32> final_address = myALU.ALUOperation(001,myRF.ReadData1,IMM);

                //myRF.ReadWrite(0,0,RT,read_data_mem,1);
                
                bitset<32> write_data_mem = myDataMem.MemoryAccess(final_address,myRF.ReadData2,0,1);
                PC = bitset<32> (PC.to_ulong()+4); 
            }
            else if(op_type == "001001")
            {
                cout<<"addiu";
                bitset<5> RS (instruction.substr(6,5));
                bitset<5> RT (instruction.substr(11,5));
                bitset<32> IMM (instruction.substr(16,16));
                
                myRF.ReadWrite(RS,0,0,0,0);
                
                bitset<32> final_sum = myALU.ALUOperation(001,myRF.ReadData1,IMM);
                
                myRF.ReadWrite(0,0,RT,final_sum,1);
                PC = bitset<32> (PC.to_ulong()+4);
            }
            else if(op_type == "000100")
            {
                cout<<"beq";
                bitset<5> RS (instruction.substr(6,5));
                bitset<5> RT (instruction.substr(11,5));
                bitset<32> IMM (instruction.substr(16,16));
                
                myRF.ReadWrite(RS,RT,0,0,0);
                
                if(myRF.ReadData1 == myRF.ReadData2)
                {
                    IMM<<2;
                    PC = myALU.ALUOperation(001,PC,IMM);
                    PC = bitset<32> (PC.to_ulong()+4); 
                }
                else
                {
                    PC = bitset<32> (PC.to_ulong()+4);
                }
                
                
            }
            else if(op_type == "000010")
            {
                cout<<"jm";
                string PC_string = PC.to_string();
                //bitset<5> PC_MSB (PC_string.substr(0,6));
                bitset<32> IMM (instruction.substr(6,26));
                string jump_address = PC_string.substr(0,6) + IMM.to_string();
                
                PC = bitset<32> (jump_address);
            }
            else{}
            

        }

        instruction_number++;

        //PC = bitset<32> (PC.to_ulong()+4);
      
        // If current insturciton is "11111111111111111111111111111111", then break;

        // decode(Read RF)

        // Execute

        // Read/Write Mem

        // Write back to RF

        myRF.OutputRF(); // dump RF;    
    }
    myDataMem.OutputDataMem(); // dump data mem

    return 0;

}
