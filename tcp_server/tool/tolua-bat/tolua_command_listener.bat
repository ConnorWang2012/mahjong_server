cd ..
tolua++ -n command_listener -o ../src/cpp/lua_bind/lua_bind_command_listener.cc ../src/lua/tolua_pkg/command_listener.pkg
pause
rem tolua -a -n pkgname -o myfile.c myfile.pkg