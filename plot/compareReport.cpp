#include "readReport.cpp"



Double_t calcBinomRatioErr(Double_t numerCnts, Double_t denomCnts) {
  return (0.5*(Double_t) numerCnts / (Double_t) denomCnts) * TMath::Sqrt((1./((Double_t) numerCnts)) + (1./((Double_t) denomCnts)));
}

void compareReport(Double_t fact=1,Int_t option=1){
gStyle->SetOptFit();
  FILE *fp = fopen("livetimes.txt","r");  
  Float_t rn, ps, rt, eto, etf,eso, esf, tto, ttf, tso, tsf;
  Float_t deno,num;
  Double_t cutCurrent,current,f,denom,numer,error,rmeas;
  Int_t ncols; 
  vector <float> rate, run, dt, err,x,xe;
  while (1) { 
    ncols = fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f",&rn,&ps,&rt,&eto,&etf,&eso,&esf,&tto,&ttf,&tso,&tsf);
    //    cout << run <<endl;
    if (ncols < 0) break;
    if(ps==fact){
      num=eto;
      denom=eso;       
      rate.push_back(rt);
      run.push_back(rn);
      dt.push_back(num/denom*ps*100);
      err.push_back(calcBinomRatioErr(num,denom)*ps*100);

      cutCurrent=readReport(rn,"BCM4C cut current");
      current=readReport(rn,"BCM4C current");
      f=(current/cutCurrent);
      rmeas=readReport(rn,"ps2 lt edtm");
      x.push_back(100*(rmeas/100-(1-f))/f);
      deno=readReport(rn,"EDTM triggers");
      numer=readReport(rn,"Accepted EDTM triggers");
      error=0.5*numer/deno*TMath::Sqrt(1/deno+1/numer);
      xe.push_back(error*100);




    }
  }
  Int_t pts=run.size();
  TGraphErrors *g=new TGraphErrors(pts,&x[0],&dt[0],&xe[0],&err[0]);
  g->GetYaxis()->SetTitle("LiveTime w/ Timing Cuts");
  g->GetXaxis()->SetTitle("LiveTime Report file corrected");

  g->GetYaxis()->SetRangeUser(70.,100.);
  g->GetXaxis()->SetRangeUser(70.,100.);
  g->SetMarkerStyle(20);
  g->Draw("ap");
  g->Fit("pol1");
  return ;
}

