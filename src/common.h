#include "ParallelsVirtualizationSDK/Parallels.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

PRL_RESULT LoginLocal(PRL_HANDLE &hServer);
PRL_RESULT LogOff(PRL_HANDLE &hServer);
PRL_RESULT GetVm(PRL_HANDLE &hRetVm, PRL_HANDLE &hServer, char* vmName );
