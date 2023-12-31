#pragma once
#include <string>

#include <maolan/audio/sndio/base.hpp>

namespace maolan::audio {
template <typename T> class SNDIOOut : public SNDIO {
public:
  SNDIOOut(const std::string &name, const std::string &device);

  virtual void fetch();
  virtual void process();
  virtual void writehw();
};
} // namespace maolan::audio
