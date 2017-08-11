// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: play_card_msg_protocol.proto

#ifndef PROTOBUF_play_5fcard_5fmsg_5fprotocol_2eproto__INCLUDED
#define PROTOBUF_play_5fcard_5fmsg_5fprotocol_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace gamer {
namespace protocol {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_play_5fcard_5fmsg_5fprotocol_2eproto();
void protobuf_AssignDesc_play_5fcard_5fmsg_5fprotocol_2eproto();
void protobuf_ShutdownFile_play_5fcard_5fmsg_5fprotocol_2eproto();

class PlayCardMsgProtocol;

// ===================================================================

class PlayCardMsgProtocol : public ::google::protobuf::Message {
 public:
  PlayCardMsgProtocol();
  virtual ~PlayCardMsgProtocol();

  PlayCardMsgProtocol(const PlayCardMsgProtocol& from);

  inline PlayCardMsgProtocol& operator=(const PlayCardMsgProtocol& from) {
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
  static const PlayCardMsgProtocol& default_instance();

  void Swap(PlayCardMsgProtocol* other);

  // implements Message ----------------------------------------------

  PlayCardMsgProtocol* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PlayCardMsgProtocol& from);
  void MergeFrom(const PlayCardMsgProtocol& from);
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

  // required int32 player_id = 1;
  inline bool has_player_id() const;
  inline void clear_player_id();
  static const int kPlayerIdFieldNumber = 1;
  inline ::google::protobuf::int32 player_id() const;
  inline void set_player_id(::google::protobuf::int32 value);

  // required int32 room_id = 2;
  inline bool has_room_id() const;
  inline void clear_room_id();
  static const int kRoomIdFieldNumber = 2;
  inline ::google::protobuf::int32 room_id() const;
  inline void set_room_id(::google::protobuf::int32 value);

  // required int32 cur_round = 3;
  inline bool has_cur_round() const;
  inline void clear_cur_round();
  static const int kCurRoundFieldNumber = 3;
  inline ::google::protobuf::int32 cur_round() const;
  inline void set_cur_round(::google::protobuf::int32 value);

  // required int32 operation_id = 4;
  inline bool has_operation_id() const;
  inline void clear_operation_id();
  static const int kOperationIdFieldNumber = 4;
  inline ::google::protobuf::int32 operation_id() const;
  inline void set_operation_id(::google::protobuf::int32 value);

  // optional int32 discard = 5 [default = 0];
  inline bool has_discard() const;
  inline void clear_discard();
  static const int kDiscardFieldNumber = 5;
  inline ::google::protobuf::int32 discard() const;
  inline void set_discard(::google::protobuf::int32 value);

  // optional int32 new_card = 6 [default = 0];
  inline bool has_new_card() const;
  inline void clear_new_card();
  static const int kNewCardFieldNumber = 6;
  inline ::google::protobuf::int32 new_card() const;
  inline void set_new_card(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:gamer.protocol.PlayCardMsgProtocol)
 private:
  inline void set_has_player_id();
  inline void clear_has_player_id();
  inline void set_has_room_id();
  inline void clear_has_room_id();
  inline void set_has_cur_round();
  inline void clear_has_cur_round();
  inline void set_has_operation_id();
  inline void clear_has_operation_id();
  inline void set_has_discard();
  inline void clear_has_discard();
  inline void set_has_new_card();
  inline void clear_has_new_card();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 player_id_;
  ::google::protobuf::int32 room_id_;
  ::google::protobuf::int32 cur_round_;
  ::google::protobuf::int32 operation_id_;
  ::google::protobuf::int32 discard_;
  ::google::protobuf::int32 new_card_;
  friend void  protobuf_AddDesc_play_5fcard_5fmsg_5fprotocol_2eproto();
  friend void protobuf_AssignDesc_play_5fcard_5fmsg_5fprotocol_2eproto();
  friend void protobuf_ShutdownFile_play_5fcard_5fmsg_5fprotocol_2eproto();

  void InitAsDefaultInstance();
  static PlayCardMsgProtocol* default_instance_;
};
// ===================================================================


// ===================================================================

// PlayCardMsgProtocol

// required int32 player_id = 1;
inline bool PlayCardMsgProtocol::has_player_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PlayCardMsgProtocol::set_has_player_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PlayCardMsgProtocol::clear_has_player_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PlayCardMsgProtocol::clear_player_id() {
  player_id_ = 0;
  clear_has_player_id();
}
inline ::google::protobuf::int32 PlayCardMsgProtocol::player_id() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.PlayCardMsgProtocol.player_id)
  return player_id_;
}
inline void PlayCardMsgProtocol::set_player_id(::google::protobuf::int32 value) {
  set_has_player_id();
  player_id_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.PlayCardMsgProtocol.player_id)
}

// required int32 room_id = 2;
inline bool PlayCardMsgProtocol::has_room_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PlayCardMsgProtocol::set_has_room_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PlayCardMsgProtocol::clear_has_room_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PlayCardMsgProtocol::clear_room_id() {
  room_id_ = 0;
  clear_has_room_id();
}
inline ::google::protobuf::int32 PlayCardMsgProtocol::room_id() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.PlayCardMsgProtocol.room_id)
  return room_id_;
}
inline void PlayCardMsgProtocol::set_room_id(::google::protobuf::int32 value) {
  set_has_room_id();
  room_id_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.PlayCardMsgProtocol.room_id)
}

// required int32 cur_round = 3;
inline bool PlayCardMsgProtocol::has_cur_round() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PlayCardMsgProtocol::set_has_cur_round() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PlayCardMsgProtocol::clear_has_cur_round() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PlayCardMsgProtocol::clear_cur_round() {
  cur_round_ = 0;
  clear_has_cur_round();
}
inline ::google::protobuf::int32 PlayCardMsgProtocol::cur_round() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.PlayCardMsgProtocol.cur_round)
  return cur_round_;
}
inline void PlayCardMsgProtocol::set_cur_round(::google::protobuf::int32 value) {
  set_has_cur_round();
  cur_round_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.PlayCardMsgProtocol.cur_round)
}

// required int32 operation_id = 4;
inline bool PlayCardMsgProtocol::has_operation_id() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PlayCardMsgProtocol::set_has_operation_id() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PlayCardMsgProtocol::clear_has_operation_id() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PlayCardMsgProtocol::clear_operation_id() {
  operation_id_ = 0;
  clear_has_operation_id();
}
inline ::google::protobuf::int32 PlayCardMsgProtocol::operation_id() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.PlayCardMsgProtocol.operation_id)
  return operation_id_;
}
inline void PlayCardMsgProtocol::set_operation_id(::google::protobuf::int32 value) {
  set_has_operation_id();
  operation_id_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.PlayCardMsgProtocol.operation_id)
}

// optional int32 discard = 5 [default = 0];
inline bool PlayCardMsgProtocol::has_discard() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void PlayCardMsgProtocol::set_has_discard() {
  _has_bits_[0] |= 0x00000010u;
}
inline void PlayCardMsgProtocol::clear_has_discard() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void PlayCardMsgProtocol::clear_discard() {
  discard_ = 0;
  clear_has_discard();
}
inline ::google::protobuf::int32 PlayCardMsgProtocol::discard() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.PlayCardMsgProtocol.discard)
  return discard_;
}
inline void PlayCardMsgProtocol::set_discard(::google::protobuf::int32 value) {
  set_has_discard();
  discard_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.PlayCardMsgProtocol.discard)
}

// optional int32 new_card = 6 [default = 0];
inline bool PlayCardMsgProtocol::has_new_card() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void PlayCardMsgProtocol::set_has_new_card() {
  _has_bits_[0] |= 0x00000020u;
}
inline void PlayCardMsgProtocol::clear_has_new_card() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void PlayCardMsgProtocol::clear_new_card() {
  new_card_ = 0;
  clear_has_new_card();
}
inline ::google::protobuf::int32 PlayCardMsgProtocol::new_card() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.PlayCardMsgProtocol.new_card)
  return new_card_;
}
inline void PlayCardMsgProtocol::set_new_card(::google::protobuf::int32 value) {
  set_has_new_card();
  new_card_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.PlayCardMsgProtocol.new_card)
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

#endif  // PROTOBUF_play_5fcard_5fmsg_5fprotocol_2eproto__INCLUDED
