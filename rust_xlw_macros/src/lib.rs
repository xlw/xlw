extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, ItemFn, Lit, Meta, NestedMeta};

#[proc_macro_attribute]
pub fn xl_func(attr: TokenStream, item: TokenStream) -> TokenStream {
    // Parse the annotated function
    let func = parse_macro_input!(item as ItemFn);

    // --- Parse attributes of the macro itself (e.g., #[xl_func(name = "MyExcelFunc")]) ---
    let mut excel_func_name = func.sig.ident.to_string(); // Default to Rust function name
    let mut category = "RustXLW Functions".to_string();
    let mut description = "".to_string();
    let mut help_topic = "".to_string();
    let mut is_volatile = false;
    let mut is_thread_safe = false; // Default to false; Excel requires explicit opt-in for thread-safety
    let mut is_cluster_safe = false;
    let mut is_macro_sheet_equivalent = true; // Typically true for UDFs
    let mut is_asynchronous = false;

    let macro_attrs = parse_macro_input!(attr as syn::AttributeArgs);
    for attr_arg in macro_attrs {
        if let NestedMeta::Meta(Meta::NameValue(nv)) = attr_arg {
            let ident_str = nv.path.get_ident().map_or(String::new(), |i| i.to_string());
            if let Lit::Str(lit_str) = nv.lit {
                match ident_str.as_str() {
                    "name" => excel_func_name = lit_str.value(),
                    "category" => category = lit_str.value(),
                    "description" => description = lit_str.value(),
                    "help_topic" => help_topic = lit_str.value(),
                    _ => {} // Ignore unknown string attributes for now
                }
            } else if let Lit::Bool(lit_bool) = nv.lit {
                 match ident_str.as_str() {
                    "volatile" => is_volatile = lit_bool.value(),
                    "thread_safe" => is_thread_safe = lit_bool.value(),
                    "cluster_safe" => is_cluster_safe = lit_bool.value(),
                    "macro_sheet" => is_macro_sheet_equivalent = lit_bool.value(),
                    "asynchronous" => is_asynchronous = lit_bool.value(),
                    _ => {} // Ignore unknown bool attributes
                 }
            }
        }
    }

    let rust_func_name_str = func.sig.ident.to_string();
    // The wrapper function will have a unique name to avoid collisions.
    let wrapper_func_name = format!("xlw_wrapper_{}", rust_func_name_str);
    // let wrapper_ident = syn::Ident::new(&wrapper_func_name, func.sig.ident.span()); // Not used yet

    // --- Placeholder for argument parsing and type conversion ---
    // This will be expanded in the next step (generating the wrapper)
    // For now, let's assume a simple function like `fn add(a: f64, b: f64) -> f64`
    // and generate metadata for it. Actual argument parsing from `func.sig.inputs` is complex.

    // let num_args = func.sig.inputs.len(); // Not used yet
    let mut arg_names_vec: Vec<String> = Vec::new();
    let mut arg_types_vec: Vec<String> = Vec::new(); // Excel type codes
    // let mut arg_descs_vec: Vec<String> = Vec::new(); // Placeholder descriptions // Not used yet

    for (i, input) in func.sig.inputs.iter().enumerate() {
        if let syn::FnArg::Typed(pat_type) = input {
            if let syn::Pat::Ident(pat_ident) = &*pat_type.pat {
                arg_names_vec.push(pat_ident.ident.to_string());
            } else {
                arg_names_vec.push(format!("arg{}", i));
            }
            // THIS IS A GROSS SIMPLIFICATION FOR TYPE MAPPING - NEEDS PROPER HANDLING
            let ty_str = quote!(#pat_type.ty).to_string();
            if ty_str.contains("f64") { arg_types_vec.push("B".to_string()); } // double
            else if ty_str.contains("i32") || ty_str.contains("i16") { arg_types_vec.push("E".to_string()); } // short int
            else if ty_str.contains("String") || ty_str.contains("str") { arg_types_vec.push("C%".to_string()); } // string (C% for wide string)
            else if ty_str.contains("bool") { arg_types_vec.push("L".to_string()); } // boolean
            else { arg_types_vec.push("P".to_string()); } // Default to LPXLOPER12 / RustOper
            // arg_descs_vec.push(format!("Argument {}", i+1)); // Not used yet
        }
    }

    // THIS IS A GROSS SIMPLIFICATION FOR RETURN TYPE MAPPING
    let mut return_type_code = "P".to_string(); // Default to LPXLOPER12 / RustOper
    if let syn::ReturnType::Type(_, ty) = &func.sig.output {
        let ty_str = quote!(#ty).to_string();
        if ty_str.contains("f64") { return_type_code = "B".to_string(); }
        else if ty_str.contains("i32") || ty_str.contains("i16") { return_type_code = "E".to_string(); }
        else if ty_str.contains("String") || ty_str.contains("str") { return_type_code = "C%".to_string(); }
        else if ty_str.contains("bool") { return_type_code = "L".to_string(); }
    }


    // --- Generate the wrapper function (placeholder for now) ---
    // This will be expanded in Step 18.
    // For now, just output the original function.
    // let generated_wrapper = quote! { // Not used yet
        // Placeholder for the actual extern "C" wrapper function
        // that will convert arguments, call #func, and convert return type.
    // };

    // --- Generate static registration code (placeholder for now) ---
    // This will be expanded in Step 19.
    // It needs to call `rust_xlw::registration::add_function_to_registry`.
    // This requires the main `rust_xlw` crate to be a dependency for the generated code,
    // or for the registration data to be collected in some other way.
    // Using `ctor` crate is a common way to run code at library load time.

    // For now, we just print the metadata to assist in debugging the macro.
    // In a real macro, this would generate code that calls add_function_to_registry.
    // let debug_metadata_str = format!( // Not used yet
    //     "Excel Name: {}, Rust Name: {}, Wrapper: {}, Args: {:?}, ArgTypes: {:?}, Return: {}, Volatile: {}, ThreadSafe: {}",
    //     excel_func_name, rust_func_name_str, wrapper_func_name, arg_names_vec, arg_types_vec, return_type_code, is_volatile, is_thread_safe
    // );

    // Combine the original function with any generated code.
    // For this step, we are mostly parsing and preparing.
    // The actual code generation for wrapper and registration call is deferred.
    let output = quote! {
        #func // Output the original function

        // TODO in later steps:
        // #generated_wrapper
        // ... code to call add_function_to_registry with the parsed metadata ...

        // Temporary: print metadata during compilation for debugging macro
        // const _: &str = #debug_metadata_str;
        // Using compile_error! to print is a common trick, but only for errors.
        // For now, this macro won't add any new *functional* code to the user's crate,
        // it just parses and prepares data.
    };

    output.into()
}
