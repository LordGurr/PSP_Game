 #include <pspkernel.h>
 #include <pspdebug.h>
 #include <pspctrl.h>
 #include <string> 
 #include <cstdlib>

PSP_MODULE_INFO("Tutorial",0,1,0);

auto exit_callback(int arg1, int arg2, void* common)
{
    sceKernelExitGame();
    return 0;
}

auto callbackThread(SceSize args, void* argp)
{
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThreadCB();
    return 0;
}

auto setupCallbacks()
{
    int thid = sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0 ,NULL);
    if (thid >= 0)
    {
        sceKernelStartThread(thid,0,NULL);
    }
}

 auto main() -> int
 {
     setupCallbacks();
     pspDebugScreenInit();

     pspDebugScreenPrintf("Hello world from c++");
     sceCtrlSetSamplingCycle(0);
     sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
     int x = 2;
     int y = 2;
     SceCtrlData ctrlData;
     while (true)
     {
         sceCtrlReadBufferPositive(&ctrlData,1);
         if (ctrlData.Buttons & PSP_CTRL_DOWN)
         {
             y++;
         }
         else if (ctrlData.Buttons & PSP_CTRL_UP)
         {
             y--;
         }
         else if (ctrlData.Buttons & PSP_CTRL_LEFT)
         {
             x--;
         }
         else if (ctrlData.Buttons & PSP_CTRL_RIGHT)
         {
             x++;
         }
         pspDebugScreenClear();
         pspDebugScreenSetXY(0,0);
         pspDebugScreenPrintf("X: ");
         pspDebugScreenPrintf(std::to_string(x).c_str());
         pspDebugScreenPrintf(" Y: ");
         pspDebugScreenPrintf(std::to_string(y).c_str());
         pspDebugScreenSetXY(x,y);
         pspDebugScreenPrintf("X");
     }
     
     
 }