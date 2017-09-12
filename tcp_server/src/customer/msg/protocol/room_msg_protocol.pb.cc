// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: room_msg_protocol.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "room_msg_protocol.pb.h"

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

const ::google::protobuf::Descriptor* RoomMsgProtocol_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  RoomMsgProtocol_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_room_5fmsg_5fprotocol_2eproto() {
  protobuf_AddDesc_room_5fmsg_5fprotocol_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "room_msg_protocol.proto");
  GOOGLE_CHECK(file != NULL);
  RoomMsgProtocol_descriptor_ = file->message_type(0);
  static const int RoomMsgProtocol_offsets_[12] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, room_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, room_owner_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, players_num_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, cur_round_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, total_round_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, remain_cards_num_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, banker_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, banker_is_same_time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, operating_player_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, operation_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, remain_cards_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, player_cards_),
  };
  RoomMsgProtocol_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      RoomMsgProtocol_descriptor_,
      RoomMsgProtocol::default_instance_,
      RoomMsgProtocol_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoomMsgProtocol, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(RoomMsgProtocol));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_room_5fmsg_5fprotocol_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    RoomMsgProtocol_descriptor_, &RoomMsgProtocol::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_room_5fmsg_5fprotocol_2eproto() {
  delete RoomMsgProtocol::default_instance_;
  delete RoomMsgProtocol_reflection_;
}

void protobuf_AddDesc_room_5fmsg_5fprotocol_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::gamer::protocol::protobuf_AddDesc_player_5fcards_5fmsg_5fprotocol_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\027room_msg_protocol.proto\022\016gamer.protoco"
    "l\032\037player_cards_msg_protocol.proto\"\307\002\n\017R"
    "oomMsgProtocol\022\017\n\007room_id\030\001 \002(\005\022\025\n\rroom_"
    "owner_id\030\002 \002(\005\022\023\n\013players_num\030\003 \001(\005\022\021\n\tc"
    "ur_round\030\004 \001(\005\022\023\n\013total_round\030\005 \001(\005\022\030\n\020r"
    "emain_cards_num\030\006 \001(\005\022\021\n\tbanker_id\030\007 \001(\005"
    "\022\033\n\023banker_is_same_time\030\010 \001(\005\022\033\n\023operati"
    "ng_player_id\030\t \001(\005\022\024\n\014operation_id\030\n \001(\005"
    "\022\024\n\014remain_cards\030\013 \003(\005\022<\n\014player_cards\030\014"
    " \003(\0132&.gamer.protocol.PlayerCardsMsgProt"
    "ocol", 404);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "room_msg_protocol.proto", &protobuf_RegisterTypes);
  RoomMsgProtocol::default_instance_ = new RoomMsgProtocol();
  RoomMsgProtocol::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_room_5fmsg_5fprotocol_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_room_5fmsg_5fprotocol_2eproto {
  StaticDescriptorInitializer_room_5fmsg_5fprotocol_2eproto() {
    protobuf_AddDesc_room_5fmsg_5fprotocol_2eproto();
  }
} static_descriptor_initializer_room_5fmsg_5fprotocol_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int RoomMsgProtocol::kRoomIdFieldNumber;
const int RoomMsgProtocol::kRoomOwnerIdFieldNumber;
const int RoomMsgProtocol::kPlayersNumFieldNumber;
const int RoomMsgProtocol::kCurRoundFieldNumber;
const int RoomMsgProtocol::kTotalRoundFieldNumber;
const int RoomMsgProtocol::kRemainCardsNumFieldNumber;
const int RoomMsgProtocol::kBankerIdFieldNumber;
const int RoomMsgProtocol::kBankerIsSameTimeFieldNumber;
const int RoomMsgProtocol::kOperatingPlayerIdFieldNumber;
const int RoomMsgProtocol::kOperationIdFieldNumber;
const int RoomMsgProtocol::kRemainCardsFieldNumber;
const int RoomMsgProtocol::kPlayerCardsFieldNumber;
#endif  // !_MSC_VER

RoomMsgProtocol::RoomMsgProtocol()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:gamer.protocol.RoomMsgProtocol)
}

void RoomMsgProtocol::InitAsDefaultInstance() {
}

RoomMsgProtocol::RoomMsgProtocol(const RoomMsgProtocol& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:gamer.protocol.RoomMsgProtocol)
}

void RoomMsgProtocol::SharedCtor() {
  _cached_size_ = 0;
  room_id_ = 0;
  room_owner_id_ = 0;
  players_num_ = 0;
  cur_round_ = 0;
  total_round_ = 0;
  remain_cards_num_ = 0;
  banker_id_ = 0;
  banker_is_same_time_ = 0;
  operating_player_id_ = 0;
  operation_id_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

RoomMsgProtocol::~RoomMsgProtocol() {
  // @@protoc_insertion_point(destructor:gamer.protocol.RoomMsgProtocol)
  SharedDtor();
}

void RoomMsgProtocol::SharedDtor() {
  if (this != default_instance_) {
  }
}

void RoomMsgProtocol::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* RoomMsgProtocol::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RoomMsgProtocol_descriptor_;
}

const RoomMsgProtocol& RoomMsgProtocol::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_room_5fmsg_5fprotocol_2eproto();
  return *default_instance_;
}

RoomMsgProtocol* RoomMsgProtocol::default_instance_ = NULL;

RoomMsgProtocol* RoomMsgProtocol::New() const {
  return new RoomMsgProtocol;
}

void RoomMsgProtocol::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<RoomMsgProtocol*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 255) {
    ZR_(room_id_, banker_is_same_time_);
  }
  ZR_(operating_player_id_, operation_id_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  remain_cards_.Clear();
  player_cards_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool RoomMsgProtocol::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:gamer.protocol.RoomMsgProtocol)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 room_id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &room_id_)));
          set_has_room_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_room_owner_id;
        break;
      }

      // required int32 room_owner_id = 2;
      case 2: {
        if (tag == 16) {
         parse_room_owner_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &room_owner_id_)));
          set_has_room_owner_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_players_num;
        break;
      }

      // optional int32 players_num = 3;
      case 3: {
        if (tag == 24) {
         parse_players_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &players_num_)));
          set_has_players_num();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_cur_round;
        break;
      }

      // optional int32 cur_round = 4;
      case 4: {
        if (tag == 32) {
         parse_cur_round:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &cur_round_)));
          set_has_cur_round();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_total_round;
        break;
      }

      // optional int32 total_round = 5;
      case 5: {
        if (tag == 40) {
         parse_total_round:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &total_round_)));
          set_has_total_round();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_remain_cards_num;
        break;
      }

      // optional int32 remain_cards_num = 6;
      case 6: {
        if (tag == 48) {
         parse_remain_cards_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &remain_cards_num_)));
          set_has_remain_cards_num();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(56)) goto parse_banker_id;
        break;
      }

      // optional int32 banker_id = 7;
      case 7: {
        if (tag == 56) {
         parse_banker_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &banker_id_)));
          set_has_banker_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(64)) goto parse_banker_is_same_time;
        break;
      }

      // optional int32 banker_is_same_time = 8;
      case 8: {
        if (tag == 64) {
         parse_banker_is_same_time:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &banker_is_same_time_)));
          set_has_banker_is_same_time();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(72)) goto parse_operating_player_id;
        break;
      }

      // optional int32 operating_player_id = 9;
      case 9: {
        if (tag == 72) {
         parse_operating_player_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &operating_player_id_)));
          set_has_operating_player_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(80)) goto parse_operation_id;
        break;
      }

      // optional int32 operation_id = 10;
      case 10: {
        if (tag == 80) {
         parse_operation_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &operation_id_)));
          set_has_operation_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(88)) goto parse_remain_cards;
        break;
      }

      // repeated int32 remain_cards = 11;
      case 11: {
        if (tag == 88) {
         parse_remain_cards:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 88, input, this->mutable_remain_cards())));
        } else if (tag == 90) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_remain_cards())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(88)) goto parse_remain_cards;
        if (input->ExpectTag(98)) goto parse_player_cards;
        break;
      }

      // repeated .gamer.protocol.PlayerCardsMsgProtocol player_cards = 12;
      case 12: {
        if (tag == 98) {
         parse_player_cards:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_player_cards()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(98)) goto parse_player_cards;
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
  // @@protoc_insertion_point(parse_success:gamer.protocol.RoomMsgProtocol)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:gamer.protocol.RoomMsgProtocol)
  return false;
#undef DO_
}

void RoomMsgProtocol::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:gamer.protocol.RoomMsgProtocol)
  // required int32 room_id = 1;
  if (has_room_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->room_id(), output);
  }

  // required int32 room_owner_id = 2;
  if (has_room_owner_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->room_owner_id(), output);
  }

  // optional int32 players_num = 3;
  if (has_players_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->players_num(), output);
  }

  // optional int32 cur_round = 4;
  if (has_cur_round()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->cur_round(), output);
  }

  // optional int32 total_round = 5;
  if (has_total_round()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->total_round(), output);
  }

  // optional int32 remain_cards_num = 6;
  if (has_remain_cards_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->remain_cards_num(), output);
  }

  // optional int32 banker_id = 7;
  if (has_banker_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(7, this->banker_id(), output);
  }

  // optional int32 banker_is_same_time = 8;
  if (has_banker_is_same_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(8, this->banker_is_same_time(), output);
  }

  // optional int32 operating_player_id = 9;
  if (has_operating_player_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(9, this->operating_player_id(), output);
  }

  // optional int32 operation_id = 10;
  if (has_operation_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(10, this->operation_id(), output);
  }

  // repeated int32 remain_cards = 11;
  for (int i = 0; i < this->remain_cards_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(
      11, this->remain_cards(i), output);
  }

  // repeated .gamer.protocol.PlayerCardsMsgProtocol player_cards = 12;
  for (int i = 0; i < this->player_cards_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      12, this->player_cards(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:gamer.protocol.RoomMsgProtocol)
}

::google::protobuf::uint8* RoomMsgProtocol::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:gamer.protocol.RoomMsgProtocol)
  // required int32 room_id = 1;
  if (has_room_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->room_id(), target);
  }

  // required int32 room_owner_id = 2;
  if (has_room_owner_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->room_owner_id(), target);
  }

  // optional int32 players_num = 3;
  if (has_players_num()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->players_num(), target);
  }

  // optional int32 cur_round = 4;
  if (has_cur_round()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->cur_round(), target);
  }

  // optional int32 total_round = 5;
  if (has_total_round()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->total_round(), target);
  }

  // optional int32 remain_cards_num = 6;
  if (has_remain_cards_num()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->remain_cards_num(), target);
  }

  // optional int32 banker_id = 7;
  if (has_banker_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(7, this->banker_id(), target);
  }

  // optional int32 banker_is_same_time = 8;
  if (has_banker_is_same_time()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(8, this->banker_is_same_time(), target);
  }

  // optional int32 operating_player_id = 9;
  if (has_operating_player_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(9, this->operating_player_id(), target);
  }

  // optional int32 operation_id = 10;
  if (has_operation_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(10, this->operation_id(), target);
  }

  // repeated int32 remain_cards = 11;
  for (int i = 0; i < this->remain_cards_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteInt32ToArray(11, this->remain_cards(i), target);
  }

  // repeated .gamer.protocol.PlayerCardsMsgProtocol player_cards = 12;
  for (int i = 0; i < this->player_cards_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        12, this->player_cards(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:gamer.protocol.RoomMsgProtocol)
  return target;
}

int RoomMsgProtocol::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 room_id = 1;
    if (has_room_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->room_id());
    }

    // required int32 room_owner_id = 2;
    if (has_room_owner_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->room_owner_id());
    }

    // optional int32 players_num = 3;
    if (has_players_num()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->players_num());
    }

    // optional int32 cur_round = 4;
    if (has_cur_round()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->cur_round());
    }

    // optional int32 total_round = 5;
    if (has_total_round()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->total_round());
    }

    // optional int32 remain_cards_num = 6;
    if (has_remain_cards_num()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->remain_cards_num());
    }

    // optional int32 banker_id = 7;
    if (has_banker_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->banker_id());
    }

    // optional int32 banker_is_same_time = 8;
    if (has_banker_is_same_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->banker_is_same_time());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional int32 operating_player_id = 9;
    if (has_operating_player_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->operating_player_id());
    }

    // optional int32 operation_id = 10;
    if (has_operation_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->operation_id());
    }

  }
  // repeated int32 remain_cards = 11;
  {
    int data_size = 0;
    for (int i = 0; i < this->remain_cards_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        Int32Size(this->remain_cards(i));
    }
    total_size += 1 * this->remain_cards_size() + data_size;
  }

  // repeated .gamer.protocol.PlayerCardsMsgProtocol player_cards = 12;
  total_size += 1 * this->player_cards_size();
  for (int i = 0; i < this->player_cards_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->player_cards(i));
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

void RoomMsgProtocol::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const RoomMsgProtocol* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const RoomMsgProtocol*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void RoomMsgProtocol::MergeFrom(const RoomMsgProtocol& from) {
  GOOGLE_CHECK_NE(&from, this);
  remain_cards_.MergeFrom(from.remain_cards_);
  player_cards_.MergeFrom(from.player_cards_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_room_id()) {
      set_room_id(from.room_id());
    }
    if (from.has_room_owner_id()) {
      set_room_owner_id(from.room_owner_id());
    }
    if (from.has_players_num()) {
      set_players_num(from.players_num());
    }
    if (from.has_cur_round()) {
      set_cur_round(from.cur_round());
    }
    if (from.has_total_round()) {
      set_total_round(from.total_round());
    }
    if (from.has_remain_cards_num()) {
      set_remain_cards_num(from.remain_cards_num());
    }
    if (from.has_banker_id()) {
      set_banker_id(from.banker_id());
    }
    if (from.has_banker_is_same_time()) {
      set_banker_is_same_time(from.banker_is_same_time());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_operating_player_id()) {
      set_operating_player_id(from.operating_player_id());
    }
    if (from.has_operation_id()) {
      set_operation_id(from.operation_id());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void RoomMsgProtocol::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RoomMsgProtocol::CopyFrom(const RoomMsgProtocol& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RoomMsgProtocol::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void RoomMsgProtocol::Swap(RoomMsgProtocol* other) {
  if (other != this) {
    std::swap(room_id_, other->room_id_);
    std::swap(room_owner_id_, other->room_owner_id_);
    std::swap(players_num_, other->players_num_);
    std::swap(cur_round_, other->cur_round_);
    std::swap(total_round_, other->total_round_);
    std::swap(remain_cards_num_, other->remain_cards_num_);
    std::swap(banker_id_, other->banker_id_);
    std::swap(banker_is_same_time_, other->banker_is_same_time_);
    std::swap(operating_player_id_, other->operating_player_id_);
    std::swap(operation_id_, other->operation_id_);
    remain_cards_.Swap(&other->remain_cards_);
    player_cards_.Swap(&other->player_cards_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata RoomMsgProtocol::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = RoomMsgProtocol_descriptor_;
  metadata.reflection = RoomMsgProtocol_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace protocol
}  // namespace gamer

// @@protoc_insertion_point(global_scope)
