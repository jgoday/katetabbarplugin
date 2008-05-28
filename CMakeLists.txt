project(katetabs)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules )

# search packages used by KDE
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)

# The FindKDE4.cmake module sets _KDE4_PLATFORM_DEFINITIONS with
# definitions like _GNU_SOURCE that are needed on each platform.
set(CMAKE_REQUIRED_DEFINITIONS ${_KDE4_PLATFORM_DEFINITIONS})

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories (${QDBUS_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})


set(katetabs_SRCS 
    katetabsplugin.cpp
    katetabbar.cpp
)


kde4_add_plugin(katetabsplugin ${katetabs_SRCS})
target_link_libraries(katetabsplugin  ${KDE4_KDEUI_LIBS} kateinterfaces)

install(TARGETS katetabsplugin  DESTINATION ${PLUGIN_INSTALL_DIR} )
install(FILES katetabs-plugin.desktop  DESTINATION  ${SERVICES_INSTALL_DIR})