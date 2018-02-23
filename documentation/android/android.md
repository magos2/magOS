## Android Studio
Android Strudion is the IDE for android application development. It is based on IntelliJ IDEA.

**Create a Virtual Device for emulation**
  
    Tools > Android > AVD Manager
    Create new Hardware Profile : 
     Name: Galaxy S5 mini. Skins: http://developer.samsung.com/technical-doc/view.do?v=T000000095 


**Run Apps on a Hardware Device**
* [Set up a device for development](https://developer.android.com/studio/run/device.html#setting-up)
* [Windows: Install OEM USB Drivers](https://developer.android.com/studio/run/oem-usb.html)
* Linux 
    apt install android-tools-adb
* [Install Google USB Driver](https://developer.android.com/studio/run/win-usb.html)


**SDK**
> Tools > Android > SDK Manager

Save disk space by uncheck *Android Emulator*, if you dont use emulation. SDK is installed in *~/Android/Sdk*

___**ERRORS: Resolved**___

Problem: *Android Studio: Installation failed with message Failed to establish session.*
>Resoluion: disable Instant Run  
>File > Settings > Build,Execution,Deployment > Instant Run 
 

Problem : *Android Studio: An existing connection was forcibly closed by the remote host*.
> Resolution 1:  
> cd /cygdrive/c/Users/arahali/AppData/Local/Android/sdk/platform-tools  
> ./adb.exe kill-server  
> ./adb.exe devices  

> Resolution 2:  
> note SDK version : File>Project Structure
> Tools>Android>SDK Manager , and only check the wanted version of SDK  

## Programming
**Activity**: is a page gui containing gadgets(TextViews, Buttons,etc). Design is defined in _res/layout/activity_login.xml_. Logic code in _java/.../LoginActivity.java_.
each activity must be declared in _AndroidManifest.xml_  
Match activity to a layout:

    protected void onCreate(Bundle savedInstanceState) {  
      setContentView(R.layout.activity_main);  
    ...}  

