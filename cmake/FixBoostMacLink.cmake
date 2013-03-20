MACRO(FixBoostMacLink lib_name)

  foreach(lib boost_thread boost_chrono boost_system boost_date_time)
    add_custom_command(TARGET ${lib_name}
	POST_BUILD
	COMMAND ${CMAKE_INSTALL_NAME_TOOL} -change lib${lib}.dylib ${Boost_LIBRARY_DIRS}/lib${lib}.dylib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib${lib_name}.dylib
        WORKING_DIRECTORY ${CMAKE_CURRENT_BIN_DIR}
    )
  endforeach()

ENDMACRO(FixBoostMacLink)
