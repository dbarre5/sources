/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    IMPESFoam

Description
    Reservoir simulation through the IMPES method

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "simpleControl.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCase.H"

    #include "createTime.H"
    #include "createMesh.H"

    #include "createFields.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    
    

    Info << Vol << endl;
     while (runTime.run())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

	runTime++;
   
	    /*Brooks and Corey calculation of rel perms*/
            kro = kroMax * Foam::pow((((1-Sw) - Sor) / (1-Sor-Swr)),kroCoefA);
	    krw = krwMax * Foam::pow(((Sw - Swr) / (1-Sor-Swr)),krwCoefA);
	    Info << "interpolating" << endl;
	    /*surfaceScalarField To = fvc::interpolate(kro);*/
	    surfaceScalarField To("To", mult1 * perm / nuOil * fvc::interpolate(kro));
            surfaceScalarField Tw("Tw", mult2 * perm / nuWater * fvc::interpolate(krw));
            surfaceScalarField T("T", Tw+To);
            Info << "interpolating done" << endl;
	    volScalarField fw("fw", 1/(1+nuWater / ((krw+0.0001)) * kro / nuOil));
	    
            Info << fw << endl;

	     Pc = CoefA*Foam::pow(Sw,CoefB);

    	    Info<< "\nCalculating Pressure Distribution\n" << endl;
            /*nEED TO FIX UNIT CONVERSION IN FRONT OF DDT*/
	    fvScalarMatrix PEqn
            (
            ct*por*fvm::ddt(P) == fvm::laplacian(T,P) - qw - qo
            );

            /*Calculate Water pressures*/
            Pw = P - Pc;
	    

            #include "UEqn.H"
          

	    /*Vol is the time conversion... needs to be renamed...*/
	    Info<< "\nCalculating Saturation Distribution\n" << endl;
	    /*Sw == Sw  -Vol / por * fvc::laplacian(Tw, P)+Vol / por *qw;*/
	    fvScalarMatrix SwEqn
            (
            fvm::ddt(Sw) == -1 / por * fvc::laplacian(Tw, P)+qw / por + qo/por*1/(1+nuWater / ((krw+0.000000000000000000000000001)) * kro / nuOil)
	    );


            
	 
            PEqn.solve();
	    SwEqn.solve();
            
        

        #include "write.H"

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
