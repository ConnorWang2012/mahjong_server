cd ..
tolua++ -n event_manager -o ../src/cpp/lua_bind/lua_bind_event_manager.cc ../src/lua/tolua_pkg/event_manager.pkg
pause
rem tolua -a -n pkgname -o myfile.c myfile.pkg