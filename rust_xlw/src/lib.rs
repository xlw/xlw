pub mod registration;
pub mod rust_oper;
pub mod ffi;

use std::os::raw::c_int;
use crate::ffi::*; // Import all FFI definitions
// Make sure WCHAR is imported if it's used directly in xlAutoOpen, or qualified.
use crate::ffi::{XLCallVer, XLC_ALERT, XLRET_SUCCESS, XLOPER12, XLOPER12_val, XLTYPE_STR, XLTYPE_INT, XLTYPE_EMPTY, LPXLOPER12, WCHAR};


#[no_mangle]
pub extern "C" fn xlAutoOpen() -> c_int {
    eprintln!("[rust_xlw] xlAutoOpen called");

    // Perform registrations
    if let Err(e) = crate::registration::perform_registrations() {
        eprintln!("[rust_xlw] Error during function registration: {}", e);
        // Decide if we should prevent XLL from loading by returning 0
        // For now, we print error and continue (return 1)
    }

    // Original alert box code (can be kept for testing initial load)
    unsafe {
        let api_version = XLCallVer();
        eprintln!("[rust_xlw] Excel C API Version: {}", api_version);

        let mut message_text_excel: Vec<WCHAR> = "Rust XLW Loaded! Reg attempted. API v".chars().map(|c| c as WCHAR).collect();
        message_text_excel.extend(api_version.to_string().chars().map(|c| c as WCHAR));
        message_text_excel.insert(0, message_text_excel.len() as WCHAR);

        let mut xl_message_oper = XLOPER12 {
            val: XLOPER12_val { str: message_text_excel.as_mut_ptr() },
            xltype: XLTYPE_STR,
        };
        let mut xl_type_oper = XLOPER12 {
            val: XLOPER12_val { int_val: 2 },
            xltype: XLTYPE_INT,
        };
        let mut result_oper_temp = XLOPER12 {
            val: XLOPER12_val { num: 0.0 },
            xltype: XLTYPE_EMPTY,
        };

        let arg1_ptr_alert: LPXLOPER12 = &mut xl_message_oper;
        let arg2_ptr_alert: LPXLOPER12 = &mut xl_type_oper;
        let result_ptr_alert: LPXLOPER12 = &mut result_oper_temp;


        let ret_code = Excel12(
            XLC_ALERT as c_int,
            result_ptr_alert,
            2,
            arg1_ptr_alert,
            arg2_ptr_alert
        );

        if ret_code != XLRET_SUCCESS {
            eprintln!("[rust_xlw] xlcAlert failed with code: {}", ret_code);
        }
    }
    1 // Return 1 for success
}

#[no_mangle]
pub extern "C" fn xlAutoClose() -> c_int {
    eprintln!("[rust_xlw] xlAutoClose called");

    // Perform deregistrations
    if let Err(e) = crate::registration::perform_deregistrations() {
        eprintln!("[rust_xlw] Error during function deregistration: {}", e);
        // Typically, you still want to return 1 from xlAutoClose.
    }
    1 // Return 1 for success
}

// Simple test function to ensure compilation and linking works.
// Not registered with Excel yet.
pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}
