
#include <iomanip>
#include <iostream>

void addErr(){
  Int_t printAll=1;
  ofstream ofile;
  ofile.open("hms.txt");
  FILE *fp = fopen("hmsBoilingCut12.txt","r");  
  //  ofile.open("shms.txt");
  //  FILE *fp = fopen("boilingCut12.txt","r");  
  Float_t trig, s1x, cut, clt, clte, elt, elte, tlt, tlte, fifty, hundred;    Int_t ncols, run; 
 
  while (1) { 
    ncols = fscanf(fp,"%d %f %f %f %f %f %f %f %f %f",&run, &trig, &s1x, &cut, &clt, &clte, &elt, &elte, &tlt, &tlte);
    if (ncols < 0) break;
    fifty = 1. - 50E-9*s1x;
    hundred = 1. - 100E-9*s1x;
    ofile<<std::fixed<<std::setprecision(0);
    ofile << run <<"\t"<< trig <<"\t"<< s1x <<"\t";
    ofile<<std::fixed<<std::setprecision(2);
ofile<< cut <<"\t";
    ofile<<std::fixed<<std::setprecision(6);
    ofile << clt <<"\t"<< clte <<"\t"<< fifty <<"\t"<< hundred<<endl;
  }
  return;
}

