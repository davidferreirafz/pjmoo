; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=FZPong
AppVerName=PJMOO :: FZPong
AppPublisher=DukItan Games
AppPublisherURL=http://pjmoo.sourceforge.net
AppSupportURL=http://davidferreira-fz.blogspot.com/
AppUpdatesURL=http://pjmoo.codigolivre.org.br/wiki/index.php/FZPong
DefaultDirName={pf}\PJMOO\FZPong
DefaultGroupName=PJMOO\FZPong
LicenseFile=C:\Projeto\pjmoo\projetos\games\fzpong\bin\GPL-pt_BR.txt
Compression=lzma/ultra
SolidCompression=true
ShowLanguageDialog=auto
WizardImageBackColor=clBlack
UninstallDisplayIcon={app}\fzpong.ico
VersionInfoVersion=1.5
VersionInfoCompany=DukItan Games
OutputDir=C:\Projeto\pjmoo\distro\games
OutputBaseFilename=FZPong.1.5.install.bin.win32
AppCopyright=GPL
SourceDir=C:\Projeto\pjmoo\projetos\games\fzpong\bin
WizardImageFile=C:\Projeto\pjmoo\projetos\games\fzpong\deploy\ImageBanner.bmp
WizardSmallImageFile=C:\Projeto\pjmoo\projetos\games\fzpong\deploy\ImageSmall.bmp
InternalCompressLevel=ultra
LanguageDetectionMethod=locale
DirExistsWarning=no
VersionInfoDescription=FZPong, Pong, OpenSource
VersionInfoTextVersion=Seja Livre! Use tecnologias Livre!
VersionInfoCopyright=GPL
AppVersion=1.5
AppContact=davidferreira.fz@gmail.com


[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked; Languages: 

[Files]
Source: FZPong.exe; DestDir: {app}; Flags: ignoreversion
Source: *; DestDir: {app}; Flags: ignoreversion recursesubdirs; Excludes: *cvs*, *svn*, *.xcf,*.log, *.bat, *.sh, stdout.txt; Tasks: ; Languages: 
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
Source: fzpong.ico; DestDir: {app}; Flags: ignoreversion; Tasks: 

[Icons]
Name: {group}\FZPong; Filename: {app}\FZPong.exe; IconFilename: {app}\FZPong.ico; IconIndex: 0; Components: ; Tasks: ; Languages: 
Name: {group}\FZPong - Modo Janela; Filename: {app}\FZPong.exe; IconFilename: {app}\FZPong.ico; Parameters: --window; Comment: Executar em Janela; IconIndex: 0; Components: ; Tasks: ; Languages: 
Name: {userdesktop}\FZPong; Filename: {app}\FZPong.exe; Tasks: desktopicon; IconFilename: {app}\FZPong.ico; Languages: ; IconIndex: 0; Components: 


[Run]
Filename: {app}\FZPong.exe; Description: {cm:LaunchProgram,FZPong}; Flags: nowait postinstall skipifsilent; Components: ; Tasks: ; Languages: 


[Components]

[INI]
Filename: {group}\PJMOO.url; Section: InternetShortcut; Key: URL; String: http://pjmoo.sourceforge.net
Filename: {group}\FZ Pong.url; Section: InternetShortcut; Key: URL; String: http://pjmoo.wiki.sourceforge.net/FZPong
[UninstallDelete]
Type: files; Name: {group}\PJMOO.url
Type: files; Name: {group}\FZ Pong.url
[Languages]
Name: English; MessagesFile: compiler:Default.isl
Name: Portugues; MessagesFile: compiler:Languages\BrazilianPortuguese.isl
