#include <maolan/dynamichw.hpp>

using namespace maolan;

int main() {
  DynamicHW sndio{"./libmaolansndio.so"};

  sndio.audio.out("SndioAudioOut", "default", 4);
  sndio.audio.in("SndioAudioOut", "default", 4);
  // sndio.midi.out("SndioMidiOut", "default");
  // sndio.midi.in("SndioMidiIn", "default");
  return 0;
}
