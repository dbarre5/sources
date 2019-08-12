/*
rhoL = function of Temp and Pressure at the grid Block
rhoG = function of Temp and Pressure at the grid Block
muL = function of Temp and Pressure at the grid Block
muG = function of Temp and Pressure at the grid Block
Bg
Rs
#include FluidProperties.H
*/
Area = 3.14 / 4 * pow(d,2);
qG = (Rp - Rs) * Bg*qL*(1-WCut);
vsl = (qL) / Area / 86400*5.614;
vsg = qG / Area / 86400;

cout << qL << " ------------------------qL" << endl;
cout << qG << " ------------------------qG" << endl;

/*Prevents a nan error*/
if (vsg <= 0.001){
	vsg = 0.0001;
}



vm = vsg+vsl;
gammaL = vsl / vm;
muL = 2;
muG = 0.019;
sigma = 31.6;

;
double Pwh = 500;

NLV = 1.938 * vsl * pow((rhoL/sigma),0.25);
Nd = 120.872 * d * pow((rhoL/sigma),0.5);
NGV = 1.938 * vsg * pow((rhoL/sigma),0.25);
NL = 0.15726 * muL * pow((1/(rhoL*pow(sigma,3))),0.25);



CNL = 0.0019 + 0.0322*NL - 0.66422*pow(NL,2) + 4.9951 * pow(NL,3);
CNL = CNL / (1 - 10.0147*NL+33.8696*pow(NL,2)+277.2817*pow(NL,3));

/*What is P here*/
H= NLV * pow((Pwh / 14.7),0.1) * CNL / pow(NGV,0.575) / Nd;
B = NGV * pow(NL,0.380) / pow(Nd,2.14);

phi = 1.0886 - 69.9473*B + 2334.3497*pow(B,2) - 12896.683*pow(B,3);
phi = phi / (1 - 53.4401 * B + 1517.9369*pow(B,2) - 8419.811*pow(B,3));

HL = (0.0047 + 1123.32 * H + 729489.64*pow(H,2));
HL = HL / (1+1097.1566*H + 722153.97*pow(H,2));
HL = phi*pow(HL,0.5);


/*--------------------------IMPORTANT-----------------------------------------------------*/
/*bug in my code??? HL can go above 1 in certain cases... I need to check this out later...
/*----------------------------------------------------------------------------------------*/
if (HL > 1){
HL = 1;
}



muSlip = pow(muL,HL) * pow(muG,(1-HL));
rhoSlip = rhoL*HL + rhoG * (1-HL);
rhoNS = rhoL*gammaL + rhoG * (1-gammaL);

ReTP = 1488 * rhoNS * vm * d / muSlip;
fTP = 0.184*pow(ReTP,-0.2);




rhoTP = pow(rhoNS,2) / rhoSlip;
dPdL = (fTP * rhoTP * pow(vm,2)) / (2 * g * d); /*friction component*/

dPdL = dPdL + rhoSlip * 1 * sinThetas[i]; /*Gravity Component*/

dPdL = dPdL / 144; /*Convert to psi/ft from psf/ft*/

cout << "HL iis = " <<  HL << endl;
cout << "HL iis = " <<  rhoO << endl;
cout << "HL iis = " <<  gammaO << endl;





