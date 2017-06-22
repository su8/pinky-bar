#![crate_type = "staticlib"]

use std::os::raw::c_char;
use std::ffi::CString;

#[no_mangle]
pub extern fn uzer_func() -> *mut c_char {
  let mut str = String::from("Hello World");

  let c_str = CString::new(str).unwrap();
  c_str.into_raw()
}

#[no_mangle]
pub extern fn Rfree(s: *mut c_char) {
  unsafe {
    if s.is_null() { return }
    CString::from_raw(s)
  };
}
