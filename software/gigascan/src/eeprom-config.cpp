#include <eeprom-config.h>

#include <EEPROM.h>

StoreStruct default_config = DEFAULT_CONFIG;

StoreStruct user_config = DEFAULT_CONFIG;

void loadConfig() {
  // To make sure there are settings, and they are YOURS!
  // If nothing is found it will use the default settings.
  if (EEPROM.read(CONFIG_START + 0) == CONFIG_VERSION[0] &&
      EEPROM.read(CONFIG_START + 1) == CONFIG_VERSION[1] &&
      EEPROM.read(CONFIG_START + 2) == CONFIG_VERSION[2]) {
      for (unsigned int t=0; t<sizeof(user_config); t++)
        *((char*)&user_config + t) = EEPROM.read(CONFIG_START + t);
    } else {
      resetToDefaultConfig();
    }
}

void resetToDefaultConfig() {
  for (unsigned int t=0; t<sizeof(default_config); t++)
    EEPROM.write(CONFIG_START + t, *((char*)&default_config + t));
  loadConfig();
}

void saveConfig() {
  for (unsigned int t=0; t<sizeof(user_config); t++)
    EEPROM.write(CONFIG_START + t, *((char*)&user_config + t));
}
