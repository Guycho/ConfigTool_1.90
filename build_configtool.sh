#!/bin/bash

# SimpleFOC ConfigTool Build Script
echo "🔧 Building SimpleFOC ConfigTool..."

# Check if Qt is available
if ! command -v qmake &> /dev/null; then
    echo "❌ Error: qmake not found. Please install Qt development tools."
    echo "   Ubuntu/Debian: sudo apt install qt5-qmake qtbase5-dev qtserialport5-dev"
    echo "   Fedora: sudo dnf install qt5-qtbase-devel qt5-qtserialport-devel"
    exit 1
fi

# Clean previous build
echo "🧹 Cleaning previous build..."
make clean 2>/dev/null || true
rm -f Makefile
rm -f SerialPortConnector

# Generate Makefile
echo "📋 Generating Makefile..."
qmake SerialPortConnector.pro

if [ $? -ne 0 ]; then
    echo "❌ Error: qmake failed"
    exit 1
fi

# Build the project
echo "🔨 Building project..."
make -j$(nproc)

if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    echo "🚀 Run with: ./SerialPortConnector"
    echo ""
    echo "📋 SimpleFOC Features:"
    echo "   • Complete GUI for all 21 SimpleFOC parameters"
    echo "   • AS5600 PWM/Analog presets"
    echo "   • PID tuning presets (Conservative/Balanced/Aggressive)"
    echo "   • DShot velocity mapping (1000-2000 range)"
    echo "   • Real-time parameter validation"
    echo "   • MSP communication with AM32 firmware"
    echo ""
    echo "🔗 Connect to your AM32 ESC and use the SimpleFOC tab!"
else
    echo "❌ Build failed"
    exit 1
fi
