#include <iomanip>
#include <iostream>
#include "src/getRate.cpp"
void boilingTLT(){
  Int_t printAll=1;
  ofstream ofile;
  ofile.open("cut7boiling.txt");
  FILE *fp = fopen("cut7shmsBoiling.txt","r");  
  Float_t cut, rt, eto, etf,eso, esf, tto, ttf, tso, tsf, trig1rt;
  Float_t denom,num,clt,tlt,elt,tlte,clte,elte, planeRate;
  Int_t ncols,rn; 
  vector <float> run, bcmcut, top, bottom,  lt, lte, rate;

  while (1) { 
    ncols = fscanf(fp,"%d %f %f %f %f %f %f %f %f %f %f %f",&rn,&cut,&rt,&trig1rt,&eto,&etf,&eso,&esf,&tto,&ttf,&tso,&tsf);
    if (ncols < 0) break;
    num=eto;
    denom=eso;      
    //
    tlt=(num/denom);
    tlte=TMath::Sqrt(num*abs(1-num/denom))/denom;
    run.push_back(rn);    
    bcmcut.push_back(cut);
    top.push_back(num);
    bottom.push_back(denom);
    double tlt=1/(1+0.000179683*rt);
    lt.push_back(tlt);
    double tlte=rt*tlt*tlt*4.58953E-7;
    lte.push_back(tlte);
    rate.push_back(rt);

  }
  Int_t pts=run.size();
  cout << pts <<endl;
  for(Int_t i=0; i<pts; i++)
    {
      cout << "Hello\n";
      ofile<<std::fixed;
      ofile<<std::setprecision(0);
      ofile << run.at(i) <<"\t";
      ofile<<std::setprecision(2);
      ofile << bcmcut.at(i) <<"\t";
      ofile<<std::setprecision(0);
      ofile << top.at(i) <<"\t";
      ofile << bottom.at(i) <<"\t";
      ofile<<std::setprecision(4);
      ofile << lt.at(i) <<"\t";
      ofile << lte.at(i) <<"\t";
      ofile << rate.at(i) <<endl;
    }
  return;
}

