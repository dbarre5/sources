

/*A = Cp * w / U / 3.14 / d*/



gGSea = -0.0121;
gGEarth = 0.01;

if (Location[i] > WH_Location){
	gG = gGSea;
	U = USea;
	d = TubingID/ 12;
}
else{
	gG = gGEarth;
	U = USurr;
	d = CasingID/12;
}

/*Lr = 2 * 3.14 *d/2 * U / Cp / w*/
w = rhoLi * qLi;

A = Cp * w / U / 3.14 / d*5.614/24;

cout << "w------------------------------------------------" << w << endl;
cout << "T1"<< T1 << endl;
cout << "Tei"<< Tei << endl;






TemporaryT = T1 + (Tf[i-1]-Tei)*pow(2.71828,(-dL/A)) + gG*sinThetas[i]*A*(1-pow(2.71828,(-dL/A)));


cout << "Tei-------------------"<< Tf[i-1] << endl;

