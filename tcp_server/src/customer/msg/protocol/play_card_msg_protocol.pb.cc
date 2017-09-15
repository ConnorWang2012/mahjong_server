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
  static const int PlayCardMsgProtocol_offsets_[12] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, player_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, room_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, cur_round_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, operation_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, discard_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, new_card_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, next_operate_player_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, has_next_operate_player_new_card_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, my_available_operation_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, operating_cards_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, invisible_hand_cards_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PlayCardMsgProtocol, ting_cards_),
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

  ::gamer::protocol::protobuf_AddDesc_ting_5fcard_5fmsg_5fprotocol_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\034play_card_msg_protocol.proto\022\016gamer.pr"
    "otocol\032\034ting_card_msg_protocol.proto\"\367\002\n"
    "\023PlayCardMsgProtocol\022\021\n\tplayer_id\030\001 \002(\005\022"
    "\017\n\007room_id\030\002 \002(\005\022\021\n\tcur_round\030\003 \002(\005\022\024\n\014o"
    "peration_id\030\004 \002(\005\022\023\n\007discard\030\005 \001(\005:\002-1\022\024"
    "\n\010new_card\030\006 \001(\005:\002-1\022!\n\026next_operate_pla"
    "yer_id\030\007 \001(\005:\0010\022/\n has_next_operate_play"
    "er_new_card\030\010 \001(\010:\005false\022$\n\031my_available"
    "_operation_id\030\t \001(\005:\0010\022\027\n\017operating_card"
    "s\030\n \003(\005\022\034\n\024invisible_hand_cards\030\013 \003(\005\0227\n"
    "\nting_cards\030\014 \003(\0132#.gamer.protocol.TingC"
    "ardMsgProtocol", 454);
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
const int PlayCardMsgProtocol::kNewCardFieldNumber;
const int PlayCardMsgProtocol::kNextOperatePlayerIdFieldNumber;
const int PlayCardMsgProtocol::kHasNextOperatePlayerNewCardFieldNumber;
const int PlayCardMsgProtocol::kMyAvailableOperationIdFieldNumber;
const int PlayCardMsgProtocol::kOperatingCardsFieldNumber;
const int PlayCardMsgProtocol::kInvisibleHandCardsFieldNumber;
const int PlayCardMsgProtocol::kTingCardsFieldNumber;
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
  discard_ = -1;
  new_card_ = -1;
  next_operate_player_id_ = 0;
  has_next_operate_player_new_card_ = false;
  my_available_operation_id_ = 0;
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

  if (_has_bits_[0 / 32] & 255) {
    ZR_(player_id_, operation_id_);
    ZR_(next_operate_player_id_, has_next_operate_player_new_card_);
    discard_ = -1;
    new_card_ = -1;
  }
  my_available_operation_id_ = 0;

#undef OFFSET_OF_FIELD_
#undef ZR_

  operating_cards_.Clear();
  invisible_hand_cards_.Clear();
  ting_cards_.Clear();
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

      // optional int32 discard = 5 [default = -1];
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
        if (input->ExpectTag(48)) goto parse_new_card;
        break;
      }

      // optional int32 new_card = 6 [default = -1];
      case 6: {
        if (tag == 48) {
         parse_new_card:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &new_card_)));
          set_has_new_card();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(56)) goto parse_next_operate_player_id;
        break;
      }

      // optional int32 next_operate_player_id = 7 [default = 0];
      case 7: {
        if (tag == 56) {
         parse_next_operate_player_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &next_operate_player_id_)));
          set_has_next_operate_player_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(64)) goto parse_has_next_operate_player_new_card;
        break;
      }

      // optional bool has_next_operate_player_new_card = 8 [default = false];
      case 8: {
        if (tag == 64) {
         parse_has_next_operate_player_new_card:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &has_next_operate_player_new_card_)));
          set_has_has_next_operate_player_new_card();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(72)) goto parse_my_available_operation_id;
        break;
      }

      // optional int32 my_available_operation_id = 9 [default = 0];
      case 9: {
        if (tag == 72) {
         parse_my_available_operation_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &my_available_operation_id_)));
          set_has_my_available_operation_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(80)) goto parse_operating_cards;
        break;
      }

      // repeated int32 operating_cards = 10;
      case 10: {
        if (tag == 80) {
         parse_operating_cards:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 80, input, this->mutable_operating_cards())));
        } else if (tag == 82) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_operating_cards())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(80)) goto parse_operating_cards;
        if (input->ExpectTag(88)) goto parse_invisible_hand_cards;
        break;
      }

      // repeated int32 invisible_hand_cards = 11;
      case 11: {
        if (tag == 88) {
         parse_invisible_hand_cards:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 88, input, this->mutable_invisible_hand_cards())));
        } else if (tag == 90) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_invisible_hand_cards())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(88)) goto parse_invisible_hand_cards;
        if (input->ExpectTag(98)) goto parse_ting_cards;
        break;
      }

      // repeated .gamer.protocol.TingCardMsgProtocol ting_cards = 12;
      case 12: {
        if (tag == 98) {
         parse_ting_cards:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_ting_cards()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(98)) goto parse_ting_cards;
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

  // optional int32 discard = 5 [default = -1];
  if (has_discard()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->discard(), output);
  }

  // optional int32 new_card = 6 [default = -1];
  if (has_new_card()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->new_card(), output);
  }

  // optional int32 next_operate_player_id = 7 [default = 0];
  if (has_next_operate_player_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(7, this->next_operate_player_id(), output);
  }

  // optional bool has_next_operate_player_new_card = 8 [default = false];
  if (has_has_next_operate_player_new_card()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(8, this->has_next_operate_player_new_card(), output);
  }

  // optional int32 my_available_operation_id = 9 [default = 0];
  if (has_my_available_operation_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(9, this->my_available_operation_id(), output);
  }

  // repeated int32 operating_cards = 10;
  for (int i = 0; i < this->operating_cards_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(
      10, this->operating_cards(i), output);
  }

  // repeated int32 invisible_hand_cards = 11;
  for (int i = 0; i < this->invisible_hand_cards_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(
      11, this->invisible_hand_cards(i), output);
  }

  // repeated .gamer.protocol.TingCardMsgProtocol ting_cards = 12;
  for (int i = 0; i < this->ting_cards_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      12, this->ting_cards(i), output);
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

  // optional int32 discard = 5 [default = -1];
  if (has_discard()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->discard(), target);
  }

  // optional int32 new_card = 6 [default = -1];
  if (has_new_card()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->new_card(), target);
  }

  // optional int32 next_operate_player_id = 7 [default = 0];
  if (has_next_operate_player_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(7, this->next_operate_player_id(), target);
  }

  // optional bool has_next_operate_player_new_card = 8 [default = false];
  if (has_has_next_operate_player_new_card()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(8, this->has_next_operate_player_new_card(), target);
  }

  // optional int32 my_available_operation_id = 9 [default = 0];
  if (has_my_available_operation_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(9, this->my_available_operation_id(), target);
  }

  // repeated int32 operating_cards = 10;
  for (int i = 0; i < this->operating_cards_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteInt32ToArray(10, this->operating_cards(i), target);
  }

  // repeated int32 invisible_hand_cards = 11;
  for (int i = 0; i < this->invisible_hand_cards_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteInt32ToArray(11, this->invisible_hand_cards(i), target);
  }

  // repeated .gamer.protocol.TingCardMsgProtocol ting_cards = 12;
  for (int i = 0; i < this->ting_cards_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        12, this->ting_cards(i), target);
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

    // optional int32 discard = 5 [default = -1];
    if (has_discard()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->discard());
    }

    // optional int32 new_card = 6 [default = -1];
    if (has_new_card()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->new_card());
    }

    // optional int32 next_operate_player_id = 7 [default = 0];
    if (has_next_operate_player_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->next_operate_player_id());
    }

    // optional bool has_next_operate_player_new_card = 8 [default = false];
    if (has_has_next_operate_player_new_card()) {
      total_size += 1 + 1;
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional int32 my_available_operation_id = 9 [default = 0];
    if (has_my_available_operation_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->my_available_operation_id());
    }

  }
  // repeated int32 operating_cards = 10;
  {
    int data_size = 0;
    for (int i = 0; i < this->operating_cards_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        Int32Size(this->operating_cards(i));
    }
    total_size += 1 * this->operating_cards_size() + data_size;
  }

  // repeated int32 invisible_hand_cards = 11;
  {
    int data_size = 0;
    for (int i = 0; i < this->invisible_hand_cards_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        Int32Size(this->invisible_hand_cards(i));
    }
    total_size += 1 * this->invisible_hand_cards_size() + data_size;
  }

  // repeated .gamer.protocol.TingCardMsgProtocol ting_cards = 12;
  total_size += 1 * this->ting_cards_size();
  for (int i = 0; i < this->ting_cards_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->ting_cards(i));
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
  operating_cards_.MergeFrom(from.operating_cards_);
  invisible_hand_cards_.MergeFrom(from.invisible_hand_cards_);
  ting_cards_.MergeFrom(from.ting_cards_);
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
    if (from.has_new_card()) {
      set_new_card(from.new_card());
    }
    if (from.has_next_operate_player_id()) {
      set_next_operate_player_id(from.next_operate_player_id());
    }
    if (from.has_has_next_operate_player_new_card()) {
      set_has_next_operate_player_new_card(from.has_next_operate_player_new_card());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_my_available_operation_id()) {
      set_my_available_operation_id(from.my_available_operation_id());
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
    std::swap(new_card_, other->new_card_);
    std::swap(next_operate_player_id_, other->next_operate_player_id_);
    std::swap(has_next_operate_player_new_card_, other->has_next_operate_player_new_card_);
    std::swap(my_available_operation_id_, other->my_available_operation_id_);
    operating_cards_.Swap(&other->operating_cards_);
    invisible_hand_cards_.Swap(&other->invisible_hand_cards_);
    ting_cards_.Swap(&other->ting_cards_);
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
