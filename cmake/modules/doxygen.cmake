option(BUILD_DOXYGEN "Enable Doxygen documentation generation" ON)

if(BUILD_DOXYGEN)
    add_custom_target(doc_doxygen
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR} doxygen ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
    )
endif()