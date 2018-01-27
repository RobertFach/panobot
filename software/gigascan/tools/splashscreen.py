import sys
cx = -0.8;
cy = 0.156;

for x in range(0,128):
  for y in range(0,64):
      zx = float(x)/128 * 2 - 1;
      zy = float(y)/64 * 2 - 1;
      iteration = 0;
      max_iteration = 50;
      while (zx*zx+zy*zy<4 and iteration<max_iteration): 
        xtemp = zx*zx-zy*zy;
        zy = 2*zx*zy+cy;
        zx = xtemp + cx;

        iteration += 1;

      if (iteration == max_iteration):
         sys.stdout.write("1")
      else:
         sys.stdout.write("0")
