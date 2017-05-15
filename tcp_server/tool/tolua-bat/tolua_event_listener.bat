cd ..
tolua++ -n event_listener -o ../src/cpp/lua_bind/lua_bind_event_listener.cc ../src/lua/tolua_pkg/event_listener.pkg
pause
rem tolua -a -n pkgname -o myfile.c myfile.pkg