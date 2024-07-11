#ifndef KINECT2_COMPAT_H
#define KINECT2_COMPAT_H

#include <cstdint>
#include <cstddef>
#include <time.h>  // For struct timespec and clock_gettime
#include <string>  // For std::wstring

typedef struct {
    int width;
    int height;
    void* pFrameTexture;
    uint32_t dwFrameNumber;
    struct {
        int64_t QuadPart;
    } liTimeStamp;
} NUI_IMAGE_FRAME;

typedef struct {
    int Pitch;
    void* pBits;
    size_t size;
} NUI_LOCKED_RECT;

typedef struct {
    uint16_t depth;
    uint16_t playerIndex;
} NUI_DEPTH_IMAGE_PIXEL;

// Define the RGBQUAD structure
typedef struct {
    uint8_t rgbBlue;
    uint8_t rgbGreen;
    uint8_t rgbRed;
    uint8_t rgbReserved;
} RGBQUAD;

typedef int NUI_IMAGE_TYPE;
typedef int NUI_IMAGE_RESOLUTION;
typedef void* HANDLE;

#define NUI_CAMERA_COLOR_NOMINAL_HORIZONTAL_FOV 57.0
#define NUI_CAMERA_DEPTH_NOMINAL_HORIZONTAL_FOV 58.5
#define NUI_CAMERA_COLOR_NOMINAL_VERTICAL_FOV  43.0
#define NUI_CAMERA_DEPTH_NOMINAL_VERTICAL_FOV  45.6

typedef struct timespec LARGE_INTEGER;  // Replacement for LARGE_INTEGER

inline void QueryPerformanceCounter(LARGE_INTEGER* counter) {
    clock_gettime(CLOCK_MONOTONIC, counter);
}

typedef int HRESULT;
#define S_OK 0
#define E_FAIL -1
#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)

#define NUI_IMAGE_STREAM_FLAG_ENABLE_NEAR_MODE 0x0001

// Define a mock INuiSensor structure with necessary methods
struct Vector4 {
    float x, y, z, w;
};

struct INuiSensor {
    virtual HRESULT NuiInitialize(uint32_t dwFlags) = 0;
    virtual void NuiShutdown() = 0;
    virtual unsigned long Release() = 0;
    virtual HRESULT NuiCameraElevationSetAngle(long angle) = 0;
    virtual HRESULT NuiSetForceInfraredEmitterOff(bool off) { return S_OK; } // Mock function
    virtual bool NuiGetForceInfraredEmitterOff() const { return false; } // Mock function
    virtual std::wstring NuiAudioArrayId() const { return L"mock_array_id"; } // Mock function
    virtual HRESULT NuiAccelerometerGetCurrentReading(Vector4* pReading) { 
        pReading->x = 0.0f; 
        pReading->y = 0.0f; 
        pReading->z = 0.0f; 
        pReading->w = 0.0f; 
        return S_OK; 
    } // Mock function
    virtual HRESULT NuiCameraElevationGetAngle(long* pAngle) { *pAngle = 0; return S_OK; } // Mock function
};

// Mock implementation of INuiSensor methods
class NuiSensorImpl : public INuiSensor {
public:
    HRESULT NuiInitialize(uint32_t dwFlags) override {
        // Add initialization logic here
        return S_OK;
    }

    void NuiShutdown() override {
        // Add shutdown logic here
    }

    unsigned long Release() override {
        // Add release logic here
        return 0;
    }

    HRESULT NuiCameraElevationSetAngle(long angle) override {
        // Add logic to set camera elevation angle here
        return S_OK;
    }
};


 struct ColorSpacePoint { float X, Y; };
 struct CameraSpacePoint { float X, Y, Z; };

#endif  // KINECT2_COMPAT_H
