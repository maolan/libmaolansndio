#include <poll.h>
#include <maolan/audio/input.hpp>

#include "maolan/audio/base.hpp"


using namespace maolan::audio;


SNDIO::SNDIO(const std::string &name, const std::string &device, const unsigned int &mode, const size_t &sampleSize)
  : HW{name, device}
{
  struct pollfd pfd;

  _parameters = new sio_par;
  sio_initpar(_parameters);
  _parameters->bits = sampleSize * 8;
  _parameters->le = SIO_LE_NATIVE;
  _parameters->rate = Config::samplerate;
  _parameters->appbufsz = 4096;
  _handle = sio_open(device.data(), mode, 0);
  sio_setpar(_handle, _parameters);
  sio_getpar(_handle, _parameters);
  sio_start(_handle);
  Config::audioBufferSize = _parameters->appbufsz;
  if (mode == SIO_REC) { sio_pollfd(_handle, &pfd, POLLIN); }
  else { sio_pollfd(_handle, &pfd, POLLOUT); }
  _bytes = new int8_t[_parameters->bufsz];
  _fd = pfd.fd;
}


nlohmann::json SNDIO::json()
{
  auto data = IO::json();
  data["bits"] = _parameters->bits;
  data["samplerate"] = Config::samplerate;
  return data;
}


SNDIO::~SNDIO()
{ 
  sio_stop(_handle);
  delete _bytes;
  delete _parameters;
}


size_t SNDIO::channels() const { return _outputs.size(); }
