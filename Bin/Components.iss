; -- Components.iss --
; Demonstrates a components-based installation.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Languages]
Name: cn; MessagesFile: "compiler:Languages\Chinese.isl"

[Setup]
AppId={{69D1853D-0DFE-4D17-8BEE-AF8C2DB6F001}
AppName=福瑞堂医药管理系统
AppVersion=1.00
DefaultDirName={pf}\福瑞堂医药管理系统
DefaultGroupName=福瑞堂医药管理系统UninstallDisplayName=福瑞堂医药管理系统
OutputDir=Setup

[Types]
Name: "all"; Description: "完全安装"
Name: "manager"; Description: "安装后台管理"
Name: "pos"; Description: "安装POS收银终端"

[Components]
Name: "manager"; Description: "后台管理"; Types: all manager
Name: "pos"; Description: "POS收银终端"; Types: all pos

[Files]
Source: "Configuration\Config.ini"; DestDir: "{app}\Configuration"
Source: "libmysql.dll"; DestDir: "{app}"
Source: "Manager.exe"; DestDir: "{app}"; Components: manager
Source: "POS.exe"; DestDir: "{app}"; Components: pos
Source: "Configuration\PrintFormat.dat"; DestDir: "{app}\Configuration"; Components: pos
Source: "Configure.exe"; DestDir: "{app}"; AfterInstall: ExcCurrentFile

[Tasks] 
Name:   "desktopicon";   Description:   "{cm:CreateDesktopIcon} ";   GroupDescription:   "{cm:AdditionalIcons} ";   

[Icons]Name: "{group}\后台管理"; Filename: "{app}\Manager.exe";Components: manager;
Name: "{group}\POS收银终端"; Filename: "{app}\POS.exe";Components: pos;
Name: "{group}\卸载"; Filename: "{app}\unins000.exe"
Name: "{commondesktop}\后台管理"; Filename: "{app}\Manager.exe";Components: manager; Tasks: desktopicon
Name: "{commondesktop}\POS收银终端"; Filename: "{app}\POS.exe";Components: pos; Tasks: desktopicon

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
    '修改或删除', '选择你希望的操作',
    '',
    True, False);
  SetupTypePage.Add('修改');
  SetupTypePage.Add('删除');
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
