#include <iomanip>
#include <iostream>
#include "src/getRate.cpp"
void finalResults2(){
  Int_t printAll=1;
  ofstream ofile;
  ofile.open("hmsBoilingCut11.txt");
  FILE *fp = fopen("livetimes.txt","r");  
  Float_t ps, rt, eto, etf,eso, esf, tto, ttf, tso, tsf, s1xrate, current, trash;
  Float_t denom,num,clt,tlt,elt,tlte,clte,elte;
  Int_t ncols,rn; 
  vector <float> planeRate,rate, run, compLive, elecLive, errCLT, errELT, totalLive, errTotal, bcmcut;

  while (1) { 
    ncols = fscanf(fp,"%d %f %f %f %f %f %f %f %f %f %f %f",&rn,&current,&rt,&s1xrate,&eto,&etf,&eso,&esf,&tto,&ttf,&tso,&tsf);
    if (ncols < 0) break;
    // CLT_A
    ps=1;
    num=tto+eto;
    denom=tso;      
    // CLT_P
    num=tto;
    denom=tso-eso;      
    //
    clt=(num/denom*ps);
    clte=TMath::Sqrt(num*abs(1-num/denom))*ps/denom;
    //    planeRate=getRate(rn,"s1x");
    //hms cut 11
        elt=1.0/(1.0+s1xrate*-2.65359E-8);
        elte=s1xrate*elt*elt*1.14893E-8;
    //hms cut 12
    //        elt=1.0/(1.0+s1xrate*-3.91205E-8);
	//        elte=s1xrate*elt*elt*1.72496E-8;
    //cut12
    //    elt=1.0/(1.0+s1xrate*2.24611E-8);
    //    elte=s1xrate*elt*elt*1.17749E-8;
    //cut11
    //    elt=1.0/(1.0+s1xrate*9.59508E-8);
    //    elte=s1xrate*elt*elt*1.25098E-8;
    //cut10
    //    elt=1.0/(1.0+s1xrate*1.18491E-7);
    //    elte=s1xrate*elt*elt*1.28556E-8;
    //    elt=1.0/(1.0+planeRate*4.76733E-8);
    //    elte=planeRate*elt*elt*1.20481E-8;
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
    bcmcut.push_back(current);    
    rate.push_back(rt);
    planeRate.push_back(s1xrate);
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
      ofile<<std::setprecision(0);
	ofile << rate.at(i) <<"\t";
	ofile << planeRate.at(i) <<"\t";
      ofile<<std::setprecision(6);
	ofile << bcmcut.at(i) <<"\t";
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

