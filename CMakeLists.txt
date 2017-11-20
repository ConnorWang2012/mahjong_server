# Author : connor
# Copyright (c) 2017-2020 ConnorAndTheirFriendsCompany.Inc.
# mahjong server

cmake_minimum_required (VERSION 3.0)

project (mahjong_server)

# define some variables

set(APP_NAME mahjong_server)

# the version number
set(MAHJONG_SERVER_VERSION 1.0)

set(SERVER_MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tcp_server)

# debug or release
if (NOT CMAKE_BUILD_TYPE)
  if(DEBUG_MODE)
    set(CMAKE_BUILD_TYPE DEBUG)
  else(DEBUG_MODE)
    set(CMAKE_BUILD_TYPE RELEASE)
  endif(DEBUG_MODE)
endif(NOT CMAKE_BUILD_TYPE)

# include dir
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/cpp_redis/src/include
  ${CMAKE_CURRENT_SOURCE_DIR}/libevent/src/include
  ${CMAKE_CURRENT_SOURCE_DIR}/libevent/src/compat
  ${CMAKE_CURRENT_SOURCE_DIR}/tcp_server/src
  ${CMAKE_CURRENT_SOURCE_DIR}/tcp_server/src/customer
  ${CMAKE_CURRENT_SOURCE_DIR}/tcp_server/src/framework
  ${CMAKE_CURRENT_SOURCE_DIR}/tcp_server/src/framework/network
  ${CMAKE_CURRENT_SOURCE_DIR}/tcp_server/src/framework/util/google
)

# add src
#add_subdirectory(cpp_redis/src)
#add_subdirectory(libevent/src)
#add_subdirectory(tcp_server/src)

set(ALL_SRC
  tcp_server/main.cpp
  tcp_server/src/framework/cache/cache_proxy.cc
  tcp_server/src/framework/event/command.cc
  tcp_server/src/framework/event/command_listener.cc
  tcp_server/src/framework/event/command_manager.cc
  tcp_server/src/framework/event/event_listener.cc
  tcp_server/src/framework/event/event_manager.cc
  tcp_server/src/framework/log/mylog.cc
  tcp_server/src/framework/network/network_manager.cc
  tcp_server/src/framework/network/google/protobuf/descriptor.cc
  tcp_server/src/framework/network/google/protobuf/descriptor.pb.cc
  tcp_server/src/framework/network/google/protobuf/descriptor_database.cc
  tcp_server/src/framework/network/google/protobuf/dynamic_message.cc
  tcp_server/src/framework/network/google/protobuf/extension_set.cc
  tcp_server/src/framework/network/google/protobuf/extension_set_heavy.cc
  tcp_server/src/framework/network/google/protobuf/generated_message_reflection.cc
  tcp_server/src/framework/network/google/protobuf/generated_message_util.cc
  tcp_server/src/framework/network/google/protobuf/message.cc  
  tcp_server/src/framework/network/google/protobuf/message_lite.cc
  tcp_server/src/framework/network/google/protobuf/reflection_ops.cc
  tcp_server/src/framework/network/google/protobuf/repeated_field.cc
  tcp_server/src/framework/network/google/protobuf/service.cc
  tcp_server/src/framework/network/google/protobuf/text_format.cc
  tcp_server/src/framework/network/google/protobuf/unknown_field_set.cc
  tcp_server/src/framework/network/google/protobuf/wire_format.cc
  tcp_server/src/framework/network/google/protobuf/wire_format_lite.cc  
  tcp_server/src/framework/network/google/protobuf/io/coded_stream.cc
  tcp_server/src/framework/network/google/protobuf/io/gzip_stream.cc
  tcp_server/src/framework/network/google/protobuf/io/printer.cc
  tcp_server/src/framework/network/google/protobuf/io/strtod.cc
  tcp_server/src/framework/network/google/protobuf/io/tokenizer.cc
  tcp_server/src/framework/network/google/protobuf/io/zero_copy_stream.cc
  tcp_server/src/framework/network/google/protobuf/io/zero_copy_stream_impl.cc
  tcp_server/src/framework/network/google/protobuf/io/zero_copy_stream_impl_lite.cc
  tcp_server/src/framework/network/google/protobuf/stubs/atomicops_internals_x86_gcc.cc
  tcp_server/src/framework/network/google/protobuf/stubs/atomicops_internals_x86_msvc.cc
  tcp_server/src/framework/network/google/protobuf/stubs/common.cc
  tcp_server/src/framework/network/google/protobuf/stubs/once.cc
  tcp_server/src/framework/network/google/protobuf/stubs/stringprintf.cc
  tcp_server/src/framework/network/google/protobuf/stubs/structurally_valid.cc
  tcp_server/src/framework/network/google/protobuf/stubs/strutil.cc
  tcp_server/src/framework/network/google/protobuf/stubs/substitute.cc
  tcp_server/src/framework/service/runtime/server.cc
  tcp_server/src/framework/util/chess_card_algorithm.cc
  tcp_server/src/framework/util/google/absl/base/dynamic_annotations.cc
  tcp_server/src/framework/util/google/absl/base/internal/cycleclock.cc
  tcp_server/src/framework/util/google/absl/base/internal/log_severity.cc
  tcp_server/src/framework/util/google/absl/base/internal/low_level_alloc.cc
  tcp_server/src/framework/util/google/absl/base/internal/malloc_extension.cc
  tcp_server/src/framework/util/google/absl/base/internal/malloc_hook.cc
  tcp_server/src/framework/util/google/absl/base/internal/raw_logging.cc
  tcp_server/src/framework/util/google/absl/base/internal/spinlock.cc
  tcp_server/src/framework/util/google/absl/base/internal/spinlock_wait.cc
  tcp_server/src/framework/util/google/absl/base/internal/sysinfo.cc
  tcp_server/src/framework/util/google/absl/base/internal/thread_identity.cc
  tcp_server/src/framework/util/google/absl/base/internal/throw_delegate.cc
  tcp_server/src/framework/util/google/absl/base/internal/unscaledcycleclock.cc
  tcp_server/src/framework/util/google/absl/container/internal/test_instance_tracker.cc
  tcp_server/src/framework/util/google/absl/debugging/leak_check.cc
  tcp_server/src/framework/util/google/absl/debugging/leak_check_disable.cc
  tcp_server/src/framework/util/google/absl/debugging/stacktrace.cc
  tcp_server/src/framework/util/google/absl/debugging/internal/address_is_readable.cc
  tcp_server/src/framework/util/google/absl/debugging/internal/elf_mem_image.cc
  tcp_server/src/framework/util/google/absl/debugging/internal/vdso_support.cc
  tcp_server/src/framework/util/google/absl/numeric/int128.cc
  tcp_server/src/framework/util/google/absl/strings/internal/utf8.cc
  tcp_server/src/framework/util/google/absl/strings/internal/memutil.cc
  tcp_server/src/framework/util/google/absl/strings/ascii.cc
  tcp_server/src/framework/util/google/absl/strings/escaping.cc
  tcp_server/src/framework/util/google/absl/strings/match.cc
  tcp_server/src/framework/util/google/absl/strings/numbers.cc
  tcp_server/src/framework/util/google/absl/strings/str_cat.cc
  tcp_server/src/framework/util/google/absl/strings/string_view.cc
  tcp_server/src/framework/util/google/absl/strings/str_replace.cc
  tcp_server/src/framework/util/google/absl/strings/str_split.cc
  tcp_server/src/framework/util/google/absl/strings/substitute.cc
#  tcp_server/src/framework/util/google/absl/synchronization/barrier.cc
#  tcp_server/src/framework/util/google/absl/synchronization/mutex.cc
#  tcp_server/src/framework/util/google/absl/synchronization/notification.cc
#  tcp_server/src/framework/util/google/absl/synchronization/internal/create_thread_identity.cc
#  tcp_server/src/framework/util/google/absl/synchronization/internal/graphcycles.cc
#  tcp_server/src/framework/util/google/absl/synchronization/internal/mutex_nonprod.cc
#  tcp_server/src/framework/util/google/absl/synchronization/internal/per_thread_sem.cc
#  tcp_server/src/framework/util/google/absl/synchronization/internal/waiter.cc
#  tcp_server/src/framework/util/google/absl/time/clock.cc
#  tcp_server/src/framework/util/google/absl/time/duration.cc
#  tcp_server/src/framework/util/google/absl/time/format.cc
#  tcp_server/src/framework/util/google/absl/time/time.cc
  tcp_server/src/framework/util/google/absl/types/bad_any_cast.cc
  tcp_server/src/framework/util/google/absl/types/bad_optional_access.cc
  tcp_server/src/framework/util/google/absl/types/optional.cc
  tcp_server/src/framework/util/google/absl/utility/utility.cc
  tcp_server/src/framework/util/tinyxml/tinyxml2.cpp
  tcp_server/src/customer/data/config_mgr.cc
  tcp_server/src/customer/data/data_manager.cc
  tcp_server/src/customer/msg/msg_manager.cc
  tcp_server/src/customer/msg/protocol/create_room_msg_protocol.pb.cc
  tcp_server/src/customer/msg/protocol/game_end_msg_protocol.pb.cc
  tcp_server/src/customer/msg/protocol/my_login_msg_protocol.pb.cc
  tcp_server/src/customer/msg/protocol/play_card_msg_protocol.pb.cc
  tcp_server/src/customer/msg/protocol/player_cards_msg_protocol.pb.cc
  tcp_server/src/customer/msg/protocol/player_msg_protocol.pb.cc
  tcp_server/src/customer/msg/protocol/room_msg_protocol.pb.cc
  tcp_server/src/customer/msg/protocol/room_operation_msg_protocol.pb.cc
  tcp_server/src/customer/msg/protocol/ting_card_msg_protocol.pb.cc
  tcp_server/src/customer/player/player.cc
  tcp_server/src/customer/player/player_manager.cc
  cpp_redis/src/cpp_redis/logger.cpp
  cpp_redis/src/cpp_redis/redis_client.cpp
  cpp_redis/src/cpp_redis/redis_subscriber.cpp
  cpp_redis/src/cpp_redis/reply.cpp
  cpp_redis/src/cpp_redis/builders/array_builder.cpp
  cpp_redis/src/cpp_redis/builders/builders_factory.cpp
  cpp_redis/src/cpp_redis/builders/bulk_string_builder.cpp
  cpp_redis/src/cpp_redis/builders/error_builder.cpp
  cpp_redis/src/cpp_redis/builders/integer_builder.cpp
  cpp_redis/src/cpp_redis/builders/reply_builder.cpp
  cpp_redis/src/cpp_redis/builders/simple_string_builder.cpp
  cpp_redis/src/cpp_redis/network/redis_connection.cpp
  cpp_redis/src/tacopie/error.cpp
  cpp_redis/src/tacopie/logger.cpp
  cpp_redis/src/tacopie/network/tcp_client.cpp
  cpp_redis/src/tacopie/network/unix/io_service.cpp
  cpp_redis/src/tacopie/network/unix/self_pipe.cpp
  cpp_redis/src/tacopie/network/unix/tcp_socket.cpp
  cpp_redis/src/tacopie/utils/thread_pool.cpp
  libevent/src/compat/sys/queue.h
  libevent/src/buffer.c
  libevent/src/bufferevent.c
# libevent/src/bufferevent_async.c
  libevent/src/bufferevent_filter.c
# libevent/src/bufferevent_openssl.c
  libevent/src/bufferevent_pair.c
  libevent/src/bufferevent_ratelim.c
  libevent/src/bufferevent_sock.c
# libevent/src/buffer_iocp.c
  libevent/src/devpoll.c
  libevent/src/epoll.c
  libevent/src/epoll_sub.c
  libevent/src/evdns.c
  libevent/src/event.c
# libevent/src/event_iocp.c
  libevent/src/event_tagging.c
  libevent/src/evmap.c
  libevent/src/evport.c
  libevent/src/evrpc.c
  libevent/src/evthread.c
  libevent/src/evthread_pthread.c
  libevent/src/evutil.c
  libevent/src/evutil_rand.c
  libevent/src/evutil_time.c
  libevent/src/http.c
  libevent/src/kqueue.c
  libevent/src/listener.c
  libevent/src/log.c
  libevent/src/poll.c
  libevent/src/select.c
  libevent/src/signal.c
  libevent/src/strlcpy.c
)

#list(APPEND ALL_SRC ${SERVER_MAIN_DIR}/main.cpp)

add_executable(${APP_NAME} ${ALL_SRC})

target_link_libraries(${APP_NAME} libzip.a)
target_link_libraries(${APP_NAME} pthread)