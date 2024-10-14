import 'dart:io';
import 'ruapu_api.dart';
import 'package:path/path.dart' as path;

void main() {
  var libraryPath =
  path.join(Directory.current.path, 'build', 'libruapu.so');

  if (Platform.isMacOS) {
    libraryPath =
        path.join(Directory.current.path, 'build', 'libruapu.dylib');
  }

  if (Platform.isWindows) {
    libraryPath = path.join(
        Directory.current.path, 'build', 'Debug', 'ruapu.dll');
  }

  Ruapu api = Ruapu(libraryPath);

  api.init();

  List<String> isas = api.getRuapuISA();
  print("This CPU Support:");
  for (String isa in isas) {
    print(isa);
  }
  print("=================");

  String isaToCheck = 'aes';
  bool isSupported = api.supportsISA(isaToCheck);
  print('Does the system support $isaToCheck? $isSupported');
}