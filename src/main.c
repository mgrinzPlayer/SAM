#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "reciter.h"
#include "sam.h"

extern int bufferpos;
extern char *buffer;

char* sayThis(char *text)
{
  int i;
  char input[256];

  for(i=0; i<256; i++) input[i] = 0;

  strncat(input, text, 256);

  for(i=0; input[i] != 0; i++)
    input[i] = toupper((int)input[i]);

  strncat(input, "[", 256);

  if (TextToPhonemes(input)) {
    SetInput(input);

    bufferpos = 0;
    buffer = malloc(22050*20);

    buffer = buffer+44;

    if (SAMMain()) {

      buffer = buffer-44;

      memcpy(&buffer[0] , "RIFF", 4);
      memcpy(&buffer[8] , "WAVE", 4);
      memcpy(&buffer[12], "fmt ", 4);

      unsigned int fmtlength = 16;
      memcpy(&buffer[16], &fmtlength, 4);

      unsigned short int format=1; //PCM
      memcpy(&buffer[20], &format ,2);

      unsigned short int channels=1;
      memcpy(&buffer[22], &channels, 2);

      unsigned int samplerate = 22050;
      memcpy(&buffer[24], &samplerate, 4);
      memcpy(&buffer[28], &samplerate, 4); // bytes/second

      unsigned short int blockalign = 1;
      memcpy(&buffer[32], &blockalign, 2);

      unsigned short int bitspersample=8;
      memcpy(&buffer[34], &bitspersample, 2);

      memcpy(&buffer[36], "data", 4);

      int bufferlength = bufferpos/50;
      unsigned int filesize=bufferlength + 28;

      memcpy(&buffer[4], &filesize, 4);
      memcpy(&buffer[40], &bufferlength, 4);

      return buffer;
    }
  }
  return NULL;
}






