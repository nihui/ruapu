package ruapu;

import java.nio.file.FileSystems;

public class Ruapu {

    public Ruapu()
    {
        init();
    }

    public static void main(String args[]) {};

    public static native void init();

    public static native int supports(String isa);

    public static native String[] rua();

    static
    {
        // TODO -- Add windows format support here 
        System.load(
        FileSystems.getDefault()
            .getPath("./ruapu/libruapu_binding.so")  // Dynamic link
            .normalize().toAbsolutePath().toString());
    }
}
