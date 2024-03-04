program ruapu;

uses ruapu_pascal;

var
  has_avx2: integer;
  supported: PPAnsiChar;
begin
  // initialize ruapu once
  ruapu_init();

  // now, tell me if this cpu has avx2
  has_avx2 := ruapu_supports('avx2');

  // loop all supported features
  supported := ruapu_rua();
  while supported^ <> nil do
  begin
      writeln(supported^);
      inc(supported);
  end;

  readln();
end.

