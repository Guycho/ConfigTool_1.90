# SimpleFOC ConfigTool Extension Plan

## 🎯 **Goal**
Extend the existing AM32 ConfigTool to include SimpleFOC-specific parameters for easy GUI configuration.

## 📋 **SimpleFOC Parameters to Add**

### **Core Parameters**
| Parameter | ID | Type | Range | Description |
|-----------|----|----- |-------|-------------|
| `simplefoc_enabled` | P0 | Boolean | 0/1 | Enable SimpleFOC mode |
| `pole_pairs` | P1 | Integer | 1-50 | Motor pole pairs |
| `voltage_limit` | P2 | Float | 0-25.5V | Motor voltage limit |
| `current_limit` | P3 | Float | 0-51A | Motor current limit |
| `velocity_limit` | P4 | Float | 0-2550 rad/s | Maximum velocity |

### **PID Controllers**
| Parameter | ID | Type | Range | Description |
|-----------|----|----- |-------|-------------|
| `pid_current_p` | P5 | Float | 0-25.5 | Current loop P gain |
| `pid_current_i` | P6 | Float | 0-25.5 | Current loop I gain |
| `pid_current_d` | P7 | Float | 0-25.5 | Current loop D gain |
| `pid_velocity_p` | P8 | Float | 0-25.5 | Velocity loop P gain |
| `pid_velocity_i` | P9 | Float | 0-25.5 | Velocity loop I gain |
| `pid_velocity_d` | P10 | Float | 0-25.5 | Velocity loop D gain |

### **Sensor Configuration**
| Parameter | ID | Type | Range | Description |
|-----------|----|----- |-------|-------------|
| `sensor_min_pulse` | P11 | Integer | 0-65535 μs | PWM sensor min pulse |
| `sensor_max_pulse` | P12 | Integer | 0-65535 μs | PWM sensor max pulse |
| `sensor_type` | P13 | Select | PWM/Analog | Sensor type (requires reboot) |
| `sensor_direction` | P14 | Boolean | 0/1 | Sensor direction |
| `sensor_offset` | P15 | Float | 0-6.28 rad | Sensor zero offset |
| `filter_alpha` | P16 | Float | 0-2.55 | Low-pass filter strength |

### **DShot Velocity Mapping**
| Parameter | ID | Type | Range | Description |
|-----------|----|----- |-------|-------------|
| `dshot_max_velocity` | P17 | Integer | 0-65535 rad/s | Max velocity for DShot 1000-2000 |
| `dshot_deadband` | P18 | Float | 0-25.5% | Deadband around center (1500) |
| `dshot_expo` | P19 | Float | 0-2.55 | Exponential response curve |
| `dshot_direction` | P20 | Boolean | 0/1 | DShot direction |

## 🔧 **Implementation Plan**

### **Phase 1: UI Extension**
1. **Add SimpleFOC Tab** - New tab in the main interface
2. **Group Parameters** - Organize into logical groups:
   - Motor Configuration
   - PID Tuning
   - Sensor Setup
   - DShot Mapping

### **Phase 2: Communication Protocol**
1. **Extend MSP Commands** - Add SimpleFOC parameter read/write
2. **Parameter Validation** - Range checking and type validation
3. **Reboot Notification** - Warn user when reboot required

### **Phase 3: User Experience**
1. **Presets** - Common configurations (AS5600 PWM/Analog)
2. **Wizards** - Step-by-step setup guides
3. **Real-time Monitoring** - Live parameter display

## 📁 **Files to Modify**

### **Core Files**
- `widget.ui` - Add SimpleFOC tab and controls
- `widget.h` - Add SimpleFOC parameter handling
- `widget.cpp` - Implement SimpleFOC functionality
- `defaults.h` - Add SimpleFOC default values

### **New Files to Create**
- `simplefoc_params.h` - SimpleFOC parameter definitions
- `simplefoc_presets.h` - Common configuration presets
- `simplefoc_wizard.cpp/h` - Setup wizard implementation

## 🎨 **UI Layout Design**

```
┌─────────────────────────────────────────────────────────┐
│ AM32 ConfigTool - SimpleFOC Extension                   │
├─────────────────────────────────────────────────────────┤
│ [General] [Motor] [ESC] [SimpleFOC] [Advanced]         │
├─────────────────────────────────────────────────────────┤
│ SimpleFOC Configuration                                 │
│                                                         │
│ ┌─ Enable SimpleFOC ─────────────────────────────────┐ │
│ │ [✓] Enable SimpleFOC Mode (Velocity Only)          │ │
│ │     ⚠️  Requires reboot to take effect             │ │
│ └─────────────────────────────────────────────────────┘ │
│                                                         │
│ ┌─ Motor Configuration ──────────────────────────────┐ │
│ │ Pole Pairs:     [7    ] (14-pole motor)           │ │
│ │ Voltage Limit:  [12.0 ] V                         │ │
│ │ Current Limit:  [10.0 ] A                         │ │
│ │ Velocity Limit: [1500 ] rad/s                     │ │
│ └─────────────────────────────────────────────────────┘ │
│                                                         │
│ ┌─ Sensor Configuration ─────────────────────────────┐ │
│ │ Sensor Type:    [PWM ▼] ⚠️  Requires reboot       │ │
│ │ Min Pulse:      [128  ] μs (PWM mode only)        │ │
│ │ Max Pulse:      [4223 ] μs (PWM mode only)        │ │
│ │ Direction:      [Normal ▼]                        │ │
│ │ Zero Offset:    [0.0  ] rad                       │ │
│ │ Filter Alpha:   [0.1  ] (0.0-2.55)               │ │
│ │                                                   │ │
│ │ [AS5600 PWM Preset] [AS5600 Analog Preset]       │ │
│ └─────────────────────────────────────────────────────┘ │
│                                                         │
│ ┌─ DShot Velocity Mapping (1000-2000 range) ────────┐ │
│ │ Max Velocity:   [1500 ] rad/s                     │ │
│ │ Deadband:       [2.0  ] % (around 1500)          │ │
│ │ Exponential:    [1.0  ] (1.0 = linear)           │ │
│ │ Direction:      [Normal ▼]                        │ │
│ │                                                   │ │
│ │ DShot Range: 0-1000 (Reserved) | 1000-2000 (Vel) │ │
│ └─────────────────────────────────────────────────────┘ │
│                                                         │
│ ┌─ PID Tuning ───────────────────────────────────────┐ │
│ │ Current Loop:  P[5.0] I[10.0] D[0.0]              │ │
│ │ Velocity Loop: P[0.5] I[10.0] D[0.0]              │ │
│ │                                                   │ │
│ │ [Conservative] [Balanced] [Aggressive] [Custom]   │ │
│ └─────────────────────────────────────────────────────┘ │
│                                                         │
│ [Read from ESC] [Write to ESC] [Reset to Defaults]     │
└─────────────────────────────────────────────────────────┘
```

## 🚀 **Quick Start Implementation**

### **Step 1: Add SimpleFOC Tab**
```cpp
// In widget.ui - add new tab
<widget class="QTabWidget" name="mainTabs">
  <widget class="QWidget" name="simplefocTab">
    <attribute name="title">
      <string>SimpleFOC</string>
    </attribute>
    <!-- SimpleFOC controls here -->
  </widget>
</widget>
```

### **Step 2: Add Parameter Handling**
```cpp
// In widget.h - add SimpleFOC members
private:
    // SimpleFOC parameters
    bool simplefoc_enabled;
    int pole_pairs;
    float voltage_limit;
    // ... etc
    
    void readSimpleFOCParams();
    void writeSimpleFOCParams();
    void setSimpleFOCDefaults();
```

### **Step 3: Implement Communication**
```cpp
// In widget.cpp - add SimpleFOC MSP commands
void Widget::readSimpleFOCParams() {
    // Send MSP commands to read P0-P20
    for (int i = 0; i <= 20; i++) {
        send_mspCommand(MSP_GET_SIMPLEFOC_PARAM, QByteArray(1, i));
    }
}
```

## ✅ **Benefits of This Approach**

1. **✅ User-Friendly** - GUI instead of UART commands
2. **✅ Parameter Validation** - Range checking and type safety
3. **✅ Presets** - Quick setup for common sensors
4. **✅ Visual Feedback** - Real-time parameter display
5. **✅ Documentation** - Built-in help and tooltips
6. **✅ Backup/Restore** - Save/load configurations
7. **✅ Cross-Platform** - Qt works on Windows/Mac/Linux

This extension will make SimpleFOC configuration much more accessible while maintaining all the advanced features we've implemented!
