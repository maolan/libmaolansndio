#include <maolan/audio/sndio/in.hpp>
#include <maolan/audio/sndio/out.hpp>

using namespace maolan::audio;

extern "C" HW *createAudioOut(const std::string &name,
                              const std::string &device, const size_t &size) {
  if (size == 1) {
    return new SNDIOOut<int8_t>{name, device};
  }
  if (size == 2) {
    return new SNDIOOut<int16_t>{name, device};
  }
  if (size == 4) {
    return new SNDIOOut<int32_t>{name, device};
  }
  throw std::invalid_argument{"No such size"};
}

extern "C" HW *createAudioIn(const std::string &name, const std::string &device,
                             const size_t &size) {
  if (size == 1) {
    return new SNDIOIn<int8_t>{name, device};
  }
  if (size == 2) {
    return new SNDIOIn<int16_t>{name, device};
  }
  if (size == 4) {
    return new SNDIOIn<int32_t>{name, device};
  }
  throw std::invalid_argument{"No such size"};
}
