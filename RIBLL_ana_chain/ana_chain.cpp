#define ana_chain_cxx
#include "ana_chain.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#include<fstream>
#include<TEllipse.h>
#include<TPaveText.h>

void ana_chain::Loop(char *filename_out)
{
//   In a ROOT session, you can do:
//      Root > .L ana_chain.C
//      Root > ana_chain t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   TFile *f_out=new TFile(filename_out,"recreate");
   TH1F *h_si0_ene=new TH1F("h21","h21",300,0,7);
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(decay_of_im_id==21)
      h_si0_ene->Fill(si_ene[0]);
      // if (Cut(ientry) < 0) continue;
   }//end entry loop
   f_out->Write();
   f_out->Close();
}//end founction loop

void ana_chain::decay_num_in_one_event(char *filename_out)
{
  if (fChain == 0) return;
  TFile *f_out=new TFile(filename_out,"recreate");
  int bin_num=600;
  char si_all_name[256],si0_si_around_name[256],decay_num_in_one_event_name[256],one_third_back_name[256],back_name[256],without_back_name[256];
  TH1F *h_si_all[6];
  for(int i=0;i<6;i++)
  {
    sprintf(si_all_name,"si_all_%d",23-i);
    h_si_all[i]=new TH1F(si_all_name,si_all_name,bin_num,0,7);
  }
  TH1F *h_decay_num_in_one_event[6];
  for(int i=0;i<6;i++)
  {
   sprintf(decay_num_in_one_event_name,"decay_num_one_event_%d",23-i);
   h_decay_num_in_one_event[i]=new TH1F(decay_num_in_one_event_name,decay_num_in_one_event_name,7,0,7);
  }
  TH2F *h_si0_si_around[6];
  for(int i=0;i<6;i++)
  {
    sprintf(si0_si_around_name,"si0_si_around_%d",23-i);
    h_si0_si_around[i]=new TH2F(si0_si_around_name,si0_si_around_name,bin_num,0,7,bin_num,0,7);
  }
  TH1F *h_one_third_back[6];
  for(int i=0;i<6;i++)
  {
    sprintf(one_third_back_name,"one_third_back_all_%d",23-i);
    h_one_third_back[i]=new TH1F(one_third_back_name,one_third_back_name,bin_num,0,7);
  }
  TH1F *h_back[6];
  for(int i=0;i<6;i++)
  {
    sprintf(back_name,"back_all_%d",23-i);
    h_back[i]=new TH1F(back_name,back_name,bin_num,0,7);
  } 
  TH1F *h_without_back[6];
  for(int i=0;i<6;i++)
  {
    sprintf(without_back_name,"without_back_all_%d",23-i);
    h_without_back[i]=new TH1F(without_back_name,without_back_name,bin_num,0,7);
  } 

  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"The entries is "<<nentries<<endl;
  int decay_num[6];
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    memset(decay_num,0,sizeof(decay_num));
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if(decay_of_im_id==23)
    {
      for(int i=1;i<7;i++)
      {
        if(si_flag[i]==1)
        {
          decay_num[0]++;
        }
      }
      if(decay_num[0]==0)
      {
        h_si_all[0]->Fill(si_ene[0]);
        if(life_time>2000)
        h_one_third_back[0]->Fill(si_ene[0]);
        h_si0_si_around[0]->Fill(si_ene[0],0);
      }
      if(decay_num[0]==1)
      {
        for(int i=1;i<7;i++)
        {
          if(si_flag[i]==1)
          {
            h_si0_si_around[0]->Fill(si_ene[0],si_ene[i]);
            if(i<4&&qsd_flag[i]==0)
            {
              h_si_all[0]->Fill(si_ene[0]+si_ene[i]);
              if(life_time>2000)
              h_one_third_back[0]->Fill(si_ene[0]+si_ene[i]);
            }
            if(i<4&&qsd_flag[i]==1)
            {
              h_si_all[0]->Fill(si_ene[0]+si_ene[i]+qsd_ene[i]);
              if(life_time>2000)
              h_one_third_back[0]->Fill(si_ene[0]+si_ene[i]+qsd_ene[i]);
            }
            if(i>=4)
            {
              h_si_all[0]->Fill(si_ene[0]+si_ene[i]);
              if(life_time>2000)
              h_one_third_back[0]->Fill(si_ene[0]+si_ene[i]);
            }
          }
        }
      }
      h_decay_num_in_one_event[0]->Fill(decay_num[0]);
    }//end id==23
    if(decay_of_im_id==22)
    {
      for(int i=1;i<7;i++)
      {
        if(si_flag[i]==1)
        {
          decay_num[1]++;
        }
      }
      if(decay_num[1]==0)
      {
        h_si_all[1]->Fill(si_ene[0]);
        if(life_time>2000)
        h_one_third_back[1]->Fill(si_ene[0]);
        h_si0_si_around[1]->Fill(si_ene[0],0);
      }
      if(decay_num[1]==1)
      {
        for(int i=1;i<7;i++)
        {
          if(si_flag[i]==1)
          {
            h_si0_si_around[1]->Fill(si_ene[0],si_ene[i]);
            if(i<4&&qsd_flag[i]==0)
            {
              h_si_all[1]->Fill(si_ene[0]+si_ene[i]);
              if(life_time>2000)
              h_one_third_back[1]->Fill(si_ene[0]+si_ene[i]);
            }
            if(i<4&&qsd_flag[i]==1)
            {
              h_si_all[1]->Fill(si_ene[0]+si_ene[i]+qsd_ene[i]);
              if(life_time>2000)
              h_one_third_back[1]->Fill(si_ene[0]+si_ene[i]+qsd_ene[i]);
            }
            if(i>=4)
            {
              h_si_all[1]->Fill(si_ene[0]+si_ene[i]);
              if(life_time>2000)
              h_one_third_back[1]->Fill(si_ene[0]+si_ene[i]);
            }
          }
        }
      }
      h_decay_num_in_one_event[1]->Fill(decay_num[1]);
    }//end id==22
    if(decay_of_im_id==21)
    {
      for(int i=1;i<7;i++)
      {
        if(si_flag[i]==1)
        {
          decay_num[2]++;
        }
      }
      if(decay_num[2]==0)
      {
        h_si_all[2]->Fill(si_ene[0]);
        if(life_time>2000)
        h_one_third_back[2]->Fill(si_ene[0]);
        h_si0_si_around[2]->Fill(si_ene[0],0.);
      }
      if(decay_num[2]==1)
      {
        for(int i=1;i<7;i++)
        {
          if(si_flag[i]==1)
          {
            h_si0_si_around[2]->Fill(si_ene[0],si_ene[i]);
            if(i<4&&qsd_flag[i]==0)
            {
              h_si_all[2]->Fill(si_ene[0]+si_ene[i]);
              if(life_time>2000)
              h_one_third_back[2]->Fill(si_ene[0]+si_ene[i]);
            }
            if(i<4&&qsd_flag[i]==1)
            {
              h_si_all[2]->Fill(si_ene[0]+si_ene[i]+qsd_ene[i]);
              if(life_time>2000)
              h_one_third_back[2]->Fill(si_ene[0]+si_ene[i]+qsd_ene[i]);
            }
            if(i>=4)
            {
              h_si_all[2]->Fill(si_ene[0]+si_ene[i]);
              if(life_time>2000)
              h_one_third_back[2]->Fill(si_ene[0]+si_ene[i]);
            }
          }
        }
      }
      h_decay_num_in_one_event[2]->Fill(decay_num[2]);
    }//end id==21
    if(decay_of_im_id==20)
    {
      for(int i=1;i<7;i++)
      {
        if(si_flag[i]==1)
        {
          decay_num[3]++;
        }
      }
      if(decay_num[3]==0)
      {
        h_si_all[3]->Fill(si_ene[0]);
        if(life_time>2000)
        h_one_third_back[3]->Fill(si_ene[0]);
        h_si0_si_around[3]->Fill(si_ene[0],0.);
      }
      if(decay_num[3]==1)
      {
        for(int i=1;i<7;i++)
        {
          if(si_flag[i]==1)
          {
            h_si0_si_around[3]->Fill(si_ene[0],si_ene[i]);
            if(i<4&&qsd_flag[i]==0)
            {
              h_si_all[3]->Fill(si_ene[0]+si_ene[i]);
              if(life_time>2000)
              h_one_third_back[3]->Fill(si_ene[0]+si_ene[i]);
            }
            if(i<4&&qsd_flag[i]==1)
            {
              h_si_all[3]->Fill(si_ene[0]+si_ene[i]+qsd_ene[i]);
              if(life_time>2000)
              h_one_third_back[3]->Fill(si_ene[0]+si_ene[i]+qsd_ene[i]);
            }
            if(i>=4)
            {
              h_si_all[3]->Fill(si_ene[0]+si_ene[i]);
              if(life_time>2000)
              h_one_third_back[3]->Fill(si_ene[0]+si_ene[i]);
            }
          }
        }
      }
      h_decay_num_in_one_event[3]->Fill(decay_num[3]);
    }//end id==20
    if(decay_of_im_id==19)
    {
      for(int i=1;i<7;i++)
      {
        if(si_flag[i]==1)
        {
          decay_num[4]++;
        }
      }
      if(decay_num[4]==0)
      {
        h_si_all[4]->Fill(si_ene[0]);
        if(life_time>2000)
        h_one_third_back[4]->Fill(si_ene[0]);
        h_si0_si_around[4]->Fill(si_ene[0],0.);
      }
      if(decay_num[4]==1)
      {
        for(int i=1;i<7;i++)
        {
          if(si_flag[i]==1)
          {
            h_si0_si_around[4]->Fill(si_ene[0],si_ene[i]);
            if(i<4&&qsd_flag[i]==0)
            {
              h_si_all[4]->Fill(si_ene[0]+si_ene[i]);
              if(life_time>2000)
              h_one_third_back[4]->Fill(si_ene[0]+si_ene[i]);
            }
            if(i<4&&qsd_flag[i]==1)
            {
              h_si_all[4]->Fill(si_ene[0]+si_ene[i]+qsd_ene[i]);
              if(life_time>2000)
              h_one_third_back[4]->Fill(si_ene[0]+si_ene[i]+qsd_ene[i]);
            }
            if(i>=4)
            {
              h_si_all[4]->Fill(si_ene[0]+si_ene[i]);
              if(life_time>2000)
              h_one_third_back[4]->Fill(si_ene[0]+si_ene[i]);
            }
          }
        }
      }
      h_decay_num_in_one_event[4]->Fill(decay_num[4]);
    }//end id==19
    if(decay_of_im_id==18)
    {
      for(int i=1;i<7;i++)
      {
        if(si_flag[i]==1)
        {
          decay_num[5]++;
        }
      }
      if(decay_num[5]==0)
      {
        h_si_all[5]->Fill(si_ene[0]);
        if(life_time>2000)
        h_one_third_back[5]->Fill(si_ene[0]);
        h_si0_si_around[5]->Fill(si_ene[0],0.);
      }
      if(decay_num[5]==1)
      {
        for(int i=1;i<7;i++)
        {
          if(si_flag[i]==1)
          {
            h_si0_si_around[5]->Fill(si_ene[0],si_ene[i]);
            if(i<4&&qsd_flag[i]==0)
            {
              h_si_all[5]->Fill(si_ene[0]+si_ene[i]);
              if(life_time>2000)
              h_one_third_back[4]->Fill(si_ene[0]+si_ene[i]);
            }
            if(i<4&&qsd_flag[i]==1)
            {
              h_si_all[5]->Fill(si_ene[0]+si_ene[i]+qsd_ene[i]);
              if(life_time>2000)
              h_one_third_back[5]->Fill(si_ene[0]+si_ene[i]+qsd_ene[i]);
            }
            if(i>=4)
            {
              h_si_all[5]->Fill(si_ene[0]+si_ene[i]);
              if(life_time>2000)
              h_one_third_back[5]->Fill(si_ene[0]+si_ene[i]);
            }
          }
        }
      }
      h_decay_num_in_one_event[5]->Fill(decay_num[4]);
    }//end id==18

  }//end entry loop
  for(int i=0;i<6;i++)
  {
    h_back[i]->Add(h_one_third_back[i],3);
    h_without_back[i]->Add(h_si_all[i],h_back[i],1,-1);
  }
  f_out->Write();
  f_out->Close();
}//end function decay_num_in_one_event()




