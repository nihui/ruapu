import ruapu.Ruapu;
import java.util.*;

class Example {
    public static void main(String args[]) {
        Ruapu ruapu = new Ruapu();

        System.out.println("avx: " + ruapu.supports("avx"));
        System.out.println(Arrays.toString(ruapu.rua()));
    }
}