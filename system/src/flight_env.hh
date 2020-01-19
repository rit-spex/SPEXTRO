
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

    bool is_vaild(){
        return m_valid;
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

struct sensor_bno055_accel{
    // mps is meters per second squared
    int16_t accel_x_mpss;
    int16_t accel_y_mpss;
    int16_t accel_z_mpss;
};

struct gps_position{
    float latitude;
    float longitude;
};

struct quaternion{
    int16_t a;
    int16_t b;
    int16_t c;
    int16_t d;
};

enum flight_phase{
    STANDBY = 0,
    LAUNCH_READY = 1,
    LAUNCHED = 2,
    PAYLOAD_DEPLOYED = 3,
    PARACHUTE_DEPLOYED = 4,
    RECOVERY = 5
};

struct payload_data{
    data_point<flight_phase> system_phase;
    data_point<float> altitude_meters;
    data_point<float> sea_level_altitude_meters;
    data_point<quaternion> abs_orentation;
    data_point<gps_position> gps_position;
    // Add more...
};

struct raw_sensor_data{
    data_point<sensor_bme680> bme680;
    data_point<sensor_bno055_accel> bno055_accel;
    // Add more...
};

struct flight_env{
    payload_data payload_params;
    raw_sensor_data raw_sensor_params;
};