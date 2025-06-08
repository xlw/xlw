use crate::ffi::*;
use std::os::raw::c_int;

// --- Custom Error type for RustOper conversions ---
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum RustOperError {
    TypeMismatch(String), // Expected type, Actual type
    ExcelError(u16),      // Excel error code (e.g., #N/A, #VALUE!)
    CoercionFailed(String), // Reason for coercion failure
    StringConversionFailed(String), // Error during string conversion (e.g. UTF-16 to Rust String)
    MissingArgument(String), // Argument was missing
    NotAnArray,
    IndexOutOfBounds,
}

impl std::fmt::Display for RustOperError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            RustOperError::TypeMismatch(msg) => write!(f, "Type mismatch: {}", msg),
            RustOperError::ExcelError(code) => {
                // Basic mapping, can be expanded
                let err_str = match *code {
                    XLERR_NULL => "#NULL!", XLERR_DIV0 => "#DIV/0!", XLERR_VALUE => "#VALUE!",
                    XLERR_REF => "#REF!", XLERR_NAME => "#NAME?", XLERR_NUM => "#NUM!",
                    XLERR_NA => "#N/A", XLERR_GETTING_DATA => "#GETTING_DATA",
                    _ => "Unknown Excel Error",
                };
                write!(f, "Excel error: {} ({})", err_str, code)
            }
            RustOperError::CoercionFailed(reason) => write!(f, "Coercion failed: {}", reason),
            RustOperError::StringConversionFailed(reason) => write!(f, "String conversion failed: {}", reason),
            RustOperError::MissingArgument(arg_name) => write!(f, "Missing argument: {}", arg_name),
            RustOperError::NotAnArray => write!(f, "Not an array/multi type"),
            RustOperError::IndexOutOfBounds => write!(f, "Index out of bounds"),
        }
    }
}

impl std::error::Error for RustOperError {}

// --- RustOperCell: A Rust-idiomatic representation of cell data ---
#[derive(Debug, Clone, PartialEq)]
pub enum RustOperCell {
    Num(f64),
    Str(String),
    Bool(bool),
    Err(u16), // Excel error code
    Nil,      // Empty cell
    Missing,  // Missing argument (less common for cell values, but possible)
}

impl RustOperCell {
    /// Converts a RustOper into a RustOperCell.
    pub fn from_rust_oper(roper: &RustOper) -> Result<Self, RustOperError> {
        // Ensure we are not trying to convert an owned complex type without proper handling.
        // This conversion should ideally work on what the RustOper represents, not its ownership.
        match roper.xl_type() & 0xFFF {
            XLTYPE_NUM => Ok(RustOperCell::Num(unsafe { roper.oper.val.num })),
            XLTYPE_STR => {
                // This needs to convert the Excel string (LPWSTR) to Rust String.
                // Re-use as_string logic but without full RustOper error context if possible.
                if roper.oper.val.str.is_null() { Ok(RustOperCell::Str(String::new())) }
                else {
                    unsafe {
                        let len_prefix = *roper.oper.val.str as usize;
                        if len_prefix == 0 { Ok(RustOperCell::Str(String::new())) }
                        else {
                            let wide_char_slice = std::slice::from_raw_parts(roper.oper.val.str.offset(1), len_prefix);
                            let os_string = std::ffi::OsString::from_wide(wide_char_slice);
                            os_string.into_string()
                                .map(RustOperCell::Str)
                                .map_err(|_| RustOperError::StringConversionFailed("RustOperCell: Invalid UTF-16".to_string()))
                        }
                    }
                }
            }
            XLTYPE_BOOL => Ok(RustOperCell::Bool(unsafe { roper.oper.val.bool_val != 0 })),
            XLTYPE_INT => Ok(RustOperCell::Num(unsafe { roper.oper.val.int_val as f64 })), // Promote Int to Num
            XLTYPE_ERR => Ok(RustOperCell::Err(unsafe { roper.oper.val.err })),
            XLTYPE_NIL => Ok(RustOperCell::Nil),
            XLTYPE_MISSING => Ok(RustOperCell::Missing),
            XLTYPE_MULTI | XLTYPE_SREF | XLTYPE_REF | XLTYPE_FLOW => {
                Err(RustOperError::TypeMismatch(format!("Cannot convert complex type {} to RustOperCell directly", roper.type_name())))
            }
            _ => Err(RustOperError::TypeMismatch(format!("Unknown type {} for RustOperCell conversion", roper.type_name()))),
        }
    }
}

impl From<RustOperCell> for RustOper {
    fn from(cell: RustOperCell) -> Self {
        match cell {
            RustOperCell::Num(n) => RustOper::new_num(n),
            RustOperCell::Str(s) => RustOper::new_str(&s),
            RustOperCell::Bool(b) => RustOper::new_bool(b),
            RustOperCell::Err(e) => RustOper::new_err(e),
            RustOperCell::Nil => RustOper::new_nil(),
            RustOperCell::Missing => RustOper::new_missing(),
        }
    }
}

/// # Safety
/// Frees the internal data of an XLOPER12 if it is a type that owns memory (e.g. STR, MULTI).
/// This does NOT free the XLOPER12 struct itself, only what it points to.
/// This is intended for XLOPER12s stored inside a RustOper array.
unsafe fn free_excel_oper_contents(oper: &mut XLOPER12) {
    match oper.xltype & 0xFFF {
        XLTYPE_STR => {
            if !oper.val.str.is_null() {
                let len_chars = *oper.val.str as usize;
                let total_elements = len_chars + 1;
                let _ = Vec::from_raw_parts(oper.val.str, total_elements, total_elements);
                // oper.val.str = std::ptr::null_mut(); // Not strictly needed as we set type to NIL
            }
        }
        XLTYPE_MULTI => {
            // Now use the correct val.array structure
            if !(oper.val.array.lparray.is_null()) {
                let rows = oper.val.array.rows;
                let cols = oper.val.array.columns;
                let num_elements = (rows as usize) * (cols as usize);
                for i in 0..num_elements {
                    free_excel_oper_contents(&mut *oper.val.array.lparray.add(i));
                }
                // Free the lparray itself (which was from Vec::leak of XLOPER12s)
                let _ = Vec::from_raw_parts(oper.val.array.lparray, num_elements, num_elements);
                // oper.val.array.lparray = std::ptr::null_mut();
            }
        }
        _ => {}
    }
    oper.xltype = XLTYPE_NIL;
}

/// Represents an Excel XLOPER12 in Rust, managing its own memory.
/// This struct will own the XLOPER12 data it contains.
#[derive(Debug)] // Added Debug for easier inspection initially
pub struct RustOper {
    oper: XLOPER12,
    /// Indicates if this RustOper instance has taken ownership and is responsible for freeing.
    /// This is a simplification for now. Real XLW C++ has more complex memory management
    /// with TempMemoryManager etc.
    owned: bool,
}

impl RustOper {
    /// Creates a new RustOper of type xltypeMissing.
    pub fn new() -> Self {
        RustOper {
            oper: XLOPER12 {
                val: XLOPER12_val { num: 0.0 }, // Initialize union with something
                xltype: XLTYPE_MISSING,
            },
            owned: true, // Typically, a new RustOper created this way owns its data.
        }
    }

    /// Creates a RustOper that wraps an existing LPXLOPER12 received from Excel.
    /// This RustOper does NOT own the memory initially, but might be responsible for freeing it
    /// if xlbitXLFree is set on the passed oper.
    ///
    /// # Safety
    /// The caller must ensure that lpxloper points to a valid XLOPER12 structure.
    /// The lifetime of the RustOper must not exceed the lifetime of the pointed-to XLOPER12,
    /// unless Excel indicates it should be freed by this DLL (xlbitDLLFree) or the data is copied.
    /// For now, we assume this wrapper will check flags and free if necessary.
    pub unsafe fn from_excel_lpxloper(lpxloper: LPXLOPER12) -> Self {
        // We are taking responsibility for this oper if DLLFREE is set,
        // or if it is a type that Excel expects to be freed by us after it passes it.
        // For now, we make a copy if we need to free it to simplify ownership.
        // This is a placeholder for more sophisticated memory management.

        let should_free_eventually = ((*lpxloper).xltype & XLTYPE_DLLFREE) != 0;

        if should_free_eventually {
            // If DLL is responsible for freeing, we can take ownership of this specific oper.
            // However, XLW C++ XlfOper has complex logic with TempMemory.
            // A simple approach for now: if DLLFREE is set, this RustOper instance
            // will be responsible. We assume the LPXLOPER12 itself can be managed by this RustOper.
             RustOper {
                oper: *lpxloper, // shallow copy the XLOPER12 struct
                owned: true, // We are now responsible because DLLFREE was set
            }
        } else {
            // If Excel manages it (e.g. xlbitXLFree) or it is not dynamically allocated,
            // we should not free it. We are just observing it.
            // For safety in a simple model, we might copy, or use lifetimes.
            // For now, let's assume if not DLLFREE, we are just observing.
            // THIS IS A MAJOR SIMPLIFICATION AND POTENTIALLY UNSAFE WITHOUT LIFETIMES
            // OR A MORE ROBUST OWNERSHIP MODEL.
            // A truly safe wrapper might need to always copy if not taking ownership via DLLFREE.
            // Or, it would need a lifetime tied to the Excel call.
             RustOper {
                oper: std::ptr::read(lpxloper), // Make a copy
                owned: true, // The RustOper owns this copy.
            }
        }
    }

    // --- Constructors for basic types ---

    /// Creates a new RustOper of type xltypeNum.
    pub fn new_num(val: f64) -> Self {
        RustOper {
            oper: XLOPER12 {
                val: XLOPER12_val { num: val },
                xltype: XLTYPE_NUM,
            },
            owned: true,
        }
    }

    /// Creates a new RustOper of type xltypeBool.
    pub fn new_bool(val: bool) -> Self {
        RustOper {
            oper: XLOPER12 {
                val: XLOPER12_val { bool_val: if val { 1 } else { 0 } },
                xltype: XLTYPE_BOOL,
            },
            owned: true,
        }
    }

    /// Creates a new RustOper of type xltypeInt.
    /// Note: XLOPER12 stores int as c_short (i16).
    /// This function will truncate if the value is out of c_short range.
    pub fn new_int(val: i32) -> Self {
        RustOper {
            oper: XLOPER12 {
                // TODO: Add proper error handling or clamping for out-of-range values.
                val: XLOPER12_val { int_val: val as c_short },
                xltype: XLTYPE_INT,
            },
            owned: true,
        }
    }

    /// Creates a new RustOper of type xltypeInt from c_short.
    pub fn new_short(val: c_short) -> Self {
        RustOper {
            oper: XLOPER12 {
                val: XLOPER12_val { int_val: val },
                xltype: XLTYPE_INT,
            },
            owned: true,
        }
    }

    /// Creates a new RustOper of type xltypeErr.
    pub fn new_err(err_code: u16) -> Self {
        RustOper {
            oper: XLOPER12 {
                val: XLOPER12_val { err: err_code },
                xltype: XLTYPE_ERR,
            },
            owned: true,
        }
    }

    /// Creates a new RustOper of type xltypeNil (empty cell value).
    pub fn new_nil() -> Self {
        RustOper {
            oper: XLOPER12 {
                val: XLOPER12_val { num: 0.0 }, // Initialize union field
                xltype: XLTYPE_NIL,
            },
            owned: true,
        }
    }

    /// Creates a new RustOper of type xltypeMissing (for absent arguments).
    pub fn new_missing() -> Self { // Same as current new()
        RustOper {
            oper: XLOPER12 {
                val: XLOPER12_val { num: 0.0 },
                xltype: XLTYPE_MISSING,
            },
            owned: true,
        }
    }

    /// Creates a new RustOper of type xltypeStr from a Rust string slice.
    /// This allocates memory for the Excel Pascal-style string.
    /// The Drop implementation for RustOper will need to free this memory.
    pub fn new_str(text: &str) -> Self {
        let wide_chars: Vec<WCHAR> = text.encode_utf16().collect();
        let len = wide_chars.len();

        if len > 255 {
            // Excel's XLOPER12 string length is practically limited,
            // often to 255 chars for simple xltypeStr in older contexts,
            // though XLOPER12 can technically handle up to 32767.
            // For now, let's truncate or return error for very long strings.
            // Here, we will truncate to 255, which is a common safe limit.
            // TODO: Handle strings longer than 255 characters more gracefully (e.g. return #VALUE! error or use BigData)
            let truncated_wide_chars: Vec<WCHAR> = wide_chars.into_iter().take(255).collect();
            let new_len = truncated_wide_chars.len();

            let mut pascal_string_data = Vec::with_capacity(new_len + 1);
            pascal_string_data.push(new_len as WCHAR); // Length prefix
            pascal_string_data.extend_from_slice(&truncated_wide_chars);

            // Keep the vector alive and leak its memory, then get a pointer.
            // This pointer needs to be freed in Drop.
            let ptr = pascal_string_data.leak().as_mut_ptr();

            return RustOper {
                oper: XLOPER12 {
                    val: XLOPER12_val { str: ptr },
                    xltype: XLTYPE_STR,
                },
                owned: true, // RustOper owns this allocated string
            };
        }

        let mut pascal_string_data = Vec::with_capacity(len + 1);
        pascal_string_data.push(len as WCHAR); // Length prefix
        pascal_string_data.extend_from_slice(&wide_chars);

        let ptr = pascal_string_data.leak().as_mut_ptr();

        RustOper {
            oper: XLOPER12 {
                val: XLOPER12_val { str: ptr },
                xltype: XLTYPE_STR,
            },
            owned: true, // RustOper owns this allocated string
        }
    }

    // --- Type Inspection Methods ---

    /// Returns the raw xltype WORD of the oper.
    pub fn xl_type(&self) -> WORD {
        self.oper.xltype
    }

    /// Checks if the oper is of type xltypeNum.
    pub fn is_num(&self) -> bool {
        (self.oper.xltype & XLTYPE_NUM) != 0
    }

    /// Checks if the oper is of type xltypeStr.
    pub fn is_str(&self) -> bool {
        (self.oper.xltype & XLTYPE_STR) != 0
    }

    /// Checks if the oper is of type xltypeBool.
    pub fn is_bool(&self) -> bool {
        (self.oper.xltype & XLTYPE_BOOL) != 0
    }

    /// Checks if the oper is of type xltypeRef (complex/multiple reference).
    /// Note: For XLOPER12, this usually implies xltypeMulti when used for arrays,
    /// or a true reference structure for val.mref.
    /// Use is_sref() for simple rectangular references.
    pub fn is_ref(&self) -> bool {
        (self.oper.xltype & XLTYPE_REF) != 0
    }

    /// Checks if the oper is of type xltypeSRef (simple rectangular reference).
    pub fn is_sref(&self) -> bool {
        (self.oper.xltype & XLTYPE_SREF) != 0
    }

    /// Checks if the oper is of type xltypeErr.
    pub fn is_err(&self) -> bool {
        (self.oper.xltype & XLTYPE_ERR) != 0
    }

    /// Checks if the oper is of type xltypeMulti (array).
    pub fn is_multi(&self) -> bool {
        (self.oper.xltype & XLTYPE_MULTI) != 0
    }

    /// Checks if the oper is of type xltypeMissing.
    pub fn is_missing(&self) -> bool {
        (self.oper.xltype & XLTYPE_MISSING) != 0
    }

    /// Checks if the oper is of type xltypeNil or xltypeEmpty.
    pub fn is_nil(&self) -> bool {
        (self.oper.xltype & XLTYPE_NIL) != 0 // XLTYPE_NIL and XLTYPE_EMPTY are the same
    }

    /// Checks if the oper is of type xltypeInt.
    pub fn is_int(&self) -> bool {
        (self.oper.xltype & XLTYPE_INT) != 0
    }

    /// Returns a string representation of the Excel type.
    /// (Does not include flags like XLFREE/DLLFREE).
    pub fn type_name(&self) -> &'static str {
        match self.oper.xltype & 0xFFF {
            XLTYPE_NUM => "Number (xltypeNum)",
            XLTYPE_STR => "String (xltypeStr)",
            XLTYPE_BOOL => "Boolean (xltypeBool)",
            XLTYPE_REF => "Reference (xltypeRef)",
            XLTYPE_ERR => "Error (xltypeErr)",
            XLTYPE_FLOW => "Flow Control (xltypeFlow)",
            XLTYPE_MULTI => "Array (xltypeMulti)",
            XLTYPE_MISSING => "Missing (xltypeMissing)",
            XLTYPE_NIL => "Nil/Empty (xltypeNil)", // XLTYPE_EMPTY is same
            XLTYPE_SREF => "Simple Reference (xltypeSRef)",
            XLTYPE_INT => "Integer (xltypeInt)",
            _ => "Unknown or Complex Type",
        }
    }

    // --- Conversion (AsType) Methods ---

    /// Converts the RustOper to a f64.
    /// Handles direct xltypeNum or attempts coercion from other types.
    pub fn as_f64(&self) -> Result<f64, RustOperError> {
        match self.oper.xltype & 0xFFF {
            XLTYPE_NUM => Ok(unsafe { self.oper.val.num }),
            XLTYPE_INT => Ok(unsafe { self.oper.val.int_val as f64 }),
            XLTYPE_BOOL => Ok(if unsafe { self.oper.val.bool_val != 0 } { 1.0 } else { 0.0 }),
            XLTYPE_MISSING => Err(RustOperError::MissingArgument("Cannot convert missing to f64".to_string())),
            XLTYPE_NIL => Ok(0.0), // Excel often treats empty cells as 0 in numeric contexts
            XLTYPE_ERR => Err(RustOperError::ExcelError(unsafe { self.oper.val.err })),
            XLTYPE_STR => {
                // Try to parse the string as a float.
                // This is a simple version. Excel's string-to-number conversion is locale-dependent.
                let rust_str = self.as_string_priv(false)?; // Get string without coercion first
                rust_str.parse::<f64>().map_err(|_| RustOperError::CoercionFailed(format!("Could not parse string \"{}\" as f64", rust_str)))
            }
            _ => Err(RustOperError::TypeMismatch(format!("Cannot directly convert {} to f64 without coercion", self.type_name()))),
            // TODO: Implement coercion via Excel12(xlCoerce, ...) for other types
        }
    }

    /// Converts the RustOper to a bool.
    pub fn as_bool(&self) -> Result<bool, RustOperError> {
        match self.oper.xltype & 0xFFF {
            XLTYPE_BOOL => Ok(unsafe { self.oper.val.bool_val != 0 }),
            XLTYPE_NUM => Ok(unsafe { self.oper.val.num != 0.0 }),
            XLTYPE_INT => Ok(unsafe { self.oper.val.int_val != 0 }),
            XLTYPE_MISSING => Err(RustOperError::MissingArgument("Cannot convert missing to bool".to_string())),
            XLTYPE_NIL => Ok(false), // Excel treats empty as FALSE
            XLTYPE_ERR => Err(RustOperError::ExcelError(unsafe { self.oper.val.err })),
            XLTYPE_STR => {
                 // Excel specific string to bool: "TRUE" (case-insensitive) is true, "FALSE" is false.
                 // Other strings might be errors or specific values depending on context.
                 // For now, simple true/false.
                let rust_str = self.as_string_priv(false)?;
                if rust_str.eq_ignore_ascii_case("true") { Ok(true) }
                else if rust_str.eq_ignore_ascii_case("false") { Ok(false) }
                else { Err(RustOperError::CoercionFailed(format!("String \"{}\" is not TRUE or FALSE", rust_str))) }
            }
            _ => Err(RustOperError::TypeMismatch(format!("Cannot directly convert {} to bool without coercion", self.type_name()))),
            // TODO: Coercion for other types.
        }
    }

    /// Converts the RustOper to an i32.
    /// Note: Excel internal integer is c_short (i16). This may involve truncation or checking.
    pub fn as_i32(&self) -> Result<i32, RustOperError> {
        match self.oper.xltype & 0xFFF {
            XLTYPE_INT => Ok(unsafe { self.oper.val.int_val as i32 }),
            XLTYPE_NUM => {
                let num = unsafe { self.oper.val.num };
                // Check if it can be safely converted or if it truncates.
                if num >= (i32::MIN as f64) && num <= (i32::MAX as f64) && num.fract() == 0.0 {
                    Ok(num as i32)
                } else {
                    Err(RustOperError::CoercionFailed(format!("Number {} cannot be safely converted to i32", num)))
                }
            }
            XLTYPE_BOOL => Ok(if unsafe { self.oper.val.bool_val != 0 } { 1 } else { 0 }),
            XLTYPE_MISSING => Err(RustOperError::MissingArgument("Cannot convert missing to i32".to_string())),
            XLTYPE_NIL => Ok(0),
            XLTYPE_ERR => Err(RustOperError::ExcelError(unsafe { self.oper.val.err })),
            XLTYPE_STR => {
                let rust_str = self.as_string_priv(false)?;
                rust_str.parse::<i32>().map_err(|_| RustOperError::CoercionFailed(format!("Could not parse string \"{}\" as i32", rust_str)))
            }
            _ => Err(RustOperError::TypeMismatch(format!("Cannot directly convert {} to i32 without coercion", self.type_name()))),
        }
    }

    /// Converts the RustOper to a Rust String.
    /// If `coerce_to_str` is true, it will attempt to call Excel to coerce the current type to a string.
    /// If false, it only converts if the type is already xltypeStr.
    /// Note: This is a preliminary version. Coercion is not yet implemented.
    fn as_string_priv(&self, _coerce_to_str: bool) -> Result<String, RustOperError> {
        if (self.oper.xltype & XLTYPE_STR) == 0 {
            // TODO: Implement coercion to string via Excel12(xlCoerce, ...) if coerce_to_str is true.
            // For now, only direct conversion is supported by this private helper.
             return Err(RustOperError::TypeMismatch("Not a string type, and coercion not yet implemented in as_string_priv".to_string()));
        }

        if self.oper.val.str.is_null() {
            // This case should ideally not happen if type is XLTYPE_STR,
            // as str pointer should point to at least the length prefix.
            // However, if it does, it could be an empty string with a null pointer.
            // Excel documentation says for xltypeStr, oper.val.str points to a string
            // where the first byte/word is the length. An empty string would have length 0.
            // A truly null pointer here might be an invalid XLOPER12.
            return Ok(String::new());
        }

        unsafe {
            let len_prefix = *self.oper.val.str as usize;
            if len_prefix == 0 {
                return Ok(String::new());
            }
            // Points to the actual characters after the length prefix.
            let wide_char_slice = std::slice::from_raw_parts(self.oper.val.str.offset(1), len_prefix);

            // OsString::from_wide can handle UTF-16. Then try to convert to String (UTF-8).
            // This can fail if the UTF-16 data is not valid for conversion to UTF-8 (e.g. lone surrogates).
            let os_string = std::ffi::OsString::from_wide(wide_char_slice);
            os_string.into_string().map_err(|_| RustOperError::StringConversionFailed("Invalid UTF-16 sequence or unpaired surrogates".to_string()))
        }
    }

    pub fn as_string(&self) -> Result<String, RustOperError> {
        // Public version - for now, does not attempt coercion.
        // Will be enhanced with coercion later.
        match self.oper.xltype & 0xFFF {
            XLTYPE_STR => self.as_string_priv(false),
            XLTYPE_NUM => Ok(unsafe { self.oper.val.num }.to_string()), // Basic number to string
            XLTYPE_BOOL => Ok((if unsafe { self.oper.val.bool_val != 0} { "TRUE" } else { "FALSE" }).to_string()),
            XLTYPE_INT => Ok(unsafe { self.oper.val.int_val }.to_string()),
            XLTYPE_MISSING => Ok("<Missing>".to_string()), // Or error? Excel shows blank for missing in string context.
            XLTYPE_NIL => Ok(String::new()), // Empty string for NIL
            XLTYPE_ERR => Err(RustOperError::ExcelError(unsafe{ self.oper.val.err })), // Or format error code?
            _ => Err(RustOperError::TypeMismatch(format!("Cannot convert {} to String without coercion", self.type_name()))),
        }
    }

    // --- Array (xltypeMulti) Handling Methods ---

    /// Creates a new RustOper of type xltypeMulti with the given dimensions.
    /// The array elements are initialized to xltypeNil.
    /// Memory for the array of XLOPER12s is allocated and owned by this RustOper.
    pub fn new_array(rows: u16, cols: u16) -> Result<Self, RustOperError> {
        if rows == 0 || cols == 0 {
            return Err(RustOperError::CoercionFailed("Array dimensions must be greater than 0".to_string()));
        }

        let num_elements = (rows as usize) * (cols as usize);
        // Check for potential overflow if rows*cols is huge, though u16 limits this.
        if num_elements > (i32::MAX as usize) { // Arbitrary large limit, Excel has its own.
             return Err(RustOperError::CoercionFailed("Array dimensions too large".to_string()));
        }

        let mut elements_vec: Vec<XLOPER12> = Vec::with_capacity(num_elements);
        for _ in 0..num_elements {
            elements_vec.push(XLOPER12 {
                val: XLOPER12_val { num: 0.0 }, // Default init for a union field
                xltype: XLTYPE_NIL,
            });
        }

        let elements_ptr = elements_vec.leak().as_mut_ptr();

        Ok(RustOper {
            oper: XLOPER12 {
                val: XLOPER12_val {
                    array: XLOPER12_array { // Now using the correct ffi field
                        rows: rows,
                        columns: cols,
                        lparray: elements_ptr,
                    }
                },
                xltype: XLTYPE_MULTI,
            },
            owned: true,
        })
    }

    /// Returns the number of rows if the oper is an array (xltypeMulti).
    /// Returns RustOperError::TypeMismatch if not an array.
    /// This method relies on ffi.rs XLOPER12_val having an `array` field.
    pub fn rows(&self) -> Result<u16, RustOperError> {
        if !self.is_multi() {
            return Err(RustOperError::TypeMismatch("Not an xltypeMulti".to_string()));
        }
        Ok(unsafe { self.oper.val.array.rows })
    }

    /// Returns the number of columns if the oper is an array (xltypeMulti).
    /// Returns RustOperError::TypeMismatch if not an array.
    /// This method relies on ffi.rs XLOPER12_val having an `array` field.
    pub fn cols(&self) -> Result<u16, RustOperError> {
        if !self.is_multi() {
            return Err(RustOperError::TypeMismatch("Not an xltypeMulti".to_string()));
        }
        Ok(unsafe { self.oper.val.array.columns })
    }

    /// Gets a copy of the element at `(row, col)` from an array (xltypeMulti) RustOper.
    /// Row and col are 0-indexed.
    /// Returns a new owned RustOper containing the copy.
    /// This method relies on ffi.rs XLOPER12_val having an `array` field.
    pub fn get_element(&self, row: u16, col: u16) -> Result<RustOper, RustOperError> {
        if !self.is_multi() {
            return Err(RustOperError::TypeMismatch("Not an xltypeMulti".to_string()));
        }
        let (arr_rows, arr_cols, lparray) = unsafe {
            // Accessing union field val.array directly
            (self.oper.val.array.rows, self.oper.val.array.columns, self.oper.val.array.lparray)
        };

        if row >= arr_rows || col >= arr_cols {
            return Err(RustOperError::IndexOutOfBounds);
        }

        let index = (row as usize) * (arr_cols as usize) + (col as usize);
        let element_lpxloper = unsafe { lparray.add(index) };

        Ok(unsafe { RustOper::from_excel_lpxloper_copy(element_lpxloper) })
    }

    /// Sets the element at `(row, col)` in an array (xltypeMulti) RustOper.
    /// Row and col are 0-indexed.
    /// The `value` RustOper is consumed (its data is copied).
    /// This method relies on ffi.rs XLOPER12_val having an `array` field.
    pub fn set_element(&mut self, row: u16, col: u16, value: RustOper) -> Result<(), RustOperError> {
        if !self.is_multi() {
            return Err(RustOperError::TypeMismatch("Not an xltypeMulti".to_string()));
        }
        if !self.owned {
            return Err(RustOperError::CoercionFailed("Cannot modify a non-owned RustOper array".to_string()));
        }

        let (arr_rows, arr_cols, lparray) = unsafe {
             // Accessing union field val.array directly
            (self.oper.val.array.rows, self.oper.val.array.columns, self.oper.val.array.lparray)
        };

        if row >= arr_rows || col >= arr_cols {
            return Err(RustOperError::IndexOutOfBounds);
        }

        let index = (row as usize) * (arr_cols as usize) + (col as usize);
        let target_lpxloper = unsafe { lparray.add(index) };

        unsafe { free_excel_oper_contents(&mut *target_lpxloper) };

        unsafe {
            let mut temp_value = value;
            let new_oper_data = std::mem::replace(
                &mut temp_value.oper,
                XLOPER12 { val: XLOPER12_val { num: 0.0 }, xltype: XLTYPE_NIL }
            );
            temp_value.owned = false;
            *target_lpxloper = new_oper_data;
        }
        Ok(())
    }

    // Helper for from_excel_lpxloper to make a copy
    // Assumes the new RustOper will own the copied data.
    unsafe fn from_excel_lpxloper_copy(lpxloper: LPXLOPER12) -> Self {
        let mut new_oper_data = std::ptr::read(lpxloper);

        match new_oper_data.xltype & 0xFFF {
            XLTYPE_STR => {
                if !new_oper_data.val.str.is_null() {
                    let len_chars = *new_oper_data.val.str as usize;
                    let total_elements_including_prefix = len_chars + 1;
                    let original_slice = std::slice::from_raw_parts(new_oper_data.val.str, total_elements_including_prefix);
                    let mut new_vec = Vec::with_capacity(total_elements_including_prefix);
                    new_vec.extend_from_slice(original_slice);
                    new_oper_data.val.str = new_vec.leak().as_mut_ptr();
                }
            }
            XLTYPE_MULTI => {
                // Placeholder for deep copy of XLTYPE_MULTI. This is complex.
                // For now, the shallow copy of lparray pointer is problematic if source is freed.
                // This should ideally perform a deep copy by calling new_array and set_element recursively.
                // panic!("Deep copy of XLTYPE_MULTI in from_excel_lpxloper_copy not yet implemented");
            }
            _ => {}
        }
        RustOper { oper: new_oper_data, owned: true }
    }

    // --- CellMatrix-like Functionality ---

    /// Converts an XLTYPE_MULTI RustOper into a Vec<Vec<RustOperCell>>.
    pub fn as_cell_matrix(&self) -> Result<Vec<Vec<RustOperCell>>, RustOperError> {
        if !self.is_multi() {
            return Err(RustOperError::TypeMismatch("Not an xltypeMulti for as_cell_matrix".to_string()));
        }

        let rows = self.rows()? as usize;
        let cols = self.cols()? as usize;
        let mut matrix: Vec<Vec<RustOperCell>> = Vec::with_capacity(rows);

        for r_idx in 0..rows {
            let mut current_row: Vec<RustOperCell> = Vec::with_capacity(cols);
            for c_idx in 0..cols {
                // get_element returns an owned RustOper copy of the element.
                let element_roper = self.get_element(r_idx as u16, c_idx as u16)?;
                current_row.push(RustOperCell::from_rust_oper(&element_roper)?);
            }
            matrix.push(current_row);
        }
        Ok(matrix)
    }

    /// Creates a new XLTYPE_MULTI RustOper from a Vec<Vec<RustOperCell>>.
    pub fn new_from_cell_matrix(matrix: &[Vec<RustOperCell>]) -> Result<Self, RustOperError> {
        if matrix.is_empty() || matrix[0].is_empty() {
            return Err(RustOperError::CoercionFailed("Input matrix cannot be empty".to_string()));
        }
        let rows = matrix.len() as u16;
        let cols = matrix[0].len() as u16;

        // Validate that all rows have the same number of columns
        for r in matrix {
            if r.len() as u16 != cols {
                return Err(RustOperError::CoercionFailed("All rows in matrix must have the same number of columns".to_string()));
            }
        }

        let mut new_array_roper = RustOper::new_array(rows, cols)?;
        for (r_idx, row_vec) in matrix.iter().enumerate() {
            for (c_idx, cell_value) in row_vec.iter().enumerate() {
                // Convert RustOperCell to RustOper and set it.
                // RustOper::from(cell_value.clone()) creates an owned RustOper.
                // set_element consumes this owned RustOper.
                new_array_roper.set_element(r_idx as u16, c_idx as u16, RustOper::from(cell_value.clone()))?;
            }
        }
        Ok(new_array_roper)
    }

    // --- SRef (Sheet Reference) Handling ---

    /// Creates a new RustOper of type xltypeSRef.
    /// Note: XLREF12 for SRef does not include sheet ID. That is part of XLMREF / external references.
    /// This creates a reference on the currently active sheet.
    pub fn new_sref(rw_first: WORD, rw_last: WORD, col_first: WORD, col_last: WORD) -> Self {
        RustOper {
            oper: XLOPER12 {
                val: XLOPER12_val {
                    sref: XLREF12 { // Using the correct ffi field
                        rwFirst: rw_first,
                        rwLast: rw_last,
                        colFirst: col_first,
                        colLast: col_last,
                    }
                },
                xltype: XLTYPE_SREF,
            },
            owned: true, // Owns the XLOPER12 struct itself, no external data for SRef value.
        }
    }

    /// Creates a new RustOper of type xltypeSRef from an XLREF12 struct.
    pub fn new_from_xlref12(sref_val: XLREF12) -> Self {
        RustOper {
            oper: XLOPER12 {
                val: XLOPER12_val { sref: sref_val },
                xltype: XLTYPE_SREF,
            },
            owned: true,
        }
    }

    /// Converts the RustOper to an XLREF12 if it is of type xltypeSRef.
    pub fn as_sref(&self) -> Result<XLREF12, RustOperError> {
        if !self.is_sref() {
            return Err(RustOperError::TypeMismatch(format!("Not an xltypeSRef, actual type: {}", self.type_name())));
        }
        // XLREF12 is Copy, so we can directly return it.
        Ok(unsafe { self.oper.val.sref })
    }

    /// Returns a mutable pointer to the internal XLOPER12.
    /// # Safety
    /// Caller must ensure RustOper outlives the use of this pointer.
    /// Modifying the XLOPER12 directly can break RustOper invariants if not done carefully.
    pub unsafe fn as_lpxloper12_mut(&mut self) -> LPXLOPER12 {
        &mut self.oper
    }

    /// Returns a const pointer to the internal XLOPER12.
    /// # Safety
    /// Caller must ensure RustOper outlives the use of this pointer.
    pub unsafe fn as_lpxloper12_const(&self) -> *const XLOPER12 { // Changed to *const
        &self.oper as *const XLOPER12
    }
} // End of impl RustOper

impl Default for RustOper {
    fn default() -> Self {
        Self::new()
    }
}

impl Drop for RustOper {
    fn drop(&mut self) {
        if !self.owned {
            return;
        }

        unsafe {
            // We call free_excel_oper_contents on self.oper here.
            // This function is designed to recursively free contents.
            // For a top-level RustOper, this will handle its owned string or array.
            // It also conveniently sets the oper to NIL after freeing.
            free_excel_oper_contents(&mut self.oper);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::ffi::OsString;
    use std::os::windows::ffi::OsStringExt;

    #[test]
    fn test_new_rust_oper_default() {
        let roper = RustOper::new();
        assert_eq!(roper.oper.xltype, XLTYPE_MISSING);
        assert!(roper.owned);
    }

    #[test]
    fn test_new_num() {
        let roper = RustOper::new_num(123.45);
        assert_eq!(roper.oper.xltype, XLTYPE_NUM);
        unsafe { assert_eq!(roper.oper.val.num, 123.45); }
    }

    #[test]
    fn test_new_bool() {
        let roper_true = RustOper::new_bool(true);
        assert_eq!(roper_true.oper.xltype, XLTYPE_BOOL);
        unsafe { assert_eq!(roper_true.oper.val.bool_val, 1); }
    }

    #[test]
    fn test_new_int_and_short() {
        let roper_int = RustOper::new_int(12345);
        assert_eq!(roper_int.oper.xltype, XLTYPE_INT);
        unsafe { assert_eq!(roper_int.oper.val.int_val, 12345 as c_short); }
    }

    #[test]
    fn test_new_err() {
        let roper = RustOper::new_err(XLERR_NA);
        assert_eq!(roper.oper.xltype, XLTYPE_ERR);
        unsafe { assert_eq!(roper.oper.val.err, XLERR_NA); }
    }

    #[test]
    fn test_new_nil() {
        let roper = RustOper::new_nil();
        assert_eq!(roper.oper.xltype, XLTYPE_NIL);
    }

    #[test]
    fn test_new_missing() {
        let roper = RustOper::new_missing();
        assert_eq!(roper.oper.xltype, XLTYPE_MISSING);
    }

    #[test]
    fn test_new_str_and_drop() { // Test that drop works for string
        let text = "Hello Rust XLW!";
        {
            let roper = RustOper::new_str(text);
            assert_eq!(roper.oper.xltype, XLTYPE_STR);
            assert!(roper.owned);
            unsafe {
                assert!(!roper.oper.val.str.is_null());
                let len = *roper.oper.val.str as usize;
                assert_eq!(len, text.len());
                let slice = std::slice::from_raw_parts(roper.oper.val.str.offset(1), len);
                let round_trip_text = OsString::from_wide(slice).into_string().unwrap();
                assert_eq!(round_trip_text, text);
            }
        } // roper is dropped here
        // If drop is correct, memory is freed. No easy assert for this in test, relies on sanitizers/valgrind.
    }

    #[test]
    fn test_new_str_truncate() {
        let long_text = String::from_utf8(vec![b'A'; 300]).unwrap();
        let roper = RustOper::new_str(&long_text);
        assert_eq!(roper.oper.xltype, XLTYPE_STR);
        unsafe {
            let len = *roper.oper.val.str as usize;
            assert_eq!(len, 255);
        }
    }

    #[test]
    fn test_as_f64() {
        assert_eq!(RustOper::new_num(12.5).as_f64().unwrap(), 12.5);
        assert_eq!(RustOper::new_str("3.14").as_f64().unwrap(), 3.14);
    }

    #[test]
    fn test_as_bool() {
        assert_eq!(RustOper::new_bool(true).as_bool().unwrap(), true);
        assert_eq!(RustOper::new_str("FALSE").as_bool().unwrap(), false);
    }

    #[test]
    fn test_as_i32() {
        assert_eq!(RustOper::new_int(42).as_i32().unwrap(), 42);
        assert_eq!(RustOper::new_str("-100").as_i32().unwrap(), -100);
    }

    #[test]
    fn test_as_string() {
        assert_eq!(RustOper::new_str("hello").as_string().unwrap(), "hello");
        assert_eq!(RustOper::new_num(123.45).as_string().unwrap(), "123.45");
    }

    #[test]
    fn test_new_array() { // Removed should_panic
        let rows = 2u16;
        let cols = 3u16;
        let r_array = RustOper::new_array(rows, cols).expect("new_array failed");

        assert!(r_array.is_multi());
        assert!(r_array.owned);
        assert_eq!(r_array.rows().unwrap(), rows);
        assert_eq!(r_array.cols().unwrap(), cols);

        for r in 0..rows {
            for c in 0..cols {
                let elem = r_array.get_element(r, c).unwrap();
                assert!(elem.is_nil()); // Default elements are NIL
            }
        }
    } // r_array is dropped here, testing multi-level drop

    #[test]
    fn test_array_set_get_element() { // Removed should_panic
        let mut r_array = RustOper::new_array(2, 2).expect("Array creation failed");

        // Set a number
        r_array.set_element(0, 0, RustOper::new_num(10.0)).unwrap();
        let elem00 = r_array.get_element(0, 0).unwrap();
        assert!(elem00.is_num());
        assert_eq!(elem00.as_f64().unwrap(), 10.0);

        // Set a string
        r_array.set_element(0, 1, RustOper::new_str("test")).unwrap();
        let elem01 = r_array.get_element(0, 1).unwrap();
        assert!(elem01.is_str());
        assert_eq!(elem01.as_string().unwrap(), "test");

        // Set a boolean in the same spot, old string should be freed by set_element
        r_array.set_element(0, 1, RustOper::new_bool(true)).unwrap();
        let elem01_new = r_array.get_element(0, 1).unwrap();
        assert!(elem01_new.is_bool());
        assert_eq!(elem01_new.as_bool().unwrap(), true);

        // Set an array element with another array (array of arrays)
        let inner_array = RustOper::new_array(1, 2).unwrap();
        // Note: current `from_excel_lpxloper_copy` does not deep copy XLTYPE_MULTI.
        // `set_element` moves the `inner_array.oper` data.
        // The `Drop` for the outer `r_array` must correctly handle dropping this inner array.
        r_array.set_element(1, 0, inner_array).unwrap();
        let retrieved_inner_array_oper = r_array.get_element(1,0).unwrap();
        assert!(retrieved_inner_array_oper.is_multi());
        assert_eq!(retrieved_inner_array_oper.rows().unwrap(), 1);
        assert_eq!(retrieved_inner_array_oper.cols().unwrap(), 2);

    } // r_array is dropped here. Its Drop should call free_excel_oper_contents for each element.
      // This will test recursive drop for the inner array at (1,0).

    #[test]
    fn test_rust_oper_cell_from_rust_oper() {
        assert_eq!(RustOperCell::from_rust_oper(&RustOper::new_num(5.5)).unwrap(), RustOperCell::Num(5.5));
        assert_eq!(RustOperCell::from_rust_oper(&RustOper::new_str("hello")).unwrap(), RustOperCell::Str("hello".to_string()));
        assert_eq!(RustOperCell::from_rust_oper(&RustOper::new_bool(true)).unwrap(), RustOperCell::Bool(true));
        assert_eq!(RustOperCell::from_rust_oper(&RustOper::new_int(10)).unwrap(), RustOperCell::Num(10.0)); // Promoted
        assert_eq!(RustOperCell::from_rust_oper(&RustOper::new_err(XLERR_DIV0)).unwrap(), RustOperCell::Err(XLERR_DIV0));
        assert_eq!(RustOperCell::from_rust_oper(&RustOper::new_nil()).unwrap(), RustOperCell::Nil);
        assert_eq!(RustOperCell::from_rust_oper(&RustOper::new_missing()).unwrap(), RustOperCell::Missing);

        let multi = RustOper::new_array(1,1).unwrap();
        assert!(RustOperCell::from_rust_oper(&multi).is_err());
    }

    #[test]
    fn test_rust_oper_from_rust_oper_cell() {
        let cell_num = RustOperCell::Num(1.2);
        let roper_num = RustOper::from(cell_num);
        assert!(roper_num.is_num());
        assert_eq!(roper_num.as_f64().unwrap(), 1.2);

        let cell_str = RustOperCell::Str("world".to_string());
        let roper_str = RustOper::from(cell_str);
        assert!(roper_str.is_str());
        assert_eq!(roper_str.as_string().unwrap(), "world");
    }

    #[test]
    fn test_as_cell_matrix_and_new_from_cell_matrix() {
        // 1. Create a matrix of RustOperCell
        let matrix_data: Vec<Vec<RustOperCell>> = vec![
            vec![RustOperCell::Num(1.0), RustOperCell::Str("A".to_string()), RustOperCell::Bool(true)],
            vec![RustOperCell::Nil, RustOperCell::Err(XLERR_NA), RustOperCell::Num(100.0)],
        ];

        // 2. Convert it to a RustOper (XLTYPE_MULTI)
        let roper_array = RustOper::new_from_cell_matrix(&matrix_data).expect("new_from_cell_matrix failed");
        assert!(roper_array.is_multi());
        assert_eq!(roper_array.rows().unwrap(), 2);
        assert_eq!(roper_array.cols().unwrap(), 3);

        // 3. Convert the RustOper back to a Vec<Vec<RustOperCell>>
        let retrieved_matrix = roper_array.as_cell_matrix().expect("as_cell_matrix failed");
        assert_eq!(retrieved_matrix.len(), 2);
        assert_eq!(retrieved_matrix[0].len(), 3);
        assert_eq!(retrieved_matrix, matrix_data); // Check for equality

        // 4. Check one element specifically after round trip
        let elem11 = roper_array.get_element(1,1).unwrap(); // XLERR_NA
        assert_eq!(RustOperCell::from_rust_oper(&elem11).unwrap(), RustOperCell::Err(XLERR_NA));
    }

    #[test]
    fn test_new_from_cell_matrix_empty_or_ragged() {
        let empty_matrix: Vec<Vec<RustOperCell>> = vec![];
        assert!(RustOper::new_from_cell_matrix(&empty_matrix).is_err());

        let empty_row_matrix: Vec<Vec<RustOperCell>> = vec![vec![]];
        assert!(RustOper::new_from_cell_matrix(&empty_row_matrix).is_err());

        let ragged_matrix: Vec<Vec<RustOperCell>> = vec![
            vec![RustOperCell::Num(1.0)],
            vec![RustOperCell::Num(2.0), RustOperCell::Num(3.0)],
        ];
        assert!(RustOper::new_from_cell_matrix(&ragged_matrix).is_err());
    }

    #[test]
    fn test_new_sref_and_as_sref() {
        let sref_val = XLREF12 { rwFirst: 0, rwLast: 0, colFirst: 1, colLast: 1 }; // B1

        // Test new_from_xlref12
        let roper1 = RustOper::new_from_xlref12(sref_val);
        assert!(roper1.is_sref());
        let retrieved_sref1 = roper1.as_sref().unwrap();
        assert_eq!(retrieved_sref1.rwFirst, sref_val.rwFirst);
        assert_eq!(retrieved_sref1.colLast, sref_val.colLast);

        // Test new_sref
        let roper2 = RustOper::new_sref(2, 4, 1, 3); // B3:D5
        assert!(roper2.is_sref());
        let retrieved_sref2 = roper2.as_sref().unwrap();
        assert_eq!(retrieved_sref2.rwFirst, 2);
        assert_eq!(retrieved_sref2.rwLast, 4);
        assert_eq!(retrieved_sref2.colFirst, 1);
        assert_eq!(retrieved_sref2.colLast, 3);

        // Test error case for as_sref
        let num_roper = RustOper::new_num(1.0);
        assert!(num_roper.as_sref().is_err());
        match num_roper.as_sref() {
            Err(RustOperError::TypeMismatch(msg)) => {
                assert!(msg.contains("Not an xltypeSRef"));
            }
            _ => panic!("Expected TypeMismatch error"),
        }
    }
}
