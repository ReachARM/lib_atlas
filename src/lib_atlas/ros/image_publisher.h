/**
 * \file	image_publisher.h
 * \author	Thibaut Mattio <thibaut.mattio@gmail.com>
 * \date	23/05/2015
 * \copyright Copyright (c) 2015 Thibaut Mattio. All rights reserved.
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */

#ifndef ATLAS_ROS_IMAGE_PUBLISHER_H_
#define ATLAS_ROS_IMAGE_PUBLISHER_H_

#include <mutex>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

#include <lib_atlas/typedef.h>
#include <lib_atlas/macros.h>
#include <lib_atlas/io/image_sequence_writer.h>

namespace atlas {

class ImagePublisher : public ImageSequenceWriter {
 public:
  //============================================================================
  // C O N S T R U C T O R S   A N D   D E S T R U C T O R

  explicit ImagePublisher(NodeHandlePtr node_handle,
                          const std::string &topic_name) ATLAS_NOEXCEPT;

  ~ImagePublisher() ATLAS_NOEXCEPT;

 private:
  //============================================================================
  // P R I V A T E   M E T H O D S

  /**
   * Publish an image on the topic.
   *
   * This is using the paradigm of ImageSequenceWriter for publishing the image
   * on the topic.
   *
   * If this image writer is streaming and listening a Subject<const cv::Mat &>,
   * this method will be called for every image that is streamed by the
   * provider.
   *
   * For exemple, you could attach this ImageSequenceWriter to a class that
   * stream the content of a video file in order to publish it to a topic:
   * Everything is going to be handled by the system.
   */
  virtual auto WriteImage(const cv::Mat &image) ATLAS_NOEXCEPT -> void override;

  //============================================================================
  // P R I V A T E   M E M B E R S

  std::string topic_name_;

  image_transport::ImageTransport img_transport_;

  image_transport::Publisher publisher_;
};

}  // namespace atlas

#include <lib_atlas/ros/image_publisher_inl.h>

#endif  // ATLAS_ROS_IMAGE_PUBLISHER_H_
