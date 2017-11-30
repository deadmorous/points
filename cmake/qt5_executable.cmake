cmake_policy(SET CMP0020 NEW)

file (GLOB_RECURSE SOURCE_FILE_LIST RELATIVE ${PROJECT_SOURCE_DIR} *.cpp *.cxx *.c)
file (GLOB_RECURSE HEADER_FILES RELATIVE ${PROJECT_SOURCE_DIR} *.h *.hpp *.hxx)
file (GLOB_RECURSE RESOURCES RELATIVE ${PROJECT_SOURCE_DIR} *.qrc)
file (GLOB_RECURSE WINRC_FILES RELATIVE ${PROJECT_SOURCE_DIR} *.rc)
qt5_wrap_cpp (MOC_SOURCES ${HEADER_FILES})
qt5_add_resources (QRC_SOURCES ${RESOURCES})
qt5_create_translation (QM_FILE ${SOURCE_FILE_LIST} ${HEADER_FILES} ${TS_FILE})

source_group ("Generated Files" FILES ${MOC_SOURCES} ${QRC_SOURCES} ${QM_FILE})
source_group ("Translation Files" FILES ${TS_FILE})
add_executable(${PROJECT_NAME}
        ${CTM_WINGUI}
        ${SOURCE_FILE_LIST}
        ${HEADER_FILES}
        ${MOC_SOURCES}
        ${QRC_SOURCES}
        ${TS_FILE}
        ${QM_FILE}
        ${WINRC_FILES}
        )
