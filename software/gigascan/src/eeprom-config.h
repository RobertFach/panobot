#ifndef __EEPROM_CONFIG_H__
#define __EEPROM_CONFIG_H__

#define CONFIG_VERSION "PB1"

#define CONFIG_START 32

struct StoreStruct {
  char version[4];
  double crop_factor;
  int focal_length;
  int horizontal_overlap;
  int vertical_overlap;
  int pan_steps_per_degree;
  int tilt_steps_per_degree;
  double maximum_pan_speed;
  double pan_acceleration;
  double maximum_tilt_speed;
  double tilt_acceleration;
  int stabilize_and_write_delay;
  int focus_delay;
  int trigger_delay;
  int scan_max_pan_left;
  int scan_max_pan_right;
  int scan_max_tilt_up;
  int scan_max_tilt_down;
};

extern StoreStruct user_config;

#define DEFAULT_CONFIG { CONFIG_VERSION, 1.6, 70, 30, 30, 56, 35 /*50 for big gear*/, 3000.0, 2000.0, 2000.0, 2000.0, 500, 250, 500, -10, 10, 5, -5}

void loadConfig();
void resetToDefaultConfig();
void saveConfig();

#endif
