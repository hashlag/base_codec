!include "MUI2.nsh"
!include "logiclib.nsh"

!define NAME "Base32 Codec"
!define APPFILE "base_encoder.exe"
!define VERSION "0.0.0"
!define SLUG "${NAME} v${VERSION}"

Name "${NAME}"
OutFile "${NAME} Setup.exe"
InstallDir "$PROGRAMFILES\${NAME}"
InstallDirRegKey HKCU "Software\${NAME}" ""
RequestExecutionLevel admin

!define MUI_ABORTWARNING
!define MUI_WELCOMEPAGE_TITLE "${SLUG} Setup"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Set UI language
!insertmacro MUI_LANGUAGE "English"

Section "Gtk3"
    SetOutPath "$INSTDIR\Redist"
    File "redist\gtk3-runtime-3-win64.exe"
    DetailPrint "Running Gtk3 Setup..."
    ExecWait "$INSTDIR\Redist\gtk3-runtime-3-win64.exe"
    DetailPrint "Finished Gtk3 Setup"
SectionEnd

Section "-hidden app"
    SectionIn RO
    SetOutPath "$INSTDIR"
    File /r "app\*.*"
    WriteRegStr HKCU "Software\${NAME}" "" $INSTDIR
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" \
                     "DisplayName" "Base32 Codec"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" \
                     "UninstallString" "$\"$INSTDIR\Uninstall.exe$\""
    WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

Section "Explorer Context Menu Integration" SEC_ContextMenu
    SectionIn 1
    WriteRegStr HKCR "*\shell\${NAME}\command" "" "$INSTDIR\${APPFILE} %1"
SectionEnd

Section "Create Start Menu Shortcut"
    CreateDirectory "$SMPROGRAMS\${NAME}"
    CreateShortCut "$SMPROGRAMS\${NAME}\${NAME}.lnk" "$INSTDIR\${APPFILE}" "" "$INSTDIR\${APPFILE}" 0
SectionEnd

Function un.RMDirUP
    !define RMDirUP '!insertmacro RMDirUPCall'

    !macro RMDirUPCall _PATH
          push '${_PATH}'
          Call un.RMDirUP
    !macroend

    ; $0 - current folder
    ClearErrors

    Exch $0
    ;DetailPrint "ASDF - $0\.."
    RMDir "$0\.."

    IfErrors Skip
    ${RMDirUP} "$0\.."
    Skip:

    Pop $0
FunctionEnd

Section "Uninstall"
  ;Delete Uninstall
  Delete "$INSTDIR\Uninstall.exe"

  ;Delete Folder
  RMDir /r "$INSTDIR"
  ${RMDirUP} "$INSTDIR"

  Delete "$SMPROGRAMS\${NAME}\${NAME}.lnk"
  RMDir "$SMPROGRAMS\${NAME}"

  ; Remove context menu integration
  DeleteRegKey HKCR "*\shell\${NAME}\command"
  DeleteRegKey HKCR "*\shell\${NAME}"

  DeleteRegKey /ifempty HKCU "Software\${NAME}"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}"
SectionEnd
