
clipInnerRad = 2.5;
clipThikness = 1;
clipHeight = 10;

supportWidth = 0;
supportHeight = 0;

rotate([0,0,-90]){
	clip(ir=clipInnerRad-supportWidth/2,t=clipThikness+supportWidth,h=supportHeight);
	translate([0,0,supportHeight])clip();
}

module clip(ir=clipInnerRad,t=clipThikness,h=clipHeight){

	difference(){
		cylinder(r=ir+t,h=h,$fn=PI*(ir+t)*5);
		translate([0,0,-.5])
		cylinder(r=ir,h=h+1,$fn=PI*ir*5);

		rotate([0,0,-45])
		translate([0,0,-.5])
		cube([10e10,10e10,h+1]);
	}

	for (r=[-45,45]) rotate([0,0,r])
	translate([ir+t,0,0])
	cylinder(r=t,h=h,$fn=PI*t*5);

}
