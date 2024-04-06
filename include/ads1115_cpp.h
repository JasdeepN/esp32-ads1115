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
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_system.h"

#include "ads1115.h"
#include "globals.h"


#define TEST_I2C_PORT I2C_ADDRESS
#define I2C_MASTER_SCL_IO SCL_GPIO_PIN
#define I2C_MASTER_SDA_IO SDA_GPIO_PIN

namespace App {
    class ads1115_cpp {

      
        // accessible outside class
        public:
            ads1115_cpp();
            int scan();
            int readChannel(ads1115_t *ads, ads1115_mux_t channelNo);
            void readAllChannels(ads1115_t *ads);

        // in class only
        private:
            int result;


        // access in class and children inherit it
        protected:
        
    }; // end class ads1115cpp
}; // end namespace App

#ifdef __cplusplus
}
#endif

#endif // _ADS1115_CPP_H_QFMDEuwLPHjE