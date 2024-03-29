#include <iomanip>
#include <iostream>
#include "src/getRate.cpp"
void finalResults(){
  Int_t printAll=1;
  ofstream ofile;
  ofile.open("livetimes_April2021.txt",ios::app | ios::out );
  FILE *fp = fopen("livetimes.txt","r");  
  Float_t ps, rt, eto, etf,eso, esf, tto, ttf, tso, tsf, trig1rt;
  Float_t denom,num,clt,tlt,elt,tlte,clte,elte, cut;
  Int_t ncols,rn; 
  vector <float> rate, run, compLive, elecLive, errCLT, errELT, totalLive, errTotal;
  double fit_time, planeRate;


  while (1) { 
         ncols = fscanf(fp,"%d %f %f %f %f %f %f %f %f %f %f %f %f",&rn,&ps,&rt,&trig1rt,&cut,&eto,&etf,&eso,&esf,&tto,&ttf,&tso,&tsf);
    if (ncols < 0) break;
    // CLT_A
    num=tto+eto;
    denom=tso;      
    // CLT_P
    num=tto;
    denom=tso-eso;      
    //
    clt=(num/denom*ps);
    clte=TMath::Sqrt(num*abs(1-num/denom))*ps/denom;
    if(rn<2200.)fit_time=23.8E-9;
    else fit_time=37.1E-9;
    planeRate=getRate(rn,"s1x");
    elt=1.0 - planeRate*fit_time;
    elte=1 - elt;
    // shms el real raw cut
    //       elt=1.0/(1.0+planeRate*1.34038E-7);
    //        elte=planeRate*elt*elt*1.34748E-8;
    // hms el clean
    //   elt=1.0/(1.0+planeRate*2.897E-9);
    //    elte=planeRate*elt*elt*1.296E-9;
    //hms el real
    //    elt=1.0/(1.0+planeRate*5.437E-8);
    //    elte=planeRate*elt*elt*4.403E-9;
    //  shms el clean
    //        elt=1.0/(1.0+planeRate*7.252E-8);
    //        elte=planeRate*elt*elt*2.171E-9;
    //   Fit including runs after run 3101
    //    elt=1.0/(1.0+planeRate*2.094E-7);
    ///    elte=planeRate*elt*elt*2.029E-9;

    //   Fit for shms up tp 3101
    //    elt=1.0/(1.0+planeRate*2.066E-7);
    //    elte=planeRate*elt*elt*2.179E-9;
    tlt=elt*clt;
    tlte=sqrt(clte*clte/clt/clt+elte*elte/elt/elt)*tlt;
    run.push_back(rn);    
    rate.push_back(planeRate);
    compLive.push_back(clt);
    errCLT.push_back(clte);
    elecLive.push_back(elt);
    errELT.push_back(elte);
    totalLive.push_back(tlt);
    errTotal.push_back(tlte);

  }
  Int_t pts=run.size();
  for(Int_t i=0; i<pts; i++)
    {
      ofile<<std::fixed;
      ofile<<std::setprecision(0);
      ofile << run.at(i) <<"\t";
      //      ofile<<std::fixed;
      ofile<<std::setprecision(6);

      if(printAll==1){
      ofile<<std::setprecision(1);
      ofile << rate.at(i)<<setw(4) <<"\t";
      ofile<<std::setprecision(6);
	ofile << compLive.at(i) <<"\t";
	ofile << errCLT.at(i) <<"\t";
	ofile << elecLive.at(i) <<"\t";
	ofile << errELT.at(i) <<"\t";
      }      
	ofile << totalLive.at(i) <<"\t";
	ofile << errTotal.at(i) <<endl;
    }
  return;
}

