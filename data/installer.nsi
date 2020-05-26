!define VERSION 0.1.0
!define NAME netinfo
!define ENTRY Software\${NAME}
!define REPO "https://github.com/midbel/netinfo-gui"

Name "${NAME} installer v${VERSION}"
OutFile "${NAME}-setup.exe"
InstallDir $PROGRAMFILES\${NAME}

BrandingText "${NAME} version ${VERSION}"

SetCompressor /SOLID lzma

ShowInstDetails show
ShowUnInstDetails show

SetDateSave off
SetOverwrite on

Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section "Installer"

SetOutPath $INSTDIR
WriteUninstaller $INSTDIR\uninstall.exe

FILE /r ..\..\Deploy\netinfo\

createShortCut $SMPROGRAMS\netinfo.lnk $INSTDIR\netinfo\NetInfo.exe
DetailPrint "adding shortcut $SMPROGRAMS\netinfo.lnk"

WriteRegStr HKCU ${ENTRY} "DisplayName" ${NAME}
DetailPrint "adding to registryDisplayName(${NAME}) in ${ENTRY}"
WriteRegStr HKCU ${ENTRY} "DisplayVersion" ${VERSION}
DetailPrint "adding to registryDisplayVersion(${VERSION}) in ${ENTRY}"
WriteRegStr HKCU ${ENTRY} "Repository" ${REPO}
DetailPrint "adding to registryRepository(${REPO}) in ${ENTRY}"
WriteRegStr HKCU ${ENTRY} "UninstallString" $INSTDIR\uninstall.exe
DetailPrint "adding to registryUnsinstallString() in ${ENTRY}"

SectionEnd

Section "Uninstall"

DELETE $INSTDIR\*exe
RMDIR /r $INSTDIR\netinfo\

DELETE $SMPROGRAMS\netinfo.lnk

DetailPrint "delete shortcut $SMPROGRAMS\netinfo.lnk"

DeleteRegKey HKCU ${ENTRY}
DetailPrint "deleting from registry ${ENTRY}"

SectionEnd
