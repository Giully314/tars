add_library(tars)
target_sources(tars 
    PUBLIC
    FILE_SET CXX_MODULES FILES 
        tars/tars.cppm
        tars/tars_symbol.cppm 
        tars/tars_typetraits.cppm 
        tars/tars_algebraictraits.cppm 
        tars/tars_symbolicfunctions.cppm) 