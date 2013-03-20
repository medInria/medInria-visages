MACRO(FixBoostMacInstall)

  foreach(lib boost_thread boost_chrono boost_system boost_date_time)
    foreach(linkedlib boost_thread boost_chrono boost_system boost_date_time)
      execute_process(COMMAND ${CMAKE_INSTALL_NAME_TOOL} -change lib${linkedlib}.dylib ${Boost_LIBRARY_DIRS}/lib${linkedlib}.dylib ${Boost_LIBRARY_DIRS}/lib${lib}.dylib)
    endforeach()
  endforeach()

ENDMACRO(FixBoostMacInstall)
