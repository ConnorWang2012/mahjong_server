// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: room_msg_protocol.proto

#ifndef PROTOBUF_room_5fmsg_5fprotocol_2eproto__INCLUDED
#define PROTOBUF_room_5fmsg_5fprotocol_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "table_msg_protocol.pb.h"
// @@protoc_insertion_point(includes)

namespace gamer {
namespace protocol {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_room_5fmsg_5fprotocol_2eproto();
void protobuf_AssignDesc_room_5fmsg_5fprotocol_2eproto();
void protobuf_ShutdownFile_room_5fmsg_5fprotocol_2eproto();

class RoomMsgProtocol;

// ===================================================================

class RoomMsgProtocol : public ::google::protobuf::Message {
 public:
  RoomMsgProtocol();
  virtual ~RoomMsgProtocol();

  RoomMsgProtocol(const RoomMsgProtocol& from);

  inline RoomMsgProtocol& operator=(const RoomMsgProtocol& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RoomMsgProtocol& default_instance();

  void Swap(RoomMsgProtocol* other);

  // implements Message ----------------------------------------------

  RoomMsgProtocol* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RoomMsgProtocol& from);
  void MergeFrom(const RoomMsgProtocol& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 room_id = 1;
  inline bool has_room_id() const;
  inline void clear_room_id();
  static const int kRoomIdFieldNumber = 1;
  inline ::google::protobuf::uint32 room_id() const;
  inline void set_room_id(::google::protobuf::uint32 value);

  // required uint32 room_owner_id = 2;
  inline bool has_room_owner_id() const;
  inline void clear_room_owner_id();
  static const int kRoomOwnerIdFieldNumber = 2;
  inline ::google::protobuf::uint32 room_owner_id() const;
  inline void set_room_owner_id(::google::protobuf::uint32 value);

  // optional uint32 room_type = 3;
  inline bool has_room_type() const;
  inline void clear_room_type();
  static const int kRoomTypeFieldNumber = 3;
  inline ::google::protobuf::uint32 room_type() const;
  inline void set_room_type(::google::protobuf::uint32 value);

  // optional uint32 players_num = 4;
  inline bool has_players_num() const;
  inline void clear_players_num();
  static const int kPlayersNumFieldNumber = 4;
  inline ::google::protobuf::uint32 players_num() const;
  inline void set_players_num(::google::protobuf::uint32 value);

  // repeated .gamer.protocol.TableMsgProtocol table_list = 5;
  inline int table_list_size() const;
  inline void clear_table_list();
  static const int kTableListFieldNumber = 5;
  inline const ::gamer::protocol::TableMsgProtocol& table_list(int index) const;
  inline ::gamer::protocol::TableMsgProtocol* mutable_table_list(int index);
  inline ::gamer::protocol::TableMsgProtocol* add_table_list();
  inline const ::google::protobuf::RepeatedPtrField< ::gamer::protocol::TableMsgProtocol >&
      table_list() const;
  inline ::google::protobuf::RepeatedPtrField< ::gamer::protocol::TableMsgProtocol >*
      mutable_table_list();

  // @@protoc_insertion_point(class_scope:gamer.protocol.RoomMsgProtocol)
 private:
  inline void set_has_room_id();
  inline void clear_has_room_id();
  inline void set_has_room_owner_id();
  inline void clear_has_room_owner_id();
  inline void set_has_room_type();
  inline void clear_has_room_type();
  inline void set_has_players_num();
  inline void clear_has_players_num();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 room_id_;
  ::google::protobuf::uint32 room_owner_id_;
  ::google::protobuf::uint32 room_type_;
  ::google::protobuf::uint32 players_num_;
  ::google::protobuf::RepeatedPtrField< ::gamer::protocol::TableMsgProtocol > table_list_;
  friend void  protobuf_AddDesc_room_5fmsg_5fprotocol_2eproto();
  friend void protobuf_AssignDesc_room_5fmsg_5fprotocol_2eproto();
  friend void protobuf_ShutdownFile_room_5fmsg_5fprotocol_2eproto();

  void InitAsDefaultInstance();
  static RoomMsgProtocol* default_instance_;
};
// ===================================================================


// ===================================================================

// RoomMsgProtocol

// required uint32 room_id = 1;
inline bool RoomMsgProtocol::has_room_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RoomMsgProtocol::set_has_room_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RoomMsgProtocol::clear_has_room_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RoomMsgProtocol::clear_room_id() {
  room_id_ = 0u;
  clear_has_room_id();
}
inline ::google::protobuf::uint32 RoomMsgProtocol::room_id() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.RoomMsgProtocol.room_id)
  return room_id_;
}
inline void RoomMsgProtocol::set_room_id(::google::protobuf::uint32 value) {
  set_has_room_id();
  room_id_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.RoomMsgProtocol.room_id)
}

// required uint32 room_owner_id = 2;
inline bool RoomMsgProtocol::has_room_owner_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RoomMsgProtocol::set_has_room_owner_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RoomMsgProtocol::clear_has_room_owner_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RoomMsgProtocol::clear_room_owner_id() {
  room_owner_id_ = 0u;
  clear_has_room_owner_id();
}
inline ::google::protobuf::uint32 RoomMsgProtocol::room_owner_id() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.RoomMsgProtocol.room_owner_id)
  return room_owner_id_;
}
inline void RoomMsgProtocol::set_room_owner_id(::google::protobuf::uint32 value) {
  set_has_room_owner_id();
  room_owner_id_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.RoomMsgProtocol.room_owner_id)
}

// optional uint32 room_type = 3;
inline bool RoomMsgProtocol::has_room_type() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void RoomMsgProtocol::set_has_room_type() {
  _has_bits_[0] |= 0x00000004u;
}
inline void RoomMsgProtocol::clear_has_room_type() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void RoomMsgProtocol::clear_room_type() {
  room_type_ = 0u;
  clear_has_room_type();
}
inline ::google::protobuf::uint32 RoomMsgProtocol::room_type() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.RoomMsgProtocol.room_type)
  return room_type_;
}
inline void RoomMsgProtocol::set_room_type(::google::protobuf::uint32 value) {
  set_has_room_type();
  room_type_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.RoomMsgProtocol.room_type)
}

// optional uint32 players_num = 4;
inline bool RoomMsgProtocol::has_players_num() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void RoomMsgProtocol::set_has_players_num() {
  _has_bits_[0] |= 0x00000008u;
}
inline void RoomMsgProtocol::clear_has_players_num() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void RoomMsgProtocol::clear_players_num() {
  players_num_ = 0u;
  clear_has_players_num();
}
inline ::google::protobuf::uint32 RoomMsgProtocol::players_num() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.RoomMsgProtocol.players_num)
  return players_num_;
}
inline void RoomMsgProtocol::set_players_num(::google::protobuf::uint32 value) {
  set_has_players_num();
  players_num_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.RoomMsgProtocol.players_num)
}

// repeated .gamer.protocol.TableMsgProtocol table_list = 5;
inline int RoomMsgProtocol::table_list_size() const {
  return table_list_.size();
}
inline void RoomMsgProtocol::clear_table_list() {
  table_list_.Clear();
}
inline const ::gamer::protocol::TableMsgProtocol& RoomMsgProtocol::table_list(int index) const {
  // @@protoc_insertion_point(field_get:gamer.protocol.RoomMsgProtocol.table_list)
  return table_list_.Get(index);
}
inline ::gamer::protocol::TableMsgProtocol* RoomMsgProtocol::mutable_table_list(int index) {
  // @@protoc_insertion_point(field_mutable:gamer.protocol.RoomMsgProtocol.table_list)
  return table_list_.Mutable(index);
}
inline ::gamer::protocol::TableMsgProtocol* RoomMsgProtocol::add_table_list() {
  // @@protoc_insertion_point(field_add:gamer.protocol.RoomMsgProtocol.table_list)
  return table_list_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::gamer::protocol::TableMsgProtocol >&
RoomMsgProtocol::table_list() const {
  // @@protoc_insertion_point(field_list:gamer.protocol.RoomMsgProtocol.table_list)
  return table_list_;
}
inline ::google::protobuf::RepeatedPtrField< ::gamer::protocol::TableMsgProtocol >*
RoomMsgProtocol::mutable_table_list() {
  // @@protoc_insertion_point(field_mutable_list:gamer.protocol.RoomMsgProtocol.table_list)
  return &table_list_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace protocol
}  // namespace gamer

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_room_5fmsg_5fprotocol_2eproto__INCLUDED