//
// Copyright (c) 2014, Jeongseok Lee (jslee02@gmail.com)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifndef _DART_ENUMS_H_
#define _DART_ENUMS_H_

#include <string>

namespace dart {

class StringEnum
{
public:
//  StringEnum;
};

//enum class ObjectType {
//  None,
//  Invalid
//};

typedef std::string ObjectType;

enum class PropertyCategory {

};

enum class PropertyName {
  Name,
  String,
  DynamicDefVal
};

enum class PropertyType : unsigned long
{
  Normal = 0x00000000,

  GeneralTypeMask = 0x000000FF,
  EnumTypeMask    = 0x0000FF00,
  PointerTypeMask = 0x00FF0000,
  TypeMasks       = 0x00FFFFFF,
  BehaviorMask    = 0xFF000000,

  ReadOnly        = 0x01000000,
  NotSerializable = 0x02000000,
  DynamicDefVal   = 0x04000000,
  NoSave          = 0x08000000,
  UI_Hidden       = 0x10000000,
  UI_Disabled     = 0x20000000,

  Collection = 0x00000001,

  Char   = 0x00000010,
  Byte   = 0x00000011,
  Int32  = 0x00000012,
  UInt32 = 0x00000013,
  Float  = 0x00000014,
  Double = 0x00000015,
  Real   = 0x00000016,
  String = 0x00000017,

  RGB   = 0x0000001C,
  Font  = 0x0000001E,
  GUID  = 0x00000020,
  CLSID = 0x00000021,

  CompName       = 0x00000028,
  MultiLineText  = 0x00000029,
  SingleLineText = 0x00000030,
  FilePath       = 0x00000031,

  UserProperties = 0x00000040,
  UserEvents     = 0x00000041,

  Vec2    = 0x00000050,
  Vec3    = 0x00000051,
  InvVec3 = 0x00000052,
  SO3     = 0x00000053,
  se3     = 0x00000054,
  SE3     = 0x00000055,
  dse3    = 0x00000056,
  Inertia = 0x00000057,

/*EnumerationType: 0x0000??00*/
  ObjectType         = 0x00001100,
  Boolean            = 0x00001200,
  ActuatorType       = 0x00001300,
  MassShapeType      = 0x00001400,
  CollisionShapeType = 0x00001500,
  JointLimitType     = 0x00001600,
  FunctionOnOff      = 0x00001700,
  ControlSyncMode    = 0x00001800,

/*XComponent*: 0x00??0000*/
  CompPtr          = 0x00010000,
  LinkPtr          = 0x00020000,
  JointPtr         = 0x00030000,
  CompArrayPtr     = 0x00040000,
  LinkArrayPtr     = 0x00050000,
  JointArrayPtr    = 0x00060000,
  CompPtrAbs       = 0x00070000,
  LinkPtrAbs       = 0x00080000,
  JointPtrAbs      = 0x00090000,
  CompArrayPtrAbs  = 0x000A0000,
  LinkArrayPtrAbs  = 0x000B0000,
  JointArrayPtrAbs = 0x000C0000,
};

enum TraitString
{
  traitDef  = 0x0001,
  traitAux  = 0x0002,
  traitRes  = 0x0004,
  traitAuto = 0x0008,

  traitAuxNonUnique = 0x0020,
  traitResNonUnique = 0x0040,
  traitAllUnique    = 0x0080,
};

enum class XError {
  Success           = 0,
  TransactionFailed = 1
};

}

#endif  // _DART_ENUMS_H_
