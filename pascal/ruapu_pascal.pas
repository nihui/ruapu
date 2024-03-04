unit ruapu_pascal;

{$mode ObjFPC}{$H+}

interface
uses
  Classes, SysUtils;

const
{$IFDEF MSWINDOWS}
  ruapu_lib = 'ruapu.dll';
{$ELSE}
{$IFDEF DARWIN}
  ruapu_lib = 'libruapu.dylib';
{$ENDIF}
{$IFDEF ANDROID}
  ruapu_lib = 'libruapu.so';
{$ENDIF}
{$IFDEF linux}
  ruapu_lib = 'libruapu.so';
{$ENDIF}
{$ENDIF}

procedure ruapu_init(); cdecl; external ruapu_lib name 'ruapu_init_c';
function ruapu_supports(const isa: PAnsiChar): Integer; cdecl; external ruapu_lib name 'ruapu_supports_c';
function ruapu_rua(): PPAnsiChar; cdecl; external ruapu_lib name 'ruapu_rua_c';

implementation

end.

