// AgriProbe - Parametric Carriage & Motor Mount Script
// Compatible with OpenSCAD Online / Desktop Modeler

module carriage_mount() {
    difference() {
        // Main structural block for the linear carriage
        cube([50, 40, 15], center = true);
        
        // T8 Lead Screw clearance hole
        cylinder(h = 20, r = 4.5, center = true);
        
        // Guide rod holes for twin 8mm smooth rods
        translate([18, 0, 0])
            cylinder(h = 20, r = 4.2, center = true);
        translate([-18, 0, 0])
            cylinder(h = 20, r = 4.2, center = true);
            
        // Mounting screw holes
        translate([0, 14, 0])
            cylinder(h = 20, r = 1.8, center = true);
        translate([0, -14, 0])
            cylinder(h = 20, r = 1.8, center = true);
    }
}

// Render the 3D model
carriage_mount();
