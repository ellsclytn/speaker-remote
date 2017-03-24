#include <IRremote.h>

int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;
long msgRecv;
int speakerLength = 32;

long tvPower      = 0x6A68351E;
long tvVolumeDown = 0x776C6E7A;
long tvVolumeUp   = 0x22D912BB;
long tvMute       = 0x92DFD41F;

long speakerVolumeUp   = 0x400555AA;
long speakerVolumeDown = 0x400556A9;
long speakerMute       = 0x400557A8;
long speakerPower      = 0x400501FE;

void setup() {
  Serial.begin(9600);

  irrecv.enableIRIn();
}

void sendSpeakerCommand(long msg) {
  irsend.sendNEC(msg, speakerLength);
}

void loop() {
  if (irrecv.decode(&results)) {
    msgRecv = results.value;

    if (msgRecv == tvVolumeUp) {
      Serial.println("Turning up volume");
      sendSpeakerCommand(speakerVolumeUp);
    } else if (msgRecv == tvVolumeDown) {
      Serial.println("Turning down volume");
      sendSpeakerCommand(speakerVolumeDown);
    } else if (msgRecv == tvMute) {
      Serial.println("Muting");
      sendSpeakerCommand(speakerMute);
    } else if (msgRecv == tvPower) {
      Serial.println("Setting power");
      sendSpeakerCommand(speakerPower);
    }

    irrecv.enableIRIn();
    irrecv.resume();
  }
}
