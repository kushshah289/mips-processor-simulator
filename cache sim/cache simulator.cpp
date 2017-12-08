/*
Cache Simulator
Level one L1 and level two L2 cache parameters are read from file (block size, line per set and set per cache).
The 32 bit address is divided into tag bits (t), set index bits (s) and block offset bits (b)
s = log2(#sets)   b = log2(block size)  t=32-s-b
*/
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
//access state:
#define NA 0 // no action
#define RH 1 // read hit
#define RM 2 // read miss
#define WH 3 // Write hit
#define WM 4 // write miss




struct config{
       int L1blocksize;
       int L1setsize;
       int L1size;
       int L2blocksize;
       int L2setsize;
       int L2size;
      
       int L1_way;
       int L2_way;
       int full_way;
       int full_way2;
       };

/* you can define the cache class here, or design your own data structure for L1 and L2 cache
class cache {
     
      }
*/      
      
       class cache{
          
       public:
           int init(int L1blocksize, int L1setsize, int L1size, int L2blocksize, int L2setsize, int L2size){

               cout << "init";
               cout << L1blocksize << endl;
               cout << L1setsize << endl;
               cout << L1size << endl;
               cout << L2blocksize << endl;
               cout << L2setsize << endl;
               cout << L2size << endl;
               //return 0;
              
             
           }
          
          
          
       };
      
    
      
int main(int argc, char* argv[]){

   
    cache newcache;
    //string cache_params = "";
    config cacheconfig;
    ifstream cache_params;
    string dummyLine;
    cache_params.open(argv[1]);
    while(!cache_params.eof())  // read config file
    {
//        if ( ! cache_params.is_open() ) {                
//            cout <<" Failed to open" << endl;
//        }
//        else {
//            cout <<"Opened OK" << endl;
//        }
      cache_params>>dummyLine;
      cache_params>>cacheconfig.L1blocksize;
      cache_params>>cacheconfig.L1setsize;             
      cache_params>>cacheconfig.L1size;
      cache_params>>dummyLine;             
      cache_params>>cacheconfig.L2blocksize;          
      cache_params>>cacheconfig.L2setsize;       
      cache_params>>cacheconfig.L2size;
     
      }
    //cout << "qwe";
   
    //newcache.init(7,7,7,7,7,7);
   
    newcache.init(cacheconfig.L1blocksize, cacheconfig.L1setsize, cacheconfig.L1size, cacheconfig.L2blocksize, cacheconfig.L2setsize, cacheconfig.L2size);
  
   //---------------------------------------------------------------------------
               int L1_blocksize = log2(cacheconfig.L1blocksize);
               //int L1_setsize = log2(cacheconfig.L1setsize);
               int L1_setsize = (cacheconfig.L1setsize!=0)?(log2(cacheconfig.L1setsize)):(0);
               int L1_size = log2(cacheconfig.L1size);
               int L2_blocksize = log2(cacheconfig.L2blocksize);
               //int L2_setsize = log2(cacheconfig.L2setsize);
               int L2_setsize = (cacheconfig.L2setsize!=0)?(log2(cacheconfig.L2setsize)):(0);
               int L2_size = log2(cacheconfig.L2size);
              
//               cout << log2(L1blocksize) << endl;
//               cout << log2(L1setsize) << endl;
//               cout << log2(L1size) << endl;
//               cout << log2(L2blocksize) << endl;
//               cout << log2(L2setsize) << endl;
//               cout << log2(L2size) << endl;
              
               int L1_block_bits = log2(cacheconfig.L1blocksize);
               int L1_array_size = log2(cacheconfig.L1size) + 10 - L1_block_bits;
               int L1_index_bits = log2(cacheconfig.L1size) + 10 - L1_block_bits - L1_setsize;
               int L1_tag_bits = 32 - L1_block_bits - L1_index_bits;
               int L1_assoc = log2(cacheconfig.L1setsize);
              
               cout << "L1::::bb:"<<L1_block_bits<<"--ib:"<<L1_index_bits<<"--tb:"<<L1_tag_bits<<"--ar:"<<L1_array_size<<endl;
              
               unsigned long L1_tag_array[(int)pow(2,L1_array_size)];
               unsigned long L1_valid_array[(int)pow(2,L1_array_size)];
               
               //int L1_valid_array[2^L1_index_bits][2^L1_block_bits] = {0};
               //int L1_dirty_array[2^L1_index_bits][2^L1_block_bits] = {0};
              
               int L2_block_bits = log2(cacheconfig.L2blocksize);
               int L2_array_size = log2(cacheconfig.L2size) + 10 - L2_block_bits;
               int L2_index_bits = log2(cacheconfig.L2size) + 10 - L2_block_bits - L2_setsize;
               int L2_tag_bits = 32 - L2_block_bits - L2_index_bits;
               int L2_assoc = log2(cacheconfig.L2setsize);
              
               cout << "L2::::bb:"<<L2_block_bits<<"--ib:"<<L2_index_bits<<"--tb:"<<L2_tag_bits<<"--ar:"<<L2_array_size<<endl;
              
               unsigned long L2_tag_array[(int)pow(2,L2_array_size)];
               unsigned long L2_valid_array[(int)pow(2,L2_array_size)];
               //int L2_valid_array[2^L2_index_bits][2^L2_block_bits] = {0};
               //int L2_dirty_array[2^L2_index_bits][2^L2_block_bits] = {0};
               
               
   //---------------------------------------------------------------------------
   // Implement by you:
   // initialize the hirearch cache system with those configs
   // probably you may define a Cache class for L1 and L2, or any data structure you like
  
  
  
  
  //int L1AcceState =0; // L1 access state variable, can be one of NA, RH, RM, WH, WM;
  //int L2AcceState =0; // L2 access state variable, can be one of NA, RH, RM, WH, WM;
  
  
    ifstream traces;
    ofstream tracesout;
    string outname;
    outname = "traceout.out";
   
    traces.open(argv[2]);
    //traces.open("C:\\Users\\Kushu\\Desktop\\trace.txt");
    tracesout.open(outname.c_str());
   
    string line;
    string accesstype;  // the Read/Write access type from the memory trace;
    string xaddr;       // the address from the memory trace store in hex;
    unsigned int addr;  // the address from the memory trace store in unsigned int;       
    bitset<32> accessaddr; // the address from the memory trace store in the bitset;
    cacheconfig.L1_way = 0;
    cacheconfig.L2_way = 0;
    cacheconfig.full_way = 0;
    cacheconfig.full_way2 = 0;
   
   
    if (traces.is_open()&&tracesout.is_open()){   
        while (getline (traces,line)){   // read mem access file and access Cache
           
           
           
            istringstream iss(line);
            if (!(iss >> accesstype >> xaddr)) {break;}
            stringstream saddr(xaddr);
            saddr >> std::hex >> addr;
            accessaddr = bitset<32> (addr);
            string addr_string = accessaddr.to_string();
          
            cout << accessaddr << endl; 
            bitset <32> L1_index (addr_string.substr(L1_tag_bits, L1_index_bits));
            bitset <32> L1_tag (addr_string.substr(0, L1_tag_bits));
            bitset <32> L1_offset (addr_string.substr(L1_tag_bits + L1_index_bits, L1_block_bits ));
           
            bitset <32> L2_index (addr_string.substr(L2_tag_bits, L2_index_bits));
            bitset <32> L2_tag (addr_string.substr(0, L2_tag_bits));
            bitset <32> L2_offset (addr_string.substr(L2_tag_bits + L2_index_bits, L2_block_bits ));
           
            //cout << L1_index << endl;           
            int L1AcceState =0; // L1 access state variable, can be one of NA, RH, RM, WH, WM;
            int L2AcceState =0; // L2 access state variable, can be one of NA, RH, RM, WH, WM;
           //access the L1 and L2 Cache according to the trace;
//            cout<<endl;
//            cout<<L1_tag<<endl;
//            cout<<L1_index<<endl;
//            cout<<L1_offset<<endl;
            //cout<<"--"<<L1_tag.to_ulong();
            //if(cacheconfig.L1_way == cacheconfig.L1setsize)
            //{
            //    cacheconfig.L1_way = 0;
            //}
            //if(cacheconfig.L2_way == cacheconfig.L2setsize)
            //{
            //    cacheconfig.L2_way = 0;
            //}
             if (accesstype.compare("R")==0)
             {   
                 //Implement by you:
                 // read access to the L1 Cache,
                 //  and then L2 (if required),
                 //  update the L1 and L2 access state variable;
                 
                 if(cacheconfig.L1setsize!=0)
                 {
                 for(int i=0; i<cacheconfig.L1setsize;i++)
                    { 
                     if(L1_tag_array[L1_index.to_ulong() + i*((int)pow(2,L1_array_size)/cacheconfig.L1setsize) ] == L1_tag.to_ulong() && L1_valid_array[L1_index.to_ulong() + i*((int)pow(2,L1_array_size)/cacheconfig.L1setsize) ] == 1)
                      {
                        L1AcceState = 1;
                        L2AcceState = 0;
                        break;
                      }
                     else
                      {
                        L1AcceState = 2;
                      }
                    }
                
                
                 if(L1AcceState == 2)
                 {
                   for(int i=0; i<cacheconfig.L2setsize;i++)
                    { 
                     if(L2_tag_array[L2_index.to_ulong() + i*((int)pow(2,L2_array_size)/cacheconfig.L2setsize) ] == L2_tag.to_ulong() && L2_valid_array[L2_index.to_ulong() + i*((int)pow(2,L2_array_size)/cacheconfig.L2setsize) ] == 1)
                      {
                        L2AcceState = 1;
                        break;
                      }
                     else
                      {
                        L2AcceState = 2;
                      }
                    }
                 }
                
                                     //--
                    if (L2AcceState == 1)
                    {
                        //cout<<L2AcceState;
                       
                        L1_tag_array[L1_index.to_ulong() + (cacheconfig.L1_way * ((int)pow(2,L1_array_size) / cacheconfig.L1setsize)) ] = L1_tag.to_ulong();
                        L1_valid_array[L1_index.to_ulong() + (cacheconfig.L1_way * ((int)pow(2,L1_array_size) / cacheconfig.L1setsize)) ] = 1;
                        cacheconfig.L1_way++;
                        
                        if(cacheconfig.L1_way == cacheconfig.L1setsize)
                        {
                            cacheconfig.L1_way = 0;
                        }
            
                                    //cout<<L1_index.to_ulong()<<"--"<<L1_offset.to_ulong()<<"--"<<L1_tag_array[L1_index.to_ulong() + (j * ((2^L1_index_bits) / cacheconfig.L1setsize)) ];
                            
                    }   
                    if (L2AcceState == 2)
                    {
                       
                        L1_tag_array[L1_index.to_ulong() + (cacheconfig.L1_way * ((int)pow(2,L1_array_size) / cacheconfig.L1setsize)) ] = L1_tag.to_ulong();
                        L1_valid_array[L1_index.to_ulong() + (cacheconfig.L1_way * ((int)pow(2,L1_array_size) / cacheconfig.L1setsize)) ] = 1;
                        cacheconfig.L1_way++;       
                                //cout<<L1_index.to_ulong()+ (i * ((2^L1_index_bits) / cacheconfig.L1setsize))<<"--"<<L1_offset.to_ulong()<<"--"<<L1_tag_array[L1_index.to_ulong() + (i * ((2^L1_index_bits) / cacheconfig.L1setsize)) ];
                              
                        if(cacheconfig.L1_way == cacheconfig.L1setsize)
                        {
                            cacheconfig.L1_way = 0;
                        }

                       
                        L2_tag_array[L2_index.to_ulong() + (cacheconfig.L2_way * ((int)pow(2,L2_array_size) / cacheconfig.L2setsize)) ] = L2_tag.to_ulong();
                        L2_valid_array[L2_index.to_ulong() + (cacheconfig.L2_way * ((int)pow(2,L2_array_size) / cacheconfig.L2setsize)) ] = 1;
                        cacheconfig.L2_way++;       
                                //cout<<L2_index.to_ulong()<<"--"<<L2_offset.to_ulong()<<"--"<<L2_tag_array[L2_index.to_ulong() + (i * ((2^L2_index_bits) / cacheconfig.L1setsize)) ];
                        if(cacheconfig.L2_way == cacheconfig.L2setsize)
                        {
                            cacheconfig.L2_way = 0;
                        }        
                        
                    }
                 }
                 //fully assoc
                 if(cacheconfig.L1setsize==0)
                 {
                     for(int i=0;i<(int)pow(2,L1_array_size);i++)
                     {
                         if(L1_tag_array[i] == L1_tag.to_ulong())
                         {
                            L1AcceState = 1;
                            //L2AcceState = 0;
                            break;
                         }
                         else
                         {
                             L1AcceState = 2;
                         }
                     }
                     
                     if(L1AcceState == 2)
                     {
                       for(int i=0; i<cacheconfig.L2setsize;i++)
                        { 
                         if(L2_tag_array[L2_index.to_ulong() + i*((int)pow(2,L2_array_size)/cacheconfig.L2setsize) ] == L2_tag.to_ulong() && L2_valid_array[L2_index.to_ulong() + i*((int)pow(2,L2_array_size)/cacheconfig.L2setsize) ] == 1)
                          {
                            L2AcceState = 1;
                            break;
                          }
                         else
                          {
                            L2AcceState = 2;
                          }
                        }
                     }
                     
                     if (L2AcceState == 1)
                        {
                            //cout<<L2AcceState;

                            L1_tag_array[cacheconfig.full_way] = L1_tag.to_ulong();
                             cacheconfig.full_way++;
                             if(cacheconfig.full_way >= (int)pow(2,L1_array_size))
                             {
                                 cacheconfig.full_way = 0;
                             }

                        }
                     
                     if (L2AcceState == 2)
                    {
                       
                        L1_tag_array[cacheconfig.full_way] = L1_tag.to_ulong();
                             cacheconfig.full_way++;
                             if(cacheconfig.full_way >= (int)pow(2,L1_array_size))
                             {
                                 cacheconfig.full_way = 0;
                             }

                       
                        L2_tag_array[L2_index.to_ulong() + (cacheconfig.L2_way * ((int)pow(2,L2_array_size) / cacheconfig.L2setsize)) ] = L2_tag.to_ulong();
                        L2_valid_array[L2_index.to_ulong() + (cacheconfig.L2_way * ((int)pow(2,L2_array_size) / cacheconfig.L2setsize)) ] = 1;
                        cacheconfig.L2_way++;       
                                //cout<<L2_index.to_ulong()<<"--"<<L2_offset.to_ulong()<<"--"<<L2_tag_array[L2_index.to_ulong() + (i * ((2^L2_index_bits) / cacheconfig.L1setsize)) ];
                        if(cacheconfig.L2_way == cacheconfig.L2setsize)
                        {
                            cacheconfig.L2_way = 0;
                        }        
                        
                    }
                     
                     
                     
                 }
                    
                     
                     
             }
            //write ops start
             else
             {   
                   //Implement by you:
                  // write access to the L1 Cache,
                  //and then L2 (if required),
                  //update the L1 and L2 access state variable;
                 if(cacheconfig.L1setsize!=0)
                 {
                    for(int i=0; i<cacheconfig.L1setsize;i++)
                    {
                        if(L1_tag_array[L1_index.to_ulong() + i*((int)pow(2,L1_array_size)/cacheconfig.L1setsize)] == L1_tag.to_ulong() && L1_valid_array[L1_index.to_ulong() + i*((int)pow(2,L1_array_size)/cacheconfig.L1setsize)] == 1)
                        {
                          L1AcceState = 3;
                          L2AcceState = 0;
                          break;
                        }
                        else
                        {
                          L1AcceState = 4;
                        }
                     }
               
                if (L1AcceState == 4)
                {
                    for (int i = 0; i < cacheconfig.L2setsize; i++)
                    {
                        if (L2_tag_array[L2_index.to_ulong() + (i * ((int)pow(2,L2_array_size) / cacheconfig.L2setsize)) ] == L2_tag.to_ulong() && L2_valid_array[L2_index.to_ulong() + (i * ((int)pow(2,L2_array_size) / cacheconfig.L2setsize)) ] == 1)
                        {
                            L2AcceState = 3;
                            break;
                        }
                        else
                        {
                            L2AcceState = 4;
                        }
                    }
                }
                 }
                 
                 if(cacheconfig.L1setsize==0)
                 {
                     for(int i=0;i<(int)pow(2,L1_array_size);i++)
                     {
                         if(L1_tag_array[i] == L1_tag.to_ulong())
                         {
                            L1AcceState = 3;
                            L2AcceState = 0;
                            break;
                         }
                         else
                         {
                             L1AcceState = 4;
                         }
                     }
                 }
                 
                 if(cacheconfig.L2setsize==0)
                 {
                     for(int i=0;i<(int)pow(2,L2_array_size);i++)
                     {
                         if(L2_tag_array[i] == L2_tag.to_ulong())
                         {
                            
                            L2AcceState = 3;
                            break;
                         }
                         else
                         {
                             L1AcceState = 4;
                         }
                     }
                 }
                 else
                 {
                    if (L1AcceState == 4)
                    {
                        for (int i = 0; i < cacheconfig.L2setsize; i++)
                        {
                            if (L2_tag_array[L2_index.to_ulong() + (i * ((int)pow(2,L2_array_size) / cacheconfig.L2setsize)) ] == L2_tag.to_ulong() && L2_valid_array[L2_index.to_ulong() + (i * ((int)pow(2,L2_array_size) / cacheconfig.L2setsize)) ] == 1)
                            {
                                L2AcceState = 3;
                                break;
                            }
                            else
                            {
                                L2AcceState = 4;
                            }
                        }
                    }
                 }

                 
                 
                 
                 
             }
             
             
            
            tracesout<< L1AcceState << " " << L2AcceState << endl;  // Output hit/miss results for L1 and L2 to the output file;
            
            
        }
        traces.close();
        tracesout.close();
    }
    else cout<< "Unable to open trace or traceout file ";


  
   
 

  
    return 0;
}