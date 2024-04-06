#include <stdio.h>
#include "ads1115_cpp.h"
#include <iostream>


namespace App {
    ads1115_cpp::ads1115_cpp(){
        std::cout << "starting ADS1115" << std::endl;
        App::Led->setColour(led::Colours::light_pink);

        i2c_config_t conf = { 
            .mode = I2C_MODE_MASTER,
            .sda_io_num = 6,
            .scl_io_num = 7,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master = { .clk_speed = 100000 },
            .clk_flags = 0
        };
        ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));

        ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0));

        std::cout << "installed i2c driver" << std::endl;
        ads1115_t cfg = ads1115_config(I2C_NUM_0 , 0x48);

        // ads1115_set_rdy_pin(&cfg, gpio_num_t gpio); // set up data-ready pin
        ads1115_set_mux(&cfg, ADS1115_MUX_0_1); // set multiplexer THIS IS THE CHANNEL
        ads1115_set_pga(&cfg, ADS1115_FSR_2_048); // set fsr

        ads1115_set_mode(&cfg, ADS1115_MODE_SINGLE); // set read mode
        ads1115_set_sps(&cfg, ADS1115_SPS_128); // set sampling speed
        ads1115_set_max_ticks(&cfg, 20); // maximum wait ticks for i2c bus

        std::cout << "setup ADS1115" << std::endl;
       
        App::Led->setColour(led::Colours::hot_pink);
        scan();
        std::cout << "Channel No.\t1\t2\t3\t4" << std::endl;

        for(;;){
            readAllChannels(&cfg);
            vTaskDelay(pdMS_TO_TICKS(2000));
        }
        
    }




    int ads1115_cpp::readChannel(ads1115_t *ads, ads1115_mux_t channelNo){
        ads1115_set_mux(ads, channelNo); // set multiplexer THIS IS THE CHANNEL
        vTaskDelay(pdMS_TO_TICKS(75));

        return ads1115_get_raw(ads);
    }

    void ads1115_cpp::readAllChannels(ads1115_t *ads){
        int result = 0;
        std::cout << "Raw Val\t\t" ;
        for (int i = 4; i < 8; i++) {
            result = readChannel(ads, ads1115_mux_t(i));
            std::cout << i-3 << "->" << result << "\t";
        }
        std::cout << std::endl;        
    }   


    int ads1115_cpp::scan(){
    
        std::cout << "Scanning i2c bus.." << std::endl;

        int devices_found = 0;
        for(int address = 1; address < 127; address++) {
            // create and execute the command link
            // std::cout << "checking address " << address << std::endl;
            i2c_cmd_handle_t cmd = i2c_cmd_link_create();
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
            i2c_master_stop(cmd);
            if(i2c_master_cmd_begin(I2C_NUM_0, cmd, 200 / portTICK_RATE_MS) == ESP_OK) {
                std::cout << "-> found device with address " << address << std::endl;
                devices_found++;
            }
            i2c_cmd_link_delete(cmd);
        }
        return devices_found;
    }   
};