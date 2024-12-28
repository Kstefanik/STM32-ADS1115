#include "ADS1115.hpp"

ks::ADS1115::ADS1115()
{
    m_i2c_handle = hi2c1;
    m_address = 0x48;
    
    set_mux(A0_A1);
    set_gain(PGA_2_048);
    set_ADS_mode(SINGLE_SHOT);
    set_data_rate(DR_128);
    set_comp_mode(DEFAULT);
    set_comp_polarity(ACTIVE_LOW);
    set_comp_latch(NON_LATCHING);
    set_comp_que(DISABLE_COMP);
}

ks::ADS1115::ADS1115(ADDR address, I2C_HandleTypeDef i2c_handle)
{
    m_address = address;
    m_i2c_handle = i2c_handle;

    set_mux(A0_A1);
    set_gain(PGA_2_048);
    set_ADS_mode(SINGLE_SHOT);
    set_data_rate(DR_128);
    set_comp_mode(DEFAULT);
    set_comp_polarity(ACTIVE_LOW);
    set_comp_latch(NON_LATCHING);
    set_comp_que(DISABLE_COMP);
}

void ks::ADS1115::set_i2c_handle(I2C_HandleTypeDef i2c_handle)
{
    m_i2c_handle = i2c_handle;
}

int16_t ks::ADS1115::read_single(CHANNEL channel)
{
    switch(channel)
    {
        case(A0):
            set_mux(A0_GND);
            HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 3, 100);
            ADS_write[0] = 0x00;
            HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 1, 100);
            HAL_Delay(20);
            HAL_I2C_Master_Receive(&m_i2c_handle, m_address<<1, ADS_write, 2, 100);
            reading = ADS_write[0] << 8 | ADS_write[1];

            if(reading < 0)
            {
                reading = 0;
            }

            return reading;
        break;

        case(A1):
            set_mux(A1_GND);
            HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 3, 100);
            ADS_write[0] = 0x00;
            HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 1, 100);
            HAL_Delay(20);
            HAL_I2C_Master_Receive(&m_i2c_handle, m_address<<1, ADS_write, 2, 100);
            reading = ADS_write[0] << 8 | ADS_write[1];
            
            if(reading < 0)
            {
                reading = 0;
            }

            return reading;
        break;

        case(A2):
            set_mux(A2_GND);
            HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 3, 100);
            ADS_write[0] = 0x00;
            HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 1, 100);
            HAL_Delay(20);
            HAL_I2C_Master_Receive(&m_i2c_handle, m_address<<1, ADS_write, 2, 100);
            reading = ADS_write[0] << 8 | ADS_write[1];
            
            if(reading < 0)
            {
                reading = 0;
            }

            return reading;
        break;

        case(A3):
            set_mux(A3_GND);
            HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 3, 100);
            ADS_write[0] = 0x00;
            HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 1, 100);
            HAL_Delay(20);
            HAL_I2C_Master_Receive(&m_i2c_handle, m_address<<1, ADS_write, 2, 100);
            reading = ADS_write[0] << 8 | ADS_write[1];
            
            if(reading < 0)
            {
                reading = 0;
            }

            return reading;
        break;
    }
}

int16_t ks::ADS1115::read_diff_0_1()
{
    set_mux(A0_A1);
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 3, 100);
    ADS_write[0] = 0x00;
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 1, 100);
    HAL_Delay(20);
    HAL_I2C_Master_Receive(&m_i2c_handle, m_address<<1, ADS_write, 2, 100);
    reading = ADS_write[0] << 8 | ADS_write[1];
            
    if(reading < 0)
    {
        reading = 0;
    }

    return reading;
}

int16_t ks::ADS1115::read_diff_0_3()
{
    set_mux(A0_A3);
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 3, 100);
    ADS_write[0] = 0x00;
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 1, 100);
    HAL_Delay(20);
    HAL_I2C_Master_Receive(&m_i2c_handle, m_address<<1, ADS_write, 2, 100);
    reading = ADS_write[0] << 8 | ADS_write[1];
            
    if(reading < 0)
    {
        reading = 0;
    }

    return reading;
}

int16_t ks::ADS1115::read_diff_1_3()
{
    set_mux(A1_A3);
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 3, 100);
    ADS_write[0] = 0x00;
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 1, 100);
    HAL_Delay(20);
    HAL_I2C_Master_Receive(&m_i2c_handle, m_address<<1, ADS_write, 2, 100);
    reading = ADS_write[0] << 8 | ADS_write[1];
            
    if(reading < 0)
    {
        reading = 0;
    }

    return reading;    
}

int16_t ks::ADS1115::read_diff_2_3()
{
    set_mux(A2_A3);
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 3, 100);
    ADS_write[0] = 0x00;
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, ADS_write, 1, 100);
    HAL_Delay(20);
    HAL_I2C_Master_Receive(&m_i2c_handle, m_address<<1, ADS_write, 2, 100);
    reading = ADS_write[0] << 8 | ADS_write[1];
            
    if(reading < 0)
    {
        reading = 0;
    }

    return reading;    
}

float ks::ADS1115::to_voltage(int16_t reading)
{
    float voltage = reading * m_gain / 32768.0;

    return voltage;
}

void ks::ADS1115::set_mux(MUX mux)
{
    m_mux = mux;
}

void ks::ADS1115::set_gain(GAIN gain)
{
    switch(gain)
    {
        case(PGA_6_144):
            m_gain = 6.144;
        break;

        case(PGA_4_096):
            m_gain = 4.096;
        break;

        case(PGA_2_048):
            m_gain = 2.048;
        break;

        case(PGA_1_024):
            m_gain = 1.024;
        break;

        case(PGA_0_512):
            m_gain = 0.512;
        break;

        case(PGA_0_256):
            m_gain = 0.256;
        break;
    }
    
}

void ks::ADS1115::set_ADS_mode(ADS_MODE mode)
{
    if(mode == SINGLE_SHOT)
    {
        ADS_write[1] |= (1 << 0);
    }

    else if(mode == CONTINUOUS)
    {
        ADS_write[1] &= ~(1 << 0);
    }
}

void ks::ADS1115::set_data_rate(DATA_RATE data_rate)
{
    switch(data_rate)
    {
        case(DR_8):
            ADS_write[2] &= ~(1 << 7);
            ADS_write[2] &= ~(1 << 6);
            ADS_write[2] &= ~(1 << 5);
        break;

        case(DR_16):
            ADS_write[2] &= ~(1 << 7);
            ADS_write[2] &= ~(1 << 6);
            ADS_write[2] |= (1 << 5);
        break;

        case(DR_32):
            ADS_write[2] &= ~(1 << 7);
            ADS_write[2] |= (1 << 6);
            ADS_write[2] &= ~(1 << 5);
        break;

        case(DR_64):
            ADS_write[2] &= ~(1 << 7);
            ADS_write[2] |= (1 << 6);
            ADS_write[2] |= (1 << 5);
        break;

        case(DR_128):
            ADS_write[2] |= (1 << 7);
            ADS_write[2] &= ~(1 << 6);
            ADS_write[2] &= ~(1 << 5);
        break;

        case(DR_250):
            ADS_write[2] |= (1 << 7);
            ADS_write[2] &= ~(1 << 6);
            ADS_write[2] |= (1 << 5);
        break;

        case(DR_475):
            ADS_write[2] |= (1 << 7);
            ADS_write[2] |= (1 << 6);
            ADS_write[2] &= ~(1 << 5);
        break;

        case(DR_860):
            ADS_write[2] |= (1 << 7);
            ADS_write[2] |= (1 << 6);
            ADS_write[2] |= (1 << 5);
        break;
    }
}

void ks::ADS1115::set_comp_mode(COMP_MODE comp_mode)
{
    if(comp_mode == DEFAULT)
    {
        ADS_write[2] &= ~(1 << 4);
    }

    else if(comp_mode == WINDOW)
    {
        ADS_write[2] |= (1 << 4);
    }
}

void ks::ADS1115::set_comp_polarity(COMP_POLARITY comp_polarity)
{
    if( comp_polarity== ACTIVE_LOW)
    {
        ADS_write[2] &= ~(1 << 3);
    }

    else if(comp_polarity == ACTIVE_HIGH)
    {
        ADS_write[2] |= (1 << 3);
    }
}

void ks::ADS1115::set_comp_latch(COMP_LATCH comp_latch)
{
    if( comp_latch == NON_LATCHING)
    {
        ADS_write[2] &= ~(1 << 2);
    }

    else if(comp_latch == LATCHING)
    {
        ADS_write[2] |= (1 << 2);
    }
}

void ks::ADS1115::set_comp_que(COMP_QUE comp_que)
{
    switch(comp_que)
    {
        case(ASSERT_AFTER_1_CONV):
            ADS_write[2] &= ~(1 << 1);
            ADS_write[2] &= ~(1 << 0);
        break;

        case(ASSERT_AFTER_2_CONV):
            ADS_write[2] &= ~(1 << 1);
            ADS_write[2] |= (1 << 0);
        break;

        case(ASSERT_AFTER_4_CONV):
            ADS_write[2] |= (1 << 1);
            ADS_write[2] &= ~(1 << 0);
        break;

        case(DISABLE_COMP):
            ADS_write[2] |= (1 << 1);
            ADS_write[2] |= (1 << 0);
        break;
    }
}