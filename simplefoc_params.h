#ifndef SIMPLEFOC_PARAMS_H
#define SIMPLEFOC_PARAMS_H

#include <QWidget>
#include <QString>

// SimpleFOC Parameter IDs (matching AM32 firmware)
enum SimpleFOCParamID {
    SIMPLEFOC_PARAM_ENABLED = 0,
    SIMPLEFOC_PARAM_POLE_PAIRS = 1,
    SIMPLEFOC_PARAM_VOLTAGE_LIMIT = 2,
    SIMPLEFOC_PARAM_CURRENT_LIMIT = 3,
    SIMPLEFOC_PARAM_VELOCITY_LIMIT = 4,
    SIMPLEFOC_PARAM_PID_CURRENT_P = 5,
    SIMPLEFOC_PARAM_PID_CURRENT_I = 6,
    SIMPLEFOC_PARAM_PID_CURRENT_D = 7,
    SIMPLEFOC_PARAM_PID_VELOCITY_P = 8,
    SIMPLEFOC_PARAM_PID_VELOCITY_I = 9,
    SIMPLEFOC_PARAM_PID_VELOCITY_D = 10,
    SIMPLEFOC_PARAM_SENSOR_MIN_PULSE = 11,
    SIMPLEFOC_PARAM_SENSOR_MAX_PULSE = 12,
    SIMPLEFOC_PARAM_SENSOR_TYPE = 13,
    SIMPLEFOC_PARAM_SENSOR_DIRECTION = 14,
    SIMPLEFOC_PARAM_SENSOR_OFFSET = 15,
    SIMPLEFOC_PARAM_FILTER_ALPHA = 16,
    SIMPLEFOC_PARAM_DSHOT_MAX_VEL = 17,
    SIMPLEFOC_PARAM_DSHOT_DEADBAND = 18,
    SIMPLEFOC_PARAM_DSHOT_EXPO = 19,
    SIMPLEFOC_PARAM_DSHOT_DIRECTION = 20,
    SIMPLEFOC_PARAM_COUNT = 21
};

// SimpleFOC Parameter Structure
struct SimpleFOCParams {
    // Core parameters
    bool enabled;
    int pole_pairs;
    float voltage_limit;
    float current_limit;
    float velocity_limit;
    
    // PID parameters
    float pid_current_p;
    float pid_current_i;
    float pid_current_d;
    float pid_velocity_p;
    float pid_velocity_i;
    float pid_velocity_d;
    
    // Sensor parameters
    int sensor_min_pulse;
    int sensor_max_pulse;
    int sensor_type;  // 0=PWM, 1=Analog
    bool sensor_direction;
    float sensor_offset;
    float filter_alpha;
    
    // DShot velocity mapping
    int dshot_max_velocity;
    float dshot_deadband;
    float dshot_expo;
    bool dshot_direction;
    
    // Constructor with defaults
    SimpleFOCParams() {
        setDefaults();
    }
    
    void setDefaults() {
        enabled = false;
        pole_pairs = 7;
        voltage_limit = 12.0f;
        current_limit = 10.0f;
        velocity_limit = 1000.0f;
        
        pid_current_p = 5.0f;
        pid_current_i = 10.0f;
        pid_current_d = 0.0f;
        pid_velocity_p = 0.5f;
        pid_velocity_i = 10.0f;
        pid_velocity_d = 0.0f;
        
        sensor_min_pulse = 128;
        sensor_max_pulse = 4223;
        sensor_type = 0;  // PWM
        sensor_direction = true;  // Normal
        sensor_offset = 0.0f;
        filter_alpha = 0.1f;
        
        dshot_max_velocity = 1500;
        dshot_deadband = 2.0f;
        dshot_expo = 1.0f;
        dshot_direction = false;  // Normal
    }
    
    void setAS5600PWMPreset() {
        sensor_type = 0;  // PWM
        sensor_min_pulse = 128;
        sensor_max_pulse = 4223;
        filter_alpha = 0.1f;  // Light filtering for PWM
    }
    
    void setAS5600AnalogPreset() {
        sensor_type = 1;  // Analog
        sensor_min_pulse = 0;  // Not used in analog mode
        sensor_max_pulse = 0;  // Not used in analog mode
        filter_alpha = 0.2f;  // More filtering for analog
    }
    
    void setConservativePIDPreset() {
        pid_current_p = 3.0f;
        pid_current_i = 5.0f;
        pid_current_d = 0.0f;
        pid_velocity_p = 0.2f;
        pid_velocity_i = 5.0f;
        pid_velocity_d = 0.0f;
    }
    
    void setBalancedPIDPreset() {
        pid_current_p = 5.0f;
        pid_current_i = 10.0f;
        pid_current_d = 0.0f;
        pid_velocity_p = 0.5f;
        pid_velocity_i = 10.0f;
        pid_velocity_d = 0.0f;
    }
    
    void setAggressivePIDPreset() {
        pid_current_p = 8.0f;
        pid_current_i = 15.0f;
        pid_current_d = 0.1f;
        pid_velocity_p = 1.0f;
        pid_velocity_i = 15.0f;
        pid_velocity_d = 0.05f;
    }
};

// Parameter validation functions
inline bool isValidPolePairs(int value) {
    return value >= 1 && value <= 50;
}

inline bool isValidVoltageLimit(float value) {
    return value >= 0.0f && value <= 25.5f;
}

inline bool isValidCurrentLimit(float value) {
    return value >= 0.0f && value <= 51.0f;
}

inline bool isValidVelocityLimit(float value) {
    return value >= 0.0f && value <= 2550.0f;
}

inline bool isValidPIDGain(float value) {
    return value >= 0.0f && value <= 25.5f;
}

inline bool isValidPulseWidth(int value) {
    return value >= 0 && value <= 65535;
}

inline bool isValidSensorType(int value) {
    return value == 0 || value == 1;  // PWM or Analog
}

inline bool isValidSensorOffset(float value) {
    return value >= 0.0f && value <= 6.28f;  // 0 to 2π
}

inline bool isValidFilterAlpha(float value) {
    return value >= 0.0f && value <= 2.55f;
}

inline bool isValidDShotVelocity(int value) {
    return value >= 0 && value <= 65535;
}

inline bool isValidDShotDeadband(float value) {
    return value >= 0.0f && value <= 25.5f;
}

inline bool isValidDShotExpo(float value) {
    return value >= 0.0f && value <= 2.55f;
}

// Parameter info structure for UI generation
struct SimpleFOCParamInfo {
    SimpleFOCParamID id;
    QString name;
    QString description;
    QString unit;
    float min_value;
    float max_value;
    int decimals;
    bool requires_reboot;
};

// Parameter information table
static const SimpleFOCParamInfo SIMPLEFOC_PARAM_INFO[] = {
    {SIMPLEFOC_PARAM_ENABLED, "Enable SimpleFOC", "Enable SimpleFOC velocity control mode", "", 0, 1, 0, true},
    {SIMPLEFOC_PARAM_POLE_PAIRS, "Pole Pairs", "Number of motor pole pairs", "", 1, 50, 0, true},
    {SIMPLEFOC_PARAM_VOLTAGE_LIMIT, "Voltage Limit", "Maximum motor voltage", "V", 0.0f, 25.5f, 1, true},
    {SIMPLEFOC_PARAM_CURRENT_LIMIT, "Current Limit", "Maximum motor current", "A", 0.0f, 51.0f, 1, true},
    {SIMPLEFOC_PARAM_VELOCITY_LIMIT, "Velocity Limit", "Maximum motor velocity", "rad/s", 0.0f, 2550.0f, 0, true},
    {SIMPLEFOC_PARAM_PID_CURRENT_P, "Current P", "Current loop proportional gain", "", 0.0f, 25.5f, 1, true},
    {SIMPLEFOC_PARAM_PID_CURRENT_I, "Current I", "Current loop integral gain", "", 0.0f, 25.5f, 1, true},
    {SIMPLEFOC_PARAM_PID_CURRENT_D, "Current D", "Current loop derivative gain", "", 0.0f, 25.5f, 1, true},
    {SIMPLEFOC_PARAM_PID_VELOCITY_P, "Velocity P", "Velocity loop proportional gain", "", 0.0f, 25.5f, 1, true},
    {SIMPLEFOC_PARAM_PID_VELOCITY_I, "Velocity I", "Velocity loop integral gain", "", 0.0f, 25.5f, 1, true},
    {SIMPLEFOC_PARAM_PID_VELOCITY_D, "Velocity D", "Velocity loop derivative gain", "", 0.0f, 25.5f, 1, true},
    {SIMPLEFOC_PARAM_SENSOR_MIN_PULSE, "Min Pulse", "PWM sensor minimum pulse width", "μs", 0, 65535, 0, true},
    {SIMPLEFOC_PARAM_SENSOR_MAX_PULSE, "Max Pulse", "PWM sensor maximum pulse width", "μs", 0, 65535, 0, true},
    {SIMPLEFOC_PARAM_SENSOR_TYPE, "Sensor Type", "Sensor type (PWM or Analog)", "", 0, 1, 0, true},
    {SIMPLEFOC_PARAM_SENSOR_DIRECTION, "Sensor Direction", "Sensor rotation direction", "", 0, 1, 0, true},
    {SIMPLEFOC_PARAM_SENSOR_OFFSET, "Sensor Offset", "Sensor zero position offset", "rad", 0.0f, 6.28f, 2, true},
    {SIMPLEFOC_PARAM_FILTER_ALPHA, "Filter Alpha", "Low-pass filter coefficient", "", 0.0f, 2.55f, 2, true},
    {SIMPLEFOC_PARAM_DSHOT_MAX_VEL, "DShot Max Velocity", "Maximum velocity for DShot 1000-2000 range", "rad/s", 0, 65535, 0, true},
    {SIMPLEFOC_PARAM_DSHOT_DEADBAND, "DShot Deadband", "Deadband around DShot center (1500)", "%", 0.0f, 25.5f, 1, true},
    {SIMPLEFOC_PARAM_DSHOT_EXPO, "DShot Exponential", "DShot exponential response curve", "", 0.0f, 2.55f, 2, true},
    {SIMPLEFOC_PARAM_DSHOT_DIRECTION, "DShot Direction", "DShot input direction", "", 0, 1, 0, true}
};

#endif // SIMPLEFOC_PARAMS_H
