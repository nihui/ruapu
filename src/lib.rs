#[macro_use]
extern crate lazy_static;

use std::ffi::{CString, NulError};
use std::os::raw::c_char;
use std::sync::Mutex;
use std::result::Result;

lazy_static! {
    static ref RUAPU_INITILIASED: Mutex<bool> = Mutex::new(false);
}

extern "C" {
    fn ruapu_init();
    fn ruapu_supports(isa: *const c_char) -> i32;
}

pub fn supports(isa: &str) -> Result<bool, NulError> {
    if !*(RUAPU_INITILIASED.lock().unwrap()) {
        unsafe {
            ruapu_init();
        }
        *(RUAPU_INITILIASED.lock().unwrap()) = true;
    }
    let isa = CString::new(isa)?;
    let isa_ptr = isa.as_ptr();
    unsafe {
        Ok(ruapu_supports(isa_ptr) != 0)
    }
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

        let nul_error = supports("neon\0avx2").unwrap_err();
        assert_eq!(nul_error.into_vec(), b"neon\0avx2");
    }
}
