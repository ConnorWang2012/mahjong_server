cd ..
tolua++ -n event -o ../src/cpp/lua_bind/lua_bind_event.cc ../src/lua/tolua_pkg/event.pkg
pause
rem tolua -a -n pkgname -o myfile.c myfile.pkg