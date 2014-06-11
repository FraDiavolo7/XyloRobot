// Bloc Glockenspiel Moteur

// Hauteur : 15 mm
// Largeur : 72 mm
// Longueur : 80.5 mm

Hauteur = 17.5;
Largeur = 72;
Longueur = 80.5;
EpaisseurCale = 2;
EpaisseurAxes = 5;
EpaisseurSocle = 20;

support ();

translate ([ -EpaisseurCale, -EpaisseurCale, Hauteur - EpaisseurCale] ) 
	cale ();

translate ([ Longueur + EpaisseurCale, -EpaisseurCale, Hauteur - EpaisseurCale] ) 
	rotate ([ 0, 0, 90])
		cale ();

translate ([ Longueur + EpaisseurCale, Largeur + EpaisseurCale, Hauteur - EpaisseurCale] ) 
	rotate ([ 0, 0, 180])
		cale ();

translate ([ -EpaisseurCale, Largeur + EpaisseurCale, Hauteur - EpaisseurCale] ) 
	rotate ([ 0, 0, 270])
		cale ();


module cale ()
{
	C0 = [ EpaisseurAxes + EpaisseurCale, 0,             0];
	C1 = [ 0,             0,             0];
	C2 = [ 0,             EpaisseurAxes + EpaisseurCale, 0];
	C3 = [ EpaisseurAxes + EpaisseurCale, EpaisseurCale, 0];
	C4 = [ EpaisseurCale, EpaisseurCale, 0];
	C5 = [ EpaisseurCale, EpaisseurAxes + EpaisseurCale, 0];
	C6 = [ EpaisseurAxes + EpaisseurCale, EpaisseurCale, -EpaisseurCale];
	C7 = [ EpaisseurCale, EpaisseurCale, -EpaisseurCale];
	C8 = [ EpaisseurCale, EpaisseurAxes + EpaisseurCale, -EpaisseurCale];

	cube ( [ EpaisseurCale, EpaisseurAxes + EpaisseurCale, EpaisseurCale * 2] );
	cube ( [ EpaisseurAxes + EpaisseurCale, EpaisseurCale, EpaisseurCale * 2] );

	polyhedron 
		( points = [ 
				   C0, C1, C2, C3, C4, C5, C6, C7, C8,
				  ],
		  triangles = [ 
					[ 0, 3, 6], [ 2, 8, 5],
					[ 3, 4, 7], [ 6, 3, 7],
					[ 5, 7, 4], [ 5, 8, 7],
					[ 0, 7, 1], [ 0, 6, 7],
					[ 1, 8, 2], [ 1, 7, 8],
					[ 0, 1, 4], [ 0, 3, 4],
					[ 4, 5, 2], [ 4, 1, 2],
				  ]
		);
}

module support ()
{
P0  = [ 0, 0, 0];
P1  = [ 0, EpaisseurAxes, 0];
P2  = [ Longueur / 2 - EpaisseurAxes, Largeur / 2, 0];
P3  = [ 0, Largeur - EpaisseurAxes, 0];
P4  = [ 0, Largeur, 0];
P5  = [ EpaisseurAxes, Largeur, 0];
P6  = [ Longueur / 2, Largeur / 2 + EpaisseurAxes, 0];
P7  = [ Longueur - EpaisseurAxes, Largeur, 0];
P8  = [ Longueur, Largeur, 0];
P9  = [ Longueur, Largeur - EpaisseurAxes, 0];
P10 = [ Longueur / 2 + EpaisseurAxes, Largeur / 2, 0];
P11 = [ Longueur, EpaisseurAxes, 0];
P12 = [ Longueur, 0, 0];
P13 = [ Longueur - EpaisseurAxes, 0, 0];
P14 = [ Longueur / 2, Largeur / 2 - EpaisseurAxes, 0];
P15 = [ EpaisseurAxes, 0, 0];

P16 = [ 0, 0, Hauteur];
P17 = [ 0, EpaisseurAxes, Hauteur];
P18 = [ Longueur / 2 - EpaisseurAxes, Largeur / 2, Hauteur];
P19 = [ 0, Largeur - EpaisseurAxes, Hauteur];
P20 = [ 0, Largeur, Hauteur];
P21 = [ EpaisseurAxes, Largeur, Hauteur];
P22 = [ Longueur / 2, Largeur / 2 + EpaisseurAxes, Hauteur];
P23 = [ Longueur - EpaisseurAxes, Largeur, Hauteur];
P24 = [ Longueur, Largeur, Hauteur];
P25 = [ Longueur, Largeur - EpaisseurAxes, Hauteur];
P26 = [ Longueur / 2 + EpaisseurAxes, Largeur / 2, Hauteur];
P27 = [ Longueur, EpaisseurAxes, Hauteur];
P28 = [ Longueur, 0, Hauteur];
P29 = [ Longueur - EpaisseurAxes, 0, Hauteur];
P30 = [ Longueur / 2, Largeur / 2 - EpaisseurAxes, Hauteur];
P31 = [ EpaisseurAxes, 0, Hauteur];


	polyhedron 
		( points = [ 
				   P0,  P1,  P2,  P3,  P4,  P5,  P6,  P7, 
				   P8,  P9,  P10, P11, P12, P13, P14, P15, 
				   P16, P17, P18, P19, P20, P21, P22, P23, 
                    P24, P25, P26, P27, P28, P29, P30, P31 
				  ],
		  triangles = [ 
					  [  0, 15,  1], [  1, 15,  7],
					  [  4,  3,  5], [  3, 13,  5],
					  [  8,  7,  9], [  7, 15,  9],
					  [ 12, 11, 13], [ 13, 11,  5],

					  [  0,  1, 16], [  1, 17, 16], 
					  [  0, 16, 15], [ 15, 16, 31], 

					  [  4,  5, 20], [  5, 21, 20], 
					  [  4, 20, 19], [  4, 19,  3], 

					  [  8,  9, 24], [  9, 25, 24], 
					  [  8, 24, 23], [  8, 23,  7], 

					  [ 12, 13, 28], [ 13, 29, 28], 
					  [ 12, 28, 27], [ 12, 27, 11], 

					  [  1,  7, 17], [  7, 23, 17],
					  [ 15, 31,  9], [  9, 31, 25],

					  [  5, 11, 21], [ 11, 27, 21],
					  [  3, 19, 13], [ 13, 19, 29],

					  [ 16, 17, 31], [ 17, 23, 31],
					  [ 20, 21, 19], [ 19, 21, 27],
					  [ 24, 25, 23], [ 23, 25, 31],
					  [ 28, 29, 27], [ 29, 19, 27]
				  ]
		);
}