// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: table_msg_protocol.proto

#ifndef PROTOBUF_table_5fmsg_5fprotocol_2eproto__INCLUDED
#define PROTOBUF_table_5fmsg_5fprotocol_2eproto__INCLUDED

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
#include "player_cards_msg_protocol.pb.h"
#include "player_msg_protocol.pb.h"
// @@protoc_insertion_point(includes)

namespace gamer {
namespace protocol {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_table_5fmsg_5fprotocol_2eproto();
void protobuf_AssignDesc_table_5fmsg_5fprotocol_2eproto();
void protobuf_ShutdownFile_table_5fmsg_5fprotocol_2eproto();

class TableMsgProtocol;

// ===================================================================

class TableMsgProtocol : public ::google::protobuf::Message {
 public:
  TableMsgProtocol();
  virtual ~TableMsgProtocol();

  TableMsgProtocol(const TableMsgProtocol& from);

  inline TableMsgProtocol& operator=(const TableMsgProtocol& from) {
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
  static const TableMsgProtocol& default_instance();

  void Swap(TableMsgProtocol* other);

  // implements Message ----------------------------------------------

  TableMsgProtocol* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TableMsgProtocol& from);
  void MergeFrom(const TableMsgProtocol& from);
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

  // required uint32 table_id = 1;
  inline bool has_table_id() const;
  inline void clear_table_id();
  static const int kTableIdFieldNumber = 1;
  inline ::google::protobuf::uint32 table_id() const;
  inline void set_table_id(::google::protobuf::uint32 value);

  // optional uint32 cur_round = 2;
  inline bool has_cur_round() const;
  inline void clear_cur_round();
  static const int kCurRoundFieldNumber = 2;
  inline ::google::protobuf::uint32 cur_round() const;
  inline void set_cur_round(::google::protobuf::uint32 value);

  // optional uint32 total_round = 3;
  inline bool has_total_round() const;
  inline void clear_total_round();
  static const int kTotalRoundFieldNumber = 3;
  inline ::google::protobuf::uint32 total_round() const;
  inline void set_total_round(::google::protobuf::uint32 value);

  // optional uint32 remain_cards_num = 4;
  inline bool has_remain_cards_num() const;
  inline void clear_remain_cards_num();
  static const int kRemainCardsNumFieldNumber = 4;
  inline ::google::protobuf::uint32 remain_cards_num() const;
  inline void set_remain_cards_num(::google::protobuf::uint32 value);

  // optional uint32 banker_id = 5;
  inline bool has_banker_id() const;
  inline void clear_banker_id();
  static const int kBankerIdFieldNumber = 5;
  inline ::google::protobuf::uint32 banker_id() const;
  inline void set_banker_id(::google::protobuf::uint32 value);

  // optional uint32 banker_is_same_time = 6;
  inline bool has_banker_is_same_time() const;
  inline void clear_banker_is_same_time();
  static const int kBankerIsSameTimeFieldNumber = 6;
  inline ::google::protobuf::uint32 banker_is_same_time() const;
  inline void set_banker_is_same_time(::google::protobuf::uint32 value);

  // optional uint32 operating_player_id = 7;
  inline bool has_operating_player_id() const;
  inline void clear_operating_player_id();
  static const int kOperatingPlayerIdFieldNumber = 7;
  inline ::google::protobuf::uint32 operating_player_id() const;
  inline void set_operating_player_id(::google::protobuf::uint32 value);

  // optional uint32 operation_id = 8;
  inline bool has_operation_id() const;
  inline void clear_operation_id();
  static const int kOperationIdFieldNumber = 8;
  inline ::google::protobuf::uint32 operation_id() const;
  inline void set_operation_id(::google::protobuf::uint32 value);

  // repeated uint32 remain_cards = 9;
  inline int remain_cards_size() const;
  inline void clear_remain_cards();
  static const int kRemainCardsFieldNumber = 9;
  inline ::google::protobuf::uint32 remain_cards(int index) const;
  inline void set_remain_cards(int index, ::google::protobuf::uint32 value);
  inline void add_remain_cards(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      remain_cards() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_remain_cards();

  // repeated .gamer.protocol.PlayerCardsMsgProtocol player_cards = 10;
  inline int player_cards_size() const;
  inline void clear_player_cards();
  static const int kPlayerCardsFieldNumber = 10;
  inline const ::gamer::protocol::PlayerCardsMsgProtocol& player_cards(int index) const;
  inline ::gamer::protocol::PlayerCardsMsgProtocol* mutable_player_cards(int index);
  inline ::gamer::protocol::PlayerCardsMsgProtocol* add_player_cards();
  inline const ::google::protobuf::RepeatedPtrField< ::gamer::protocol::PlayerCardsMsgProtocol >&
      player_cards() const;
  inline ::google::protobuf::RepeatedPtrField< ::gamer::protocol::PlayerCardsMsgProtocol >*
      mutable_player_cards();

  // repeated .gamer.protocol.PlayerMsgProtocol players = 11;
  inline int players_size() const;
  inline void clear_players();
  static const int kPlayersFieldNumber = 11;
  inline const ::gamer::protocol::PlayerMsgProtocol& players(int index) const;
  inline ::gamer::protocol::PlayerMsgProtocol* mutable_players(int index);
  inline ::gamer::protocol::PlayerMsgProtocol* add_players();
  inline const ::google::protobuf::RepeatedPtrField< ::gamer::protocol::PlayerMsgProtocol >&
      players() const;
  inline ::google::protobuf::RepeatedPtrField< ::gamer::protocol::PlayerMsgProtocol >*
      mutable_players();

  // @@protoc_insertion_point(class_scope:gamer.protocol.TableMsgProtocol)
 private:
  inline void set_has_table_id();
  inline void clear_has_table_id();
  inline void set_has_cur_round();
  inline void clear_has_cur_round();
  inline void set_has_total_round();
  inline void clear_has_total_round();
  inline void set_has_remain_cards_num();
  inline void clear_has_remain_cards_num();
  inline void set_has_banker_id();
  inline void clear_has_banker_id();
  inline void set_has_banker_is_same_time();
  inline void clear_has_banker_is_same_time();
  inline void set_has_operating_player_id();
  inline void clear_has_operating_player_id();
  inline void set_has_operation_id();
  inline void clear_has_operation_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 table_id_;
  ::google::protobuf::uint32 cur_round_;
  ::google::protobuf::uint32 total_round_;
  ::google::protobuf::uint32 remain_cards_num_;
  ::google::protobuf::uint32 banker_id_;
  ::google::protobuf::uint32 banker_is_same_time_;
  ::google::protobuf::uint32 operating_player_id_;
  ::google::protobuf::uint32 operation_id_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > remain_cards_;
  ::google::protobuf::RepeatedPtrField< ::gamer::protocol::PlayerCardsMsgProtocol > player_cards_;
  ::google::protobuf::RepeatedPtrField< ::gamer::protocol::PlayerMsgProtocol > players_;
  friend void  protobuf_AddDesc_table_5fmsg_5fprotocol_2eproto();
  friend void protobuf_AssignDesc_table_5fmsg_5fprotocol_2eproto();
  friend void protobuf_ShutdownFile_table_5fmsg_5fprotocol_2eproto();

  void InitAsDefaultInstance();
  static TableMsgProtocol* default_instance_;
};
// ===================================================================


// ===================================================================

// TableMsgProtocol

// required uint32 table_id = 1;
inline bool TableMsgProtocol::has_table_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TableMsgProtocol::set_has_table_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TableMsgProtocol::clear_has_table_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TableMsgProtocol::clear_table_id() {
  table_id_ = 0u;
  clear_has_table_id();
}
inline ::google::protobuf::uint32 TableMsgProtocol::table_id() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.TableMsgProtocol.table_id)
  return table_id_;
}
inline void TableMsgProtocol::set_table_id(::google::protobuf::uint32 value) {
  set_has_table_id();
  table_id_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.TableMsgProtocol.table_id)
}

// optional uint32 cur_round = 2;
inline bool TableMsgProtocol::has_cur_round() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TableMsgProtocol::set_has_cur_round() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TableMsgProtocol::clear_has_cur_round() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TableMsgProtocol::clear_cur_round() {
  cur_round_ = 0u;
  clear_has_cur_round();
}
inline ::google::protobuf::uint32 TableMsgProtocol::cur_round() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.TableMsgProtocol.cur_round)
  return cur_round_;
}
inline void TableMsgProtocol::set_cur_round(::google::protobuf::uint32 value) {
  set_has_cur_round();
  cur_round_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.TableMsgProtocol.cur_round)
}

// optional uint32 total_round = 3;
inline bool TableMsgProtocol::has_total_round() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TableMsgProtocol::set_has_total_round() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TableMsgProtocol::clear_has_total_round() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TableMsgProtocol::clear_total_round() {
  total_round_ = 0u;
  clear_has_total_round();
}
inline ::google::protobuf::uint32 TableMsgProtocol::total_round() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.TableMsgProtocol.total_round)
  return total_round_;
}
inline void TableMsgProtocol::set_total_round(::google::protobuf::uint32 value) {
  set_has_total_round();
  total_round_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.TableMsgProtocol.total_round)
}

// optional uint32 remain_cards_num = 4;
inline bool TableMsgProtocol::has_remain_cards_num() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void TableMsgProtocol::set_has_remain_cards_num() {
  _has_bits_[0] |= 0x00000008u;
}
inline void TableMsgProtocol::clear_has_remain_cards_num() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void TableMsgProtocol::clear_remain_cards_num() {
  remain_cards_num_ = 0u;
  clear_has_remain_cards_num();
}
inline ::google::protobuf::uint32 TableMsgProtocol::remain_cards_num() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.TableMsgProtocol.remain_cards_num)
  return remain_cards_num_;
}
inline void TableMsgProtocol::set_remain_cards_num(::google::protobuf::uint32 value) {
  set_has_remain_cards_num();
  remain_cards_num_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.TableMsgProtocol.remain_cards_num)
}

// optional uint32 banker_id = 5;
inline bool TableMsgProtocol::has_banker_id() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void TableMsgProtocol::set_has_banker_id() {
  _has_bits_[0] |= 0x00000010u;
}
inline void TableMsgProtocol::clear_has_banker_id() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void TableMsgProtocol::clear_banker_id() {
  banker_id_ = 0u;
  clear_has_banker_id();
}
inline ::google::protobuf::uint32 TableMsgProtocol::banker_id() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.TableMsgProtocol.banker_id)
  return banker_id_;
}
inline void TableMsgProtocol::set_banker_id(::google::protobuf::uint32 value) {
  set_has_banker_id();
  banker_id_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.TableMsgProtocol.banker_id)
}

// optional uint32 banker_is_same_time = 6;
inline bool TableMsgProtocol::has_banker_is_same_time() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void TableMsgProtocol::set_has_banker_is_same_time() {
  _has_bits_[0] |= 0x00000020u;
}
inline void TableMsgProtocol::clear_has_banker_is_same_time() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void TableMsgProtocol::clear_banker_is_same_time() {
  banker_is_same_time_ = 0u;
  clear_has_banker_is_same_time();
}
inline ::google::protobuf::uint32 TableMsgProtocol::banker_is_same_time() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.TableMsgProtocol.banker_is_same_time)
  return banker_is_same_time_;
}
inline void TableMsgProtocol::set_banker_is_same_time(::google::protobuf::uint32 value) {
  set_has_banker_is_same_time();
  banker_is_same_time_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.TableMsgProtocol.banker_is_same_time)
}

// optional uint32 operating_player_id = 7;
inline bool TableMsgProtocol::has_operating_player_id() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void TableMsgProtocol::set_has_operating_player_id() {
  _has_bits_[0] |= 0x00000040u;
}
inline void TableMsgProtocol::clear_has_operating_player_id() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void TableMsgProtocol::clear_operating_player_id() {
  operating_player_id_ = 0u;
  clear_has_operating_player_id();
}
inline ::google::protobuf::uint32 TableMsgProtocol::operating_player_id() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.TableMsgProtocol.operating_player_id)
  return operating_player_id_;
}
inline void TableMsgProtocol::set_operating_player_id(::google::protobuf::uint32 value) {
  set_has_operating_player_id();
  operating_player_id_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.TableMsgProtocol.operating_player_id)
}

// optional uint32 operation_id = 8;
inline bool TableMsgProtocol::has_operation_id() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void TableMsgProtocol::set_has_operation_id() {
  _has_bits_[0] |= 0x00000080u;
}
inline void TableMsgProtocol::clear_has_operation_id() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void TableMsgProtocol::clear_operation_id() {
  operation_id_ = 0u;
  clear_has_operation_id();
}
inline ::google::protobuf::uint32 TableMsgProtocol::operation_id() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.TableMsgProtocol.operation_id)
  return operation_id_;
}
inline void TableMsgProtocol::set_operation_id(::google::protobuf::uint32 value) {
  set_has_operation_id();
  operation_id_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.TableMsgProtocol.operation_id)
}

// repeated uint32 remain_cards = 9;
inline int TableMsgProtocol::remain_cards_size() const {
  return remain_cards_.size();
}
inline void TableMsgProtocol::clear_remain_cards() {
  remain_cards_.Clear();
}
inline ::google::protobuf::uint32 TableMsgProtocol::remain_cards(int index) const {
  // @@protoc_insertion_point(field_get:gamer.protocol.TableMsgProtocol.remain_cards)
  return remain_cards_.Get(index);
}
inline void TableMsgProtocol::set_remain_cards(int index, ::google::protobuf::uint32 value) {
  remain_cards_.Set(index, value);
  // @@protoc_insertion_point(field_set:gamer.protocol.TableMsgProtocol.remain_cards)
}
inline void TableMsgProtocol::add_remain_cards(::google::protobuf::uint32 value) {
  remain_cards_.Add(value);
  // @@protoc_insertion_point(field_add:gamer.protocol.TableMsgProtocol.remain_cards)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
TableMsgProtocol::remain_cards() const {
  // @@protoc_insertion_point(field_list:gamer.protocol.TableMsgProtocol.remain_cards)
  return remain_cards_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
TableMsgProtocol::mutable_remain_cards() {
  // @@protoc_insertion_point(field_mutable_list:gamer.protocol.TableMsgProtocol.remain_cards)
  return &remain_cards_;
}

// repeated .gamer.protocol.PlayerCardsMsgProtocol player_cards = 10;
inline int TableMsgProtocol::player_cards_size() const {
  return player_cards_.size();
}
inline void TableMsgProtocol::clear_player_cards() {
  player_cards_.Clear();
}
inline const ::gamer::protocol::PlayerCardsMsgProtocol& TableMsgProtocol::player_cards(int index) const {
  // @@protoc_insertion_point(field_get:gamer.protocol.TableMsgProtocol.player_cards)
  return player_cards_.Get(index);
}
inline ::gamer::protocol::PlayerCardsMsgProtocol* TableMsgProtocol::mutable_player_cards(int index) {
  // @@protoc_insertion_point(field_mutable:gamer.protocol.TableMsgProtocol.player_cards)
  return player_cards_.Mutable(index);
}
inline ::gamer::protocol::PlayerCardsMsgProtocol* TableMsgProtocol::add_player_cards() {
  // @@protoc_insertion_point(field_add:gamer.protocol.TableMsgProtocol.player_cards)
  return player_cards_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::gamer::protocol::PlayerCardsMsgProtocol >&
TableMsgProtocol::player_cards() const {
  // @@protoc_insertion_point(field_list:gamer.protocol.TableMsgProtocol.player_cards)
  return player_cards_;
}
inline ::google::protobuf::RepeatedPtrField< ::gamer::protocol::PlayerCardsMsgProtocol >*
TableMsgProtocol::mutable_player_cards() {
  // @@protoc_insertion_point(field_mutable_list:gamer.protocol.TableMsgProtocol.player_cards)
  return &player_cards_;
}

// repeated .gamer.protocol.PlayerMsgProtocol players = 11;
inline int TableMsgProtocol::players_size() const {
  return players_.size();
}
inline void TableMsgProtocol::clear_players() {
  players_.Clear();
}
inline const ::gamer::protocol::PlayerMsgProtocol& TableMsgProtocol::players(int index) const {
  // @@protoc_insertion_point(field_get:gamer.protocol.TableMsgProtocol.players)
  return players_.Get(index);
}
inline ::gamer::protocol::PlayerMsgProtocol* TableMsgProtocol::mutable_players(int index) {
  // @@protoc_insertion_point(field_mutable:gamer.protocol.TableMsgProtocol.players)
  return players_.Mutable(index);
}
inline ::gamer::protocol::PlayerMsgProtocol* TableMsgProtocol::add_players() {
  // @@protoc_insertion_point(field_add:gamer.protocol.TableMsgProtocol.players)
  return players_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::gamer::protocol::PlayerMsgProtocol >&
TableMsgProtocol::players() const {
  // @@protoc_insertion_point(field_list:gamer.protocol.TableMsgProtocol.players)
  return players_;
}
inline ::google::protobuf::RepeatedPtrField< ::gamer::protocol::PlayerMsgProtocol >*
TableMsgProtocol::mutable_players() {
  // @@protoc_insertion_point(field_mutable_list:gamer.protocol.TableMsgProtocol.players)
  return &players_;
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

#endif  // PROTOBUF_table_5fmsg_5fprotocol_2eproto__INCLUDED