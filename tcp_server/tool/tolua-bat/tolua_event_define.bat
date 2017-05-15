cd ..
tolua++ -n event_define -o ../src/cpp/lua_bind/lua_bind_event_define.cc ../src/lua/tolua_pkg/event_define.pkg
pause
rem tolua -a -n pkgname -o myfile.c myfile.pkg