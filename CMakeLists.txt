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
kde4_add_plugin(plasma_wallpaper_plasma-wp ${plasma-wp_SRCS} )
target_link_libraries(plasma_wallpaper_plasma-wp ${KDE4_PLASMA_LIBS} )


add_executable(main.run main.cpp mysettings.cpp ${HEADERS_MOC} ${HEADERS_UI})
target_link_libraries(main.run ${QT_LIBRARIES} ${KDE4_PLASMA_LIBS})
 
install(TARGETS plasma_wallpaper_plasma-wp DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-wallpaper-plasma-wp.desktop DESTINATION ${SERVICES_INSTALL_DIR})
