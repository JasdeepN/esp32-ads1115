#include <stdio.h>
#include "ads1115_cpp.h"
#include <iostream>


namespace App {
    // static xQueueHandle gpio_evt_queue = NULL;

    // static void IRAM_ATTR gpio_isr_handler(void* arg)
    // {
    // uint32_t gpio_num = (uint32_t) arg;
    // xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);


    // // notify the button task
    // ////////// xSemaphoreGiveFromISR(xSemaphore, NULL);
    // }


    ads1115_cpp::ads1115_cpp(i2c *bus, int port){
    
        std::cout << "starting ADS1115 on PORT " << port << std::endl;
        App::Led->setColour(led::Colours::light_pink);
        this->address = port;
        this->bus = bus;
        // this->ads = new ads1115_t();
        this->ads = ads1115_config(I2C_NUM_0 , port);

        // ads1115_set_rdy_pin(&cfg, gpio_num_t gpio); // set up data-ready pin
        ads1115_set_mux(&(this->ads), ADS1115_MUX_0_1); // set multiplexer THIS IS THE CHANNEL
        ads1115_set_pga(&this->ads, ADS1115_FSR_4_096); // set fsr

        ads1115_set_mode(&this->ads, ADS1115_MODE_SINGLE); // set read mode
        ads1115_set_sps(&this->ads, ADS1115_SPS_128); // set sampling speed
        ads1115_set_max_ticks(&this->ads, 25); // maximum wait ticks for i2c bus
        // this->init = true;
       
        std::cout << "setup ADS1115 on port " << port << std::endl;

        App::Led->setColour(led::Colours::hot_pink); 
        
    }

    void ads1115_cpp::check_adc(ads1115_t ads){
        // gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
        // this->bus->activate()        
        readAllChannels(ads);    
   }



    int ads1115_cpp::readChannel(int channelNo, ads1115_t &ads){
       
        ads1115_set_mux(&ads, ads1115_mux_t(channelNo+4)); // set multiplexer THIS IS THE CHANNEL
        vTaskDelay(pdMS_TO_TICKS(20));

        return ads1115_get_raw(&ads);
    }



    int ads1115_cpp::readChannel(ads1115_mux_t channelNo){
        // ads1115_set_mux(this->adcs, channelNo); // set multiplexer THIS IS THE CHANNEL
        // vTaskDelay(pdMS_TO_TICKS(20));

        // return ads1115_get_raw(this->adcs);
        return 0;
    }

    void ads1115_cpp::readAllChannels(ads1115_t &ads){
        int result = 0;

        std::cout << "Raw Val\t\t" ;
        for (int i = 0; i < 4; i++) {
            result = readChannel(i, ads);
            std::cout << i << "->" << result << "\t\t";
        }
        std::cout << std::endl;        
    }   



   
};