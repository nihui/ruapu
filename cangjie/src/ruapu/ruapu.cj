package ruapu

from std import collection.ArrayList

foreign func ruapu_init_c(): Unit

foreign func ruapu_supports_c(s: CString): Int32

foreign func ruapu_rua_c(): CPointer<CString>

public func ruapu_init(): Unit {
    unsafe{ ruapu_init_c() }
}

public func ruapu_supports(isa: String): Bool {
    var isa_c = unsafe { LibC.mallocCString(isa) }
    let result_c = unsafe { ruapu_supports_c(isa_c) }
    return result_c == 1
}

public func ruapu_rua(): Array<String> {
    var ruaList = ArrayList<String>()
    var sp = unsafe { ruapu_rua_c() }
    while(!unsafe { sp.read().isNull() }) {
        let temp = unsafe { sp.read() }
        ruaList.append(temp.toString())
        sp = unsafe { sp + 1 }
    }
    return Array<String>(ruaList)
}