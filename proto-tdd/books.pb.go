// Code generated by protoc-gen-go. DO NOT EDIT.
// source: books.proto

package addbook

import (
	fmt "fmt"
	proto "github.com/golang/protobuf/proto"
	timestamp "github.com/golang/protobuf/ptypes/timestamp"
	math "math"
)

// Reference imports to suppress errors if they are not otherwise used.
var _ = proto.Marshal
var _ = fmt.Errorf
var _ = math.Inf

// This is a compile-time assertion to ensure that this generated file
// is compatible with the proto package it is being compiled against.
// A compilation error at this line likely means your copy of the
// proto package needs to be updated.
const _ = proto.ProtoPackageIsVersion3 // please upgrade the proto package

type Person_PhoneType int32

const (
	Person_MOBILE Person_PhoneType = 0
	Person_HOME   Person_PhoneType = 1
	Person_WORK   Person_PhoneType = 2
)

var Person_PhoneType_name = map[int32]string{
	0: "MOBILE",
	1: "HOME",
	2: "WORK",
}

var Person_PhoneType_value = map[string]int32{
	"MOBILE": 0,
	"HOME":   1,
	"WORK":   2,
}

func (x Person_PhoneType) String() string {
	return proto.EnumName(Person_PhoneType_name, int32(x))
}

func (Person_PhoneType) EnumDescriptor() ([]byte, []int) {
	return fileDescriptor_01e0dc127ded4184, []int{0, 0}
}

type Person struct {
	Name                 string                `protobuf:"bytes,1,opt,name=name,proto3" json:"name,omitempty"`
	Id                   int32                 `protobuf:"varint,2,opt,name=id,proto3" json:"id,omitempty"`
	Email                string                `protobuf:"bytes,3,opt,name=email,proto3" json:"email,omitempty"`
	Phones               []*Person_PhoneNumber `protobuf:"bytes,4,rep,name=phones,proto3" json:"phones,omitempty"`
	LastUpdated          *timestamp.Timestamp  `protobuf:"bytes,5,opt,name=last_updated,json=lastUpdated,proto3" json:"last_updated,omitempty"`
	XXX_NoUnkeyedLiteral struct{}              `json:"-"`
	XXX_unrecognized     []byte                `json:"-"`
	XXX_sizecache        int32                 `json:"-"`
}

func (m *Person) Reset()         { *m = Person{} }
func (m *Person) String() string { return proto.CompactTextString(m) }
func (*Person) ProtoMessage()    {}
func (*Person) Descriptor() ([]byte, []int) {
	return fileDescriptor_01e0dc127ded4184, []int{0}
}

func (m *Person) XXX_Unmarshal(b []byte) error {
	return xxx_messageInfo_Person.Unmarshal(m, b)
}
func (m *Person) XXX_Marshal(b []byte, deterministic bool) ([]byte, error) {
	return xxx_messageInfo_Person.Marshal(b, m, deterministic)
}
func (m *Person) XXX_Merge(src proto.Message) {
	xxx_messageInfo_Person.Merge(m, src)
}
func (m *Person) XXX_Size() int {
	return xxx_messageInfo_Person.Size(m)
}
func (m *Person) XXX_DiscardUnknown() {
	xxx_messageInfo_Person.DiscardUnknown(m)
}

var xxx_messageInfo_Person proto.InternalMessageInfo

func (m *Person) GetName() string {
	if m != nil {
		return m.Name
	}
	return ""
}

func (m *Person) GetId() int32 {
	if m != nil {
		return m.Id
	}
	return 0
}

func (m *Person) GetEmail() string {
	if m != nil {
		return m.Email
	}
	return ""
}

func (m *Person) GetPhones() []*Person_PhoneNumber {
	if m != nil {
		return m.Phones
	}
	return nil
}

func (m *Person) GetLastUpdated() *timestamp.Timestamp {
	if m != nil {
		return m.LastUpdated
	}
	return nil
}

type Person_PhoneNumber struct {
	Number               string           `protobuf:"bytes,1,opt,name=number,proto3" json:"number,omitempty"`
	Type                 Person_PhoneType `protobuf:"varint,2,opt,name=type,proto3,enum=addbook.Person_PhoneType" json:"type,omitempty"`
	XXX_NoUnkeyedLiteral struct{}         `json:"-"`
	XXX_unrecognized     []byte           `json:"-"`
	XXX_sizecache        int32            `json:"-"`
}

func (m *Person_PhoneNumber) Reset()         { *m = Person_PhoneNumber{} }
func (m *Person_PhoneNumber) String() string { return proto.CompactTextString(m) }
func (*Person_PhoneNumber) ProtoMessage()    {}
func (*Person_PhoneNumber) Descriptor() ([]byte, []int) {
	return fileDescriptor_01e0dc127ded4184, []int{0, 0}
}

func (m *Person_PhoneNumber) XXX_Unmarshal(b []byte) error {
	return xxx_messageInfo_Person_PhoneNumber.Unmarshal(m, b)
}
func (m *Person_PhoneNumber) XXX_Marshal(b []byte, deterministic bool) ([]byte, error) {
	return xxx_messageInfo_Person_PhoneNumber.Marshal(b, m, deterministic)
}
func (m *Person_PhoneNumber) XXX_Merge(src proto.Message) {
	xxx_messageInfo_Person_PhoneNumber.Merge(m, src)
}
func (m *Person_PhoneNumber) XXX_Size() int {
	return xxx_messageInfo_Person_PhoneNumber.Size(m)
}
func (m *Person_PhoneNumber) XXX_DiscardUnknown() {
	xxx_messageInfo_Person_PhoneNumber.DiscardUnknown(m)
}

var xxx_messageInfo_Person_PhoneNumber proto.InternalMessageInfo

func (m *Person_PhoneNumber) GetNumber() string {
	if m != nil {
		return m.Number
	}
	return ""
}

func (m *Person_PhoneNumber) GetType() Person_PhoneType {
	if m != nil {
		return m.Type
	}
	return Person_MOBILE
}

type AddressBook struct {
	People               []*Person `protobuf:"bytes,1,rep,name=people,proto3" json:"people,omitempty"`
	XXX_NoUnkeyedLiteral struct{}  `json:"-"`
	XXX_unrecognized     []byte    `json:"-"`
	XXX_sizecache        int32     `json:"-"`
}

func (m *AddressBook) Reset()         { *m = AddressBook{} }
func (m *AddressBook) String() string { return proto.CompactTextString(m) }
func (*AddressBook) ProtoMessage()    {}
func (*AddressBook) Descriptor() ([]byte, []int) {
	return fileDescriptor_01e0dc127ded4184, []int{1}
}

func (m *AddressBook) XXX_Unmarshal(b []byte) error {
	return xxx_messageInfo_AddressBook.Unmarshal(m, b)
}
func (m *AddressBook) XXX_Marshal(b []byte, deterministic bool) ([]byte, error) {
	return xxx_messageInfo_AddressBook.Marshal(b, m, deterministic)
}
func (m *AddressBook) XXX_Merge(src proto.Message) {
	xxx_messageInfo_AddressBook.Merge(m, src)
}
func (m *AddressBook) XXX_Size() int {
	return xxx_messageInfo_AddressBook.Size(m)
}
func (m *AddressBook) XXX_DiscardUnknown() {
	xxx_messageInfo_AddressBook.DiscardUnknown(m)
}

var xxx_messageInfo_AddressBook proto.InternalMessageInfo

func (m *AddressBook) GetPeople() []*Person {
	if m != nil {
		return m.People
	}
	return nil
}

func init() {
	proto.RegisterEnum("addbook.Person_PhoneType", Person_PhoneType_name, Person_PhoneType_value)
	proto.RegisterType((*Person)(nil), "addbook.Person")
	proto.RegisterType((*Person_PhoneNumber)(nil), "addbook.Person.PhoneNumber")
	proto.RegisterType((*AddressBook)(nil), "addbook.AddressBook")
}

func init() { proto.RegisterFile("books.proto", fileDescriptor_01e0dc127ded4184) }

var fileDescriptor_01e0dc127ded4184 = []byte{
	// 308 bytes of a gzipped FileDescriptorProto
	0x1f, 0x8b, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0x6c, 0x90, 0x41, 0x4b, 0xc3, 0x40,
	0x10, 0x85, 0x4d, 0x9a, 0x46, 0x3b, 0x91, 0x5a, 0x06, 0x91, 0x58, 0x0f, 0x86, 0x5e, 0x0c, 0x88,
	0x5b, 0x68, 0xc1, 0x9b, 0x07, 0x0b, 0x05, 0x45, 0x6b, 0xcb, 0x52, 0xf1, 0x28, 0x09, 0x3b, 0xd6,
	0xd0, 0x24, 0xbb, 0x64, 0x93, 0x43, 0x7f, 0x9a, 0xff, 0x4e, 0xb2, 0x49, 0x45, 0xc4, 0xdb, 0x7b,
	0x33, 0x1f, 0x33, 0x6f, 0x06, 0xbc, 0x58, 0xca, 0xad, 0x66, 0xaa, 0x90, 0xa5, 0xc4, 0xc3, 0x48,
	0x88, 0xda, 0x0f, 0x2f, 0x37, 0x52, 0x6e, 0x52, 0x1a, 0x9b, 0x72, 0x5c, 0x7d, 0x8c, 0xcb, 0x24,
	0x23, 0x5d, 0x46, 0x99, 0x6a, 0xc8, 0xd1, 0x97, 0x0d, 0xee, 0x8a, 0x0a, 0x2d, 0x73, 0x44, 0x70,
	0xf2, 0x28, 0x23, 0xdf, 0x0a, 0xac, 0xb0, 0xc7, 0x8d, 0xc6, 0x3e, 0xd8, 0x89, 0xf0, 0xed, 0xc0,
	0x0a, 0xbb, 0xdc, 0x4e, 0x04, 0x9e, 0x42, 0x97, 0xb2, 0x28, 0x49, 0xfd, 0x8e, 0x81, 0x1a, 0x83,
	0x53, 0x70, 0xd5, 0xa7, 0xcc, 0x49, 0xfb, 0x4e, 0xd0, 0x09, 0xbd, 0xc9, 0x05, 0x6b, 0xf7, 0xb3,
	0x66, 0x34, 0x5b, 0xd5, 0xdd, 0x97, 0x2a, 0x8b, 0xa9, 0xe0, 0x2d, 0x8a, 0x77, 0x70, 0x9c, 0x46,
	0xba, 0x7c, 0xaf, 0x94, 0x88, 0x4a, 0x12, 0x7e, 0x37, 0xb0, 0x42, 0x6f, 0x32, 0x64, 0x4d, 0x62,
	0xb6, 0x4f, 0xcc, 0xd6, 0xfb, 0xc4, 0xdc, 0xab, 0xf9, 0xd7, 0x06, 0x1f, 0xae, 0xc1, 0xfb, 0x35,
	0x15, 0xcf, 0xc0, 0xcd, 0x8d, 0x6a, 0xe3, 0xb7, 0x0e, 0x6f, 0xc0, 0x29, 0x77, 0x8a, 0xcc, 0x09,
	0xfd, 0xc9, 0xf9, 0xbf, 0xc1, 0xd6, 0x3b, 0x45, 0xdc, 0x60, 0xa3, 0x6b, 0xe8, 0xfd, 0x94, 0x10,
	0xc0, 0x5d, 0x2c, 0x67, 0x8f, 0xcf, 0xf3, 0xc1, 0x01, 0x1e, 0x81, 0xf3, 0xb0, 0x5c, 0xcc, 0x07,
	0x56, 0xad, 0xde, 0x96, 0xfc, 0x69, 0x60, 0x8f, 0x6e, 0xc1, 0xbb, 0x17, 0xa2, 0x20, 0xad, 0x67,
	0x52, 0x6e, 0xf1, 0x0a, 0x5c, 0x45, 0x52, 0xa5, 0xf5, 0x07, 0xeb, 0x2f, 0x9c, 0xfc, 0x59, 0xc6,
	0xdb, 0x76, 0xec, 0x9a, 0xdb, 0xa6, 0xdf, 0x01, 0x00, 0x00, 0xff, 0xff, 0x93, 0x7f, 0x72, 0x5b,
	0xb3, 0x01, 0x00, 0x00,
}
