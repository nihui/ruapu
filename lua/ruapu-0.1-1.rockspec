package = "ruapu"
version = "0.1-1"
source = {
    url = "https://github.com/nihui/ruapu.git"
}
description = {
    summary = "Detect CPU ISA features with single-file",
    homepage = "https://github.com/nihui/ruapu",
    license = "MIT"
}
dependencies = {
    "lua >= 5.2, <= 5.4"
}
build = {
    type = "builtin",
    modules = {
        ruapu = "ruapu-binding.c"
    }
}
