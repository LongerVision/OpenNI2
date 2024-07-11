#ifndef _DEPTH_KINECT2_STREAM_H_
#define _DEPTH_KINECT2_STREAM_H_

#include "Kinect2Driver.h"
#include "Kinect2Device.h"
#include "BaseKinect2Stream.h"
// #include <Kinect.h>

namespace kinect2_device
{
  class DepthKinect2Stream : public BaseKinect2Stream
  {
    public:
      DepthKinect2Stream(Kinect2StreamImpl* pStreamImpl);
      virtual ~DepthKinect2Stream();

      virtual void frameReady(void* data, int width, int height, double timestamp);

      virtual OniStatus getProperty(int propertyId, void* data, int* pDataSize);
      virtual OniBool isPropertySupported(int propertyId);
      virtual void notifyAllProperties();

    private:
      void copyDepthPixelsStraight(const uint16_t* data_in, int width, int height, OniFrame* pFrame);
      void copyDepthPixelsWithImageRegistration(const uint16_t* data_in, int width, int height, OniFrame* pFrame);

    private:
      ColorSpacePoint* m_colorSpaceCoords;
      uint16_t* m_registeredDepthMap;
  };
} // namespace kinect2_device

#endif //_DEPTH_KINECT2_STREAM_H_
