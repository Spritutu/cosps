# Microsoft Developer Studio Project File - Name="CoolTabDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CoolTabDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CoolTabDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CoolTabDemo.mak" CFG="CoolTabDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CoolTabDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CoolTabDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CoolTabDemo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\ResizableLib\1.3\ResizableLib" /I "..\..\tinyxml_2_5_3" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 tinyxml.lib ResizableLib.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\tinyxml_2_5_3\Release" /libpath:"..\..\ResizableLib\1.3\ResizableLib\Release"

!ELSEIF  "$(CFG)" == "CoolTabDemo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\ResizableLib\1.3\ResizableLib" /I "..\..\tinyxml_2_5_3" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tinyxmld.lib ResizableLib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\tinyxml_2_5_3\Debug" /libpath:"..\..\ResizableLib\1.3\ResizableLib\Debug"

!ENDIF 

# Begin Target

# Name "CoolTabDemo - Win32 Release"
# Name "CoolTabDemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CCommonDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolTabCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolTabDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolTabDemo.rc
# End Source File
# Begin Source File

SOURCE=.\CoolTabDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\gtb.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageBkgTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ImagePureTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ResMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TempDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TempDlg2.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CCommonDlg.h
# End Source File
# Begin Source File

SOURCE=.\CoolTabCommon.h
# End Source File
# Begin Source File

SOURCE=.\CoolTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CoolTabDemo.h
# End Source File
# Begin Source File

SOURCE=.\CoolTabDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\gtb.h
# End Source File
# Begin Source File

SOURCE=.\gtbutil.h
# End Source File
# Begin Source File

SOURCE=.\ImageBkgTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ImagePureTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ResMgr.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TempDlg.h
# End Source File
# Begin Source File

SOURCE=.\TempDlg2.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\CoolTabDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\CoolTabDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
