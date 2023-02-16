#ifndef LoadJSONFromSD_h
#define LoadJSONFromSD_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD.h>

class LoadJSONFromSD {
   private:
    File _file;
    char _filename[256];
    StaticJsonDocument<1024> _doc;
    DeserializationError err;

   public:
    LoadJSONFromSD(const char* filename) { strcpy(_filename, filename); }

    int begin() {
        _file = SD.open(_filename);
        err = deserializeJson(_doc, _file);
        _file.close();
        return err.code();
    }

    JsonObject load(const char* load) { return _doc[load]; }
};

#endif  // LoadJSONFromSD