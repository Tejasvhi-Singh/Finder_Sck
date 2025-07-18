#!/bin/bash

# Mac File Explorer Build Script
# This script builds the C++ file explorer application for macOS

set -e

echo "🚀 Building Mac File Explorer..."

# Configuration
PROJECT_NAME="MacFileExplorer"
BUILD_TYPE="Release"
BUILD_DIR="build"
INSTALL_DIR="dist"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Functions
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check prerequisites
check_prerequisites() {
    print_status "Checking prerequisites..."
    
    # Check if we're on macOS
    if [[ "$OSTYPE" != "darwin"* ]]; then
        print_error "This script is designed for macOS only!"
        exit 1
    fi
    
    # Check for cmake
    if ! command -v cmake &> /dev/null; then
        print_error "CMake is required but not installed. Please install it using: brew install cmake"
        exit 1
    fi
    
    # Check for Qt6
    if ! command -v qmake6 &> /dev/null && ! command -v qmake &> /dev/null; then
        print_error "Qt6 is required but not installed. Please install it using: brew install qt@6"
        exit 1
    fi
    
    # Check for Xcode Command Line Tools
    if ! command -v clang++ &> /dev/null; then
        print_error "Xcode Command Line Tools are required. Please install them using: xcode-select --install"
        exit 1
    fi
    
    print_success "All prerequisites are met!"
}

# Clean build directory
clean_build() {
    print_status "Cleaning build directory..."
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
    fi
    mkdir -p "$BUILD_DIR"
    print_success "Build directory cleaned!"
}

# Configure CMake
configure_cmake() {
    print_status "Configuring CMake..."
    cd "$BUILD_DIR"
    
    # Find Qt6 installation
    QT6_PATH=""
    if [ -d "/opt/homebrew/opt/qt@6" ]; then
        QT6_PATH="/opt/homebrew/opt/qt@6"
    elif [ -d "/usr/local/opt/qt@6" ]; then
        QT6_PATH="/usr/local/opt/qt@6"
    elif [ -d "/opt/Qt/6.7.0/macos" ]; then
        QT6_PATH="/opt/Qt/6.7.0/macos"
    fi
    
    CMAKE_ARGS="-DCMAKE_BUILD_TYPE=$BUILD_TYPE"
    CMAKE_ARGS="$CMAKE_ARGS -DCMAKE_OSX_DEPLOYMENT_TARGET=10.15"
    CMAKE_ARGS="$CMAKE_ARGS -DCMAKE_OSX_ARCHITECTURES=arm64;x86_64"
    
    if [ ! -z "$QT6_PATH" ]; then
        CMAKE_ARGS="$CMAKE_ARGS -DCMAKE_PREFIX_PATH=$QT6_PATH"
        print_status "Using Qt6 from: $QT6_PATH"
    fi
    
    cmake .. $CMAKE_ARGS
    
    if [ $? -eq 0 ]; then
        print_success "CMake configuration completed!"
    else
        print_error "CMake configuration failed!"
        exit 1
    fi
    
    cd ..
}

# Build the project
build_project() {
    print_status "Building project..."
    cd "$BUILD_DIR"
    
    # Use all available cores for compilation
    CORES=$(sysctl -n hw.ncpu)
    make -j$CORES
    
    if [ $? -eq 0 ]; then
        print_success "Build completed successfully!"
    else
        print_error "Build failed!"
        exit 1
    fi
    
    cd ..
}

# Create application bundle
create_bundle() {
    print_status "Creating application bundle..."
    
    # Create distribution directory
    mkdir -p "$INSTALL_DIR"
    
    # Copy the application bundle
    if [ -d "$BUILD_DIR/$PROJECT_NAME.app" ]; then
        cp -R "$BUILD_DIR/$PROJECT_NAME.app" "$INSTALL_DIR/"
        print_success "Application bundle created at $INSTALL_DIR/$PROJECT_NAME.app"
    else
        print_error "Application bundle not found!"
        exit 1
    fi
}

# Deploy Qt libraries
deploy_qt() {
    print_status "Deploying Qt libraries..."
    
    # Find macdeployqt
    MACDEPLOYQT=""
    if [ -f "/opt/homebrew/opt/qt@6/bin/macdeployqt" ]; then
        MACDEPLOYQT="/opt/homebrew/opt/qt@6/bin/macdeployqt"
    elif [ -f "/usr/local/opt/qt@6/bin/macdeployqt" ]; then
        MACDEPLOYQT="/usr/local/opt/qt@6/bin/macdeployqt"
    elif command -v macdeployqt &> /dev/null; then
        MACDEPLOYQT="macdeployqt"
    fi
    
    if [ ! -z "$MACDEPLOYQT" ]; then
        "$MACDEPLOYQT" "$INSTALL_DIR/$PROJECT_NAME.app"
        if [ $? -eq 0 ]; then
            print_success "Qt libraries deployed successfully!"
        else
            print_warning "Qt deployment completed with warnings"
        fi
    else
        print_warning "macdeployqt not found. Manual Qt deployment may be required."
    fi
}

# Sign the application (if developer certificate is available)
sign_application() {
    print_status "Checking for code signing..."
    
    # Check if developer certificate is available
    if security find-identity -v -p codesigning | grep -q "Developer ID Application"; then
        print_status "Developer certificate found. Signing application..."
        codesign --deep --force --verify --verbose --sign "Developer ID Application" "$INSTALL_DIR/$PROJECT_NAME.app"
        if [ $? -eq 0 ]; then
            print_success "Application signed successfully!"
        else
            print_warning "Code signing failed, but application should still run"
        fi
    else
        print_warning "No developer certificate found. Application will not be signed."
        print_warning "For distribution, you may need to sign the application manually."
    fi
}

# Create DMG (optional)
create_dmg() {
    print_status "Creating DMG installer..."
    
    DMG_NAME="$PROJECT_NAME-1.0.0.dmg"
    
    if command -v create-dmg &> /dev/null; then
        create-dmg \
            --volname "$PROJECT_NAME" \
            --volicon "$INSTALL_DIR/$PROJECT_NAME.app/Contents/Resources/app_icon.icns" \
            --window-pos 200 120 \
            --window-size 600 400 \
            --icon-size 100 \
            --icon "$PROJECT_NAME.app" 175 190 \
            --hide-extension "$PROJECT_NAME.app" \
            --app-drop-link 425 190 \
            "$INSTALL_DIR/$DMG_NAME" \
            "$INSTALL_DIR/$PROJECT_NAME.app"
        
        if [ $? -eq 0 ]; then
            print_success "DMG created: $INSTALL_DIR/$DMG_NAME"
        else
            print_warning "DMG creation failed"
        fi
    else
        print_warning "create-dmg not found. Install it using: brew install create-dmg"
    fi
}

# Main build process
main() {
    print_status "Starting Mac File Explorer build process..."
    
    # Check command line arguments
    while [[ $# -gt 0 ]]; do
        case $1 in
            --debug)
                BUILD_TYPE="Debug"
                shift
                ;;
            --clean)
                clean_build
                shift
                ;;
            --help)
                echo "Usage: $0 [options]"
                echo "Options:"
                echo "  --debug     Build in debug mode"
                echo "  --clean     Clean build directory before building"
                echo "  --help      Show this help message"
                exit 0
                ;;
            *)
                print_error "Unknown option: $1"
                exit 1
                ;;
        esac
    done
    
    # Execute build steps
    check_prerequisites
    clean_build
    configure_cmake
    build_project
    create_bundle
    deploy_qt
    sign_application
    create_dmg
    
    print_success "🎉 Build completed successfully!"
    print_status "Application available at: $INSTALL_DIR/$PROJECT_NAME.app"
    print_status "You can now run the application or distribute it."
}

# Run main function
main "$@" 