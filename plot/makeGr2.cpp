#include "readReport.cpp"
Double_t calcBinomRatioErr(Double_t numerCnts, Double_t denomCnts) {
  return (0.5*(Double_t) numerCnts / (Double_t) denomCnts) * TMath::Sqrt((1./((Double_t) numerCnts)) + (1./((Double_t) denomCnts)));
}

TGraphErrors* makeGr2(Double_t fact=1,Int_t option=1){

  FILE *fp = fopen("livetimes.txt","r");  
  Float_t rn, ps, rt, eto, etf,eso, esf, tto, ttf, tso, tsf;
  Float_t denom,num;
  Int_t ncols; 
  vector <float> rate, run, dt, err;
  while (1) { 
    ncols = fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f",&rn,&ps,&rt,&eto,&etf,&eso,&esf,&tto,&ttf,&tso,&tsf);
    //    cout << run <<endl;
    if (ncols < 0) break;
    if(ps==fact){
      if(option==1){num=eto+etf;denom=eso+esf;}       
      if(option==2){num=tto+ttf;denom=tso+tsf;}       
      rate.push_back(1000*readReport(rn,"pTRIG2 rate"));
      run.push_back(rn);
      dt.push_back(num/denom*ps);
      err.push_back(calcBinomRatioErr(num,denom)*ps);
    }
  }
  Int_t pts=run.size();
  TGraphErrors *g=new TGraphErrors(pts,&rate[0],&dt[0],0,&err[0]);
  g->SetMarkerStyle(20);
  //  g->Draw();
  return g;
}

