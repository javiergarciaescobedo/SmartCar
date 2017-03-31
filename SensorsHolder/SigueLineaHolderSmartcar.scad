separacionTornillos = 50;
fondoSoportes = 8;
grosorSuelo = 2;
alturaTotal = 35;
huecoX = 30;
tamXTotal = separacionTornillos + fondoSoportes;
distanciaTornilloSensor = 17;

// Soporte izquierdo
difference() {
    cube([tamXTotal/2-huecoX/2+0.1, fondoSoportes, 10]);
    translate([fondoSoportes/2, fondoSoportes/2, -0.1]) {
        cylinder(h = 15.2, r = 1.8, $fn=100);
    }
}

// Soporte derecho
difference() {
    translate([tamXTotal/2+huecoX/2-0.1, 0, -0.1]) {
        cube([tamXTotal/2-huecoX/2, fondoSoportes, 10]);
    }
    translate([separacionTornillos+fondoSoportes/2, fondoSoportes/2, -0.2]) {
        cylinder(h = 15.2, r = 1.8, $fn=100);
    }
}

// Suelo soporte
translate([tamXTotal/2-huecoX/2, 0, 0]) {
    difference() {
        cube([huecoX, distanciaTornilloSensor + 6, grosorSuelo]);
        translate([huecoX/2, distanciaTornilloSensor, 0]) {
            translate([-7, 0, 0]) {
                cylinder(h = 15.2, r = 1.8, $fn=100);
            }
            translate([7, 0, 0]) {
                cylinder(h = 15.2, r = 1.8, $fn=100);
            }
        }        
    }
}



//    translate([20 + 5 + 22, 6, -0.1]) {
//        cylinder(h = 5.2, r = 1.8, $fn=100);
//    }
    
// 14 ancho
// 24 hasta tornillo

//translate([9, 0, 0]) {    
//    // base central
//    difference() {
//        cube([5 + 24 + 5, 12, 20]);
//        // Hueco
//        translate([5, 0, 0]) {    
//            cube([24, 12, 15]);
//        }
//    }
//    // Ala Izquierda
//    difference() {
//        cube([5, 12, 20 + 16]);
//        translate([5/2, 12/2, 20 + 16 - 8]) {
//            cylinder(h = 8.1, r = 1.3, $fn=100);
//        }
//    }
//    // Ala Derecha
//    translate([5 + 24, 0, 0]) {
//        difference() {
//            cube([5, 12, 20 + 16]);
//            translate([5/2, 12/2, 20 + 16 - 8]) {
//                cylinder(h = 8.1, r = 1.3, $fn=100);
//            }
//            // Muesca para cable
//            translate([-0.1, -0.1, 24]) {
//                cube([5.2, 8, 3]);
//            }
//        }
//    }
//}
