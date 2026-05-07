Name "Restaurant Simulator"

OutFile "RestaurantSimulatorInstaller.exe"
InstallDir "$PROGRAMFILES\RestaurantSimulator"
Icon "assets\icons\icon.ico"
UninstallIcon "assets\icons\icon.ico"
RequestExecutionLevel admin

Page directory
Page instfiles

Section "Install"

  SetOutPath "$INSTDIR"
  File "build\RestaurantSimulator.exe"
  File /r "build\*.dll"
  SetOutPath "$INSTDIR\assets"
  File /r "assets\*.*"
  SetOutPath "$INSTDIR"
  File "readme.txt"
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  CreateDirectory "$SMPROGRAMS\RestaurantSimulator"
  CreateShortCut "$SMPROGRAMS\RestaurantSimulator\RestaurantSimulator.lnk" "$INSTDIR\RestaurantSimulator.exe" "" "$INSTDIR\assets\icons\icon.ico" 0 SW_SHOWNORMAL "" "$INSTDIR"
  CreateShortCut "$DESKTOP\RestaurantSimulator.lnk" "$INSTDIR\RestaurantSimulator.exe" "" "$INSTDIR\assets\icons\icon.ico" 0 SW_SHOWNORMAL "" "$INSTDIR"
  CreateShortCut "$SMPROGRAMS\RestaurantSimulator\Uninstall.lnk" "$INSTDIR\Uninstall.exe" "" "$INSTDIR\assets\icons\icon.ico"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RestaurantSimulator" "DisplayName" "RestaurantSimulator"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RestaurantSimulator" "UninstallString" "$INSTDIR\Uninstall.exe"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RestaurantSimulator" "DisplayIcon" "$INSTDIR\assets\icons\icon.ico"

SectionEnd

Section "Uninstall"

  Delete "$INSTDIR\RestaurantSimulator.exe"
  Delete "$INSTDIR\*.dll"
  RMDir /r "$INSTDIR\assets"
  Delete "$INSTDIR\restaurantSimulator.ini"
  Delete "$INSTDIR\stats.txt"
  Delete "$INSTDIR\readme.txt"
  Delete "$INSTDIR\Uninstall.exe"
  Delete "$SMPROGRAMS\RestaurantSimulator\RestaurantSimulator.lnk"
  Delete "$SMPROGRAMS\RestaurantSimulator\Uninstall.lnk"
  RMDir "$SMPROGRAMS\RestaurantSimulator"
  Delete "$DESKTOP\RestaurantSimulator.lnk"
  RMDir "$INSTDIR"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RestaurantSimulator"

SectionEnd