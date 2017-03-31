separacionTornillos = 50;
fondo = 12;
grosor = 5;
alturaTotal = 35;
huecoXMotor = 24;
huecoYMotor = 16;

rotate([-90, 0, 0]) {
    // Suelo
    difference() {
        cube([separacionTornillos+fondo, fondo, grosor]);
        // Perforaciones fijaciones suelo
        translate([fondo/2, fondo/2, -0.1]) {
            cylinder(h = 5.2, r = 1.8, $fn=100);
        }
        translate([separacionTornillos+fondo/2, fondo/2, -0.1]) {
            cylinder(h = 5.2, r = 1.8, $fn=100);
        }
    }

    // Ala Izquierda
    translate([fondo, 0, 0]) {
        difference() {
            cube([grosor, fondo, alturaTotal]);
            // Fijación motor
            translate([grosor/2, fondo/2, alturaTotal - 8]) {
                cylinder(h = 8.1, r = 1.3, $fn=100);
            }    
        }    
    }
    
    // Ala Derecha
    translate([fondo + huecoXMotor + grosor, 0, 0]) {
        difference() {
            cube([grosor, fondo, alturaTotal]);
            // Fijación motor
            translate([5/2, fondo/2, alturaTotal - 8]) {
                cylinder(h = 8.1, r = 1.3, $fn=100);
            }
            // Muesca para cable
            translate([-0.1, -0.1, 23]) {
                cube([5.2, 8, 3]);
            }
        }
    }
    
    // Base motor
    translate([fondo, 0, alturaTotal - huecoYMotor - grosor]) {
        cube([huecoXMotor+grosor*2, fondo, grosor]);
    }    

//    translate([9, 0, 0]) {    
//        // base central
//        difference() {
//            cube([5 + 24 + 5, tamY, 20]);
//            // Hueco
//            translate([5, 0, 0]) {    
//                cube([24, tamY, 15]);
//            }
//        }
//        // Ala Izquierda
//        difference() {
//            cube([grosor, tamY, 20 + 16]);
//            translate([5/2, tamY/2, 20 + 16 - 8]) {
//                cylinder(h = 8.1, r = 1.3, $fn=100);
//            }
//        }
//        // Ala Derecha
//        translate([5 + 24, 0, 0]) {
//            difference() {
//                cube([grosor, tamY, 20 + 16]);
//                translate([5/2, tamY/2, 20 + 16 - 8]) {
//                    cylinder(h = 8.1, r = 1.3, $fn=100);
//                }
//                // Muesca para cable
//                translate([-0.1, -0.1, 24]) {
//                    cube([5.2, 8, 3]);
//                }
//            }
//        }
//    }
}
