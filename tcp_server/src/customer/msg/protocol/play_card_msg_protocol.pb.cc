// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: play_card_msg_protocol.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "play_card_msg_protocol.pb.h"

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

const ::google::protobuf::Descriptor* PlayCardMsgProtocol_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  PlayCardMsgProtocol_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_play_5fcard_5fmsg_5fprotocol_2eproto() {
  protobuf_AddDesc_play_5fcard_5fmsg_5fprotocol_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "play_card_msg_protocol.proto");
  GOOGLE_CHECK(file != NULL);
  PlayCardMsgProtocol_descriptor_ = file->message_type(0);
  static const int PlayCardMsgProtocol_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, player_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, room_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, cur_round_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, operation_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, discard_),
  };
  PlayCardMsgProtocol_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      PlayCardMsgProtocol_descriptor_,
      PlayCardMsgProtocol::default_instance_,
      PlayCardMsgProtocol_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(PlayCardMsgProtocol));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_play_5fcard_5fmsg_5fprotocol_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    PlayCardMsgProtocol_descriptor_, &PlayCardMsgProtocol::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_play_5fcard_5fmsg_5fprotocol_2eproto() {
  delete PlayCardMsgProtocol::default_instance_;
  delete PlayCardMsgProtocol_reflection_;
}

void protobuf_AddDesc_play_5fcard_5fmsg_5fprotocol_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\034play_card_msg_protocol.proto\022\016gamer.pr"
    "otocol\"s\n\023PlayCardMsgProtocol\022\021\n\tplayer_"
    "id\030\001 \002(\005\022\017\n\007room_id\030\002 \002(\005\022\021\n\tcur_round\030\003"
    " \002(\005\022\024\n\014operation_id\030\004 \002(\005\022\017\n\007discard\030\005 "
    "\001(\005", 163);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "play_card_msg_protocol.proto", &protobuf_RegisterTypes);
  PlayCardMsgProtocol::default_instance_ = new PlayCardMsgProtocol();
  PlayCardMsgProtocol::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_play_5fcard_5fmsg_5fprotocol_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_play_5fcard_5fmsg_5fprotocol_2eproto {
  StaticDescriptorInitializer_play_5fcard_5fmsg_5fprotocol_2eproto() {
    protobuf_AddDesc_play_5fcard_5fmsg_5fprotocol_2eproto();
  }
} static_descriptor_initializer_play_5fcard_5fmsg_5fprotocol_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int PlayCardMsgProtocol::kPlayerIdFieldNumber;
const int PlayCardMsgProtocol::kRoomIdFieldNumber;
const int PlayCardMsgProtocol::kCurRoundFieldNumber;
const int PlayCardMsgProtocol::kOperationIdFieldNumber;
const int PlayCardMsgProtocol::kDiscardFieldNumber;
#endif  // !_MSC_VER

PlayCardMsgProtocol::PlayCardMsgProtocol()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:gamer.protocol.PlayCardMsgProtocol)
}

void PlayCardMsgProtocol::InitAsDefaultInstance() {
}

PlayCardMsgProtocol::PlayCardMsgProtocol(const PlayCardMsgProtocol& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:gamer.protocol.PlayCardMsgProtocol)
}

void PlayCardMsgProtocol::SharedCtor() {
  _cached_size_ = 0;
  player_id_ = 0;
  room_id_ = 0;
  cur_round_ = 0;
  operation_id_ = 0;
  discard_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

PlayCardMsgProtocol::~PlayCardMsgProtocol() {
  // @@protoc_insertion_point(destructor:gamer.protocol.PlayCardMsgProtocol)
  SharedDtor();
}

void PlayCardMsgProtocol::SharedDtor() {
  if (this != default_instance_) {
  }
}

void PlayCardMsgProtocol::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* PlayCardMsgProtocol::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PlayCardMsgProtocol_descriptor_;
}

const PlayCardMsgProtocol& PlayCardMsgProtocol::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_play_5fcard_5fmsg_5fprotocol_2eproto();
  return *default_instance_;
}

PlayCardMsgProtocol* PlayCardMsgProtocol::default_instance_ = NULL;

PlayCardMsgProtocol* PlayCardMsgProtocol::New() const {
  return new PlayCardMsgProtocol;
}

void PlayCardMsgProtocol::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<PlayCardMsgProtocol*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 31) {
    ZR_(player_id_, discard_);
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool PlayCardMsgProtocol::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:gamer.protocol.PlayCardMsgProtocol)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 player_id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &player_id_)));
          set_has_player_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_room_id;
        break;
      }

      // required int32 room_id = 2;
      case 2: {
        if (tag == 16) {
         parse_room_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &room_id_)));
          set_has_room_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_cur_round;
        break;
      }

      // required int32 cur_round = 3;
      case 3: {
        if (tag == 24) {
         parse_cur_round:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &cur_round_)));
          set_has_cur_round();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_operation_id;
        break;
      }

      // required int32 operation_id = 4;
      case 4: {
        if (tag == 32) {
         parse_operation_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &operation_id_)));
          set_has_operation_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_discard;
        break;
      }

      // optional int32 discard = 5;
      case 5: {
        if (tag == 40) {
         parse_discard:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &discard_)));
          set_has_discard();
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
  // @@protoc_insertion_point(parse_success:gamer.protocol.PlayCardMsgProtocol)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:gamer.protocol.PlayCardMsgProtocol)
  return false;
#undef DO_
}

void PlayCardMsgProtocol::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:gamer.protocol.PlayCardMsgProtocol)
  // required int32 player_id = 1;
  if (has_player_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->player_id(), output);
  }

  // required int32 room_id = 2;
  if (has_room_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->room_id(), output);
  }

  // required int32 cur_round = 3;
  if (has_cur_round()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->cur_round(), output);
  }

  // required int32 operation_id = 4;
  if (has_operation_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->operation_id(), output);
  }

  // optional int32 discard = 5;
  if (has_discard()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->discard(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:gamer.protocol.PlayCardMsgProtocol)
}

::google::protobuf::uint8* PlayCardMsgProtocol::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:gamer.protocol.PlayCardMsgProtocol)
  // required int32 player_id = 1;
  if (has_player_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->player_id(), target);
  }

  // required int32 room_id = 2;
  if (has_room_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->room_id(), target);
  }

  // required int32 cur_round = 3;
  if (has_cur_round()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->cur_round(), target);
  }

  // required int32 operation_id = 4;
  if (has_operation_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->operation_id(), target);
  }

  // optional int32 discard = 5;
  if (has_discard()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->discard(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:gamer.protocol.PlayCardMsgProtocol)
  return target;
}

int PlayCardMsgProtocol::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 player_id = 1;
    if (has_player_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->player_id());
    }

    // required int32 room_id = 2;
    if (has_room_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->room_id());
    }

    // required int32 cur_round = 3;
    if (has_cur_round()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->cur_round());
    }

    // required int32 operation_id = 4;
    if (has_operation_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->operation_id());
    }

    // optional int32 discard = 5;
    if (has_discard()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->discard());
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

void PlayCardMsgProtocol::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const PlayCardMsgProtocol* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const PlayCardMsgProtocol*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void PlayCardMsgProtocol::MergeFrom(const PlayCardMsgProtocol& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_player_id()) {
      set_player_id(from.player_id());
    }
    if (from.has_room_id()) {
      set_room_id(from.room_id());
    }
    if (from.has_cur_round()) {
      set_cur_round(from.cur_round());
    }
    if (from.has_operation_id()) {
      set_operation_id(from.operation_id());
    }
    if (from.has_discard()) {
      set_discard(from.discard());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void PlayCardMsgProtocol::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PlayCardMsgProtocol::CopyFrom(const PlayCardMsgProtocol& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PlayCardMsgProtocol::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;

  return true;
}

void PlayCardMsgProtocol::Swap(PlayCardMsgProtocol* other) {
  if (other != this) {
    std::swap(player_id_, other->player_id_);
    std::swap(room_id_, other->room_id_);
    std::swap(cur_round_, other->cur_round_);
    std::swap(operation_id_, other->operation_id_);
    std::swap(discard_, other->discard_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata PlayCardMsgProtocol::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = PlayCardMsgProtocol_descriptor_;
  metadata.reflection = PlayCardMsgProtocol_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace protocol
}  // namespace gamer

// @@protoc_insertion_point(global_scope)