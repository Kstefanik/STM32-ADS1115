#pragma once

#define OS_BIT              15
#define MUX_BIT             14
#define PGA_BIT             11
#define MODE_BIT            8
#define DR_BIT              7
#define COMP_MODE_BIT       4
#define COMP_POL_BIT        3
#define COMP_LAT_BIT        2
#define COMP_QUE_BIT        1

#include "stm32f3xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

namespace ks
{
    enum ADDR
    {
        ADDR_0x48 = 0x48,
        ADDR_0x49 = 0x49,
        ADDR_0x4A = 0x4A,
        ADDR_0x4B = 0x4B
    };

    enum OS
    {
        START_CONV,
        NO_EFFECT
    };

    enum MUX
    {
        A0_A1,
        A0_A3,
        A1_A3,
        A2_A3,

        A0_GND,
        A1_GND,
        A2_GND,
        A3_GND,
    };

    enum GAIN
    {
        PGA_6_144,
        PGA_4_096,
        PGA_2_048,
        PGA_1_024,
        PGA_0_512,
        PGA_0_256
    };

    enum ADS_MODE
    {
        CONTINUOUS,
        SINGLE_SHOT
    };

    enum DATA_RATE
    {
        DR_8,
        DR_16,
        DR_32,
        DR_64,
        DR_128,
        DR_250,
        DR_475,
        DR_860
    };

    enum COMP_MODE
    {
        DEFAULT,
        WINDOW 
    };

    enum COMP_POLARITY
    {
        ACTIVE_LOW,
        ACTIVE_HIGH
    };

    enum COMP_LATCH
    {
        NON_LATCHING,
        LATCHING
    };

    enum COMP_QUE
    {
        ASSERT_AFTER_1_CONV,
        ASSERT_AFTER_2_CONV,
        ASSERT_AFTER_4_CONV,
        DISABLE_COMP
    };

    /*enum CHANNEL
    {
        A0 = 0,
        A1 = 1,
        A2 = 2,
        A3 = 3
    };*/

    class ADS1115
    {
    public:
        ADS1115();
        ADS1115(ADDR address, I2C_HandleTypeDef i2c_handle);

        void set_i2c_handle(I2C_HandleTypeDef i2c_handle);
        
        int16_t read_digital(MUX channel);
        float read_volt_single(MUX channel);


        int16_t read_diff_0_1();
        int16_t read_diff_0_3();
        int16_t read_diff_1_3();
        int16_t read_diff_2_3();

        void set_os(OS os);

        void set_mux(MUX mux);

        void set_gain(GAIN gain);

        void set_ADS_mode(ADS_MODE mode);

        void set_data_rate(DATA_RATE data_rate);

        void set_comp_mode(COMP_MODE comp_mode);

        void set_comp_polarity(COMP_POLARITY comp_polarity);

        void set_comp_latch(COMP_LATCH comp_latch);

        void set_comp_que(COMP_QUE comp_que);

        void upload_config();

        int16_t get_conversion();

        

    private:
        unsigned char m_ADS_write[3];
        unsigned char m_ADS_read[2];
        
        I2C_HandleTypeDef m_i2c_handle;

        int16_t m_reading;

        uint8_t m_address;
        uint8_t m_mux;
        uint8_t m_gain;
        ADS_MODE m_ADS_mode;
    };
}

