use std::os::raw::{c_int, c_short, c_ushort};

// Basic types from xlcall.h (or windows.h)
// These are simplified. A full solution might use crates like `windows-sys`.
pub type WORD = c_ushort;
pub type BOOL = c_int; // In MS-Windows, BOOL is int.
pub type WCHAR = u16; // wchar_t is u16 on Windows.
pub type LPWSTR = *mut WCHAR;
pub type LPCWSTR = *const WCHAR;

// XLOPER12 structure

// Definition for the 'array' variant of XLOPER12_val
#[repr(C)]
#[derive(Copy, Clone)]
pub struct XLOPER12_array {
    pub rows: WORD,
    pub columns: WORD,
    pub lparray: LPXLOPER12, // Pointer to the first element of the actual array of XLOPER12s
}

#[repr(C)]
pub struct XLOPER12 {
    pub val: XLOPER12_val,
    pub xltype: WORD, // Changed from DWORD to WORD as per modern xlcall.h for XLOPER12, xltype is a WORD (uint16_t)
}

#[repr(C)]
pub union XLOPER12_val {
    pub num: f64,          // xltypeNum
    pub str: LPWSTR,       // xltypeStr (Pascal-style string)
    pub bool_val: BOOL,    // xltypeBool - Changed name to avoid keyword
    pub err: WORD,         // xltypeErr - Changed from int to WORD
    pub int_val: c_short,  // xltypeInt - Changed from int to short (INT_PTR in some defs, but short for xltypeInt)
    pub sref: XLREF12,     // xltypeSRef (simple rectangular reference)
    pub mref: XLMREF12,    // xltypeRef (multiple rectangular reference)
    pub array: XLOPER12_array, // For xltypeMulti
    // Other types like BigData are omitted for now
    // pub bigdata: *mut XLDNA, // xltypeBigData
    // For xltypeNil, xltypeMissing, xltypeEmpty - no specific val field is used.
}

// XLMREF12 structure (for multiple references)
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XLMREF12 {
    pub count: WORD,
    pub reftbl: [XLREF12; 1], // Actually a variable-size array; this is a common way to represent it in C.
                              // In Rust, we will likely handle pointers to this and manage memory manually.
}

// XLREF12 structure (for single rectangular reference)
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XLREF12 {
    pub rwFirst: WORD,
    pub rwLast: WORD,
    pub colFirst: WORD,
    pub colLast: WORD,
}

// Constants for xltype
pub const XLTYPE_NUM: WORD = 0x0001;
pub const XLTYPE_STR: WORD = 0x0002;
pub const XLTYPE_BOOL: WORD = 0x0004;
pub const XLTYPE_REF: WORD = 0x0008;       // Not for XLOPER12, use XLTYPE_SREF instead for val.sref
pub const XLTYPE_ERR: WORD = 0x0010;
pub const XLTYPE_FLOW: WORD = 0x0020;      // Not directly used in val union
pub const XLTYPE_MULTI: WORD = 0x0040;     // For val.array (actually val.mref with a different interpretation or structure)
pub const XLTYPE_MISSING: WORD = 0x0080;
pub const XLTYPE_EMPTY: WORD = 0x0100;     // Same as xltypeNil
pub const XLTYPE_NIL: WORD = 0x0100;       // Same as xltypeEmpty
pub const XLTYPE_INT: WORD = 0x0400;       // Integer value
pub const XLTYPE_SREF: WORD = 0x0800;      // Simple rectangular reference

// Bit flags for xltype (can be ORed with the base types)
pub const XLTYPE_XLFREE: WORD = 0x1000;    // Excel will free the memory for this XLOPER12
pub const XLTYPE_DLLFREE: WORD = 0x4000;   // DLL should free the memory for this XLOPER12 (xlFree will be called by Excel)


// Common error codes for xltypeErr
pub const XLERR_NULL: WORD = 0;  // #NULL!
pub const XLERR_DIV0: WORD = 7;  // #DIV/0!
pub const XLERR_VALUE: WORD = 15; // #VALUE!
pub const XLERR_REF: WORD = 23;  // #REF!
pub const XLERR_NAME: WORD = 29; // #NAME?
pub const XLERR_NUM: WORD = 36;  // #NUM!
pub const XLERR_NA: WORD = 42;   // #N/A
pub const XLERR_GETTING_DATA: WORD = 43; // #GETTING_DATA (Excel 2010+)

// Pointer to XLOPER12, commonly used in Excel C API functions
pub type LPXLOPER12 = *mut XLOPER12;

// FFI bindings for Excel C API functions
extern "C" {
    pub fn Excel12(
        xlfn: c_int,          // Function number (e.g., xlcAlert, xlfRegister)
        pxResult: LPXLOPER12, // Pointer to an XLOPER12 to store the result
        count: c_int,         // Number of arguments that follow
        ...                   // Variable number of arguments, each being an LPXLOPER12
    ) -> c_int;               // Return code (e.g., xlretSuccess, xlretAbort)

    pub fn XLCallVer() -> c_int; // Returns the version of the C API
}

// Excel return codes (for Excel12 and other C API calls)
pub const XLRET_SUCCESS: c_int = 0;      // Success
pub const XLRET_ABORT: c_int = 1;        // Macro halted by user
pub const XLRET_BREAK: c_int = 2;        // Break
pub const XLRET_ERROR: c_int = 4;        // Error
pub const XLRET_FAILED: c_int = 8;       // Function failed
pub const XLRET_STACK_OVERFLOW: c_int = 16; // Stack overflow
pub const XLRET_COMMAND_FAILED: c_int = 32; // Command failed
pub const XLRET_UNCALCED: c_int = 64;     // Uncalced cell encountered
pub const XLRET_NO_PERMISSIONS: c_int = 128; // No permission to call function

// Some common Excel function codes (xlfn for Excel12)
// These are just examples; a full list is extensive.
// From XLCALL.H
// Function Classes
pub const XLF_CLASS_MASK: c_int = 0x0FFF;
pub const XLF_VOLATILE: c_int = 0x1000;        // called whenever sheet recalc'd
pub const XLF_UNCALCED: c_int = 0x2000;        // not calced in recalc
pub const XLF_THREAD_SAFE: c_int = 0x4000;     // thread safe function (Excel 2007+)
pub const XLF_CLUSTER_SAFE: c_int = 0x8000;    // cluster safe function (Excel 2007+)
pub const XLF_ASYNCHRONOUS: c_int = 0xA000;    // asynchronous function (Excel 2010+) // Note: Not a simple OR

// Commands
pub const XLC_ALERT: c_int = 72;
pub const XLC_MESSAGE: c_int = 126; // (message, buttons, helpTopic)

// Functions (usually prefixed with xlf...)
pub const XLF_REGISTER: c_int = 149;     // For registering functions
pub const XLF_UNREGISTER: c_int = 150;   // For unregistering functions
pub const XLF_CALLER: c_int = 205;       // Information about the calling cell
pub const XLF_COERCE: c_int = 213;       // Coerce XLOPER to specific type
pub const XLF_GET_WORKSPACE: c_int = 220; // Workspace information
pub const XLF_EVALUATE: c_int = 226;     // Evaluate a string expression

// Other special function codes
pub const XL_FREE: c_int = 151;          // xlFree: To free memory allocated by Excel for XLOPERs/XLOPER12s with xlbitXLFree
pub const XL_STACK: c_int = 152;         // xlStack: To check stack space
pub const XL_SET: c_int = 147;           // xlSet: Set a value in a cell (dangerous, use with caution)
