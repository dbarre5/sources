/*give directions of velocity based on pressure*/

Uwd == -100000*fvc::grad(P);

Uod == -100000*fvc::grad(P);
