import ddf.minim.analysis.*;
import ddf.minim.*;
import processing.serial.*;

Serial port;

Minim minim;
AudioInput in;
FFT fft;
float[] peaks;

int peak_hold_time = 1;  // how long before peak decays
int[] peak_age;  // tracks how long peak has been stable, before decaying

// how wide each 'peak' band is, in fft bins
int binsperband = 5;
int peaksize; // how many individual peak bands we have (dep. binsperband)
float gain = 40; // in dB
float dB_scale = 2.0;  // pixels per dB

int buffer_size = 16384;  // also sets FFT size (frequency resolution)
float sample_rate = 88200;

int spectrum_height = 176; // determines range of dB shown

int[] freq_array = {0,0,0};
int i,g;
float f;

float low_multiplier = 1;
float mid_multiplier = 2;
float high_multiplier = 5;

// TODO: add a GUI for options

float[] freq_height = {0,0,0};  //avg amplitude of each freq band

void setup()
{
  size(200, 200);

  minim = new Minim(this);
  port = new Serial(this, Serial.list()[3], 9600);

  in = minim.getLineIn(Minim.STEREO, buffer_size, sample_rate);

  // create an FFT object for each channel that
  // has a time-domain buffer
  fft = new FFT(in.bufferSize(), in.sampleRate());
  //fftRight = new FFT(in.bufferSize(), in.sampleRate());
  // attempts to taper the buffer
  fft.window(FFT.HAMMING);
  //fftRight.window(FFT.HAMMING);
}

void draw()
{
  // perform a forward FFT on the samples in input buffer
  fft.forward(in.mix);

  for (int k=0; k<3; k++) {
    freq_array[k] = 0;
  }

  // TODO: Check if calculating the maximum instead of average would be better
  freq_height[0] = fft.calcAvg((float) 0, (float) 1638);
  freq_height[1] = fft.calcAvg((float) 1639, (float) 3240);
  freq_height[2] = fft.calcAvg((float) 3241, (float) 8874);

 /* if (freq_height[0] >= 1) {
    freq_height[0] = freq_height[0] * low_multiplier;
  }
  if (freq_height[1] >= 1) {
    freq_height[1] = freq_height[1] * mid_multiplier;
  }
  if (freq_height[2] >= 1) {
    freq_height[2] = freq_height[2] * high_multiplier;
  } */

  //send to serial
  port.write(0xff); //write marker (0xff) for synchronization

  //byte[] adj_height = {0, 0, 0};
  
  //adj_height[0] = freq_height[0] * low_multiplier;
  for(i=0; i<3; i++){
    port.write((byte)freq_height[i]);
    /*if (i == 0) {
      System.out.println("low : " + (byte) freq_height[0]);
    } else if (i == 1) {
        System.out.println("mid : " + (byte) freq_height[1]);
    } else if (i == 2) {
        System.out.println("high : " + (byte) freq_height[2]);
    }*/
  }
  
  if (port.read() == 0xcc) {
    System.out.println("low : " + port.read());
    System.out.println("mid : " + port.read());
    System.out.println("high : " + port.read());
  }
}