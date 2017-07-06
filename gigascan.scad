use <MCAD/involute_gears.scad>
use <MCAD/bearing.scad>
use <MCAD/nuts_and_bolts.scad>
use <MCAD/motors.scad>
include <MCAD/stepper.scad>

$fn=100;

module mountgear() {
difference() {
union() {
    gear (
	number_of_teeth=81,
	circular_pitch=250, diametral_pitch=20,
	pressure_angle=28,
	clearance = 0.2,
	gear_thickness=7,
	rim_thickness=15,
	rim_width=5,
	hub_thickness=10,
	hub_diameter=15,
	bore_diameter=5,
	circles=0,
	backlash=0,
	twist=0,
	involute_facets=0,
	flat=false);
    //cylinder(r=15,h=20);
    cylinder(r1=45,r2=15,h=20);
}   
    translate([0,0,20-7+0.01])bearing(608,outline=true);
    translate([0,0,-0.01])bearing(608,outline=true);
    cylinder(r=4.1,h=50,center=true);
    
    rotate([0,0,45])translate([25,0,10+0.01])rotate([180,0,0])nutHole(4);
    rotate([0,0,45])translate([25,0,-0.01])cylinder(r=2,h=20);
    rotate([0,0,45])translate([25,0,10])cylinder(r=5,h=20);

    rotate([0,0,45])translate([-25,0,10+0.01])rotate([180,0,0])nutHole(4);
    rotate([0,0,45])translate([-25,0,-0.01])cylinder(r=2,h=20);
    rotate([0,0,45])translate([-25,0,10])cylinder(r=5,h=20);
}

}

module drivegear() {
    union() {
translate([56.25+9.02,0,0])gear (
	number_of_teeth=13,
	circular_pitch=250, diametral_pitch=20,
	pressure_angle=28,
	clearance = 0.2,
	gear_thickness=10,
	rim_thickness=15,
	rim_width=5,
	hub_thickness=10,
	hub_diameter=15,
	bore_diameter=5,
	circles=0,
	backlash=0,
	twist=0,
	involute_facets=0,
	flat=false);
        translate([56.25+9.02+1.9,-4,0])cube([3,8,15]);
    }
}

module pan() {
    difference() {
        union() {
            translate([-55,-40,21])cube([110,80,21]);
            translate([0,0,22])cylinder(r=15,h=20);
        }
        rotate([90,0,0])translate([40,31,-150])cylinder(r=4,h=300);
        rotate([90,0,0])translate([-40,31,-150])cylinder(r=4,h=300);
    //translate([0,56.25+9.02,28])rotate([180,0,0])stepper_motor_mount(17);
    
    cylinder(r=4.5,h=100);
    translate([0,0,20.9])bearing(608,outline=true);    
    translate([0,0,35.1])bearing(608,outline=true);
//    translate([20,23,31])minkowski(){
//        cylinder(r=8,h=10);
//        sphere(r=5);
//    }
//    translate([-20,23,31])minkowski(){
//        cylinder(r=8,h=10);
//        sphere(r=5);
//    }
//    translate([20,-23,31])minkowski(){
//        cylinder(r=8,h=10);
//        sphere(r=5);
//    }
//    translate([-20,-23,31])minkowski(){
//        cylinder(r=8,h=10);
//        sphere(r=5);
//    }
    translate([-150,-150,32])cube([300,300,0.1]);
    translate([30,30,0])cylinder(r=2,h=50);
    translate([50,30,0])cylinder(r=2,h=50);
    translate([30,0,0])cylinder(r=2,h=50);
    translate([50,0,0])cylinder(r=2,h=50);
    translate([30,-30,0])cylinder(r=2,h=50);
    translate([50,-30,0])cylinder(r=2,h=50);

    translate([-30,30,0])cylinder(r=2,h=50);
    translate([-50,30,0])cylinder(r=2,h=50);
    translate([-30,0,0])cylinder(r=2,h=50);
    translate([-50,0,0])cylinder(r=2,h=50);
    translate([-30,-30,0])cylinder(r=2,h=50);
    translate([-50,-30,0])cylinder(r=2,h=50);

  }    
}

module stepper() {
    motor(model=Nema17, size=NemaLong, dualAxis=false, pos=[56.25+9.02,0,25], orientation = [0,0,0]);
}

module steppermount() {
    difference() {
        translate([56.25+9.02-25,-55,21])cube([50,110,21]);
        //stepper();
        rotate([90,0,90])translate([40,31,-150])cylinder(r=4,h=300);
        rotate([90,0,90])translate([-40,31,-150])cylinder(r=4,h=300);        
    translate([56.25+9.02-26,-25,26])cube([55,50,30]);
    translate([56.25+9.02-25,-55,32])cube([300,300,0.1]);

    translate([56.25+9.02+31.04/2,31.04/2,0])cylinder(r=1.5,h=50);    
    translate([56.25+9.02-31.04/2,31.04/2,0])cylinder(r=1.5,h=50);    
    translate([56.25+9.02+31.04/2,-31.04/2,0])cylinder(r=1.5,h=50);    
    translate([56.25+9.02-31.04/2,-31.04/2,0])cylinder(r=1.5,h=50);
    
    translate([56.25+9.02,0,0])cylinder(r=12,h=50);    
        
    translate([56.25+9.02-15,30,0])cylinder(r=2,h=50);
    translate([56.25+9.02-15,50,0])cylinder(r=2,h=50);
    translate([56.25+9.02+15,30,0])cylinder(r=2,h=50);
    translate([56.25+9.02+15,50,0])cylinder(r=2,h=50);
        
    translate([56.25+9.02-15,-30,0])cylinder(r=2,h=50);
    translate([56.25+9.02-15,-50,0])cylinder(r=2,h=50);
    translate([56.25+9.02+15,-30,0])cylinder(r=2,h=50);
    translate([56.25+9.02+15,-50,0])cylinder(r=2,h=50);
    }
}

module panrods() {
    rotate([90,0,90])translate([40,31,-150])cylinder(r=4,h=300);
    rotate([90,0,90])translate([-40,31,-150])cylinder(r=4,h=300);    
}

module tiltsiderods() {
    rotate([0,0,90])translate([40,130,35])cylinder(r=4,h=100);
    rotate([0,0,90])translate([-40,130,35])cylinder(r=4,h=100);    
}

module tiltbaserods() {
    rotate([90,0,90])translate([30,100,-100.1])cylinder(r=4,h=200.2);
    rotate([90,0,90])translate([-30,100,-100.1])cylinder(r=4,h=200.2);    
}

module tiltside() {
    difference() {
        hull() {
            rotate([90,0,90])translate([0,145,100-10])cylinder(r=20,h=10);
            rotate([90,0,90])translate([-30,100,100-10])cylinder(r=10,h=10);
            rotate([90,0,90])translate([30,100,100-10])cylinder(r=10,h=10);
        }
        rotate([90,0,90])translate([-30,100,100-10-5])cube([60,1,1000]);            
       hull() {
           rotate([90,0,90])translate([-25,110,100-10.1])cylinder(r=3,h=11);
           rotate([90,0,90])translate([25,110,100-10.1])cylinder(r=3,h=11);
           rotate([90,0,90])translate([-10,120,100-10.1])cylinder(r=5,h=11);
           rotate([90,0,90])translate([10,120,100-10.1])cylinder(r=5,h=11);
       }
        
        rotate([90,0,90])translate([0,145,100-10-0.1])bearing(608,outline=true);
        rotate([90,0,90])translate([0,145,100-10-0.1])cylinder(r=5,h=100);
       
       rotate([90,0,90])translate([-20,110,100-5])rotate([90,0,0])cylinder(r=2,h=30);
       rotate([90,0,90])translate([20,110,100-5])rotate([90,0,0])cylinder(r=2,h=30);
    
    rotate([90,0,90])translate([30,100,-100.1])cylinder(r=4,h=200.2);
    rotate([90,0,90])translate([-30,100,-100.1])cylinder(r=4,h=200.2);    
    }

}

module tiltsidedrive() {
    difference() {
        rotate([0,0,180])tiltside();
        rotate([0,0,180])rotate([90,0,90])translate([0,130,100-10-0.1])cylinder(r=2,h=20);
        rotate([0,0,180])rotate([90,0,90])translate([0,160,100-10-0.1])cylinder(r=2,h=40);
    }
}

module tiltsidedrivegear() {
    difference() {
        union() {
        rotate([0,0,180])rotate([90,0,90])translate([0,145,100])
    gear (
	number_of_teeth=51,
	circular_pitch=250, diametral_pitch=20,
	pressure_angle=28,
	clearance = 0.2,
	gear_thickness=7,
	rim_thickness=14,
	rim_width=5,
	hub_thickness=14,
	hub_diameter=39,
	bore_diameter=10,
	circles=0,
	backlash=0,
	twist=0,
	involute_facets=0,
	flat=false);
//        rotate([0,0,180])rotate([90,0,90])translate([0,145,100+4+0.1])cylinder(r1=25,r2=20,h=11);
        }
        rotate([0,0,180])rotate([90,0,90])translate([0,145,107+0.1])bearing(608,outline=true);
//        rotate([0,0,180])rotate([90,0,90])translate([0,145,100-10+0.1])cylinder(r=5,h=50);
        rotate([0,0,180])rotate([90,0,90])translate([0,130,100-10-0.1])cylinder(r=2,h=40);
        rotate([0,0,180])rotate([90,0,90])translate([0,160,100-10-0.1])cylinder(r=2,h=40);
    }   
}

module tiltsidesteppergear() {
    union() {
        rotate([0,0,180])rotate([90,0,90])translate([0,145-35.4167-9.02778,100])
    gear(
	number_of_teeth=13,
	circular_pitch=250, diametral_pitch=20,
	pressure_angle=28,
	clearance = 0.2,
	gear_thickness=15,
	rim_thickness=15,
	rim_width=5,
	hub_thickness=10,
	hub_diameter=15,
	bore_diameter=5,
	circles=0,
	backlash=0,
	twist=0,
	involute_facets=0,
	flat=false);
        rotate([0,0,180])rotate([90,0,90])translate([1.9,145-35.4167-9.02778-4,100])cube([3,8,15]);
    }   
}

module tiltsidestepper() {
    rotate([0,0,180])rotate([90,0,90])translate([0,145-35.4167-9.02778,100])motor(model=Nema17, size=NemaLong, dualAxis=false, pos=[0,0,25], orientation = [0,0,0]);
}

module tiltsteppermount() {
    difference() {
        union() {
        hull() {
            rotate([0,0,180])rotate([90,0,90])translate([0,145,100+25-5])cylinder(r=20,h=10);
            rotate([0,0,180])rotate([90,0,90])translate([45,145-35.4167,100+25-5])cylinder(r=10,h=10);
            rotate([0,0,180])rotate([90,0,90])translate([-45,145-35.4167,100+25-5])cylinder(r=10,h=10);
    
            rotate([0,0,180])rotate([90,0,90])translate([45,145-35.4167-25,100+25-5])cylinder(r=10,h=10);
            rotate([0,0,180])rotate([90,0,90])translate([-45,145-35.4167-25,100+25-5])cylinder(r=10,h=10);
        }
    hull() {    
            rotate([0,0,180])rotate([90,0,90])translate([45,145-35.4167,100+25-5+10.1])cylinder(r=10,h=10);
            rotate([0,0,180])rotate([90,0,90])translate([-45,145-35.4167,100+25-5+10.1])cylinder(r=10,h=10);
    
            rotate([0,0,180])rotate([90,0,90])translate([45,145-35.4167-25,100+25-5+10.1])cylinder(r=10,h=10);
            rotate([0,0,180])rotate([90,0,90])translate([-45,145-35.4167-25,100+25-5+10.1])cylinder(r=10,h=10);
    }
}

        rotate([0,0,180])rotate([90,0,90])translate([0,145-35.4167-9.02778,100])cylinder(r=12,h=40);

        //stepper mount screws
        rotate([0,0,180])rotate([90,0,90])translate([31.04/2,145-35.4167-9.02778-31.04/2,100])cylinder(r=1.5,h=50);    
        rotate([0,0,180])rotate([90,0,90])translate([-31.04/2,145-35.4167-9.02778-31.04/2,100])cylinder(r=1.5,h=50);    
        rotate([0,0,180])rotate([90,0,90])translate([31.04/2,145-35.4167-9.02778+31.04/2,100])cylinder(r=1.5,h=50);    
        rotate([0,0,180])rotate([90,0,90])translate([-31.04/2,145-35.4167-9.02778+31.04/2,100])cylinder(r=1.5,h=50);
    
        rotate([0,0,180])rotate([90,0,90])translate([0,145,100+25-2+0.1])bearing(608,outline=true);
        rotate([0,0,180])rotate([90,0,90])translate([0,145,100+10])cylinder(r=5,h=50);
        tiltsidestepper();
        rotate([0,0,180])rotate([90,0,90])translate([-45/2,145-35.4167-9.02778-45/2,100+25])cube([45,45,10]);
        tiltsiderods();
        rotate([0,0,180])rotate([90,0,90])translate([-45/2,145-35.4167-9.02778-45/2-5,100+25-5+10.1])cube([45,60,11]);
        //side screws
       rotate([0,0,180])rotate([90,0,90])translate([47,145-35.4167,100])cylinder(r=2,h=50);
       rotate([0,0,180])rotate([90,0,90])translate([28,145-35.4167,100])cylinder(r=2,h=50);
       rotate([0,0,180])rotate([90,0,90])translate([47,145-35.4167-25,100])cylinder(r=2,h=50);
       rotate([0,0,180])rotate([90,0,90])translate([28,145-35.4167-25,100])cylinder(r=2,h=50);
        
       rotate([0,0,180])rotate([90,0,90])translate([-47,145-35.4167,100])cylinder(r=2,h=50);
       rotate([0,0,180])rotate([90,0,90])translate([-28,145-35.4167,100])cylinder(r=2,h=50);
       rotate([0,0,180])rotate([90,0,90])translate([-47,145-35.4167-25,100])cylinder(r=2,h=50);
       rotate([0,0,180])rotate([90,0,90])translate([-28,145-35.4167-25,100])cylinder(r=2,h=50);

    }
}

module pantiltconnector() {
    difference() {
        translate([-140,-50,20])cube([40,100,50]);
        translate([-119.9,-60,40])cube([20,130,40]);
        translate([-150,-40,30])cube([70,80,1]);
        translate([-130,-60,40])cube([20,120,1]);
        translate([-130,-60,40])cube([1,120,50]);
        translate([-110,-30,10])cylinder(r=2,h=40);
        translate([-110,30,10])cylinder(r=2,h=40);
        rotate([90,0,90])translate([-30,47,-160])cylinder(r=2,h=60);
        rotate([90,0,90])translate([30,47,-160])cylinder(r=2,h=60);
        rotate([90,0,90])translate([-30,63,-160])cylinder(r=2,h=60);
        rotate([90,0,90])translate([30,63,-160])cylinder(r=2,h=60);
        panrods();
        tiltsiderods();
    }
}

mountgear();
drivegear();
rotate([0,0,90])pan();
stepper();
steppermount();
color("green")panrods();
color("green")tiltsiderods();
color("green")tiltbaserods();
tiltside();
tiltsidedrive();
tiltsidedrivegear();
tiltsidesteppergear();
tiltsidestepper();
tiltsteppermount();
rotate([0,0,180])tiltsteppermount();
pantiltconnector();
