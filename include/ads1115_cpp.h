#pragma once 
#ifndef _ADS1115_CPP_H_QFMDEuwLPHjE
#define _ADS1115_CPP_H_QFMDEuwLPHjE

#include <string>
#include <cstring>
#include <chrono>
#include <ctime>    
#include <format>

#ifdef __cplusplus
extern "C" {
#endif

#include "Led.h"
#include "i2c.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_system.h"

#include "ads1115.h"
#include "globals.h"


namespace App {

    class ads1115_cpp{
        // static void check_adc(ads1115_t *ads);       

        // accessible outside class
        public:
            ads1115_cpp(i2c *bus, int port);
            static int readChannel(int channelNo, ads1115_t &adc);
            static void readAllChannels(ads1115_t &ads);

            ads1115_t ads; 
            
            static void check_adc(ads1115_t Ads);
        // in class only
        private:
        
            int result;
            int address;
            int readChannel(ads1115_mux_t channelNo);
         
            i2c *bus;


        // access in class and children inherit it
        protected:
        
    }; // end class ads1115cpp
    // extern ads1115_cpp *Ads;

}; // end namespace App

#ifdef __cplusplus
}
#endif

#endif // _ADS1115_CPP_H_QFMDEuwLPHjE