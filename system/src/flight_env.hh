
#pragma once

template<typename T>
struct data_point{
public:
    void update(uint32_t time, T data){
        m_time_updated = time;
        m_data = data;
        m_valid = true;
    }

    uint32_t get_time_updated(){
        return m_time_updated;
    }

    T get_data(){
        return m_data;
    }

private:
    uint32_t m_time_updated;
    T m_data;
    bool m_valid{false};
};

struct sensor_bme680{
    int16_t temperature_degC;
    uint32_t pressure_hPa;
    uint32_t humidity_rel;
};

struct payload_data{
    data_point<float> altitude_meters;
    data_point<float> sea_level_altitude_meters;
    // Add more...
};

struct raw_sensor_data{
    data_point<sensor_bme680> bme680;
    // Add more...
};

struct flight_env{
    payload_data payload_params;
    raw_sensor_data raw_sensor_params;
};