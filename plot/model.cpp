void model(){


  TF1 *f1=new TF1("f2","1-1/TMath::Factorial(2)*(.000250*x)^2*TMath::Exp(-.000250*x)",0,5000);
  TF1 *f2=new TF1("f2","1-1/TMath::Factorial(3)*(.000250*x)^3*TMath::Exp(-.000250*x)",0,12000);
  TF1 *f3=new TF1("f2","1-1/TMath::Factorial(4)*(.000250*x)^4*TMath::Exp(-.000250*x)",0,20000);
  TF1 *f5=new TF1("f2","1-1/TMath::Factorial(6)*(.000250*x)^6*TMath::Exp(-.000250*x)",0,25)  ;
  TF1 *f9=new TF1("f2","1-1/TMath::Factorial(10)*(.000250*x)^10*TMath::Exp(-.000250*x)",0,30000);
  TF1 *f17=new TF1("f2","1-1/TMath::Factorial(18)*(.000250*x)^18*TMath::Exp(-.000250*x)",0,100000);

  TF1 *f=new TF1("f","1/TMath::Factorial(0)*(.000250*x)^0*TMath::Exp(-.000250*x)+1/TMath::Factorial(1)*(.000250*x)^1*TMath::Exp(-.000250*x)",0,5000);    

  f17->GetYaxis()->SetRangeUser(.6,1.000);
 f17->Draw(); 
 f2->Draw("same");
 f3->Draw("same");
 f5->Draw("same");
 f9->Draw("same");
 f1->Draw("same");
 /*
 TCanvas *c1=new TCanvas();
 c1->Divide(2,1);
 c1->cd(1);
 f->Draw();
 c1->cd(2);
 f1->Draw();

 */
 return;
}
