#include "ADS1115.hpp"

namespace ks
{
    ADS1115::ADS1115()
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

    ADS1115::ADS1115(ADDR address, I2C_HandleTypeDef i2c_handle)
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

    void ADS1115::set_i2c_handle(I2C_HandleTypeDef i2c_handle)
    {
        m_i2c_handle = i2c_handle;
    }

    int16_t ADS1115::read_digital(MUX channel)
    {
        switch(channel)
        {
            case(A0_GND):
            
                if(m_ADS_mode == SINGLE_SHOT)
                {
                    set_os(START_CONV);
                }

                if(m_mux != A0_GND)
                {
                    set_mux(A0_GND);
                    upload_config();
                }

                return get_conversion();
            break;

            case(A1_GND):

                if(m_ADS_mode == SINGLE_SHOT)
                {
                    set_os(START_CONV);
                }

                if(m_mux != A1_GND)
                {
                    set_mux(A1_GND);
                    upload_config();
                }

                return get_conversion();
            break;

            case(A2_GND):

                if(m_ADS_mode == SINGLE_SHOT)
                {
                    set_os(START_CONV);
                }

                if(m_mux != A2_GND)
                {
                    set_mux(A2_GND);
                    upload_config();
                }

                return get_conversion();
            break;

            case(A3_GND):

                if(m_ADS_mode == SINGLE_SHOT)
                {
                    set_os(START_CONV);
                }     

                if(m_mux != A3_GND)
                {
                    set_mux(A3_GND);
                    upload_config();
                }

                return get_conversion();
            break;

            case(A0_A1):

                if(m_ADS_mode == SINGLE_SHOT)
                {
                    set_os(START_CONV);
                }

                if(m_mux != A0_A1)
                {
                    set_mux(A0_A1);
                    upload_config();
                }

                return get_conversion();
            break;

            case(A0_A3):

                if(m_ADS_mode == SINGLE_SHOT)
                {
                    set_os(START_CONV);
                }

                if(m_mux != A0_A3)
                {
                    set_mux(A0_A3);
                    upload_config();
                }

                return get_conversion();
            break;

            case(A1_A3):

                if(m_ADS_mode == SINGLE_SHOT)
                {
                    set_os(START_CONV);
                }

                if(m_mux != A1_A3)
                {
                    set_mux(A1_A3);
                    upload_config();
                }

                return get_conversion();
            break;

            case(A2_A3):

                if(m_ADS_mode == SINGLE_SHOT)
                {
                    set_os(START_CONV);
                }

                if(m_mux != A2_A3)
                {
                    set_mux(A2_A3);
                    upload_config();
                }

                return get_conversion();
            break;

            default:
                return -1;
        }     
    }

    float ADS1115::read_voltage(MUX channel)
    {
        float voltage = read_digital(channel) * m_gain / 32768.0;

        return voltage;
    }

    void ADS1115::set_os(OS os)
    {
        if(os == START_CONV)
        {
            m_ADS_write[1] |= (1 << OS_BIT);
        }

        else
        {
            m_ADS_write[1] &= ~(1 << OS_BIT);
        }  
    }
    
    void ADS1115::set_mux(MUX mux)
    {
        m_mux = mux;

        switch(mux)
        {
            case(A0_A1):
                m_ADS_write[1] &= ~(1 << MUX_BIT_1);
                m_ADS_write[1] &= ~(1 << MUX_BIT_2);
                m_ADS_write[1] &= ~(1 << MUX_BIT_3);
            break;

            case(A0_A3):
                m_ADS_write[1] &= ~(1 << MUX_BIT_1);
                m_ADS_write[1] &= ~(1 << MUX_BIT_2);
                m_ADS_write[1] |=  (1 << MUX_BIT_3);
            break;

            case(A1_A3):
                m_ADS_write[1] &= ~(1 << MUX_BIT_1);
                m_ADS_write[1] |=  (1 << MUX_BIT_2);
                m_ADS_write[1] &= ~(1 << MUX_BIT_3);
            break;

            case(A2_A3):
                m_ADS_write[1] &= ~(1 << MUX_BIT_1);
                m_ADS_write[1] |= (1 << MUX_BIT_2);
                m_ADS_write[1] |= (1 << MUX_BIT_3);
            break;

            case(A0_GND):
                m_ADS_write[1] |= (1 << MUX_BIT_1);
                m_ADS_write[1] &= ~(1 << MUX_BIT_2);
                m_ADS_write[1] &= ~(1 << MUX_BIT_3);
            break;

            case(A1_GND):
                m_ADS_write[1] |= (1 << MUX_BIT_1);
                m_ADS_write[1] &= ~(1 << MUX_BIT_2);
                m_ADS_write[1] |= (1 << MUX_BIT_3);
            break;

            case(A2_GND):
                m_ADS_write[1] |= (1 << MUX_BIT_1);
                m_ADS_write[1] |= (1 << MUX_BIT_2);
                m_ADS_write[1] &= ~(1 << MUX_BIT_3);
            break;

            case(A3_GND):
                m_ADS_write[1] |= (1 << MUX_BIT_1);
                m_ADS_write[1] |= (1 << MUX_BIT_2);
                m_ADS_write[1] |= (1 << MUX_BIT_3);
            break;
        }
    }

    MUX ADS1115::get_mux()
    {
        return m_mux;
    }

    void ADS1115::set_gain(GAIN gain)
    {
        m_pga = gain;

        switch(gain)
        {
            case(PGA_6_144):
                m_ADS_write[1] &= ~(1 << PGA_BIT_1);
                m_ADS_write[1] &= ~(1 << PGA_BIT_2);
                m_ADS_write[1] &= ~(1 << PGA_BIT_3);

                m_gain = 6.144;
            break;

            case(PGA_4_096):
                m_ADS_write[1] &= ~(1 << PGA_BIT_1);
                m_ADS_write[1] &= ~(1 << PGA_BIT_2);
                m_ADS_write[1] |= (1 << PGA_BIT_3);

                m_gain = 4.096;
            break;

            case(PGA_2_048):
                m_ADS_write[1] &= ~(1 << PGA_BIT_1);
                m_ADS_write[1] |= (1 << PGA_BIT_2);
                m_ADS_write[1] &= ~(1 << PGA_BIT_3);

                m_gain = 2.048;
            break;

            case(PGA_1_024):
                m_ADS_write[1] &= ~(1 << PGA_BIT_1);
                m_ADS_write[1] |= (1 << PGA_BIT_2);
                m_ADS_write[1] |= (1 << PGA_BIT_3);

                m_gain = 1.024;
            break;

            case(PGA_0_512):
                m_ADS_write[1] |= (1 << PGA_BIT_1);
                m_ADS_write[1] &= ~(1 << PGA_BIT_2);
                m_ADS_write[1] &= ~(1 << PGA_BIT_3);

                m_gain = 0.512;
            break;

            case(PGA_0_256):
                m_ADS_write[1] |= (1 << PGA_BIT_1);
                m_ADS_write[1] &= ~(1 << PGA_BIT_2);
                m_ADS_write[1] |= (1 << PGA_BIT_3);

                m_gain = 0.256;
            break;
        } 
    }

    GAIN ADS1115::get_gain()
    {
        return m_pga;
    }

    void ADS1115::set_ADS_mode(ADS_MODE ADS_mode)
    {
        m_ADS_mode = ADS_mode;

        if(ADS_mode == SINGLE_SHOT)
        {
            m_ADS_write[1] |= (1 << MODE_BIT);
        }

        else if(ADS_mode == CONTINUOUS)
        {
            m_ADS_write[1] &= ~(1 << MODE_BIT);
        }
    }

    ADS_MODE ADS1115::get_ADS_mode()
    {
        return m_ADS_mode;
    }

    void ADS1115::set_data_rate(DATA_RATE data_rate)
    {
        m_data_rate = data_rate;

        switch(data_rate)
        {
            case(DR_8):
                m_ADS_write[2] &= ~(1 << DR_BIT_1);
                m_ADS_write[2] &= ~(1 << DR_BIT_2);
                m_ADS_write[2] &= ~(1 << DR_BIT_3);
            break;

            case(DR_16):
                m_ADS_write[2] &= ~(1 << DR_BIT_1);
                m_ADS_write[2] &= ~(1 << DR_BIT_2);
                m_ADS_write[2] |= (1 << DR_BIT_3);
            break;

            case(DR_32):
                m_ADS_write[2] &= ~(1 << DR_BIT_1);
                m_ADS_write[2] |= (1 << DR_BIT_2);
                m_ADS_write[2] &= ~(1 << DR_BIT_3);
            break;

            case(DR_64):
                m_ADS_write[2] &= ~(1 << DR_BIT_1);
                m_ADS_write[2] |= (1 << DR_BIT_2);
                m_ADS_write[2] |= (1 << DR_BIT_3);
            break;

            case(DR_128):
                m_ADS_write[2] |= (1 << DR_BIT_1);
                m_ADS_write[2] &= ~(1 << DR_BIT_2);
                m_ADS_write[2] &= ~(1 << DR_BIT_3);
            break;

            case(DR_250):
                m_ADS_write[2] |= (1 << DR_BIT_1);
                m_ADS_write[2] &= ~(1 << DR_BIT_2);
                m_ADS_write[2] |= (1 << DR_BIT_3);
            break;

            case(DR_475):
                m_ADS_write[2] |= (1 << DR_BIT_1);
                m_ADS_write[2] |= (1 << DR_BIT_2);
                m_ADS_write[2] &= ~(1 << DR_BIT_3);
            break;

            case(DR_860):
                m_ADS_write[2] |= (1 << DR_BIT_1);
                m_ADS_write[2] |= (1 << DR_BIT_2);
                m_ADS_write[2] |= (1 << DR_BIT_3);
            break;
        }
    }

    DATA_RATE ADS1115::get_data_rate()
    {
        return m_data_rate;
    }

    void ADS1115::set_comp_mode(COMP_MODE comp_mode)
    {
        m_comp_mode = comp_mode;

        if(comp_mode == DEFAULT)
        {
            m_ADS_write[2] &= ~(1 << COMP_MODE_BIT);
        }

        else if(comp_mode == WINDOW)
        {
            m_ADS_write[2] |= (1 << COMP_MODE_BIT);
        }
    }

    COMP_MODE ADS1115::get_comp_mode()
    {
        return m_comp_mode;
    }

    void ADS1115::set_comp_polarity(COMP_POLARITY comp_polarity)
    {
        m_comp_polarity = comp_polarity;

        if( comp_polarity== ACTIVE_LOW)
        {
            m_ADS_write[2] &= ~(1 << COMP_POL_BIT);
        }

        else if(comp_polarity == ACTIVE_HIGH)
        {
            m_ADS_write[2] |= (1 << COMP_POL_BIT);
        }
    }

    COMP_POLARITY ADS1115::get_comp_polarity()
    {
        return m_comp_polarity;
    }

    void ADS1115::set_comp_latch(COMP_LATCH comp_latch)
    {
        m_comp_latch = comp_latch;

        if( comp_latch == NON_LATCHING)
        {
            m_ADS_write[2] &= ~(1 << COMP_LAT_BIT);
        }

        else if(comp_latch == LATCHING)
        {
            m_ADS_write[2] |= (1 << COMP_LAT_BIT);
        }
    }

    COMP_LATCH ADS1115::get_comp_latch()
    {
        return m_comp_latch;
    }

    void ADS1115::set_comp_que(COMP_QUE comp_que)
    {
        m_comp_que = comp_que;

        switch(comp_que)
        {
            case(ASSERT_AFTER_1_CONV):
                m_ADS_write[2] &= ~(1 << COMP_QUE_BIT_1);
                m_ADS_write[2] &= ~(1 << COMP_QUE_BIT_2);
            break;

            case(ASSERT_AFTER_2_CONV):
                m_ADS_write[2] &= ~(1 << COMP_QUE_BIT_1);
                m_ADS_write[2] |= (1 << COMP_QUE_BIT_2);
            break;

            case(ASSERT_AFTER_4_CONV):
                m_ADS_write[2] |= (1 << COMP_QUE_BIT_1);
                m_ADS_write[2] &= ~(1 << COMP_QUE_BIT_2);
            break;

            case(DISABLE_COMP):
                m_ADS_write[2] |= (1 << COMP_QUE_BIT_1);
                m_ADS_write[2] |= (1 << COMP_QUE_BIT_2);
            break;
        }
    }

    COMP_QUE ADS1115::get_comp_que()
    {
        return m_comp_que;
    }

    void ADS1115::set_low_threshold(int16_t threshold)
    {
        m_ADS_write_thresh[0] = 0x02;
        m_ADS_write_thresh[1] = (threshold >> 8) & 0xFF;
        m_ADS_write_thresh[2] = threshold & 0xFF;
        HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write_thresh, 3, 100);
    }

    void ADS1115::set_high_threshold(int16_t threshold)
    {
        m_ADS_write_thresh[0] = 0x03;
        m_ADS_write_thresh[1] = (threshold >> 8) & 0xFF;
        m_ADS_write_thresh[2] = threshold & 0xFF;
        HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write_thresh, 3, 100);
    }

    void ADS1115::upload_config()
    {
        m_ADS_write[0] = 0x01;
        HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write, 3, 100);
        m_ADS_write[0] = 0x00;
        HAL_I2C_Master_Transmit(&m_i2c_handle, m_address<<1, m_ADS_write, 1, 100);
        HAL_Delay(20);
    }

    int16_t ADS1115::get_conversion()
    {   
        HAL_I2C_Master_Receive(&hi2c1, m_address<<1, m_ADS_read, 2, 100);
        m_reading = m_ADS_read[0] << 8 | m_ADS_read[1];
        if(m_reading < 0)
        {
            m_reading = 0;
        }

        return m_reading;
    }

    ADS1115& ADS1115::operator=(const ADS1115& other)
    {
        set_mux(other.m_mux);
        set_gain(other.m_pga);
        set_ADS_mode(other.m_ADS_mode);
        set_data_rate(other.m_data_rate);
        set_comp_mode(other.m_comp_mode);
        set_comp_latch(other.m_comp_latch);
        set_comp_que(other.m_comp_que);

        return *this;
    }

    bool ADS1115::operator==(const ADS1115& other)
    {
        return (m_mux==other.m_mux && 
                m_pga == other.m_pga &&
                m_ADS_mode == other.m_ADS_mode &&
                m_data_rate == other.m_data_rate &&
                m_comp_mode == other.m_comp_mode &&
                m_comp_polarity == other.m_comp_polarity &&
                m_comp_latch == other.m_comp_latch &&
                m_comp_que == other.m_comp_que);
    }

    bool ADS1115::operator!=(const ADS1115& other)
    {
        return !(*this == other);
    }
}