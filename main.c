// LED Control v0.2 by brk3
// PWR Control v0.1 by Yoti

#include <pspkernel.h>
#include <psppower.h>

#define MS_LED 0
#define WLAN_LED 1
#define POWER_LED 2

#define STATE_ON 1
#define STATE_OFF 0

PSP_MODULE_INFO("PWRControl", 0x1000, 1, 0);
PSP_MAIN_THREAD_ATTR(0);

int main_thread(SceSize args, void *argp)
{
	while(1)
	{
		if (scePowerIsPowerOnline() == 1)
			sceSysconCtrlLED(POWER_LED, STATE_ON);
		else if (scePowerIsLowBattery() == 1)
			sceSysconCtrlLED(POWER_LED, STATE_ON);
		else
			sceSysconCtrlLED(POWER_LED, STATE_OFF);

    		sceKernelDelayThreadCB(10*1000*1000); // 10 sec
	}

	return 0;
}

int module_start(SceSize args, void *argp)
{
	int thid = sceKernelCreateThread("PWRControl", main_thread, 0x30, 0x1000, 0, NULL);
	if (thid >= 0)
		sceKernelStartThread(thid, args, argp);

	return 0;
}
