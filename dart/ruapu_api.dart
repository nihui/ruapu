import 'dart:ffi';
import 'package:ffi/ffi.dart';


typedef RuapuRUA_C = Pointer<Pointer<Utf8>> Function();
typedef RuapuRUA_Dart = Pointer<Pointer<Utf8>> Function();

typedef RuapuInit_C = Void Function();
typedef RuapuInit_Dart = void Function();

typedef RuapuSupports_C = Int32 Function(Pointer<Utf8>);
typedef RuapuSupports_Dart = int Function(Pointer<Utf8>);

class Ruapu {
  final DynamicLibrary _nativeLib;

  Ruapu(String libraryPath) : _nativeLib = DynamicLibrary.open(libraryPath);

  /// Init the ruapu environment
  void init() {
    final RuapuInit_Dart ruapu_init = _nativeLib
        .lookup<NativeFunction<RuapuInit_C>>('ruapu_init')
        .asFunction();
    ruapu_init();
  }

  /// Get the ISA support list of the CPU
  List<String> rua() {
    final RuapuRUA_Dart ruapu_rua = _nativeLib
        .lookup<NativeFunction<RuapuRUA_C>>('ruapu_rua')
        .asFunction();

    Pointer<Pointer<Utf8>> result = ruapu_rua();

    List<String> isas = [];
    int index = 0;
    while (true) {
      Pointer<Utf8> strPtr = result.elementAt(index).value;
      if (strPtr.address == 0) break;
      String str = strPtr.toDartString();
      isas.add(str);
      index++;
    }

    return isas;
  }

  /// Check the support status of a given isa
  bool supports(String isa) {
    final Pointer<Utf8> cIsa = isa.toNativeUtf8();

    final RuapuSupports_Dart ruapu_supports = _nativeLib
        .lookup<NativeFunction<RuapuSupports_C>>('ruapu_supports')
        .asFunction();

    int result = ruapu_supports(cIsa);

    malloc.free(cIsa);

    return result != 0;
  }

}