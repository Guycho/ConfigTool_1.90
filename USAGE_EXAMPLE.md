# 🚀 SimpleFOC ConfigTool - Usage Example

## **Quick Start Guide**

### **1. Build & Run**
```bash
cd /home/guy/gitroot/AM32/tools/ConfigTool
./build_configtool.sh
./SerialPortConnector
```

### **2. Connect to ESC**
1. Connect USB-UART to your AM32 ESC
2. Select serial port in ConfigTool
3. Click "Connect"

### **3. Configure SimpleFOC**

#### **🎯 Basic Setup (AS5600 PWM Sensor)**
1. Click **SimpleFOC tab**
2. Check **"Enable SimpleFOC Mode"** ✅
3. Set **Pole Pairs**: `7` (for 14-pole motor)
4. Set **Voltage Limit**: `12.0V`
5. Set **Current Limit**: `10.0A`
6. Click **"AS5600 PWM Preset"** button
7. Set **DShot Max Velocity**: `1500 rad/s`
8. Click **"Balanced"** PID preset
9. Click **"Write to ESC"**
10. **Reboot ESC** to apply changes

#### **🎯 Alternative Setup (AS5600 Analog Sensor)**
1. Follow steps 1-5 above
2. Click **"AS5600 Analog Preset"** button instead
3. Continue with steps 7-10

#### **🎯 Custom PID Tuning**
1. Start with **"Conservative"** preset for initial testing
2. If response is too slow → try **"Balanced"**
3. If still need more performance → try **"Aggressive"**
4. For custom tuning, manually adjust individual PID values

---

## **📋 Parameter Recommendations**

### **🔧 Motor Configuration**
```
14-pole motor:     pole_pairs = 7
28-pole motor:     pole_pairs = 14
12V system:        voltage_limit = 12.0V
24V system:        voltage_limit = 24.0V
Small motor:       current_limit = 5.0A
Large motor:       current_limit = 20.0A
```

### **📡 DShot Velocity Mapping**
```
Conservative:      dshot_max_velocity = 1000 rad/s
Balanced:          dshot_max_velocity = 1500 rad/s
High Performance:  dshot_max_velocity = 2000 rad/s
Deadband:          2.0% (reduces jitter around center)
```

### **🎛️ PID Tuning Guidelines**
```
Conservative (Stable):
  Current:  P=3.0, I=5.0, D=0.0
  Velocity: P=0.2, I=5.0, D=0.0

Balanced (Recommended):
  Current:  P=5.0, I=10.0, D=0.0
  Velocity: P=0.5, I=10.0, D=0.0

Aggressive (High Performance):
  Current:  P=8.0, I=15.0, D=0.1
  Velocity: P=1.0, I=15.0, D=0.05
```

---

## **⚠️ Important Notes**

### **🔄 Reboot Required**
- **SimpleFOC Enable/Disable** requires reboot
- **Sensor Type changes** require reboot  
- **Motor parameters** require reboot
- **PID and DShot parameters** take effect immediately

### **🔧 Troubleshooting**
```
Problem: "Error: Serial port not connected"
Solution: Check USB cable and select correct COM port

Problem: "Error: Invalid parameter values"  
Solution: Check all values are within valid ranges

Problem: Motor doesn't respond
Solution: 1) Verify SimpleFOC is enabled
         2) Check sensor connections
         3) Verify pole pairs setting
         4) Try conservative PID preset

Problem: Oscillations/instability
Solution: 1) Use Conservative PID preset
         2) Reduce velocity limit
         3) Increase filter_alpha value
```

### **📊 Status Messages**
- **🟢 Green**: Success (parameters written, presets applied)
- **🟠 Orange**: Warning (reboot required, sensor type changed)  
- **🔴 Red**: Error (connection failed, invalid values)
- **🔵 Blue**: Info (ready, reading parameters)

---

## **🎯 Workflow Example**

### **Complete Setup from Scratch**
```
1. Hardware Setup:
   ├── Connect AS5600 sensor to TX pin (PWM mode)
   ├── Connect DShot signal to SIGNAL pin  
   └── Connect USB-UART for configuration

2. ConfigTool Setup:
   ├── Build and run ConfigTool
   ├── Connect to ESC
   └── Navigate to SimpleFOC tab

3. Basic Configuration:
   ├── Enable SimpleFOC ✅
   ├── Set pole pairs (7 for 14-pole motor)
   ├── Set voltage limit (12.0V)
   ├── Set current limit (10.0A)
   └── Set velocity limit (1500 rad/s)

4. Sensor Configuration:
   ├── Click "AS5600 PWM Preset"
   └── Verify sensor type = PWM

5. DShot Configuration:
   ├── Set max velocity (1500 rad/s)
   └── Set deadband (2.0%)

6. PID Tuning:
   ├── Start with "Balanced" preset
   └── Adjust if needed based on performance

7. Apply Settings:
   ├── Click "Write to ESC"
   ├── Reboot ESC
   └── Test motor response

8. Fine Tuning:
   ├── Adjust PID if oscillations occur
   ├── Modify velocity limits if needed
   └── Re-write and test
```

This workflow gives you a **fully configured SimpleFOC system** with professional GUI control! 🎉
