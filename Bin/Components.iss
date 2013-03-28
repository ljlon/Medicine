; -- Components.iss --
; Demonstrates a components-based installation.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Languages]
Name: cn; MessagesFile: "compiler:Languages\Chinese.isl"

[Setup]
AppId={{69D1853D-0DFE-4D17-8BEE-AF8C2DB6F001}
AppName=������ҽҩ����ϵͳ
AppVersion=1.00
DefaultDirName={pf}\������ҽҩ����ϵͳ
DefaultGroupName=������ҽҩ����ϵͳUninstallDisplayName=������ҽҩ����ϵͳ
OutputDir=Setup

[Types]
Name: "all"; Description: "��ȫ��װ"
Name: "manager"; Description: "��װ��̨����"
Name: "pos"; Description: "��װPOS�����ն�"

[Components]
Name: "manager"; Description: "��̨����"; Types: all manager
Name: "pos"; Description: "POS�����ն�"; Types: all pos

[Files]
Source: "Configuration\Config.ini"; DestDir: "{app}\Configuration"
Source: "libmysql.dll"; DestDir: "{app}"
Source: "Manager.exe"; DestDir: "{app}"; Components: manager
Source: "POS.exe"; DestDir: "{app}"; Components: pos
Source: "Configuration\PrintFormat.dat"; DestDir: "{app}\Configuration"; Components: pos
Source: "Configure.exe"; DestDir: "{app}"; AfterInstall: ExcCurrentFile

[Tasks] 
Name:   "desktopicon";   Description:   "{cm:CreateDesktopIcon} ";   GroupDescription:   "{cm:AdditionalIcons} ";   

[Icons]Name: "{group}\��̨����"; Filename: "{app}\Manager.exe";Components: manager;
Name: "{group}\POS�����ն�"; Filename: "{app}\POS.exe";Components: pos;
Name: "{group}\ж��"; Filename: "{app}\unins000.exe"
Name: "{commondesktop}\��̨����"; Filename: "{app}\Manager.exe";Components: manager; Tasks: desktopicon
Name: "{commondesktop}\POS�����ն�"; Filename: "{app}\POS.exe";Components: pos; Tasks: desktopicon

[code]
var
  SetupTypePage: TInputOptionWizardPage;
  RetCode: Integer; 
  AlreadyInstall: boolean;   
  UnInstallCmd: String; 
  CancelConfirm: boolean;  

function InitializeSetup():Boolean;   
begin   
  AlreadyInstall:= False;   
  CancelConfirm := True;
  if RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\{69D1853D-0DFE-4D17-8BEE-AF8C2DB6F001}_is1', 'UninstallString', UnInstallCmd) then   
  begin   
  AlreadyInstall:= True;   
  end;   
  Result:= True   
end;  

procedure InitializeWizard;
begin
  { Create the pages }
  SetupTypePage := CreateInputOptionPage(wpWelcome,
    '�޸Ļ�ɾ��', 'ѡ����ϣ���Ĳ���',
    '',
    True, False);
  SetupTypePage.Add('�޸�');
  SetupTypePage.Add('ɾ��');
  SetupTypePage.SelectedValueIndex := 0;
end;

function ShouldSkipPage(PageID: Integer): Boolean;
begin
  { Skip pages that shouldn't be shown }
  if (PageID = SetupTypePage.ID) and (AlreadyInstall = False) then
    Result := True   
  else if (PageID = wpSelectDir) and (AlreadyInstall = True) then
    Result := True   
  else
    Result := False;
end;

function NextButtonClick(CurPageID: Integer): Boolean;
begin
  if (CurPageID = SetupTypePage.ID) and (SetupTypePage.SelectedValueIndex = 1) then begin
    CancelConfirm := False;
    Exec(RemoveQuotes(UnInstallCmd), '', '', SW_SHOW, ewWaitUntilTerminated, RetCode);  
    WizardForm.CancelButton.OnClick(WizardForm);
  end;
  Result := True;
end;

procedure CancelButtonClick(CurPageID: Integer; var Cancel, Confirm: Boolean);
begin
  if (CurPageID = SetupTypePage.ID) then begin
  Cancel := True;
  Confirm := CancelConfirm;
  end;
end;

procedure ExcCurrentFile();
var
  RetCode: Integer;

begin
  Exec(ExpandConstant(CurrentFileName), '', '', SW_SHOW, ewWaitUntilTerminated, RetCode);
end;
