//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct  4 19:26:09 2016 by ROOT version 5.34/24
// from TTree RIBLL_result/tree
// found on file: /home/wangyuting/ds6310/RIBLL/results/chain_root_result_11_700.root
//////////////////////////////////////////////////////////

#ifndef ana_chain_h
#define ana_chain_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <TSpectrum.h>
#include <TH2.h>
#include <TMath.h>
#include <TVirtualFitter.h>
#include <TTree.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class ana_chain {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         life_time;
   Float_t         si_ene[7];
   Float_t         qsd_ene[4];
   Float_t         clover_ene[5][4];
   Int_t           decay_of_im_id;
   Int_t           si_flag[7];
   Int_t           qsd_flag[4];
   Int_t           K;

   // List of branches
   TBranch        *b_life_time;   //!
   TBranch        *b_si_ene;   //!
   TBranch        *b_qsd_ene;   //!
   TBranch        *b_clover_ene;   //!
   TBranch        *b_decay_of_im_id;   //!
   TBranch        *b_si_flag;   //!
   TBranch        *b_qsd_flag;   //!
   TBranch        *b_K;

   ana_chain(TTree *tree=0);
   virtual ~ana_chain();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     Loop(char *filename_out);
   virtual void     decay_num_in_one_event(char *filename_out);
};

#endif

#ifdef ana_chain_cxx
ana_chain::ana_chain(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      char *c_file_in = "/home/wangyuting/ds6310/RIBLL/results/no_second_20na_cali_time_3000/chain_root_result_11_700.root";
      cout<<"The imput file is: "<<c_file_in<<endl;
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(c_file_in);
      if (!f || !f->IsOpen()) {
         f = new TFile(c_file_in);
      }
      f->GetObject("RIBLL_result",tree);

   }
   Init(tree);
}

ana_chain::~ana_chain()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ana_chain::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ana_chain::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ana_chain::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("life_time", &life_time, &b_life_time);
   fChain->SetBranchAddress("si_ene", si_ene, &b_si_ene);
   fChain->SetBranchAddress("qsd_ene", qsd_ene, &b_qsd_ene);
   fChain->SetBranchAddress("clover_ene", clover_ene, &b_clover_ene);
   fChain->SetBranchAddress("decay_of_im_id", &decay_of_im_id, &b_decay_of_im_id);
   fChain->SetBranchAddress("si_flag", si_flag, &b_si_flag);
   fChain->SetBranchAddress("qsd_flag", qsd_flag, &b_qsd_flag);
   fChain->SetBranchAddress("K",&K,&b_K);
   Notify();
}

Bool_t ana_chain::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ana_chain::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ana_chain::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ana_chain_cxx
