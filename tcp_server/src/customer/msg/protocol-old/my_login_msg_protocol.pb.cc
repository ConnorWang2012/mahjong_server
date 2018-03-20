// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: my_login_msg_protocol.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "my_login_msg_protocol.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace gamer {
namespace protocol {

namespace {

const ::google::protobuf::Descriptor* MyLoginMsgProtocol_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MyLoginMsgProtocol_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_my_5flogin_5fmsg_5fprotocol_2eproto() {
  protobuf_AddDesc_my_5flogin_5fmsg_5fprotocol_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "my_login_msg_protocol.proto");
  GOOGLE_CHECK(file != NULL);
  MyLoginMsgProtocol_descriptor_ = file->message_type(0);
  static const int MyLoginMsgProtocol_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MyLoginMsgProtocol, account_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MyLoginMsgProtocol, password_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MyLoginMsgProtocol, player_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MyLoginMsgProtocol, player_),
  };
  MyLoginMsgProtocol_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MyLoginMsgProtocol_descriptor_,
      MyLoginMsgProtocol::default_instance_,
      MyLoginMsgProtocol_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MyLoginMsgProtocol, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MyLoginMsgProtocol, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MyLoginMsgProtocol));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_my_5flogin_5fmsg_5fprotocol_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MyLoginMsgProtocol_descriptor_, &MyLoginMsgProtocol::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_my_5flogin_5fmsg_5fprotocol_2eproto() {
  delete MyLoginMsgProtocol::default_instance_;
  delete MyLoginMsgProtocol_reflection_;
}

void protobuf_AddDesc_my_5flogin_5fmsg_5fprotocol_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::gamer::protocol::protobuf_AddDesc_player_5fmsg_5fprotocol_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\033my_login_msg_protocol.proto\022\016gamer.pro"
    "tocol\032\031player_msg_protocol.proto\"}\n\022MyLo"
    "ginMsgProtocol\022\017\n\007account\030\001 \002(\t\022\020\n\010passw"
    "ord\030\002 \002(\t\022\021\n\tplayer_id\030\003 \002(\r\0221\n\006player\030\004"
    " \001(\0132!.gamer.protocol.PlayerMsgProtocol", 199);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "my_login_msg_protocol.proto", &protobuf_RegisterTypes);
  MyLoginMsgProtocol::default_instance_ = new MyLoginMsgProtocol();
  MyLoginMsgProtocol::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_my_5flogin_5fmsg_5fprotocol_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_my_5flogin_5fmsg_5fprotocol_2eproto {
  StaticDescriptorInitializer_my_5flogin_5fmsg_5fprotocol_2eproto() {
    protobuf_AddDesc_my_5flogin_5fmsg_5fprotocol_2eproto();
  }
} static_descriptor_initializer_my_5flogin_5fmsg_5fprotocol_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int MyLoginMsgProtocol::kAccountFieldNumber;
const int MyLoginMsgProtocol::kPasswordFieldNumber;
const int MyLoginMsgProtocol::kPlayerIdFieldNumber;
const int MyLoginMsgProtocol::kPlayerFieldNumber;
#endif  // !_MSC_VER

MyLoginMsgProtocol::MyLoginMsgProtocol()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:gamer.protocol.MyLoginMsgProtocol)
}

void MyLoginMsgProtocol::InitAsDefaultInstance() {
  player_ = const_cast< ::gamer::protocol::PlayerMsgProtocol*>(&::gamer::protocol::PlayerMsgProtocol::default_instance());
}

MyLoginMsgProtocol::MyLoginMsgProtocol(const MyLoginMsgProtocol& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:gamer.protocol.MyLoginMsgProtocol)
}

void MyLoginMsgProtocol::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  account_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  password_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  player_id_ = 0u;
  player_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MyLoginMsgProtocol::~MyLoginMsgProtocol() {
  // @@protoc_insertion_point(destructor:gamer.protocol.MyLoginMsgProtocol)
  SharedDtor();
}

void MyLoginMsgProtocol::SharedDtor() {
  if (account_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete account_;
  }
  if (password_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete password_;
  }
  if (this != default_instance_) {
    delete player_;
  }
}

void MyLoginMsgProtocol::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MyLoginMsgProtocol::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MyLoginMsgProtocol_descriptor_;
}

const MyLoginMsgProtocol& MyLoginMsgProtocol::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_my_5flogin_5fmsg_5fprotocol_2eproto();
  return *default_instance_;
}

MyLoginMsgProtocol* MyLoginMsgProtocol::default_instance_ = NULL;

MyLoginMsgProtocol* MyLoginMsgProtocol::New() const {
  return new MyLoginMsgProtocol;
}

void MyLoginMsgProtocol::Clear() {
  if (_has_bits_[0 / 32] & 15) {
    if (has_account()) {
      if (account_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        account_->clear();
      }
    }
    if (has_password()) {
      if (password_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        password_->clear();
      }
    }
    player_id_ = 0u;
    if (has_player()) {
      if (player_ != NULL) player_->::gamer::protocol::PlayerMsgProtocol::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MyLoginMsgProtocol::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:gamer.protocol.MyLoginMsgProtocol)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string account = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_account()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->account().data(), this->account().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "account");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_password;
        break;
      }

      // required string password = 2;
      case 2: {
        if (tag == 18) {
         parse_password:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_password()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->password().data(), this->password().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "password");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_player_id;
        break;
      }

      // required uint32 player_id = 3;
      case 3: {
        if (tag == 24) {
         parse_player_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &player_id_)));
          set_has_player_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_player;
        break;
      }

      // optional .gamer.protocol.PlayerMsgProtocol player = 4;
      case 4: {
        if (tag == 34) {
         parse_player:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_player()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:gamer.protocol.MyLoginMsgProtocol)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:gamer.protocol.MyLoginMsgProtocol)
  return false;
#undef DO_
}

void MyLoginMsgProtocol::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:gamer.protocol.MyLoginMsgProtocol)
  // required string account = 1;
  if (has_account()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->account().data(), this->account().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "account");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->account(), output);
  }

  // required string password = 2;
  if (has_password()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->password().data(), this->password().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "password");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->password(), output);
  }

  // required uint32 player_id = 3;
  if (has_player_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->player_id(), output);
  }

  // optional .gamer.protocol.PlayerMsgProtocol player = 4;
  if (has_player()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->player(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:gamer.protocol.MyLoginMsgProtocol)
}

::google::protobuf::uint8* MyLoginMsgProtocol::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:gamer.protocol.MyLoginMsgProtocol)
  // required string account = 1;
  if (has_account()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->account().data(), this->account().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "account");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->account(), target);
  }

  // required string password = 2;
  if (has_password()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->password().data(), this->password().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "password");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->password(), target);
  }

  // required uint32 player_id = 3;
  if (has_player_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->player_id(), target);
  }

  // optional .gamer.protocol.PlayerMsgProtocol player = 4;
  if (has_player()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->player(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:gamer.protocol.MyLoginMsgProtocol)
  return target;
}

int MyLoginMsgProtocol::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string account = 1;
    if (has_account()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->account());
    }

    // required string password = 2;
    if (has_password()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->password());
    }

    // required uint32 player_id = 3;
    if (has_player_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->player_id());
    }

    // optional .gamer.protocol.PlayerMsgProtocol player = 4;
    if (has_player()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->player());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MyLoginMsgProtocol::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MyLoginMsgProtocol* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MyLoginMsgProtocol*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MyLoginMsgProtocol::MergeFrom(const MyLoginMsgProtocol& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_account()) {
      set_account(from.account());
    }
    if (from.has_password()) {
      set_password(from.password());
    }
    if (from.has_player_id()) {
      set_player_id(from.player_id());
    }
    if (from.has_player()) {
      mutable_player()->::gamer::protocol::PlayerMsgProtocol::MergeFrom(from.player());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MyLoginMsgProtocol::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MyLoginMsgProtocol::CopyFrom(const MyLoginMsgProtocol& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MyLoginMsgProtocol::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  if (has_player()) {
    if (!this->player().IsInitialized()) return false;
  }
  return true;
}

void MyLoginMsgProtocol::Swap(MyLoginMsgProtocol* other) {
  if (other != this) {
    std::swap(account_, other->account_);
    std::swap(password_, other->password_);
    std::swap(player_id_, other->player_id_);
    std::swap(player_, other->player_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MyLoginMsgProtocol::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MyLoginMsgProtocol_descriptor_;
  metadata.reflection = MyLoginMsgProtocol_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace protocol
}  // namespace gamer

// @@protoc_insertion_point(global_scope)