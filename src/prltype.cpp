#include "ParallelsVirtualizationSDK/Parallels.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "common.h"

PRL_RESULT ConnectToConsole( PRL_HANDLE vm ) {

  PRL_RESULT err, nJobReturnCode = PRL_ERR_UNINITIALIZED;
  PRL_HANDLE hJob = PrlDevDisplay_ConnectToVm( vm, PDCT_LOW_QUALITY_WITHOUT_COMPRESSION );
  err = PrlJob_Wait(hJob, 10000);
  if (PRL_FAILED(err)) {
      fprintf(stderr, "PrlJob_Wait for PrlDevDisplay_ConnectToVm returned with error: %s\n",
      prl_result_to_string(err));
      PrlHandle_Free(hJob);
      return err;
  }
  err = PrlJob_GetRetCode(hJob, &nJobReturnCode);
  if (PRL_FAILED(err)) {
      fprintf(stderr, "PrlJob_GetRetCode returned with error: %s\n", prl_result_to_string(err));
      PrlHandle_Free(hJob);
      return err;
  }
  if (PRL_FAILED(nJobReturnCode)) {
      fprintf(stderr, "PrlDevDisplay_ConnectToVm returned with error: %s\n", prl_result_to_string(nJobReturnCode));
      PrlHandle_Free(hJob);
      return nJobReturnCode;
  }

  return PRL_ERR_SUCCESS;
}

PRL_RESULT DisconnectFromConsole( PRL_HANDLE vm ) {

  nanosleep((struct timespec[]){{0, 10000000}}, NULL);
  PRL_RESULT err = PrlDevDisplay_DisconnectFromVm( vm );
  if (PRL_FAILED(err)) {
      fprintf(stderr, "PrlDevDisplay_DisconnectFromVm returned with error: %s\n", prl_result_to_string(err));
  }
  return err;
}

PRL_RESULT SendScanCode( PRL_HANDLE vm, int scanCode ) {
  nanosleep((struct timespec[]){{0, 10000000}}, NULL);
  PRL_RESULT err;
  if (scanCode < 0x80)
    err = PrlDevKeyboard_SendKeyEvent( vm, scanCode, PKE_PRESS );
  else
    err = PrlDevKeyboard_SendKeyEvent( vm, scanCode - 0x80, PKE_RELEASE );
  if (PRL_FAILED(err)) {
      fprintf(stderr, "PrlDevKeyboard_SendKeyEvent returned with error: %s.\n", prl_result_to_string(err));
      PrlApi_Deinit();
      PrlHandle_Free( vm );
  }
  return err;
}

int main( int argc, char **argv ) {

  if (argc < 2) {
    fprintf(stdout, "Usage: prltype <vm-name> <scan-codes...>\nexample: prltype my-vm 30 158\n  This will press and release \"b\" on Virtual Machine \"my-vm\".\n");
    return -1;
  }

  char vmName[100];
  strcpy(vmName, argv[1]);
  int scanCodes [argc - 1];
  for (int i = 2; i < argc; i++) {
    scanCodes[i - 2] = strtol(argv[i], NULL, 16);
  }

  PRL_HANDLE hServer, hVm = PRL_INVALID_HANDLE;
  PRL_RESULT err;

  err = LoginLocal(hServer);
  if (PRL_FAILED(err))
    return err;
  err = GetVm(hVm, hServer, vmName);
  if (PRL_FAILED(err))
    return err;
  err = ConnectToConsole(hVm);
  if (PRL_FAILED(err))
    return err;

  for (int i = 0; i < argc - 2; i++) {
    err = SendScanCode(hVm, scanCodes[i]);
    if (PRL_FAILED(err))
      return err;
  }

  err = DisconnectFromConsole(hVm);
  if (PRL_FAILED(err))
    return err;

  LogOff( hServer );
}
