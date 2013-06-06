Description
=========

KDE Plasma wallpaper plugin with extra control. 

Requirements
------
Compiled and tested with the following setup
Qt: 4.8.3
KDE Development Platform: 4.10.3
kde4-config: 1.0


Note
------
Project is still under development and in an unusable stage. **Not recommended** for usage


Build
-------
Download the source ( or clone it)

$cd plasma-wp
$mkdir build
$cd build
$cmake .. -DCMAKE_INSTALL_PREFIX=`kde4-config --prefix`
$make install

Test
------
$kquitapp desktop-plasma
(after the desktop-plasma stops, start desktop-plasma again)
$desktop-plasma
