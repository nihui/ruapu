package ruapu;

import java.nio.file.FileSystems;

public class Ruapu {

    public Ruapu() {
        init();
    }

    public static void main(String args[]) {
    };

    public static native void init();

    public static native int supports(String isa);

    public static native String[] rua();

    static {
        if (System.getProperty("os.name").startsWith("Windows")) {
            System.load(
                    FileSystems.getDefault()
                            .getPath("./ruapu/ruapu_binding.dll")
                            .normalize().toAbsolutePath().toString());

        } else if (System.getProperty("os.name").startsWith("Mac")) {
            System.load(
                    FileSystems.getDefault()
                            .getPath("./ruapu/libruapu_binding.dylib")
                            .normalize().toAbsolutePath().toString());
        } else {
            System.load(
                    FileSystems.getDefault()
                            .getPath("./ruapu/libruapu_binding.so")
                            .normalize().toAbsolutePath().toString());
        }

    }
}
