unit ruapu_pascal;

{$mode ObjFPC}{$H+}

interface
uses
  Classes, SysUtils;

procedure ruapu_init_c(); cdecl;
function ruapu_supports_c(isa: PAnsiChar): Integer; cdecl;
function ruapu_rua_c(): PPAnsiChar; cdecl;

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

implementation
  procedure ruapu_init_c(); cdecl; external ruapu_lib;
  function ruapu_supports_c(isa: PAnsiChar): Integer; cdecl; external ruapu_lib;
  function ruapu_rua_c(): PPAnsiChar; cdecl; external ruapu_lib;
end.

