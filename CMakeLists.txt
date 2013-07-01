project(plasmawp)

find_package(Qt4 REQUIRED)
find_package(KDE4 REQUIRED)
find_package(KDE4Workspace REQUIRED)
include(KDE4Defaults)
include(${QT_USE_FILE})

QT4_WRAP_CPP(HEADERS_MOC mysettings.h)
QT4_WRAP_UI(HEADERS_UI mysettings.ui)

add_definitions(${KDE4_DEFINITIONS})
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})


set(plasma-wp_SRCS plasma-wp.cpp mysettings.cpp)


kde4_add_ui_files(plasma-wp_SRCS mysettings.ui)
kde4_add_plugin(plasma_wallpaper-extra ${plasma-wp_SRCS} )
target_link_libraries(plasma_wallpaper-extra ${KDE4_PLASMA_LIBS} )


add_executable(main.run main.cpp mysettings.cpp ${HEADERS_MOC} ${HEADERS_UI})
target_link_libraries(main.run ${QT_LIBRARIES} ${KDE4_PLASMA_LIBS} itpp)
 
install(TARGETS plasma_wallpaper-extra DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-wallpaper-extra.desktop DESTINATION ${SERVICES_INSTALL_DIR})



SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Wiless Bytes") #required
SET(CPACK_PACKAGE_VENDOR "github.com/wiless")
 
INCLUDE(CPack)
 
