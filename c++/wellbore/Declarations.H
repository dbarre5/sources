/*--------------------------------------Input Deck-----------------------------------------------*/
double Length; 		/*feet*/
int N;			/**/
double dL;		/*feet*/
vector<float> vertLoc; 	/*feet*/
vector<float> horLoc; 	/*feet*/
double TubingID; 	/*inch*/
double CasingID; 	/*inch*/
double TSeaBed;		/* F */
double TSeaLevel;	/* F */
double USea;		/**/
double USurr;		/**/
double Perm;		/* mD */
double thickness;	/*feet*/
double DrainageArea;	/*feet^2*/
double rwb;		/*inch*/
double DLength;		/*inch*/
double DPerm;		/* mD */
double TRes;		/* F */
double PRes;		/* psia */
double Porosity;	/**/
double Sw;		/**/
double WCut;		/**/
double GOR;		/**/
double APIOil;		/* API */
double gammaG;		/**/
double gammaW;		/**/
double TWax;		/* F */
double Tsep;
double Psep;

/*----------------------------------END INPUT DECK--------------------------------------------------------------*/



double A; /*coefficient for choke equation*/
double B; /*coefficient for choke equation*/

double Bo; /*oil formation volume factor as function of pressure and temp*/
double Bg; /*gas formation volume factor as function of pressure and temp*/

double C; /*coefficient for choke equation*/
double CNL; /*Coefficient for H&B*/
double d; /*tubing diameter*/
double dPdL; /* pressure drop*/  
double D; /*choke diameter in 64ths of an inch*/

double fTP; /*friction factor for use in hagedorn and brown*/
double gammaL; /*no slip liquid holdup*/
double g = 32.2;
double GLR;

double HL; /*Liquid holdup*/

double muL; /*viscosities in cp*/
double muG;
double muO;
double muSlip;

/*Dimensionles numbers for hagedorn and Browm */
double Nd;
double NGV;
double NL;
double NLV;

double phi; /*Coefficient for Hagedorn and Brown*/
double P; /*What is P here???*/
double Pu; /*pressure upstream from choke */
double PNext;
double POld;
double Pguess;
double qL; /* liquid flowrate*/
double qO;
double qG;

double ReTP; /*Reynolds number for use in hagedorn and brown*/

double rhoL; /*liquid density in lbm/ft^3*/
double rhoLBH; /*liquid density at bottomhole*/
double rhoG;
double rhoTP;
double rhoNS;
double rhoSlip;

double Rs; /*Solution gas oil ratio as function of temp and Pressure*/
double sigma; /*surface tension in dynes*/

double theta; /*inclination angle*/
vector<float> TubingP;

double vslBH; /*superficial Velocity at bottomhole*/
double vsl; /*superficial velocities*/
double vsg;
double vm;




/*-----------------FLUID PROPERTIES-------------------------*/
double Bob;
double Co;	/*undersaturated oil compressibility*/
double gammaO;  /*Oil gravity*/
double Pb;  	/*Bubble Point Pressue*/
double Rsb; 	/*Solution Gas Oil ratio at bubble point*/
double X;   	/*Random parameter*/

double a;
double C1;
double C2;
double C3;
double CO; /*oil compressibility*/
double gammaG100;
double gammagd;
double Rp;
double rhoO;
double rhoW;
double muOb;
double muOd;
double b;
double m;
double Z;
double T;
double Ma;




/*Temp Equation*/
vector<float> Tf;
double T1;
double Tei;
double TemporaryT;
double gGEarth;
double gGSea;
double U;
double w;

double gG;
double Cp = 0.65;
/*
gGEarth = ...
dGSea = ...*/



/**/
double WH_Location;
double BHagedorn;
double H;
double Area;
double PFinal;
double counter;
double J;
double WHL;
double Pwf;
double CHO;
double rhoLi;
double qLi;
vector<float> rhoLvec;
vector<float> TEnv; 



