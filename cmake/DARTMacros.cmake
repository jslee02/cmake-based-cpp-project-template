################################################################################
#APPEND_TO_CACHED_STRING(_string _cacheDesc [items...])
# Appends items to a cached list.
MACRO(APPEND_TO_CACHED_STRING _string _cacheDesc)
  FOREACH(newItem ${ARGN})
    SET(${_string} "${${_string}} ${newItem}" CACHE INTERNAL ${_cacheDesc} FORCE)
  ENDFOREACH(newItem ${ARGN})
  #STRING(STRIP ${${_string}} ${_string})
ENDMACRO(APPEND_TO_CACHED_STRING)

################################################################################
#generate_include_header_list(_var _target_dir _cacheDesc [headers...])
# Generate header file list to a cached list.
macro(generate_include_header_list _var _target_dir _cacheDesc)
set(${_var} "" CACHE INTERNAL ${_cacheDesc} FORCE)
foreach(header ${ARGN})
  get_filename_component(header ${header} NAME)
  append_to_cached_string(${_var}
                          ${_cacheDesc}"_HEADERS"
                          "#include \"${_target_dir}${header}\"\n")
endforeach()
endmacro(generate_include_header_list)
