PANOBOT: A Panorama robot, version 1

Panobot is a full automatic robot, which can be used to create Panoramas and Gigapixels with small and large cameras (like DSLRs). The camera is mounted on a turret to allow pan/tilt motion. After programming the capture parameters, the robot will start to rotate the camera, taking one (or multiple) pictures per position and making sure that the capture positions have enough overlap.

Panobot has the following menu features:
 * Scan
   * starts a Scan
 * Take picture
   * allows to manually take a picture, this is usefull for testing the camera trigger connection
 * Setup
   * Pan Left, Pan Right, Tilt Up, Tilt Down
     * defines the scan area of the panorama/gigapixel, the head will move while the range is defined
   * Image P-Delay
     * the longer, the more time the camera has to measure and (eventually focus, if not in manual camera mode), triggers focusing of camera
   * Image Delay
     * the delay it take for the camera to write the image to the card and/or the time it needs to stabilize the mechanical system due to rotating motion
   * Shutter Delay
     * how long the shutter will be pressed
   * Focal Length
     * the focal length which is currently by the camera
   * Horizontal& Vertical Overlap
     * defines the overlap between consecutive images, a value between 30% and 50% makes sense, usually depends on the capture situation
   * Crop factor
     * in combination with the focal length, can be used to calculate field of view, which is required for horizontal&vertical overlap

Required Hardware:
 * 3d printed parts
   * Please have a look at [Panobot at Thingiverse](https://www.thingiverse.com/thing:2503118) to find out the parts that need to be printed
 * mechanical parts
   * some screws, washers, nuts M3, M4
   * some bearings 608 (around 10)
   * some rods 8mm (for structure and as axis)
 * electronic parts
   * 2 stepper motors Nema17, like 42BYGHM810
   * Arduino Mega 2560
   * Reprap Full Graphic SmartLCD with clickencoder
   * the controller PCB (this is missing yet), which consists of two stepper drivers A4988 and two optocopplers; a PCB version will follow soon

Required Software:
   * install atom editor
     * https://atom.io/ -> install deb
   * follow steps on http://platformio.org/get-started/ide?install=atom
     * install platformio-ide package inside atom
   * code completion
     * apt-get install clang
