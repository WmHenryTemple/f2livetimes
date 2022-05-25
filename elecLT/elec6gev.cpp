
TGraphErrors *gr; 

void elec6gev(){
  TCanvas *c1=new TCanvas();
  Int_t nbin=500;
  Double_t max=.15;
  Double_t min=-.15;
  TH1F *havg=new TH1F("havg","{lt(average) - lt(fit)}/lt(fit)",nbin,min,max);
  TH1F *h100=new TH1F("h100","{lt(100,200) - lt(fit)}/lt(fit)",nbin,min,max);
  TH1F *h150=new TH1F("h150","{lt(100,150) - lt(fit)}/lt(fit)",nbin,min,max);
  TH1F *h200=new TH1F("h200","{lt(150,200) - lt(fit)}/lt(fit)",nbin,min,max);
  TH1F *herr=new TH1F("herr","Livetime error from fit parameters",nbin,-.1,1);
  TH1F *hlt=new TH1F("hlt","Livetime from fit ",nbin,90,101);
  havg->GetXaxis()->SetTitle("Percent Difference (%)");
  h100->GetXaxis()->SetTitle("Percent Difference (%)");
  h150->GetXaxis()->SetTitle("Percent Difference (%)");
  h200->GetXaxis()->SetTitle("Percent Difference (%)");
  herr->GetXaxis()->SetTitle("Livetime Error (%)");
  hlt->GetXaxis()->SetTitle("Livetime (%)");
  for(Int_t run=2400;run<3201;run++)
    {
      TString froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3b-shms-data/shms_replay_production_%d_-1.root",run);
      if (gSystem->AccessPathName(froot)==0)
	{
	  TFile *f=new TFile(froot);
	  TTree *TSP=(TTree*)f->Get("TSP");
	  Double_t sca100,sca150,sca200,sca40;
	  Double_t rate100,rate150,rate200,rate40;
	  
	  TSP->SetBranchAddress("P.pPRE100.scaler", &sca100);
	  TSP->SetBranchAddress("P.pPRE150.scaler", &sca150);
	  TSP->SetBranchAddress("P.pPRE200.scaler", &sca200);
	  TSP->SetBranchAddress("P.pPRE100.scalerRate", &rate100);
	  TSP->SetBranchAddress("P.pPRE150.scalerRate", &rate150);
	  TSP->SetBranchAddress("P.pPRE200.scalerRate", &rate200);
	  Int_t nev=TSP->GetEntries();
	  /*
	    for(Int_t i=0;i<nev;i++){TSP->GetEntry(i);
	    {
	    cout <<"run" <<"\t"<< "sca100" <<"\t"<<"sca150"<<"\t"<<"sca200";
	    cout <<"\t"<< "rate100" <<"\t"<<"rate150"<<"\t"<<"rate200"<<endl;
	    cout <<run<<"\t"<< sca100 <<"\t"<<sca150<<"\t"<<sca200;
	    cout <<"\t"<< rate100 <<"\t"<<rate150<<"\t"<<rate200<<endl;
	    }
	  */
	  TSP->GetEntry(nev-1);
	  vector<double> x;
	  vector<double> y;
	  vector<double> ye;
	  
	  x.push_back(100);
	  x.push_back(150);
	  x.push_back(200);
	  
	  y.push_back(sca100);
	  y.push_back(sca150);
	  y.push_back(sca200);
	  
	  ye.push_back(sqrt(sca100));
	  ye.push_back(sqrt(sca150));
	  ye.push_back(sqrt(sca200));
	  
	  gr=new TGraphErrors(3,&x[0],&y[0],0,&ye[0]);
	  gr->SetMarkerStyle(20);
	  gr->Draw("ap");
	  gr->GetXaxis()->SetRangeUser(0,220);
	  gr->Fit("pol1");
	  
	  Double_t chi2=gr->GetFunction("pol1")->GetChisquare();
	  Double_t b=gr->GetFunction("pol1")->GetParameter(0);
	  Double_t b_err=gr->GetFunction("pol1")->GetParError(0);
	  Double_t m=gr->GetFunction("pol1")->GetParameter(1);
	  Double_t m_err=gr->GetFunction("pol1")->GetParError(1);
	  Double_t y100=m*100.+b;
	  Double_t dt=(b-y100)/b;
	  Double_t dt_err=sqrt( m_err*m_err/m/m + b_err*b_err/b/b )*dt;
	  Double_t lt=100.-dt*100.;
	  Double_t lt_err=dt_err*100.;
	  Double_t lt100_150=100.-100*2*(sca100-sca150)/(3*sca100-2*sca150);
	  Double_t lt100_200=100.-100*1*(sca100-sca200)/(2*sca100-1*sca200);
	  Double_t lt150_200=100.-100*2*(sca150-sca200)/(4*sca150-3*sca200);
	  Double_t lt_avg=(lt100_150+lt100_200+lt150_200)/3.;
	  
	  cout <<"The slope is :"<<m<<" +/- "<<m_err<<endl;
	  cout <<"The y-int is :"<<b<<" +/- "<<b_err<<endl;
	  cout <<"The deadtime is :"<<dt<<" +/- "<<dt_err<<" %"<<endl;
	  cout <<"The livetime from fit is :"<<lt<<" +/- "<<lt_err<<" %"<<endl;
	  cout <<"The livetime(100,150) is :"<<lt100_150<<" %"<<endl;
	  cout <<"The livetime(100,200) is :"<<lt100_200<<" %"<<endl;
	  cout <<"The livetime(150,200) is :"<<lt150_200<<" %"<<endl;
	  cout <<"The average livetime is :"<<lt_avg<<" %"<<endl;
	  
	  havg->Fill(100*(lt-lt_avg)/lt);
	  h100->Fill(100*(lt-lt100_200)/lt);
	  h150->Fill(100*(lt-lt100_150)/lt);
	  h200->Fill(100*(lt-lt150_200)/lt);
	  herr->Fill(lt_err/lt*100);
	  hlt->Fill(lt);
	  c1->Clear();
	  //  herr->Draw();
	  
	  c1->Divide(2,2);
	  c1->cd(1);
	  havg->Draw();
	  c1->cd(2);
	  h100->Draw();
	  c1->cd(3);
	  h150->Draw();
	  c1->cd(4);
	  h200->Draw();
	  c1->Clear();
	  hlt->Draw();	  
	  ofstream ofile;
	  ofile.open("elecLT.txt",ios::app);
	  ofile << std::setprecision(4) << std::fixed;
	  ofile << run <<"\t"<< lt <<"\t"<< lt_err <<"\t"<<chi2<<"\t"<< lt100_150 <<"\t";
	  ofile << lt100_200 <<"\t" << lt150_200 <<"\t"<< lt_avg<<endl;
	  ofile.close();
	}
    }
  return;
}
