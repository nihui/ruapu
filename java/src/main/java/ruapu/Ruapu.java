package ruapu;

import java.io.*;

public class Ruapu {

    public Ruapu() {
        init();
    }

    public static native void init();

    public static native int supports(String isa);

    public static native String[] rua();

    static {
        String libName = "ruapu_binding";
        String suffix = "";
        if (System.getProperty("os.name").startsWith("Windows")) {
            suffix = ".dll";
        } else if (System.getProperty("os.name").startsWith("Mac")) {
            suffix = ".dylib";
        } else {
            suffix = ".so";
        }
        // Extract library to temporary place
        File temp = null;
        try {
            temp = File.createTempFile("ruapu_native_lib", suffix);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        temp.deleteOnExit();
        InputStream is = Ruapu.class.getResourceAsStream("/" + libName + suffix);
        if (is == null) {
            throw new RuntimeException("Library " + libName + " not found in resources!");
        }
        OutputStream os = null;
        try {
            os = new FileOutputStream(temp);
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        byte[] buffer = new byte[512];
        int read = -1;
        try {
            while ((read = is.read(buffer)) != -1) {
                os.write(buffer, 0, read);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        try {
            is.close();
            os.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        // load jni library from temporary file.
        System.load(temp.getAbsolutePath());
    }
}
