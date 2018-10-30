#ifndef CONFIGURATIONPROVIDER_H
#define CONFIGURATIONPROVIDER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <EEPROM.h>

#define MAX_CONFIG_OBJECT_COUNT 10

template < typename STRUCT_TYPE >
class ConfigurationProvider {
public:
	ConfigurationProvider() {}
	
	void init() {
		for (unsigned int t=0; t<sizeof(config); t++) {
			*((char*)&config + t) = EEPROM.read(t);
		}
		
		emitChange();
	}
	
	bool save() {
		bool hasChanged = false;
		
		for (unsigned int t=0; t<sizeof(config); t++) {
			if( EEPROM.read(t) != (byte)*((char*)&config + t) ){
				/*
				Serial.println(t);
				Serial.println(EEPROM.read(t), HEX);
				byte b = *((char*)&config + t);
				Serial.println(b, HEX);
				*/
				
				EEPROM.write(t, *((char*)&config + t));
				hasChanged = true;
			}
		}
		
		if (hasChanged) {
			emitChange();
		}
		
		return hasChanged;
	}
	
	STRUCT_TYPE* getConfig() {
		return &config;
	}
	
	class ConfigurationSupport {
	public:
		virtual void onConfigChanged(STRUCT_TYPE &config) = 0;
	};
	
	void registerConfigurable(ConfigurationSupport* object) {
		objects[objectCount] = object;
		objectCount++;
	}
	
private:
	STRUCT_TYPE config;
	uint8_t objectCount = 0;
	ConfigurationSupport* objects[MAX_CONFIG_OBJECT_COUNT];
	
	void emitChange() {
		for (uint8_t i=0;i<objectCount;i++) {
			objects[i]->onConfigChanged(config);
		}
	}
};


#endif		// CONFIGURATIONPROVIDER_H