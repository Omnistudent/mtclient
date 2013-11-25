# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# For each target create a dummy rule so the target does not have to exist
/usr/lib/libz.dylib:
/usr/local/lib/libIrrlicht.a:
/opt/local/lib/libjpeg.dylib:
/usr/lib/libbz2.dylib:
/opt/local/lib/libpng.dylib:
/opt/local/lib/libSM.dylib:
/opt/local/lib/libICE.dylib:
/opt/local/lib/libX11.dylib:
/opt/local/lib/libXext.dylib:
/opt/local/lib/libvorbisfile.dylib:
/opt/local/lib/libvorbis.dylib:
/usr/lib/libsqlite3.dylib:
/Users/security/mtclient/src/lua/build/Debug/liblua.a:
/Users/security/mtclient/src/json/Debug/libjsoncpp.a:
/opt/local/lib/libXxf86vm.dylib:
/usr/lib/libcurl.dylib:
/Users/security/mtclient/src/lua/build/MinSizeRel/liblua.a:
/Users/security/mtclient/src/json/MinSizeRel/libjsoncpp.a:
/Users/security/mtclient/src/lua/build/RelWithDebInfo/liblua.a:
/Users/security/mtclient/src/json/RelWithDebInfo/libjsoncpp.a:
/Users/security/mtclient/src/lua/build/Release/liblua.a:
/Users/security/mtclient/src/json/Release/libjsoncpp.a:


# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.minetest.Debug:
PostBuild.lua.Debug: /Users/security/mtclient/bin/Debug/minetest
PostBuild.jsoncpp.Debug: /Users/security/mtclient/bin/Debug/minetest
/Users/security/mtclient/bin/Debug/minetest:\
	/usr/lib/libz.dylib\
	/usr/local/lib/libIrrlicht.a\
	/opt/local/lib/libjpeg.dylib\
	/usr/lib/libbz2.dylib\
	/opt/local/lib/libpng.dylib\
	/usr/lib/libz.dylib\
	/opt/local/lib/libSM.dylib\
	/opt/local/lib/libICE.dylib\
	/opt/local/lib/libX11.dylib\
	/opt/local/lib/libXext.dylib\
	/opt/local/lib/libvorbisfile.dylib\
	/opt/local/lib/libvorbis.dylib\
	/usr/lib/libsqlite3.dylib\
	/Users/security/mtclient/src/lua/build/Debug/liblua.a\
	/Users/security/mtclient/src/json/Debug/libjsoncpp.a\
	/opt/local/lib/libXxf86vm.dylib\
	/usr/lib/libcurl.dylib\
	/usr/local/lib/libIrrlicht.a\
	/opt/local/lib/libjpeg.dylib\
	/usr/lib/libbz2.dylib\
	/opt/local/lib/libpng.dylib\
	/opt/local/lib/libSM.dylib\
	/opt/local/lib/libICE.dylib\
	/opt/local/lib/libX11.dylib\
	/opt/local/lib/libXext.dylib\
	/opt/local/lib/libvorbisfile.dylib\
	/opt/local/lib/libvorbis.dylib\
	/usr/lib/libsqlite3.dylib\
	/opt/local/lib/libXxf86vm.dylib\
	/usr/lib/libcurl.dylib
	/bin/rm -f /Users/security/mtclient/bin/Debug/minetest


PostBuild.minetestserver.Debug:
PostBuild.jsoncpp.Debug: /Users/security/mtclient/bin/Debug/minetestserver
PostBuild.lua.Debug: /Users/security/mtclient/bin/Debug/minetestserver
/Users/security/mtclient/bin/Debug/minetestserver:\
	/usr/lib/libz.dylib\
	/usr/lib/libsqlite3.dylib\
	/Users/security/mtclient/src/json/Debug/libjsoncpp.a\
	/Users/security/mtclient/src/lua/build/Debug/liblua.a\
	/usr/lib/libcurl.dylib
	/bin/rm -f /Users/security/mtclient/bin/Debug/minetestserver


PostBuild.lua.Debug:
PostBuild.jsoncpp.Debug:
PostBuild.minetest.Release:
PostBuild.lua.Release: /Users/security/mtclient/bin/Release/minetest
PostBuild.jsoncpp.Release: /Users/security/mtclient/bin/Release/minetest
/Users/security/mtclient/bin/Release/minetest:\
	/usr/lib/libz.dylib\
	/usr/local/lib/libIrrlicht.a\
	/opt/local/lib/libjpeg.dylib\
	/usr/lib/libbz2.dylib\
	/opt/local/lib/libpng.dylib\
	/usr/lib/libz.dylib\
	/opt/local/lib/libSM.dylib\
	/opt/local/lib/libICE.dylib\
	/opt/local/lib/libX11.dylib\
	/opt/local/lib/libXext.dylib\
	/opt/local/lib/libvorbisfile.dylib\
	/opt/local/lib/libvorbis.dylib\
	/usr/lib/libsqlite3.dylib\
	/Users/security/mtclient/src/lua/build/Release/liblua.a\
	/Users/security/mtclient/src/json/Release/libjsoncpp.a\
	/opt/local/lib/libXxf86vm.dylib\
	/usr/lib/libcurl.dylib\
	/usr/local/lib/libIrrlicht.a\
	/opt/local/lib/libjpeg.dylib\
	/usr/lib/libbz2.dylib\
	/opt/local/lib/libpng.dylib\
	/opt/local/lib/libSM.dylib\
	/opt/local/lib/libICE.dylib\
	/opt/local/lib/libX11.dylib\
	/opt/local/lib/libXext.dylib\
	/opt/local/lib/libvorbisfile.dylib\
	/opt/local/lib/libvorbis.dylib\
	/usr/lib/libsqlite3.dylib\
	/opt/local/lib/libXxf86vm.dylib\
	/usr/lib/libcurl.dylib
	/bin/rm -f /Users/security/mtclient/bin/Release/minetest


PostBuild.minetestserver.Release:
PostBuild.jsoncpp.Release: /Users/security/mtclient/bin/Release/minetestserver
PostBuild.lua.Release: /Users/security/mtclient/bin/Release/minetestserver
/Users/security/mtclient/bin/Release/minetestserver:\
	/usr/lib/libz.dylib\
	/usr/lib/libsqlite3.dylib\
	/Users/security/mtclient/src/json/Release/libjsoncpp.a\
	/Users/security/mtclient/src/lua/build/Release/liblua.a\
	/usr/lib/libcurl.dylib
	/bin/rm -f /Users/security/mtclient/bin/Release/minetestserver


PostBuild.lua.Release:
PostBuild.jsoncpp.Release:
PostBuild.minetest.MinSizeRel:
PostBuild.lua.MinSizeRel: /Users/security/mtclient/bin/MinSizeRel/minetest
PostBuild.jsoncpp.MinSizeRel: /Users/security/mtclient/bin/MinSizeRel/minetest
/Users/security/mtclient/bin/MinSizeRel/minetest:\
	/usr/lib/libz.dylib\
	/usr/local/lib/libIrrlicht.a\
	/opt/local/lib/libjpeg.dylib\
	/usr/lib/libbz2.dylib\
	/opt/local/lib/libpng.dylib\
	/usr/lib/libz.dylib\
	/opt/local/lib/libSM.dylib\
	/opt/local/lib/libICE.dylib\
	/opt/local/lib/libX11.dylib\
	/opt/local/lib/libXext.dylib\
	/opt/local/lib/libvorbisfile.dylib\
	/opt/local/lib/libvorbis.dylib\
	/usr/lib/libsqlite3.dylib\
	/Users/security/mtclient/src/lua/build/MinSizeRel/liblua.a\
	/Users/security/mtclient/src/json/MinSizeRel/libjsoncpp.a\
	/opt/local/lib/libXxf86vm.dylib\
	/usr/lib/libcurl.dylib\
	/usr/local/lib/libIrrlicht.a\
	/opt/local/lib/libjpeg.dylib\
	/usr/lib/libbz2.dylib\
	/opt/local/lib/libpng.dylib\
	/opt/local/lib/libSM.dylib\
	/opt/local/lib/libICE.dylib\
	/opt/local/lib/libX11.dylib\
	/opt/local/lib/libXext.dylib\
	/opt/local/lib/libvorbisfile.dylib\
	/opt/local/lib/libvorbis.dylib\
	/usr/lib/libsqlite3.dylib\
	/opt/local/lib/libXxf86vm.dylib\
	/usr/lib/libcurl.dylib
	/bin/rm -f /Users/security/mtclient/bin/MinSizeRel/minetest


PostBuild.minetestserver.MinSizeRel:
PostBuild.jsoncpp.MinSizeRel: /Users/security/mtclient/bin/MinSizeRel/minetestserver
PostBuild.lua.MinSizeRel: /Users/security/mtclient/bin/MinSizeRel/minetestserver
/Users/security/mtclient/bin/MinSizeRel/minetestserver:\
	/usr/lib/libz.dylib\
	/usr/lib/libsqlite3.dylib\
	/Users/security/mtclient/src/json/MinSizeRel/libjsoncpp.a\
	/Users/security/mtclient/src/lua/build/MinSizeRel/liblua.a\
	/usr/lib/libcurl.dylib
	/bin/rm -f /Users/security/mtclient/bin/MinSizeRel/minetestserver


PostBuild.lua.MinSizeRel:
PostBuild.jsoncpp.MinSizeRel:
PostBuild.minetest.RelWithDebInfo:
PostBuild.lua.RelWithDebInfo: /Users/security/mtclient/bin/RelWithDebInfo/minetest
PostBuild.jsoncpp.RelWithDebInfo: /Users/security/mtclient/bin/RelWithDebInfo/minetest
/Users/security/mtclient/bin/RelWithDebInfo/minetest:\
	/usr/lib/libz.dylib\
	/usr/local/lib/libIrrlicht.a\
	/opt/local/lib/libjpeg.dylib\
	/usr/lib/libbz2.dylib\
	/opt/local/lib/libpng.dylib\
	/usr/lib/libz.dylib\
	/opt/local/lib/libSM.dylib\
	/opt/local/lib/libICE.dylib\
	/opt/local/lib/libX11.dylib\
	/opt/local/lib/libXext.dylib\
	/opt/local/lib/libvorbisfile.dylib\
	/opt/local/lib/libvorbis.dylib\
	/usr/lib/libsqlite3.dylib\
	/Users/security/mtclient/src/lua/build/RelWithDebInfo/liblua.a\
	/Users/security/mtclient/src/json/RelWithDebInfo/libjsoncpp.a\
	/opt/local/lib/libXxf86vm.dylib\
	/usr/lib/libcurl.dylib\
	/usr/local/lib/libIrrlicht.a\
	/opt/local/lib/libjpeg.dylib\
	/usr/lib/libbz2.dylib\
	/opt/local/lib/libpng.dylib\
	/opt/local/lib/libSM.dylib\
	/opt/local/lib/libICE.dylib\
	/opt/local/lib/libX11.dylib\
	/opt/local/lib/libXext.dylib\
	/opt/local/lib/libvorbisfile.dylib\
	/opt/local/lib/libvorbis.dylib\
	/usr/lib/libsqlite3.dylib\
	/opt/local/lib/libXxf86vm.dylib\
	/usr/lib/libcurl.dylib
	/bin/rm -f /Users/security/mtclient/bin/RelWithDebInfo/minetest


PostBuild.minetestserver.RelWithDebInfo:
PostBuild.jsoncpp.RelWithDebInfo: /Users/security/mtclient/bin/RelWithDebInfo/minetestserver
PostBuild.lua.RelWithDebInfo: /Users/security/mtclient/bin/RelWithDebInfo/minetestserver
/Users/security/mtclient/bin/RelWithDebInfo/minetestserver:\
	/usr/lib/libz.dylib\
	/usr/lib/libsqlite3.dylib\
	/Users/security/mtclient/src/json/RelWithDebInfo/libjsoncpp.a\
	/Users/security/mtclient/src/lua/build/RelWithDebInfo/liblua.a\
	/usr/lib/libcurl.dylib
	/bin/rm -f /Users/security/mtclient/bin/RelWithDebInfo/minetestserver


PostBuild.lua.RelWithDebInfo:
PostBuild.jsoncpp.RelWithDebInfo:
