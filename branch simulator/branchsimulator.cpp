#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <bitset>

using namespace std;


int main(int argc, char* argv[]){


   
  
    ifstream config_params;
    int m;
    int miss = 0;
    int total = 0;
    string predict;
    //config_params.open(argv[1]);
    config_params.open("config.txt");
    //C:\Users\Kushu\Desktop\lab3
    while(!config_params.eof())  // read config file
    {
      config_params>>m;
    }
   
    //cout<<m;
  
    int counter[(int)pow(2,m)] ;
   
    for(int i=0; i<((int)pow(2,m));i++)
    {
        counter[i] = 11;
    }
   
    ifstream traces;
    ofstream tracesout;
    string outname;
    //outname = string(argv[2]) + ".out";
   
    traces.open("trace.txt");
    //tracesout.open(outname.c_str());
    tracesout.open("C:\\Users\\Kushu\\Desktop\\lab3\\trace.txt.out");
   
    string line;
    string result;  // the Read/Write access type from the memory trace;
    string xaddr;       // the address from the memory trace store in hex;
    unsigned int addr;  // the address from the memory trace store in unsigned int;       
    bitset<32> accessaddr; // the address from the memory trace store in the bitset;
   
    if (traces.is_open() && tracesout.is_open()){   
        while (getline (traces,line)){   // read mem access file and access Cache
           
            istringstream iss(line);
            if (!(iss >> xaddr >> result)) {cout<<"abcd";break;}
            stringstream saddr(xaddr);
            saddr >> std::hex >> addr;
            accessaddr = bitset<32> (addr);
          
           //------------
            string addr_string = accessaddr.to_string();
            bitset <32> address (addr_string.substr(32-m,m));
          
            if(counter[address.to_ulong()] == 11 || counter[address.to_ulong()] == 10)
            {
                predict = '1';
                //tracesout<<"T"<< endl;
                tracesout<<predict<< endl;
            }
            else
            {
                predict = '0';
                //tracesout<<"NT"<< endl;
                tracesout<<predict<< endl;
            }
           
           
            if(result == "1")
            {
                if(counter[address.to_ulong()] == 10)
                {
                    counter[address.to_ulong()] = 11;
                }
                if(counter[address.to_ulong()] == 01)
                {
                    counter[address.to_ulong()] = 11;
                }
                if(counter[address.to_ulong()] == 00)
                {
                    counter[address.to_ulong()] = 01;
                }
            }
            else
            {
                if(counter[address.to_ulong()] == 11)
                {
                    counter[address.to_ulong()] = 10;
                }
                if(counter[address.to_ulong()] == 10)
                {
                    counter[address.to_ulong()] = 00;
                }
                if(counter[address.to_ulong()] == 01)
                {
                    counter[address.to_ulong()] = 00;
                }
            }
           
            if(predict != result)
            {
                miss++;
            }
            total++;
           
           //------------
           
            //tracesout<< xaddr << " " << result << endl; 
            
        }
        traces.close();
        tracesout.close();
        cout<<miss<<"---"<<total<<endl;
        double x = (double)miss/(double)total*100;
        cout<<"rate:"<<x;
    }
    else cout<< "Unable to open trace or traceout file ";
  
    return 0;
}