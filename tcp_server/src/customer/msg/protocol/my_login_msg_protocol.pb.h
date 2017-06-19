// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: my_login_msg_protocol.proto

#ifndef PROTOBUF_my_5flogin_5fmsg_5fprotocol_2eproto__INCLUDED
#define PROTOBUF_my_5flogin_5fmsg_5fprotocol_2eproto__INCLUDED

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
void  protobuf_AddDesc_my_5flogin_5fmsg_5fprotocol_2eproto();
void protobuf_AssignDesc_my_5flogin_5fmsg_5fprotocol_2eproto();
void protobuf_ShutdownFile_my_5flogin_5fmsg_5fprotocol_2eproto();

class MyLoginMsgProtocol;

// ===================================================================

class MyLoginMsgProtocol : public ::google::protobuf::Message {
 public:
  MyLoginMsgProtocol();
  virtual ~MyLoginMsgProtocol();

  MyLoginMsgProtocol(const MyLoginMsgProtocol& from);

  inline MyLoginMsgProtocol& operator=(const MyLoginMsgProtocol& from) {
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
  static const MyLoginMsgProtocol& default_instance();

  void Swap(MyLoginMsgProtocol* other);

  // implements Message ----------------------------------------------

  MyLoginMsgProtocol* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MyLoginMsgProtocol& from);
  void MergeFrom(const MyLoginMsgProtocol& from);
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

  // required string account = 1;
  inline bool has_account() const;
  inline void clear_account();
  static const int kAccountFieldNumber = 1;
  inline const ::std::string& account() const;
  inline void set_account(const ::std::string& value);
  inline void set_account(const char* value);
  inline void set_account(const char* value, size_t size);
  inline ::std::string* mutable_account();
  inline ::std::string* release_account();
  inline void set_allocated_account(::std::string* account);

  // required int32 password = 2;
  inline bool has_password() const;
  inline void clear_password();
  static const int kPasswordFieldNumber = 2;
  inline ::google::protobuf::int32 password() const;
  inline void set_password(::google::protobuf::int32 value);

  // optional int32 player_id = 3 [default = 0];
  inline bool has_player_id() const;
  inline void clear_player_id();
  static const int kPlayerIdFieldNumber = 3;
  inline ::google::protobuf::int32 player_id() const;
  inline void set_player_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:gamer.protocol.MyLoginMsgProtocol)
 private:
  inline void set_has_account();
  inline void clear_has_account();
  inline void set_has_password();
  inline void clear_has_password();
  inline void set_has_player_id();
  inline void clear_has_player_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* account_;
  ::google::protobuf::int32 password_;
  ::google::protobuf::int32 player_id_;
  friend void  protobuf_AddDesc_my_5flogin_5fmsg_5fprotocol_2eproto();
  friend void protobuf_AssignDesc_my_5flogin_5fmsg_5fprotocol_2eproto();
  friend void protobuf_ShutdownFile_my_5flogin_5fmsg_5fprotocol_2eproto();

  void InitAsDefaultInstance();
  static MyLoginMsgProtocol* default_instance_;
};
// ===================================================================


// ===================================================================

// MyLoginMsgProtocol

// required string account = 1;
inline bool MyLoginMsgProtocol::has_account() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MyLoginMsgProtocol::set_has_account() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MyLoginMsgProtocol::clear_has_account() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MyLoginMsgProtocol::clear_account() {
  if (account_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    account_->clear();
  }
  clear_has_account();
}
inline const ::std::string& MyLoginMsgProtocol::account() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.MyLoginMsgProtocol.account)
  return *account_;
}
inline void MyLoginMsgProtocol::set_account(const ::std::string& value) {
  set_has_account();
  if (account_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    account_ = new ::std::string;
  }
  account_->assign(value);
  // @@protoc_insertion_point(field_set:gamer.protocol.MyLoginMsgProtocol.account)
}
inline void MyLoginMsgProtocol::set_account(const char* value) {
  set_has_account();
  if (account_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    account_ = new ::std::string;
  }
  account_->assign(value);
  // @@protoc_insertion_point(field_set_char:gamer.protocol.MyLoginMsgProtocol.account)
}
inline void MyLoginMsgProtocol::set_account(const char* value, size_t size) {
  set_has_account();
  if (account_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    account_ = new ::std::string;
  }
  account_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:gamer.protocol.MyLoginMsgProtocol.account)
}
inline ::std::string* MyLoginMsgProtocol::mutable_account() {
  set_has_account();
  if (account_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    account_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:gamer.protocol.MyLoginMsgProtocol.account)
  return account_;
}
inline ::std::string* MyLoginMsgProtocol::release_account() {
  clear_has_account();
  if (account_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = account_;
    account_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MyLoginMsgProtocol::set_allocated_account(::std::string* account) {
  if (account_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete account_;
  }
  if (account) {
    set_has_account();
    account_ = account;
  } else {
    clear_has_account();
    account_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:gamer.protocol.MyLoginMsgProtocol.account)
}

// required int32 password = 2;
inline bool MyLoginMsgProtocol::has_password() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MyLoginMsgProtocol::set_has_password() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MyLoginMsgProtocol::clear_has_password() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MyLoginMsgProtocol::clear_password() {
  password_ = 0;
  clear_has_password();
}
inline ::google::protobuf::int32 MyLoginMsgProtocol::password() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.MyLoginMsgProtocol.password)
  return password_;
}
inline void MyLoginMsgProtocol::set_password(::google::protobuf::int32 value) {
  set_has_password();
  password_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.MyLoginMsgProtocol.password)
}

// optional int32 player_id = 3 [default = 0];
inline bool MyLoginMsgProtocol::has_player_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MyLoginMsgProtocol::set_has_player_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MyLoginMsgProtocol::clear_has_player_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MyLoginMsgProtocol::clear_player_id() {
  player_id_ = 0;
  clear_has_player_id();
}
inline ::google::protobuf::int32 MyLoginMsgProtocol::player_id() const {
  // @@protoc_insertion_point(field_get:gamer.protocol.MyLoginMsgProtocol.player_id)
  return player_id_;
}
inline void MyLoginMsgProtocol::set_player_id(::google::protobuf::int32 value) {
  set_has_player_id();
  player_id_ = value;
  // @@protoc_insertion_point(field_set:gamer.protocol.MyLoginMsgProtocol.player_id)
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

#endif  // PROTOBUF_my_5flogin_5fmsg_5fprotocol_2eproto__INCLUDED
