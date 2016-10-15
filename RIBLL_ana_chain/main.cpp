#include "ana_chain.h"
#include "TString.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

#include <time.h> 
#include <stdio.h> 
#include<sys/time.h>
using namespace std;
int main(int argc, char **argv)
{
//---------------for the cpu time used---------------------//
	struct timeval startTime,endTime;
	float Timeuse;
	gettimeofday(&startTime,NULL);
//---------------------------------------------------------//
//  int maxnevt=0;
  if(argc>1)
  {
    cout<<"USAG: ./ana_chain"<<endl; return -1;
  }
//  char filename_in[256];
  char filename_out[256];
//  sprintf(filename_in,"/home/wangyuting/ds6310/RIBLL/results/chain_root_result_11_700.root.root",runnum);
  sprintf(filename_out,"/home/wangyuting/ds6310/RIBLL/results/no_second_20na_cali_time_3000/ribll_ana_chain_out.root");
//  TString rootfile_in=rootpath+filename_in;

  ana_chain *ribll_ana=new ana_chain();
//  if(argc==1)  ribll_ana->Loop(filename_out);
  if(argc==1)  ribll_ana->decay_num_in_one_event(filename_out);
  cout<<"The output file is: "<<filename_out<<endl;
//-----------------------------for the cpu time used-----------------------//
	gettimeofday(&endTime,NULL);
	
	Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
	
	Timeuse /= 1000000;
	
	printf("Timeuse = %f s\n",Timeuse);
//------------------------------------------------------------------------------//
}
