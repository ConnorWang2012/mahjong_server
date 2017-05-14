// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: login_msg_protocol.proto

#ifndef PROTOBUF_login_5fmsg_5fprotocol_2eproto__INCLUDED
#define PROTOBUF_login_5fmsg_5fprotocol_2eproto__INCLUDED

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
void  protobuf_AddDesc_login_5fmsg_5fprotocol_2eproto();
void protobuf_AssignDesc_login_5fmsg_5fprotocol_2eproto();
void protobuf_ShutdownFile_login_5fmsg_5fprotocol_2eproto();

class Msg;

// ===================================================================

class Msg : public ::google::protobuf::Message {
 public:
  Msg();
  virtual ~Msg();

  Msg(const Msg& from);

  inline Msg& operator=(const Msg& from) {
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
  static const Msg& default_instance();

  void Swap(Msg* other);

  // implements Message ----------------------------------------------

  Msg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Msg& from);
  void MergeFrom(const Msg& from);
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

  // required int32 msg_type = 1;
  inline bool has_msg_type() const;
  inline void clear_msg_type();
  static const int kMsgTypeFieldNumber = 1;
  inline ::google::protobuf::int32 msg_type() const;
  inline void set_msg_type(::google::protobuf::int32 value);

  // required int32 msg_id = 2;
  inline bool has_msg_id() const;
  inline void clear_msg_id();
  static const int kMsgIdFieldNumber = 2;
  inline ::google::protobuf::int32 msg_id() const;
  inline void set_msg_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:gamer.protocol.Msg)
 private:
  inline void set_has_msg_type();
  inline void clear_has_msg_type();
  inline void set_has_msg_id();
  inline void clear_has_msg_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 msg_type_;
  ::google::protobuf::int32 msg_id_;
  friend void  protobuf_AddDesc_login_5fmsg_5fprotocol_2eproto();
  friend void protobuf_AssignDesc_login_5fmsg_5fprotocol_2eproto();
  friend void protobuf_ShutdownFile_login_5fmsg_5fprotocol_2eproto();

  void InitAsDefaultInstance();
  static Msg* default_instance_;
};
// ===================================================================


// ===================================================================

// Msg

// required int32 msg_type = 1;
inline bool Msg::has_msg_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Msg::set_has_msg_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Msg::clear_has_msg_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Msg::clear_msg_type() {
  msg_type_ = 0;
  clear_has_msg_type();
}
inline ::google::protobuf::int32 Msg::msg_type() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.Msg.msg_type)
  return msg_type_;
}
inline void Msg::set_msg_type(::google::protobuf::int32 value) {
  set_has_msg_type();
  msg_type_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.Msg.msg_type)
}

// required int32 msg_id = 2;
inline bool Msg::has_msg_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Msg::set_has_msg_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Msg::clear_has_msg_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Msg::clear_msg_id() {
  msg_id_ = 0;
  clear_has_msg_id();
}
inline ::google::protobuf::int32 Msg::msg_id() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.Msg.msg_id)
  return msg_id_;
}
inline void Msg::set_msg_id(::google::protobuf::int32 value) {
  set_has_msg_id();
  msg_id_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.Msg.msg_id)
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

#endif  // PROTOBUF_login_5fmsg_5fprotocol_2eproto__INCLUDED
