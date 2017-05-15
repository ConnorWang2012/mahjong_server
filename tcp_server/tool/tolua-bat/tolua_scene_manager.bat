cd ..
tolua++ -n scene_manager -o ../src/cpp/lua_bind/lua_bind_scene_manager.cc ../src/lua/tolua_pkg/scene_manager.pkg
pause
rem tolua -a -n pkgname -o myfile.c myfile.pkg