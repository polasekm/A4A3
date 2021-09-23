#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../a4a3.h"

a4a3_t a4a3;

uint8_t a4a3_raw_buff[512];
uint8_t a4a3_buff[512];

uint8_t sync;
uint8_t type;

int main()
{
  uint8_t i, n;

  printf("Test A4A3 lib...\n");

  a4a3_init(&a4a3, a4a3_buff, 512);

  sync = 0;
  type = 0;
  strcpy(a4a3_buff, "Kocka leze dirou, pes oknem, pes oknem...");

  printf("Zabalena data:\n");
  printf("Sync: %u, Type: %u, Msg: %s\n", sync, type, a4a3_buff);

  n = strlen(a4a3_buff) + 1;

  n = a4a3_create(a4a3_raw_buff, 512, sync, type, a4a3_buff, strlen(a4a3_buff) + 1);

  for(i = 0; i < n; i++)
  {
    if(a4a3_receive(&a4a3, a4a3_raw_buff[i]) == 1)
    {
      printf("Rozbalena data:\n");
      printf("Sync: %u, Type: %u, Msg: %s\n", a4a3.sync, a4a3.type, a4a3.buff);

      return 0;
    }
  }

  printf("Test selhal, data nebyla nalezena!\n");

  return 0;

}
