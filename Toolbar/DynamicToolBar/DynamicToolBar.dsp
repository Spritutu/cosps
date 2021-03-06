# Microsoft Developer Studio Project File - Name="DynamicToolBar" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DynamicToolBar - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DynamicToolBar.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DynamicToolBar.mak" CFG="DynamicToolBar - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DynamicToolBar - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DynamicToolBar - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DynamicToolBar - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\ResizableLib\1.3\ResizableLib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ResizableLib.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\ResizableLib\1.3\ResizableLib\Release"

!ELSEIF  "$(CFG)" == "DynamicToolBar - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\ResizableLib\1.3\ResizableLib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ResizableLib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\ResizableLib\1.3\ResizableLib\Debug"

!ENDIF 

# Begin Target

# Name "DynamicToolBar - Win32 Release"
# Name "DynamicToolBar - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Dlg1.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg2.cpp
# End Source File
# Begin Source File

SOURCE=.\DynamicToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\DynamicToolBar.rc
# End Source File
# Begin Source File

SOURCE=.\DynamicToolBarDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyReBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MyToolBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolBarCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\VersionUtil.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Dlg1.h
# End Source File
# Begin Source File

SOURCE=.\Dlg2.h
# End Source File
# Begin Source File

SOURCE=.\DynamicToolBar.h
# End Source File
# Begin Source File

SOURCE=.\DynamicToolBarDlg.h
# End Source File
# Begin Source File

SOURCE=.\MyReBar.h
# End Source File
# Begin Source File

SOURCE=.\MyToolBarCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StaticStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ToolBarCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\VersionUtil.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\abc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DynamicToolBar.ico
# End Source File
# Begin Source File

SOURCE=.\res\DynamicToolBar.rc2
# End Source File
# Begin Source File

SOURCE=.\res\tb24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolBtnDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolBtnHot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolBtnNormal.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
