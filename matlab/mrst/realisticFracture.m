mrstModule add ad-props  ad-core ad-blackoil

%% Grid, petrophysics, and fluid objects
TS = 1;
% The grid and rock model
load('xdata.mat')
load('ydata.mat')
permeability = 0.01;
porosity = 0.06;
%Create delaunay triangulation
%must be stored in this format for well location function
DT = delaunayTriangulation(x(:), y(:));
   n = size(DT,1);
%store this same triangulation using type double
%must be in this format for triangleGrid function
   for j = 1:3
        for i = 1:n
            t(i,j) = DT(i,j);
        end
   end


plot(x(:),y(:),'k.','MarkerSize',12);

%t = delaunay(x(:), y(:));
G = triangleGrid([x(:) y(:)], t);

plotGrid(G,'FaceColor','none');

Geom = computeGeometry(G);
G = Geom;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
rock = makeRock(G, permeability*milli*darcy, porosity);
%alter permeability of the fracture
%by finding a specific size element and changing
%the permeability in these cells
 
[N,edges] = histcounts(Geom.cells.volumes,10000)
[val, idx] = max(N(:));
minimum = edges(idx);
maximum = edges(idx+1);
histogram(Geom.cells.volumes,100);
for i = 1:n
    if Geom.cells.volumes(i) > 0 && Geom.cells.volumes(i) < 3.5
        rock.perm(i) = permeability*100;
        rock.poro(i) = porosity*6;
    end
end

plotCellData(G,rock.perm)
% Fluid properties
pR  = 200*barsa;
fluid = initSimpleADIFluid('phases','W',           ... % Fluid phase: water
                           'mu',  1*centi*poise,   ... % Viscosity
                           'rho', 1000,            ... % Surface density [kg/m^3]
                           'c',   1e-4/barsa,      ... % Fluid compressibility
                           'cR',  1e-5/barsa       ... % Rock compressibility
                           );

%% Make Reservoir Model
gravity reset on
wModel = WaterModel(G, rock, fluid,'gravity',gravity);


% Well: at the midpoint of the south edge
%Specify well location
   WellLocation = [61, 15.27];
   %Find triangular element that point is located in
   ID = pointLocation(DT, WellLocation);
   %Create well using this point
W = addWell([], G, rock,  ID,     ...
        'Type', 'bhp', 'Val', pR-50*barsa, ...
        'Radius', 0.01, 'Name', 'P1','Comp_i',1,'sign',1);


% Boundary conditions: fixed pressure at bottom and no-flow elsewhere
% West sides (high pressure)
   d  = abs(Geom.faces.centroids(:,1) - min(Geom.faces.centroids(:,1)));
   ws = find (d < 1e6*eps);
   hw = plotFaces(Geom, ws, 'FaceColor', 'r');

   % East sides (low pressure)
   d  = abs(Geom.faces.centroids(:,1) - max(Geom.faces.centroids(:,1)));
   es = find (d < 1e6*eps);
   he = plotFaces(Geom, es, 'FaceColor', 'b'); drawnow
   
 % South sides (high pressure)
   d  = abs(Geom.faces.centroids(:,2) - min(Geom.faces.centroids(:,2)));
   ss = find (d < 1e6*eps);
   hs = plotFaces(Geom, ss, 'FaceColor', 'r');

   % North sides (low pressure)
   d  = abs(Geom.faces.centroids(:,2) - max(Geom.faces.centroids(:,2)));
   ns = find (d < 1e6*eps);
   hn = plotFaces(Geom, ns, 'FaceColor', 'b'); drawnow  

   bc = addBC([], ws, 'pressure', 250*barsa,'sat',1);
   bc = addBC(bc, es, 'pressure', 100*barsa,'sat',1);
   bc = addBC(bc, ns, 'pressure', 250*barsa,'sat',1);
   bc = addBC(bc, ss, 'pressure', 100*barsa,'sat',1);

% Schedule: describing time intervals and corresponding drive mechanisms
schedule1 = simpleSchedule(diff(linspace(0,0.5*day,41)), 'bc', bc, 'W', W);
schedule2 = simpleSchedule(diff(linspace(0,TS*day,41)), 'W', W);

%% Reservoir state
state.pressure = ones(G.cells.num,1)*pR;                % Constant pressure
state.wellSol  = initWellSolAD([], wModel, state);      % No well initially

% Vertical equilibrium
%verbose = false;
%nonlinear = NonLinearSolver;
%state = nonlinear.solveTimestep(state, 100*day, wModel, 'bc', bc);

clf,
plotCellData(G,state.pressure/barsa,'EdgeColor','none');
colorbar

%% Run simulations

% Simulation pressure 200 bar at top
[wellSols1, states1] = simulateScheduleAD(state, wModel, schedule2);


%% Plot results
% Prepare animation
wc = ID;
wpos = G.cells.centroids(wc,:); clf
set(gcf,'Position',[600 400 800 400])

h1 = subplot('Position',[.1 .11 .34 .815]);
hp1 = plotCellData(G,state.pressure/barsa,'EdgeColor','none');
title('Open compartment w/aquifer'); caxis([pR/barsa-50 pR/barsa]);

h2 = subplot('Position',[.54 .11 .4213 .815]);
hp2 = plotCellData(G,state.pressure/barsa,'EdgeColor','none');
title('Closed compartment'); caxis([pR/barsa-50 pR/barsa]);

colormap(jet(32)); colorbar

% Animate solutions
for i=1:numel(states1)
    set(hp1,'CData', states1{i}.pressure/barsa);
    set(hp2,'CData', states2{i}.pressure/barsa);
    drawnow, pause(0.1);
end

% Launch plotting of well responses
plotWellSols({wellSols1,wellSols2}, ...
    'Datasetnames',{'Aquifer','Closed'}, 'field','qWr');


for i = 1:numel(states2)
    ROMp(i) = 0;
    for j = 1:n
        ROMp(i) = ROMp(i) + states1{i}.pressure(j);
        p(j,i)= states1{i}.pressure(j);
    end
    ROMp(i)=ROMp(i)/n;
end

[u,s,v] = svd(p);
plot(diag(s))
plot(real(u(:,1:1)))
plotCellData(G,u(:,1:1))
plotCellData(G,u(:,20:20))