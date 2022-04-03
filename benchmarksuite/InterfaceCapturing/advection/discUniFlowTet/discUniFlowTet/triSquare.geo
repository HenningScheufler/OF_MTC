nx=10;
nz=nx;

Point(1) = {-0, -0.5, 0, 1e+22};
Point(2) = {1, -0.5, 0, 1e+22};
Point(3) = {1, -0.5, 1, 1e+22};
Point(4) = {0, -0.5, 1, 1e+22};
Line(1) = {1, 2};
Line(2) = {2, 3};
Line(3) = {3, 4};
Line(4) = {4, 1};
Line Loop(6) = {4, 1, 2, 3};

Plane Surface(6) = {6};
Physical Volume("internal") = {1};

Transfinite Line{1} = nx;
Transfinite Line{2} = nz;
Transfinite Line{3} = nx;
Transfinite Line{4} = nz;


Extrude {0, 1, 0} {
    Surface{6};
    Layers{1};
    Recombine;
}

Physical Surface("back") = {6};
Physical Surface("rim") = {27, 15, 19, 23};
Physical Surface("front") = {28};
