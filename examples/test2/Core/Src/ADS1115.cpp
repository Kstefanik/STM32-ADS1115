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

float ks::ADS1115::read_volt_single(MUX channel)
{
    float voltage = read_digital(channel) * m_gain / 32768.0;

    return voltage;
}

int16_t ks::ADS1115::read_digital(MUX channel)
{
    switch(channel)
    {
        case(A0_GND):
           
            if(m_ADS_mode == SINGLE_SHOT)
            {
                set_os(START_CONV);
            }

            
            //set_os(START_CONV);
            set_mux(A0_GND);
            upload_config();

            return get_conversion();
        break;

        case(A1_GND):

            set_os(START_CONV);
            set_mux(A1_GND);
            upload_config();

            return get_conversion();
        break;

        case(A2_GND):

            set_os(START_CONV);
            set_mux(A2_GND);
            upload_config();

            return get_conversion();
        break;

        case(A3_GND):
        
            set_os(START_CONV);
            set_mux(A2_GND);
            upload_config();

            return get_conversion();
        break;

        case(A0_A1):

            set_os(START_CONV);
            set_mux(A0_A1);
            upload_config();

            return get_conversion();
        break;

        case(A0_A3):

            set_os(START_CONV);
            set_mux(A0_A3);
            upload_config();

            return get_conversion();
        break;

        case(A1_A3):

            set_os(START_CONV);
            set_mux(A1_A3);
            upload_config();

            return get_conversion();
        break;

        case(A2_A3):

            set_os(START_CONV);
            set_mux(A2_A3);
            upload_config();

            return get_conversion();
        break;

        default:
            return -1;
    }     
}

int16_t ks::ADS1115::read_diff_0_1()
{   
    m_ADS_write[0] = 0x01;
    m_ADS_write[1] |= (1 << 7);
    set_mux(A0_A1);
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write, 3, 100);
    m_ADS_write[0] = 0x00;
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write, 1, 100);
    HAL_Delay(20);
    HAL_I2C_Master_Receive(&m_i2c_handle, m_address<<1, m_ADS_read, 2, 100);
    m_reading = m_ADS_read[0] << 8 | m_ADS_read[1];
            
    if(m_reading < 0)
    {
        m_reading = 0;
    }

    return m_reading;
}

int16_t ks::ADS1115::read_diff_0_3()
{
    set_mux(A0_A3);
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write, 3, 100);
    m_ADS_write[0] = 0x00;
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write, 1, 100);
    HAL_Delay(20);
    HAL_I2C_Master_Receive(&m_i2c_handle, m_address<<1, m_ADS_read, 2, 100);
    m_reading = m_ADS_read[0] << 8 | m_ADS_read[1];
            
    if(m_reading < 0)
    {
        m_reading = 0;
    }

    return m_reading;
}

int16_t ks::ADS1115::read_diff_1_3()
{
    set_mux(A1_A3);
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write, 3, 100);
    m_ADS_write[0] = 0x00;
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write, 1, 100);
    HAL_Delay(20);
    HAL_I2C_Master_Receive(&m_i2c_handle, m_address<<1, m_ADS_read, 2, 100);
    m_reading = m_ADS_read[0] << 8 | m_ADS_read[1];
            
    if(m_reading < 0)
    {
        m_reading = 0;
    }

    return m_reading;    
}

int16_t ks::ADS1115::read_diff_2_3()
{
    set_mux(A2_A3);
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write, 3, 100);
    m_ADS_write[0] = 0x00;
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write, 1, 100);
    HAL_Delay(20);
    HAL_I2C_Master_Receive(&m_i2c_handle, m_address<<1, m_ADS_read, 2, 100);
    m_reading = m_ADS_read[0] << 8 | m_ADS_read[1];
            
    if(m_reading < 0)
    {
        m_reading = 0;
    }

    return m_reading;    
}

void ks::ADS1115::set_os(OS os)
{
    if(os == START_CONV)
    {
        m_ADS_write[1] |= (1 << 7);
    }

    else
    {
        m_ADS_write[1] &= ~(1 << 7);
    }
    
}

void ks::ADS1115::set_mux(MUX mux)
{
    m_mux = mux;

    switch(mux)
    {
        case(A0_A1):
            m_ADS_write[1] &= ~(1 << 6);
            m_ADS_write[1] &= ~(1 << 5);
            m_ADS_write[1] &= ~(1 << 4);
        break;

        case(A0_A3):
            m_ADS_write[1] &= ~(1 << 6);
            m_ADS_write[1] &= ~(1 << 5);
            m_ADS_write[1] |= (1 << 4);
        break;

        case(A1_A3):
            m_ADS_write[1] &= ~(1 << 6);
            m_ADS_write[1] |= (1 << 5);
            m_ADS_write[1] &= ~(1 << 4);
        break;

        case(A2_A3):
            m_ADS_write[1] &= ~(1 << 6);
            m_ADS_write[1] |= (1 << 5);
            m_ADS_write[1] |= (1 << 4);
        break;

        case(A0_GND):
            m_ADS_write[1] |= (1 << 6);
            m_ADS_write[1] &= ~(1 << 5);
            m_ADS_write[1] &= ~(1 << 4);
        break;

        case(A1_GND):
            m_ADS_write[1] |= (1 << 6);
            m_ADS_write[1] &= ~(1 << 5);
            m_ADS_write[1] |= (1 << 4);
        break;

        case(A2_GND):
            m_ADS_write[1] |= (1 << 6);
            m_ADS_write[1] |= (1 << 5);
            m_ADS_write[1] &= ~(1 << 4);
        break;

        case(A3_GND):
            m_ADS_write[1] |= (1 << 6);
            m_ADS_write[1] |= (1 << 5);
            m_ADS_write[1] |= (1 << 4);
        break;
    }
}

void ks::ADS1115::set_gain(GAIN gain)
{
    switch(gain)
    {
        case(PGA_6_144):
            m_ADS_write[1] &= ~(1 << 3);
            m_ADS_write[1] &= ~(1 << 2);
            m_ADS_write[1] &= ~(1 << 1);

            m_gain = 6.144;
        break;

        case(PGA_4_096):
            m_ADS_write[1] &= ~(1 << 3);
            m_ADS_write[1] &= ~(1 << 2);
            m_ADS_write[1] |= (1 << 1);

            m_gain = 4.096;
        break;

        case(PGA_2_048):
            m_ADS_write[1] &= ~(1 << 3);
            m_ADS_write[1] |= (1 << 2);
            m_ADS_write[1] &= ~(1 << 1);

            m_gain = 2.048;
        break;

        case(PGA_1_024):
            m_ADS_write[1] &= ~(1 << 3);
            m_ADS_write[1] |= (1 << 2);
            m_ADS_write[1] |= (1 << 1);

            m_gain = 1.024;
        break;

        case(PGA_0_512):
            m_ADS_write[1] |= (1 << 3);
            m_ADS_write[1] &= ~(1 << 2);
            m_ADS_write[1] &= ~(1 << 1);

            m_gain = 0.512;
        break;

        case(PGA_0_256):
            m_ADS_write[1] |= (1 << 3);
            m_ADS_write[1] &= ~(1 << 2);
            m_ADS_write[1] |= (1 << 1);

            m_gain = 0.256;
        break;
    } 
}

void ks::ADS1115::set_ADS_mode(ADS_MODE ADS_mode)
{
    m_ADS_mode = ADS_mode;

    if(ADS_mode == SINGLE_SHOT)
    {
        m_ADS_write[1] |= (1 << 0);
    }

    else if(ADS_mode == CONTINUOUS)
    {
        m_ADS_write[1] &= ~(1 << 0);
    }
}

void ks::ADS1115::set_data_rate(DATA_RATE data_rate)
{
    switch(data_rate)
    {
        case(DR_8):
            m_ADS_write[2] &= ~(1 << 7);
            m_ADS_write[2] &= ~(1 << 6);
            m_ADS_write[2] &= ~(1 << 5);
        break;

        case(DR_16):
            m_ADS_write[2] &= ~(1 << 7);
            m_ADS_write[2] &= ~(1 << 6);
            m_ADS_write[2] |= (1 << 5);
        break;

        case(DR_32):
            m_ADS_write[2] &= ~(1 << 7);
            m_ADS_write[2] |= (1 << 6);
            m_ADS_write[2] &= ~(1 << 5);
        break;

        case(DR_64):
            m_ADS_write[2] &= ~(1 << 7);
            m_ADS_write[2] |= (1 << 6);
            m_ADS_write[2] |= (1 << 5);
        break;

        case(DR_128):
            m_ADS_write[2] |= (1 << 7);
            m_ADS_write[2] &= ~(1 << 6);
            m_ADS_write[2] &= ~(1 << 5);
        break;

        case(DR_250):
            m_ADS_write[2] |= (1 << 7);
            m_ADS_write[2] &= ~(1 << 6);
            m_ADS_write[2] |= (1 << 5);
        break;

        case(DR_475):
            m_ADS_write[2] |= (1 << 7);
            m_ADS_write[2] |= (1 << 6);
            m_ADS_write[2] &= ~(1 << 5);
        break;

        case(DR_860):
            m_ADS_write[2] |= (1 << 7);
            m_ADS_write[2] |= (1 << 6);
            m_ADS_write[2] |= (1 << 5);
        break;
    }
}

void ks::ADS1115::set_comp_mode(COMP_MODE comp_mode)
{
    if(comp_mode == DEFAULT)
    {
        m_ADS_write[2] &= ~(1 << 4);
    }

    else if(comp_mode == WINDOW)
    {
        m_ADS_write[2] |= (1 << 4);
    }
}

void ks::ADS1115::set_comp_polarity(COMP_POLARITY comp_polarity)
{
    if( comp_polarity== ACTIVE_LOW)
    {
        m_ADS_write[2] &= ~(1 << 3);
    }

    else if(comp_polarity == ACTIVE_HIGH)
    {
        m_ADS_write[2] |= (1 << 3);
    }
}

void ks::ADS1115::set_comp_latch(COMP_LATCH comp_latch)
{
    if( comp_latch == NON_LATCHING)
    {
        m_ADS_write[2] &= ~(1 << 2);
    }

    else if(comp_latch == LATCHING)
    {
        m_ADS_write[2] |= (1 << 2);
    }
}

void ks::ADS1115::set_comp_que(COMP_QUE comp_que)
{
    switch(comp_que)
    {
        case(ASSERT_AFTER_1_CONV):
            m_ADS_write[2] &= ~(1 << 1);
            m_ADS_write[2] &= ~(1 << 0);
        break;

        case(ASSERT_AFTER_2_CONV):
            m_ADS_write[2] &= ~(1 << 1);
            m_ADS_write[2] |= (1 << 0);
        break;

        case(ASSERT_AFTER_4_CONV):
            m_ADS_write[2] |= (1 << 1);
            m_ADS_write[2] &= ~(1 << 0);
        break;

        case(DISABLE_COMP):
            m_ADS_write[2] |= (1 << 1);
            m_ADS_write[2] |= (1 << 0);
        break;
    }
}

void ks::ADS1115::upload_config()
{
    m_ADS_write[0] = 0x01;
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write, 3, 100);
    m_ADS_write[0] = 0x00;
    HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write, 1, 100);
    HAL_Delay(20);
}

int16_t ks::ADS1115::get_conversion()
{
    HAL_I2C_Master_Receive(&hi2c1, m_address<<1, m_ADS_read, 2, 100);
    m_reading = m_ADS_read[0] << 8 | m_ADS_read[1];
    if(m_reading < 0)
    {
        m_reading = 0;
    }

    return m_reading;
}