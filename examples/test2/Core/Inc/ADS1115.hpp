#pragma once

/**
 * The configuration register is 16 bit so the configuration is uploaded via i2c in 2 8bit segments
 * Below are defines of configuration bits to be written
 */
// First byte (ADS_write[1])
#define OS_BIT          7
#define MUX_BIT_1       6
#define MUX_BIT_2       5
#define MUX_BIT_3       4
#define PGA_BIT_1       3
#define PGA_BIT_2       2
#define PGA_BIT_3       1
#define MODE_BIT        0

// Second byte (ADS_write[2])
#define DR_BIT_1        7
#define DR_BIT_2        6
#define DR_BIT_3        5
#define COMP_MODE_BIT   4
#define COMP_POL_BIT    3
#define COMP_LAT_BIT    2
#define COMP_QUE_BIT_1  1
#define COMP_QUE_BIT_2  0

/**
 * This library was written for STM32F3(NUCLEO-F303RE board to be exact),
 * But the HAL functions used by it should be common between other STM32 versions
 * So you should be able to externd the library support to other STM32 mcus by
 * including a different hal library.
 */
#include "stm32f3xx_hal.h"

/**
 * Defines the i2c HAL handle that will be declared in the program using this library
 * Required for the default constructor
 */
extern I2C_HandleTypeDef hi2c1;

/**
 * Avaiable adresses for ADS1115
 * On how to set them refer to ADS1115 datasheet
 */
enum ADDR
{
    ADDR_0x48 = 0x48,
    ADDR_0x49 = 0x49,
    ADDR_0x4A = 0x4A,
    ADDR_0x4B = 0x4B
};

/**
 * Enums defining avaiable configuration options(bits of the configuration register)
 */

enum OS
{
    START_CONV,
    NO_EFFECT
};

enum MUX
{   
    /**
     * Differential channels
     */
    A0_A1,
    A0_A3,
    A1_A3,
    A2_A3,

    /**
     * Single ended channels
     */
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

namespace ks
{
    class ADS1115
    {
    public:
        /**
         * Default constructor, assumes the ADS1115 address to be 0x48 uses I2C1 interface(hi2c1 HAL handle)
         * Sets the configuation bits to default values, as stated in ADS1115 datasheet:
         * Multiplexer: AINp = A0, AINn = A1
         * PGA gain: +-2.048V
         * Device operating mode: Single shot
         * Data rate: 128SPS
         * Comparator mode: Traditional comparator
         * Comparator polarity: Active low
         * Latching comparator: Nonlatching comparator
         * Comparator queue and disable: Disable comparator
         */
        ADS1115();

        /**
         * Parametrized constructor, allows for specifying the ADS1115 adress and i2c HAL handle
         * The configuartion is set the same as with default constructor
         */
        ADS1115(ADDR address, I2C_HandleTypeDef i2c_handle);

        /**
         * Sets the i2c HAL handle to be used by ADS1115 instance
         */
        void set_i2c_handle(I2C_HandleTypeDef i2c_handle);
        
        /**
         * Returns the converted digital value read from a chosen channel
         */
        int16_t read_digital(MUX channel);

        /**
         * Returns voltage in VOLTS calculated based on the output of read_digital() method 
         */
        float read_voltage(MUX channel);

        /**
         * Methods that prepare the configuration to be uploaded to ADS1115. 
         * The configuration is later uploaded to ADS1115 via config_upload() method.
         * For more information refer to ADS1115 datasheet
         */

        /**
         * Setters and getters.
         * 
         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         *                          Setters DO NOT SET the bits in the config register. 
         * They only prepare the configuration so it can be uploaded to ADS1115 using the upload_config() method.
         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         * 
         * For indepth information on ADS1115 configuration refer to the datasheet
         */

        /**
         * Sets the OS bit, which triggers the single shot conversion
         */
        void set_os(OS os);

        void set_mux(MUX mux);
        MUX get_mux();

        void set_gain(GAIN gain);
        GAIN get_gain();

        void set_ADS_mode(ADS_MODE mode);
        ADS_MODE get_ADS_mode();

        void set_data_rate(DATA_RATE data_rate);
        DATA_RATE get_data_rate();

        void set_comp_mode(COMP_MODE comp_mode);
        COMP_MODE get_comp_mode();

        void set_comp_polarity(COMP_POLARITY comp_polarity);
        COMP_POLARITY get_comp_polarity();

        void set_comp_latch(COMP_LATCH comp_latch);
        COMP_LATCH get_comp_latch();

        void set_comp_que(COMP_QUE comp_que);
        COMP_QUE get_comp_que();

        //TODO: void set_low_threshold();

        //TODO: void set_high_threshold();
        
        /**
         * Uploads the configuration to ADS1115 via i2c
         */
        void upload_config();

        /**
         * Returns the value currently stored in the conversion register
         */
        int16_t get_conversion();

        /**
         * Overloaded operators
         */ 
        ADS1115& operator=(const ADS1115& other);   //copies the configuration setup
        bool operator==(const ADS1115& other);      //compares the configuration setup
        bool operator!=(const ADS1115& other);      

    private:
        /**
         * Variable used for writting stuff(configuration) to ADS1115 via i2c
         */
        unsigned char m_ADS_write[3];

        /**
         * Variale used for reading stuff(converted value) from ADS1115 via i2c
         */
        unsigned char m_ADS_read[2];

        /**
         * I2C handle used by ADS1115 instance
         */
        I2C_HandleTypeDef m_i2c_handle;

        /**
         * Variable that stores the digital value ouputed by ADS1115
         */
        int16_t m_reading;

        /**
         * Variables representing the current configuration of ADS1115 instance
         */
        uint8_t m_address;
        MUX m_mux;
        float m_gain;   //contains the gain value required for calculating the output of ADS1115
        GAIN m_pga;     //constain the current gain setting
        ADS_MODE m_ADS_mode;
        DATA_RATE m_data_rate;
        COMP_MODE m_comp_mode;
        COMP_POLARITY m_comp_polarity;
        COMP_LATCH m_comp_latch;
        COMP_QUE m_comp_que;
    };
}

