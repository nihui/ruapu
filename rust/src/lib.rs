#[macro_use]
extern crate lazy_static;

use std::ffi::{CString, CStr, NulError};
use std::os::raw::c_char;
use std::sync::Mutex;
use std::result::Result;

lazy_static! {
    static ref RUAPU_INITILIASED: Mutex<bool> = Mutex::new(false);
}

extern "C" {
    fn ruapu_init();
    fn ruapu_supports(isa: *const c_char) -> i32;
    fn ruapu_rua() -> *const *const c_char;
}

fn init_ruapu() {
    if !*(RUAPU_INITILIASED.lock().unwrap()) {
        unsafe {
            ruapu_init();
        }
        *(RUAPU_INITILIASED.lock().unwrap()) = true;
    }
}

pub fn supports(isa: &str) -> Result<bool, NulError> {
    init_ruapu();
    let isa = CString::new(isa)?;
    let isa_ptr = isa.as_ptr();
    unsafe {
        Ok(ruapu_supports(isa_ptr) != 0)
    }
}

pub fn rua() -> Vec<String> {
    init_ruapu();
    let mut result = Vec::new();
    unsafe {
        let mut i = 0;
        let ptr = ruapu_rua();
        loop {
            let ptr = ptr.offset(i);
            if *ptr == std::ptr::null() {
                break;
            }
            let c_str = CStr::from_ptr(*ptr);
            let str = c_str.to_str().unwrap();
            result.push(str.to_string());
            i += 1;
        }
    }
    return result;
}

#[cfg(test)]
mod tests {
    use super::*;
    use claim::assert_ok;

    #[test]
    fn test_supports() {
        assert_ok!(supports("avx2"));
        assert_ok!(supports("non_exists_feature"));
        assert_eq!(supports("non_exists_feature").unwrap(), false);

        let supported_features = rua();
        for feature in supported_features {
            assert_eq!(supports(&feature).unwrap(), true);
        }

        let nul_error = supports("neon\0avx2").unwrap_err();
        assert_eq!(nul_error.into_vec(), b"neon\0avx2");
    }
}
