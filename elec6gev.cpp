void elec6gev(Int_t run=2550){
  TString froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3b-shms-data/shms_replay_production_%d_-1.root",run);
  if (!gSystem->AccessPathName(froot)==0){cout<<"Couldn't find file"<<endl;return;}

  TFile *f=new TFile(froot);
  TTree *TSP=(TTree*)f->Get("TSP");
  Double_t pre100,pre150,pre200,pre40;

  //OG 6 GeV Electronic Live Time (100, 150) : {100.0 - ((P.pPRE100.scaler - P.pPRE150.scaler)/P.pPRE100.scaler):%3.4f} %

  TSP->SetBranchAddress("P.pPRE100.scalerRate", &pre100);
  TSP->SetBranchAddress("P.pPRE150.scalerRate", &pre150);
  TSP->SetBranchAddress("P.pPRE200.scalerRate", &pre200);
  TSP->SetBranchAddress("P.pPRE40.scalerRate", &pre40);

  Int_t nev=TSP->GetEntries();

  for(Int_t i=0;i<nev;i++){TSP->GetEntry(i);}

  cout <<"run" <<"\t"<< "pre100" <<"\t"<<"pre150"<<"\t"<<"pre200"<<endl;
  cout << run <<"\t"<< pre100 <<"\t"<<pre150<<"\t"<<pre200<<endl;

  vector<double> x;
  vector<double> y;

  //  x.push_back(40);
  x.push_back(100);
  x.push_back(150);
  x.push_back(200);

  //  y.push_back(pre40);
  y.push_back(pre100);
  y.push_back(pre150);
  y.push_back(pre200);

  TGraph *gr=new TGraph(3,&x[0],&y[0]);

  gr->SetMarkerStyle(20);
  gr->Draw("ap");
  gr->GetXaxis()->SetRangeUser(0,220);
  gr->Fit("pol1");
  return;
}
