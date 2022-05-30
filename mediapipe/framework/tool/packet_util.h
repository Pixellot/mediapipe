// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MEDIAPIPE_FRAMEWORK_TOOL_PACKET_UTIL_H_
#define MEDIAPIPE_FRAMEWORK_TOOL_PACKET_UTIL_H_

#include "mediapipe/framework/packet.h"
#if !defined(MEDIAPIPE_DISABLE_TENSORFLOW)
#include "tensorflow/core/example/example.pb.h"
#endif

namespace mediapipe {
namespace tool {
// The CLIF-friendly util functions to create and access a typed MediaPipe
// Packet from MediaPipe Python interface.

// Functions for SequenceExample Packets.

// Make a SequenceExample packet from a serialized SequenceExample.
// The SequenceExample in the Packet is owned by the C++ packet.
Packet CreateSequenceExamplePacketFromString(std::string* serialized_content) {
#if !defined(MEDIAPIPE_DISABLE_TENSORFLOW)
  tensorflow::SequenceExample sequence_example;
  sequence_example.ParseFromString(*serialized_content);
  return MakePacket<tensorflow::SequenceExample>(sequence_example);
#else
  return MakePacket<std::string>(*serialized_content);
#endif
}

// Get a serialized SequenceExample std::string from a Packet.
// The ownership of the returned std::string will be transferred to the Python
// object.
std::unique_ptr<std::string> GetSerializedSequenceExample(Packet* packet) {
  return absl::make_unique<std::string>(
#if !defined(MEDIAPIPE_DISABLE_TENSORFLOW)
      packet->Get<tensorflow::SequenceExample>().SerializeAsString());
#else
      packet->Get<std::string>());
#endif
}

// Make a String packet
Packet CreateStringPacket(std::string* input_string) {
  return MakePacket<std::string>(*input_string);
}

// Get the std::string from a Packet<std::string>
std::unique_ptr<std::string> GetString(Packet* packet) {
  return absl::make_unique<std::string>(packet->Get<std::string>());
}

}  // namespace tool
}  // namespace mediapipe

#endif  // MEDIAPIPE_FRAMEWORK_TOOL_PACKET_UTIL_H_
