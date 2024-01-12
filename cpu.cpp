#include "cpu.hpp"
#include <tuple>

void Cpu::disableInterrupts(void) {
  this->interruptsEnabled = false;
}

void Cpu::enableInterrupts(void) {
  this->interruptsEnabled = true;
}

void Cpu::halt(void) {
  this->isHalted = true;
}

void Cpu::run(void) {
  this->isHalted = false;
}

bool Cpu::cOverflowAdd(uint8_t v1, uint8_t v2) {
  return ((static_cast<int>(v1) + static_cast<int>(v2)) > 0xff);
}

bool Cpu::hOverflowAdd(uint8_t v1, uint8_t v2) {
  return ((static_cast<int>(v1 & 0xf) + static_cast<int>(v2 & 0xf)) > 0xf);
}

bool Cpu::cOverflowSub(uint8_t v1, uint8_t v2) {
  return (v1 < v2);
}

bool Cpu::hOverflowSub(uint8_t v1, uint8_t v2) {
  return ((v1 & 0xf) < (v2 & 0xf));
}

bool Cpu::cOverflowAdd16(uint16_t v1, uint16_t v2) {
  return ((static_cast<int>(v1) + static_cast<int>(v2)) > 0xffff);
}

bool Cpu::hOverflowAdd16(uint16_t v1, uint16_t v2) {
  return ((static_cast<int>(v1 & 0xfff) + static_cast<int>(v2 & 0xfff)) > 0xfff);
}

uint16_t Cpu::execInstruction() {
  uint8_t opcode = 0;
  std::tie(opcode, this->pc) = this->memoryBus->fetchInstruction(this->pc);

  uint8_t &a = this->registers.a;
  uint8_t &b = this->registers.b;
  uint8_t &c = this->registers.c;
  uint8_t &d = this->registers.d;
  uint8_t &e = this->registers.e;
  uint8_t &h = this->registers.h;
  uint8_t &l = this->registers.l;

  std::cout << "OPCODE: " << std::hex << static_cast<int>(opcode) << ", PC: " << static_cast<int>(this->pc) << std::endl;

  if(opcode == 0x00) { opcode_00(); }
  if(opcode == 0x01) { opcode_01(); }
  if(opcode == 0x02) { opcode_02(a); }
  if(opcode == 0x03) { opcode_03(); }
  if(opcode == 0x04) { opcode_04(b); }
  if(opcode == 0x05) { opcode_05(b); }
  if(opcode == 0x06) { opcode_06(b); }
  if(opcode == 0x07) { opcode_07(a); }
  if(opcode == 0x08) { opcode_08(); }
  if(opcode == 0x09) { opcode_09(); }
  if(opcode == 0x0a) { opcode_0a(a); }
  if(opcode == 0x0b) { opcode_0b(); }
  if(opcode == 0x0c) { opcode_0c(c); }
  if(opcode == 0x0d) { opcode_0d(c); }
  if(opcode == 0x0e) { opcode_0e(c); }
  if(opcode == 0x0f) { opcode_0f(a); }

  if(opcode == 0x10) { opcode_10(); }
  if(opcode == 0x11) { opcode_11(); }
  if(opcode == 0x12) { opcode_12(a); }
  if(opcode == 0x13) { opcode_13(); }
  if(opcode == 0x14) { opcode_14(d); }
  if(opcode == 0x15) { opcode_15(d); }
  if(opcode == 0x16) { opcode_16(d); }
  if(opcode == 0x17) { opcode_17(a); }
  if(opcode == 0x18) { opcode_18(); }
  if(opcode == 0x19) { opcode_19(); }
  if(opcode == 0x1a) { opcode_1a(a); }
  if(opcode == 0x1b) { opcode_1b(); }
  if(opcode == 0x1c) { opcode_1c(e); }
  if(opcode == 0x1d) { opcode_1d(e); }
  if(opcode == 0x1e) { opcode_1e(e); }
  if(opcode == 0x1f) { opcode_1f(a); }

  if(opcode == 0x20) { opcode_20(); }
  if(opcode == 0x21) { opcode_21(); }
  if(opcode == 0x22) { opcode_22(a); }
  if(opcode == 0x23) { opcode_23(); }
  if(opcode == 0x24) { opcode_24(h); }
  if(opcode == 0x25) { opcode_25(h); }
  if(opcode == 0x26) { opcode_26(h); }
  if(opcode == 0x27) { opcode_27(); }
  if(opcode == 0x28) { opcode_28(); }
  if(opcode == 0x29) { opcode_29(); }
  if(opcode == 0x2a) { opcode_2a(a); }
  if(opcode == 0x2b) { opcode_2b(); }
  if(opcode == 0x2c) { opcode_2c(l); }
  if(opcode == 0x2d) { opcode_2d(l); }
  if(opcode == 0x2e) { opcode_2e(l); }
  if(opcode == 0x2f) { opcode_2f(a); }

  if(opcode == 0x30) { opcode_30(); }
  if(opcode == 0x31) { opcode_31(); }
  if(opcode == 0x32) { opcode_32(a); }
  if(opcode == 0x33) { opcode_33(); }
  if(opcode == 0x34) { opcode_34(); }
  if(opcode == 0x35) { opcode_35(); }
  if(opcode == 0x36) { opcode_36(); }
  if(opcode == 0x37) { opcode_37(); }
  if(opcode == 0x38) { opcode_38(); }
  if(opcode == 0x39) { opcode_39(); }
  if(opcode == 0x3a) { opcode_3a(a); }
  if(opcode == 0x3b) { opcode_3b(); }
  if(opcode == 0x3c) { opcode_3c(a); }
  if(opcode == 0x3d) { opcode_3d(a); }
  if(opcode == 0x3e) { opcode_3e(a); }
  if(opcode == 0x3f) { opcode_3f(); }

  if(opcode == 0x40) { opcode_40(b); }
  if(opcode == 0x41) { opcode_41(b, c); }
  if(opcode == 0x42) { opcode_42(b, d); }
  if(opcode == 0x43) { opcode_43(b, e); }
  if(opcode == 0x44) { opcode_44(b, h); }
  if(opcode == 0x45) { opcode_45(b, l); }
  if(opcode == 0x46) { opcode_46(b); }
  if(opcode == 0x47) { opcode_47(b, a); }
  if(opcode == 0x48) { opcode_48(c, b); }
  if(opcode == 0x49) { opcode_49(c); }
  if(opcode == 0x4a) { opcode_4a(c, d); }
  if(opcode == 0x4b) { opcode_4b(c, e); }
  if(opcode == 0x4c) { opcode_4c(c, h); }
  if(opcode == 0x4d) { opcode_4d(c, l); }
  if(opcode == 0x4e) { opcode_4e(c); }
  if(opcode == 0x4f) { opcode_4f(c, a); }

  if(opcode == 0x50) { opcode_50(d, b); }
  if(opcode == 0x51) { opcode_51(d, c); }
  if(opcode == 0x52) { opcode_52(d); }
  if(opcode == 0x53) { opcode_53(d, e); }
  if(opcode == 0x54) { opcode_54(d, h); }
  if(opcode == 0x55) { opcode_55(d, l); }
  if(opcode == 0x56) { opcode_56(d); }
  if(opcode == 0x57) { opcode_57(d, a); }
  if(opcode == 0x58) { opcode_58(e, b); }
  if(opcode == 0x59) { opcode_59(e, c); }
  if(opcode == 0x5a) { opcode_5a(e, d); }
  if(opcode == 0x5b) { opcode_5b(e); }
  if(opcode == 0x5c) { opcode_5c(e, h); }
  if(opcode == 0x5d) { opcode_5d(e, l); }
  if(opcode == 0x5e) { opcode_5e(e); }
  if(opcode == 0x5f) { opcode_5f(e, a); }

  if(opcode == 0x60) { opcode_60(h, b); }
  if(opcode == 0x61) { opcode_61(h, c); }
  if(opcode == 0x62) { opcode_62(h, d); }
  if(opcode == 0x63) { opcode_63(h, e); }
  if(opcode == 0x64) { opcode_64(h); }
  if(opcode == 0x65) { opcode_65(h, l); }
  if(opcode == 0x66) { opcode_66(h); }
  if(opcode == 0x67) { opcode_67(h, a); }
  if(opcode == 0x68) { opcode_68(l, b); }
  if(opcode == 0x69) { opcode_69(l, c); }
  if(opcode == 0x6a) { opcode_6a(l, d); }
  if(opcode == 0x6b) { opcode_6b(l, e); }
  if(opcode == 0x6c) { opcode_6c(l, h); }
  if(opcode == 0x6d) { opcode_6d(l); }
  if(opcode == 0x6e) { opcode_6e(l); }
  if(opcode == 0x6f) { opcode_6f(l, a); }

  if(opcode == 0x70) { opcode_70(b); }
  if(opcode == 0x71) { opcode_71(c); }
  if(opcode == 0x72) { opcode_72(d); }
  if(opcode == 0x73) { opcode_73(e); }
  if(opcode == 0x74) { opcode_74(h); }
  if(opcode == 0x75) { opcode_75(l); }
  if(opcode == 0x76) { opcode_76(); }
  if(opcode == 0x77) { opcode_77(a); }
  if(opcode == 0x78) { opcode_78(a, b); }
  if(opcode == 0x79) { opcode_79(a, c); }
  if(opcode == 0x7a) { opcode_7a(a, d); }
  if(opcode == 0x7b) { opcode_7b(a, e); }
  if(opcode == 0x7c) { opcode_7c(a, h); }
  if(opcode == 0x7d) { opcode_7d(a, l); }
  if(opcode == 0x7e) { opcode_7e(a); }
  if(opcode == 0x7f) { opcode_7f(a); }
  
  // ADD
  if(opcode == 0x80) { opcode_80(a, b); }
  if(opcode == 0x81) { opcode_81(a, c); }
  if(opcode == 0x82) { opcode_82(a, d); }
  if(opcode == 0x83) { opcode_83(a, e); }
  if(opcode == 0x84) { opcode_84(a, h); }
  if(opcode == 0x85) { opcode_85(a, l); }
  if(opcode == 0x86) { opcode_86(a); }
  if(opcode == 0x87) { opcode_87(a); }

  // ADC
  if(opcode == 0x88) { opcode_88(a, b); }
  if(opcode == 0x89) { opcode_89(a, c); }
  if(opcode == 0x8a) { opcode_8a(a, d); }
  if(opcode == 0x8b) { opcode_8b(a, e); }
  if(opcode == 0x8c) { opcode_8c(a, h); }
  if(opcode == 0x8d) { opcode_8d(a, l); }
  if(opcode == 0x8e) { opcode_8e(a); }
  if(opcode == 0x8f) { opcode_8f(a); }

  // SUB
  if(opcode == 0x90) { opcode_90(a, b); }
  if(opcode == 0x91) { opcode_91(a, c); }
  if(opcode == 0x92) { opcode_92(a, b); }
  if(opcode == 0x93) { opcode_93(a, d); }
  if(opcode == 0x94) { opcode_94(a, e); }
  if(opcode == 0x95) { opcode_95(a, h); }
  if(opcode == 0x96) { opcode_96(a); }
  if(opcode == 0x97) { opcode_97(a); }

  // SBC
  if(opcode == 0x98) { opcode_98(a, b); }
  if(opcode == 0x99) { opcode_99(a, c); }
  if(opcode == 0x9a) { opcode_9a(a, d); }
  if(opcode == 0x9b) { opcode_9b(a, e); }
  if(opcode == 0x9c) { opcode_9c(a, h); }
  if(opcode == 0x9d) { opcode_9d(a, l); }
  if(opcode == 0x9e) { opcode_9e(a); }
  if(opcode == 0x9f) { opcode_9f(a); }

  // AND
  if(opcode == 0xa0) { opcode_a0(a, b); }
  if(opcode == 0xa1) { opcode_a1(a, c); }
  if(opcode == 0xa2) { opcode_a2(a, d); }
  if(opcode == 0xa3) { opcode_a3(a, e); }
  if(opcode == 0xa4) { opcode_a4(a, h); }
  if(opcode == 0xa5) { opcode_a5(a, l); }
  if(opcode == 0xa6) { opcode_a6(a); }
  if(opcode == 0xa7) { opcode_a7(a); }

  // XOR
  if(opcode == 0xa8) { opcode_a8(a, b); }
  if(opcode == 0xa9) { opcode_a9(a, c); }
  if(opcode == 0xaa) { opcode_aa(a, d); }
  if(opcode == 0xab) { opcode_ab(a, e); }
  if(opcode == 0xac) { opcode_ac(a, h); }
  if(opcode == 0xad) { opcode_ad(a, l); }
  if(opcode == 0xae) { opcode_ae(a); }
  if(opcode == 0xaf) { opcode_af(a); }

  // OR
  if(opcode == 0xb0) { opcode_b0(a, b); }
  if(opcode == 0xb1) { opcode_b1(a, c); }
  if(opcode == 0xb2) { opcode_b2(a, d); }
  if(opcode == 0xb3) { opcode_b3(a, e); }
  if(opcode == 0xb4) { opcode_b4(a, h); }
  if(opcode == 0xb5) { opcode_b5(a, l); }
  if(opcode == 0xb6) { opcode_b6(a); }
  if(opcode == 0xb7) { opcode_b7(a); }

  // CP
  if(opcode == 0xb8) { opcode_b8(a, b); }
  if(opcode == 0xb9) { opcode_b9(a, c); }
  if(opcode == 0xba) { opcode_ba(a, d); }
  if(opcode == 0xbb) { opcode_bb(a, e); }
  if(opcode == 0xbc) { opcode_bc(a, h); }
  if(opcode == 0xbd) { opcode_bd(a, l); }
  if(opcode == 0xbe) { opcode_be(a); }
  if(opcode == 0xbf) { opcode_bf(a); }

  if(opcode == 0xc0) { opcode_c0(); }
  if(opcode == 0xc1) { opcode_c1(); }
  if(opcode == 0xc2) { opcode_c2(); }
  if(opcode == 0xc3) { opcode_c3(); }
  if(opcode == 0xc4) { opcode_c4(); }
  if(opcode == 0xc5) { opcode_c5(); }
  if(opcode == 0xc6) { opcode_c6(a); }
  if(opcode == 0xc7) { opcode_c7(); }
  if(opcode == 0xc8) { opcode_c8(); }
  if(opcode == 0xc9) { opcode_c9(); }
  if(opcode == 0xca) { opcode_ca(); }
  if(opcode == 0xcb) { opcode_cb(); }
  if(opcode == 0xcc) { opcode_cc(); }
  if(opcode == 0xcd) { opcode_cd(); }
  if(opcode == 0xce) { opcode_ce(a); }
  if(opcode == 0xcf) { opcode_cf(); }

  if(opcode == 0xd0) { opcode_d0(); }
  if(opcode == 0xd1) { opcode_d1(); }
  if(opcode == 0xd2) { opcode_d2(); }
  if(opcode == 0xd3) { opcode_d3(); }
  if(opcode == 0xd4) { opcode_d4(); }
  if(opcode == 0xd5) { opcode_d5(); }
  if(opcode == 0xd6) { opcode_d6(a); }
  if(opcode == 0xd7) { opcode_d7(); }
  if(opcode == 0xd8) { opcode_d8(); }
  if(opcode == 0xd9) { opcode_d9(); }
  if(opcode == 0xda) { opcode_da(); }
  if(opcode == 0xdb) { opcode_db(); }
  if(opcode == 0xdc) { opcode_dc(); }
  if(opcode == 0xdd) { opcode_dd(); }
  if(opcode == 0xde) { opcode_de(a); }
  if(opcode == 0xdf) { opcode_df(); }

  if(opcode == 0xe0) { opcode_e0(a); }
  if(opcode == 0xe1) { opcode_e1(); }
  if(opcode == 0xe2) { opcode_e2(a); }
  if(opcode == 0xe3) { opcode_e3(); }
  if(opcode == 0xe4) { opcode_e4(); }
  if(opcode == 0xe5) { opcode_e5(); }
  if(opcode == 0xe6) { opcode_e6(a); }
  if(opcode == 0xe7) { opcode_e7(); }
  if(opcode == 0xe8) { opcode_e8(); }
  if(opcode == 0xe9) { opcode_e9(); }
  if(opcode == 0xea) { opcode_ea(a); }
  if(opcode == 0xeb) { opcode_eb(); }
  if(opcode == 0xec) { opcode_ec(); }
  if(opcode == 0xed) { opcode_ed(); }
  if(opcode == 0xee) { opcode_ee(a); }
  if(opcode == 0xef) { opcode_ef(); }

  if(opcode == 0xf0) { opcode_f0(a); }
  if(opcode == 0xf1) { opcode_f1(); }
  if(opcode == 0xf2) { opcode_f2(a); }
  if(opcode == 0xf3) { opcode_f3(); }
  if(opcode == 0xf4) { opcode_f4(); }
  if(opcode == 0xf5) { opcode_f5(); }
  if(opcode == 0xf6) { opcode_f6(a); }
  if(opcode == 0xf7) { opcode_f7(); }
  if(opcode == 0xf8) { opcode_f8(); }
  if(opcode == 0xf9) { opcode_f9(); }
  if(opcode == 0xfa) { opcode_fa(a); }
  if(opcode == 0xfb) { opcode_fb(); }
  if(opcode == 0xfc) { opcode_fc(); }
  if(opcode == 0xfd) { opcode_fd(); }
  if(opcode == 0xfe) { opcode_fe(a); }
  if(opcode == 0xff) { opcode_ff(); }

  if(opcode != 0xcb)
    return this->pc;
  
  // if function continues execution, means opcode is 0xCB
  // i.e the prefix opcode -- meaning we need to get second
  // opcode to determine what operation to perform
  uint8_t prefix;
  std::tie(prefix, this->pc) = this->memoryBus->fetchInstruction(this->pc);
  
  if(prefix == 0x00) { opcode_cb00(b); }
  if(prefix == 0x01) { opcode_cb01(c); }
  if(prefix == 0x02) { opcode_cb02(d); }
  if(prefix == 0x03) { opcode_cb03(e); }
  if(prefix == 0x04) { opcode_cb04(h); }
  if(prefix == 0x05) { opcode_cb05(l); }
  if(prefix == 0x06) { opcode_cb06(); }
  if(prefix == 0x07) { opcode_cb07(a); }
  if(prefix == 0x08) { opcode_cb08(b); }
  if(prefix == 0x09) { opcode_cb09(c); }
  if(prefix == 0x0a) { opcode_cb0a(d); }
  if(prefix == 0x0b) { opcode_cb0b(e); }
  if(prefix == 0x0c) { opcode_cb0c(h); }
  if(prefix == 0x0d) { opcode_cb0d(l); }
  if(prefix == 0x0e) { opcode_cb0e(); }
  if(prefix == 0x0f) { opcode_cb0f(a); }
  
  if(prefix == 0x10) { opcode_cb10(b); }
  if(prefix == 0x11) { opcode_cb11(c); }
  if(prefix == 0x12) { opcode_cb12(d); }
  if(prefix == 0x13) { opcode_cb13(e); }
  if(prefix == 0x14) { opcode_cb14(h); }
  if(prefix == 0x15) { opcode_cb15(l); }
  if(prefix == 0x16) { opcode_cb16(); }
  if(prefix == 0x17) { opcode_cb17(a); }
  if(prefix == 0x18) { opcode_cb18(b); }
  if(prefix == 0x19) { opcode_cb19(c); }
  if(prefix == 0x1a) { opcode_cb1a(d); }
  if(prefix == 0x1b) { opcode_cb1b(e); }
  if(prefix == 0x1c) { opcode_cb1c(h); }
  if(prefix == 0x1d) { opcode_cb1d(l); }
  if(prefix == 0x1e) { opcode_cb1e(); }
  if(prefix == 0x1f) { opcode_cb1f(a); }

  if(prefix == 0x20) { opcode_cb20(b); }
  if(prefix == 0x21) { opcode_cb21(c); }
  if(prefix == 0x22) { opcode_cb22(d); }
  if(prefix == 0x23) { opcode_cb23(e); }
  if(prefix == 0x24) { opcode_cb24(h); }
  if(prefix == 0x25) { opcode_cb25(l); }
  if(prefix == 0x26) { opcode_cb26(); }
  if(prefix == 0x27) { opcode_cb27(a); }
  if(prefix == 0x28) { opcode_cb28(b); }
  if(prefix == 0x29) { opcode_cb29(c); }
  if(prefix == 0x2a) { opcode_cb2a(d); }
  if(prefix == 0x2b) { opcode_cb2b(e); }
  if(prefix == 0x2c) { opcode_cb2c(h); }
  if(prefix == 0x2d) { opcode_cb2d(l); }
  if(prefix == 0x2e) { opcode_cb2e(); }
  if(prefix == 0x2f) { opcode_cb2f(a); }

  if(prefix == 0x30) { opcode_cb30(b); }
  if(prefix == 0x31) { opcode_cb31(c); }
  if(prefix == 0x32) { opcode_cb32(d); }
  if(prefix == 0x33) { opcode_cb33(e); }
  if(prefix == 0x34) { opcode_cb34(h); }
  if(prefix == 0x35) { opcode_cb35(l); }
  if(prefix == 0x36) { opcode_cb36(); }
  if(prefix == 0x37) { opcode_cb37(a); }
  if(prefix == 0x38) { opcode_cb38(b); }
  if(prefix == 0x39) { opcode_cb39(c); }
  if(prefix == 0x3a) { opcode_cb3a(d); }
  if(prefix == 0x3b) { opcode_cb3b(e); }
  if(prefix == 0x3c) { opcode_cb3c(h); }
  if(prefix == 0x3d) { opcode_cb3d(l); }
  if(prefix == 0x3e) { opcode_cb3e(); }
  if(prefix == 0x3f) { opcode_cb3f(a); }

  if(prefix == 0x40) { opcode_cb40(b); }
  if(prefix == 0x41) { opcode_cb41(c); }
  if(prefix == 0x42) { opcode_cb42(d); }
  if(prefix == 0x43) { opcode_cb43(e); }
  if(prefix == 0x44) { opcode_cb44(h); }
  if(prefix == 0x45) { opcode_cb45(l); }
  if(prefix == 0x46) { opcode_cb46(); }
  if(prefix == 0x47) { opcode_cb47(a); }
  if(prefix == 0x48) { opcode_cb48(b); }
  if(prefix == 0x49) { opcode_cb49(c); }
  if(prefix == 0x4a) { opcode_cb4a(d); }
  if(prefix == 0x4b) { opcode_cb4b(e); }
  if(prefix == 0x4c) { opcode_cb4c(h); }
  if(prefix == 0x4d) { opcode_cb4d(l); }
  if(prefix == 0x4e) { opcode_cb4e(); }
  if(prefix == 0x4f) { opcode_cb4f(a); }

  if(prefix == 0x50) { opcode_cb50(b); }
  if(prefix == 0x51) { opcode_cb51(c); }
  if(prefix == 0x52) { opcode_cb52(d); }
  if(prefix == 0x53) { opcode_cb53(e); }
  if(prefix == 0x54) { opcode_cb54(h); }
  if(prefix == 0x55) { opcode_cb55(l); }
  if(prefix == 0x56) { opcode_cb56(); }
  if(prefix == 0x57) { opcode_cb57(a); }
  if(prefix == 0x58) { opcode_cb58(b); }
  if(prefix == 0x59) { opcode_cb59(c); }
  if(prefix == 0x5a) { opcode_cb5a(d); }
  if(prefix == 0x5b) { opcode_cb5b(e); }
  if(prefix == 0x5c) { opcode_cb5c(h); }
  if(prefix == 0x5d) { opcode_cb5d(l); }
  if(prefix == 0x5e) { opcode_cb5e(); }
  if(prefix == 0x5f) { opcode_cb5f(a); }

  if(prefix == 0x60) { opcode_cb60(b); }
  if(prefix == 0x61) { opcode_cb61(c); }
  if(prefix == 0x62) { opcode_cb62(d); }
  if(prefix == 0x63) { opcode_cb63(e); }
  if(prefix == 0x64) { opcode_cb64(h); }
  if(prefix == 0x65) { opcode_cb65(l); }
  if(prefix == 0x66) { opcode_cb66(); }
  if(prefix == 0x67) { opcode_cb67(a); }
  if(prefix == 0x68) { opcode_cb68(b); }
  if(prefix == 0x69) { opcode_cb69(c); }
  if(prefix == 0x6a) { opcode_cb6a(d); }
  if(prefix == 0x6b) { opcode_cb6b(e); }
  if(prefix == 0x6c) { opcode_cb6c(h); }
  if(prefix == 0x6d) { opcode_cb6d(l); }
  if(prefix == 0x6e) { opcode_cb6e(); }
  if(prefix == 0x6f) { opcode_cb6f(a); }

  if(prefix == 0x70) { opcode_cb70(b); }
  if(prefix == 0x71) { opcode_cb71(c); }
  if(prefix == 0x72) { opcode_cb72(d); }
  if(prefix == 0x73) { opcode_cb73(e); }
  if(prefix == 0x74) { opcode_cb74(h); }
  if(prefix == 0x75) { opcode_cb75(l); }
  if(prefix == 0x76) { opcode_cb76(); }
  if(prefix == 0x77) { opcode_cb77(a); }
  if(prefix == 0x78) { opcode_cb78(b); }
  if(prefix == 0x79) { opcode_cb79(c); }
  if(prefix == 0x7a) { opcode_cb7a(d); }
  if(prefix == 0x7b) { opcode_cb7b(e); }
  if(prefix == 0x7c) { opcode_cb7c(h); }
  if(prefix == 0x7d) { opcode_cb7d(l); }
  if(prefix == 0x7e) { opcode_cb7e(); }
  if(prefix == 0x7f) { opcode_cb7f(a); }

  if(prefix == 0x80) { opcode_cb80(b); }
  if(prefix == 0x81) { opcode_cb81(c); }
  if(prefix == 0x82) { opcode_cb82(d); }
  if(prefix == 0x83) { opcode_cb83(e); }
  if(prefix == 0x84) { opcode_cb84(h); }
  if(prefix == 0x85) { opcode_cb85(l); }
  if(prefix == 0x86) { opcode_cb86(); }
  if(prefix == 0x87) { opcode_cb87(a); }
  if(prefix == 0x88) { opcode_cb88(b); }
  if(prefix == 0x89) { opcode_cb89(c); }
  if(prefix == 0x8a) { opcode_cb8a(d); }
  if(prefix == 0x8b) { opcode_cb8b(e); }
  if(prefix == 0x8c) { opcode_cb8c(h); }
  if(prefix == 0x8d) { opcode_cb8d(l); }
  if(prefix == 0x8e) { opcode_cb8e(); }
  if(prefix == 0x8f) { opcode_cb8f(a); }

  if(prefix == 0x90) { opcode_cb90(b); }
  if(prefix == 0x91) { opcode_cb91(c); }
  if(prefix == 0x92) { opcode_cb92(d); }
  if(prefix == 0x93) { opcode_cb93(e); }
  if(prefix == 0x94) { opcode_cb94(h); }
  if(prefix == 0x95) { opcode_cb95(l); }
  if(prefix == 0x96) { opcode_cb96(); }
  if(prefix == 0x97) { opcode_cb97(a); }
  if(prefix == 0x98) { opcode_cb98(b); }
  if(prefix == 0x99) { opcode_cb99(c); }
  if(prefix == 0x9a) { opcode_cb9a(d); }
  if(prefix == 0x9b) { opcode_cb9b(e); }
  if(prefix == 0x9c) { opcode_cb9c(h); }
  if(prefix == 0x9d) { opcode_cb9d(l); }
  if(prefix == 0x9e) { opcode_cb9e(); }
  if(prefix == 0x9f) { opcode_cb9f(a); }

  if(prefix == 0xa0) { opcode_cba0(b); }
  if(prefix == 0xa1) { opcode_cba1(c); }
  if(prefix == 0xa2) { opcode_cba2(d); }
  if(prefix == 0xa3) { opcode_cba3(e); }
  if(prefix == 0xa4) { opcode_cba4(h); }
  if(prefix == 0xa5) { opcode_cba5(l); }
  if(prefix == 0xa6) { opcode_cba6(); }
  if(prefix == 0xa7) { opcode_cba7(a); }
  if(prefix == 0xa8) { opcode_cba8(b); }
  if(prefix == 0xa9) { opcode_cba9(c); }
  if(prefix == 0xaa) { opcode_cbaa(d); }
  if(prefix == 0xab) { opcode_cbab(e); }
  if(prefix == 0xac) { opcode_cbac(h); }
  if(prefix == 0xad) { opcode_cbad(l); }
  if(prefix == 0xae) { opcode_cbae(); }
  if(prefix == 0xaf) { opcode_cbaf(a); }

  if(prefix == 0x00) { opcode_cb00(b); }
  if(prefix == 0x01) { opcode_cb01(c); }
  if(prefix == 0x02) { opcode_cb02(d); }
  if(prefix == 0x03) { opcode_cb03(e); }
  if(prefix == 0x04) { opcode_cb04(h); }
  if(prefix == 0x05) { opcode_cb05(l); }
  if(prefix == 0x06) { opcode_cb06(); }
  if(prefix == 0x07) { opcode_cb07(a); }
  if(prefix == 0x08) { opcode_cb08(b); }
  if(prefix == 0x09) { opcode_cb09(c); }
  if(prefix == 0x0a) { opcode_cb0a(d); }
  if(prefix == 0x0b) { opcode_cb0b(e); }
  if(prefix == 0x0c) { opcode_cb0c(h); }
  if(prefix == 0x0d) { opcode_cb0d(l); }
  if(prefix == 0x0e) { opcode_cb0e(); }
  if(prefix == 0x0f) { opcode_cb0f(a); }

  if(prefix == 0xb0) { opcode_cbb0(b); }
  if(prefix == 0xb1) { opcode_cbb1(c); }
  if(prefix == 0xb2) { opcode_cbb2(d); }
  if(prefix == 0xb3) { opcode_cbb3(e); }
  if(prefix == 0xb4) { opcode_cbb4(h); }
  if(prefix == 0xb5) { opcode_cbb5(l); }
  if(prefix == 0xb6) { opcode_cbb6(); }
  if(prefix == 0xb7) { opcode_cbb7(a); }
  if(prefix == 0xb8) { opcode_cbb8(b); }
  if(prefix == 0xb9) { opcode_cbb9(c); }
  if(prefix == 0xba) { opcode_cbba(d); }
  if(prefix == 0xbb) { opcode_cbbb(e); }
  if(prefix == 0xbc) { opcode_cbbc(h); }
  if(prefix == 0xbd) { opcode_cbbd(l); }
  if(prefix == 0xbe) { opcode_cbbe(); }
  if(prefix == 0xbf) { opcode_cbbf(a); }

  if(prefix == 0xc0) { opcode_cbc0(b); }
  if(prefix == 0xc1) { opcode_cbc1(c); }
  if(prefix == 0xc2) { opcode_cbc2(d); }
  if(prefix == 0xc3) { opcode_cbc3(e); }
  if(prefix == 0xc4) { opcode_cbc4(h); }
  if(prefix == 0xc5) { opcode_cbc5(l); }
  if(prefix == 0xc6) { opcode_cbc6(); }
  if(prefix == 0xc7) { opcode_cbc7(a); }
  if(prefix == 0xc8) { opcode_cbc8(b); }
  if(prefix == 0xc9) { opcode_cbc9(c); }
  if(prefix == 0xca) { opcode_cbca(d); }
  if(prefix == 0xcb) { opcode_cbcb(e); }
  if(prefix == 0xcc) { opcode_cbcc(h); }
  if(prefix == 0xcd) { opcode_cbcd(l); }
  if(prefix == 0xce) { opcode_cbce(); }
  if(prefix == 0xcf) { opcode_cbcf(a); }

  if(prefix == 0xd0) { opcode_cbd0(b); }
  if(prefix == 0xd1) { opcode_cbd1(c); }
  if(prefix == 0xd2) { opcode_cbd2(d); }
  if(prefix == 0xd3) { opcode_cbd3(e); }
  if(prefix == 0xd4) { opcode_cbd4(h); }
  if(prefix == 0xd5) { opcode_cbd5(l); }
  if(prefix == 0xd6) { opcode_cbd6(); }
  if(prefix == 0xd7) { opcode_cbd7(a); }
  if(prefix == 0xd8) { opcode_cbd8(b); }
  if(prefix == 0xd9) { opcode_cbd9(c); }
  if(prefix == 0xda) { opcode_cbda(d); }
  if(prefix == 0xdb) { opcode_cbdb(e); }
  if(prefix == 0xdc) { opcode_cbdc(h); }
  if(prefix == 0xdd) { opcode_cbdd(l); }
  if(prefix == 0xde) { opcode_cbde(); }
  if(prefix == 0xdf) { opcode_cbdf(a); }

  if(prefix == 0xe0) { opcode_cbe0(b); }
  if(prefix == 0xe1) { opcode_cbe1(c); }
  if(prefix == 0xe2) { opcode_cbe2(d); }
  if(prefix == 0xe3) { opcode_cbe3(e); }
  if(prefix == 0xe4) { opcode_cbe4(h); }
  if(prefix == 0xe5) { opcode_cbe5(l); }
  if(prefix == 0xe6) { opcode_cbe6(); }
  if(prefix == 0xe7) { opcode_cbe7(a); }
  if(prefix == 0xe8) { opcode_cbe8(b); }
  if(prefix == 0xe9) { opcode_cbe9(c); }
  if(prefix == 0xea) { opcode_cbea(d); }
  if(prefix == 0xeb) { opcode_cbeb(e); }
  if(prefix == 0xec) { opcode_cbec(h); }
  if(prefix == 0xed) { opcode_cbed(l); }
  if(prefix == 0xee) { opcode_cbee(); }
  if(prefix == 0xef) { opcode_cbef(a); }

  if(prefix == 0xf0) { opcode_cbf0(b); }
  if(prefix == 0xf1) { opcode_cbf1(c); }
  if(prefix == 0xf2) { opcode_cbf2(d); }
  if(prefix == 0xf3) { opcode_cbf3(e); }
  if(prefix == 0xf4) { opcode_cbf4(h); }
  if(prefix == 0xf5) { opcode_cbf5(l); }
  if(prefix == 0xf6) { opcode_cbf6(); }
  if(prefix == 0xf7) { opcode_cbf7(a); }
  if(prefix == 0xf8) { opcode_cbf8(b); }
  if(prefix == 0xf9) { opcode_cbf9(c); }
  if(prefix == 0xfa) { opcode_cbfa(d); }
  if(prefix == 0xfb) { opcode_cbfb(e); }
  if(prefix == 0xfc) { opcode_cbfc(h); }
  if(prefix == 0xfd) { opcode_cbfd(l); }
  if(prefix == 0xfe) { opcode_cbfe(); }
  if(prefix == 0xff) { opcode_cbff(a); }

  return this->pc;
}

// opcode function definitions

// GENERAL OPCODE HELPER FUNCTIONS
void Cpu::opcode_inc(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;
  
  ++r8;
  
  if(r8 == 0)
    f.setZ();
  else
    f.resetZ();
  
  f.resetN();

  if(hOverflowAdd(r8, 1))
    f.setH();
  else
    f.resetH();
}

void Cpu::opcode_dec(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;
  
  --r8;
  if(r8 == 0)
    f.setZ();
  else
    f.resetZ();

  f.setN();

  if(hOverflowSub(r8, 1))
    f.setH();
  else
    f.resetH();
}

void Cpu::opcode_inc16(uint16_t (Registers::*getReg)(), void (Registers::*setReg)(uint16_t)) {
  uint16_t regVal = (this->registers.*getReg)();
  (this->registers.*setReg)(regVal + 1);
}

void Cpu::opcode_dec16(uint16_t (Registers::*getReg)(), void (Registers::*setReg)(uint16_t)) {
  uint16_t regVal = (this->registers.*getReg)();
  (this->registers.*setReg)(regVal - 1);
}

void Cpu::opcode_ld_general(uint8_t &r8) {
  uint8_t n8;
  std::tie(n8, this->pc) = this->memoryBus->fetchValue8(this->pc);
  r8 = n8;
}

void Cpu::opcode_ld_general(uint8_t &r8, uint16_t address) {
  uint8_t val = this->memoryBus->readat(address);
  r8 = val;
}

void Cpu::opcode_ld_general16(uint16_t (Registers::*getReg)(), void (Registers::*setReg)(uint16_t)) {
  uint16_t regVal = (this->registers.*getReg)();
  uint16_t newVal;
  std::tie(newVal, this->pc) = this->memoryBus->fetchValue16(this->pc);
  (this->registers.*setReg)(newVal);
}

void Cpu::opcode_rlca(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;

  uint8_t svnthBitMask = (0b1 << 7);
  uint8_t svnthBit = r8 & svnthBitMask;
  uint8_t svnthBitRotated = (svnthBit >> 7);
  r8 <<= 1;
  r8 |= svnthBitRotated;

  if(svnthBitRotated == 0b1)
    f.setC();
  else
    f.resetC();

  f.resetZ();
  f.resetN();
  f.resetH();
}

void Cpu::opcode_rrca(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;
  uint8_t zerothBitMask = 0b1;
  uint8_t zerothBit = r8 & zerothBitMask;
  uint8_t zerothBitRotated = zerothBit << 7;
  r8 >>= 1;
  r8 |= zerothBitRotated;

  if(zerothBit == 0b1)
    f.setC();
  else
    f.resetC();
  
  f.resetZ();
  f.resetN();
  f.resetH();
}

void Cpu::opcode_rlc(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;

  opcode_rlca(r8);
  if(r8 == 0)
    f.setZ();
  else
    f.resetZ();
}

void Cpu::opcode_rrc(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;

  opcode_rrca(r8);

  if(r8 == 0)
    f.setZ();
  else
    f.resetZ();
}

void Cpu::opcode_rla(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;
  bool oldCarry = f.getC();
  uint8_t zerothBit;

  if(oldCarry)
    zerothBit = 0b1;
  else
    zerothBit = 0b0;
  
  uint8_t svnthBitMask = (0b1 << 7);
  uint8_t svnthBit = (r8 & svnthBitMask);

  if(svnthBit == (0b1 << 7))
    f.setC();
  else
    f.resetC();

  r8 <<= 1;
  r8 |= zerothBit;

  f.resetZ();
  f.resetN();
  f.resetH();
}

void Cpu::opcode_rra(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;

  bool oldCarry = f.getC();
  uint8_t svnthBit;

  if(oldCarry)
    svnthBit = (0b1 << 7);
  else
    svnthBit = 0b0;
  
  uint8_t zerothBitMask = 0b1;
  uint8_t zerothBit = r8 & zerothBitMask;
  
  if(zerothBit == 0b1)
    f.setC();
  else
    f.resetC();

  r8 >>= 1;
  r8 |= svnthBit;

  f.resetZ();
  f.resetN();
  f.resetH();
}

void Cpu::opcode_rl(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;

  opcode_rla(r8);

  if(r8 == 0)
    f.setZ();
  else
    f.resetZ();
}

void Cpu::opcode_rr(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;

  opcode_rra(r8);

  if(r8 == 0)
    f.setZ();
  else
    f.resetZ();
}

void Cpu::opcode_sla(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;

  uint8_t zerothBit = 0;
  opcode_rlc(r8);
  r8 &= ~(0b1);
  
  if(r8 == 0)
    f.setZ();
  else
    f.resetZ();
}

void Cpu::opcode_sra(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;

  uint8_t svnthBitMask = 0b1 << 7;
  uint8_t svnthBit = r8 & svnthBitMask;

  opcode_rrc(r8);

  r8 |= svnthBit;

  if(r8 == 0)
    f.setZ();
  else
    f.resetZ();
}

void Cpu::opcode_swap(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;
  
  uint8_t uh = r8 & 0xf0;
  uint8_t lh = r8 & 0x0f;

  uh >>= 4;
  lh <<= 4;

  r8 = lh | uh;

  if(r8 == 0)
    f.setZ();
  else
    f.resetZ();

    f.resetN();
    f.resetH();
    f.resetC();
}

void Cpu::opcode_srl(uint8_t &r8) {
  Registers::FlagRegister &f = this->registers.f;

  uint8_t svnthBitMask = 0b1 << 7;
  svnthBitMask = ~svnthBitMask;
  opcode_rrc(r8);
  r8 &= svnthBitMask;

  if(r8 == 0)
    f.setZ();
  else
    f.resetZ();
}

void Cpu::opcode_bit(uint8_t u3, uint8_t r8) {
  Registers::FlagRegister &f = this->registers.f;
  uint8_t bitMask = 0b1 << u3;
  r8 &= bitMask;

  if(bitMask == 0)
    f.setZ();
  else
    f.resetZ();

  f.resetN();
  f.setH();
}

void Cpu::opcode_res(uint8_t u3, uint8_t &r8) {
  uint8_t bitMask = ~(0b1 << u3);
  r8 &= bitMask;
}

void Cpu::opcode_set(uint8_t u3, uint8_t &r8) {
  uint8_t bitMask = 0b1 << u3;
  r8 |= bitMask;
}

void Cpu::opcode_ld(uint8_t &rd, uint8_t r8) {
  rd = r8;
}

void Cpu::opcode_ld_hl(uint8_t r8) {
  uint16_t hl = this->registers.get_hl();
  this->memoryBus->writeto(hl, r8);
}

void Cpu::opcode_add16(uint16_t (Registers::*getRegD)(), uint16_t (Registers::*getRegS)(), void (Registers::*setRegD)(uint16_t)) {
  Registers::FlagRegister &f = this->registers.f;
  
  uint16_t regD = (this->registers.*getRegD)();
  uint16_t regS = (this->registers.*getRegS)();
  (this->registers.*setRegD)(regD + regS);

  f.resetN();

  if(hOverflowAdd16(regD, regS))
    f.setH();
  else
    f.resetH();

  if(cOverflowAdd16(regD, regS))
    f.setC();
  else
    f.resetC();
}

void Cpu::opcode_add_a(uint8_t &a, uint8_t r8) {
  Registers::FlagRegister &f = this->registers.f;
  a += r8;
  if(a == 0)
    f.setZ();
  else
    f.resetZ();
  
  if(hOverflowAdd(a, r8))
    f.setH();
  else
    f.resetH();

  if(cOverflowAdd(a, r8))
    f.setC();
  else
    f.resetC();

  f.resetN();
}

void Cpu::opcode_adc_a(uint8_t &a, uint8_t r8) {
  uint8_t carry = this->registers.f.getC();
  opcode_add_a(a, r8);
  opcode_add_a(a, carry);
}

void Cpu::opcode_sub_a(uint8_t &a, uint8_t r8) {
  Registers::FlagRegister &f = this->registers.f;
  a -= r8;
  if(a == 0)
    f.setZ();
  else
    f.resetZ();

  if(hOverflowSub(a, r8))
    f.setH();
  else
    f.resetH();
  
  if(cOverflowSub(a, r8))
    f.setC();
  else
    f.resetC();

  f.setN();  
}

void Cpu::opcode_sbc_a(uint8_t &a, uint8_t r8) {
  uint8_t carry = this->registers.f.getC();
  opcode_sub_a(a, r8);
  opcode_sub_a(a, carry);
}

void Cpu::opcode_and_a(uint8_t &a, uint8_t r8) {
  Registers::FlagRegister &f = this->registers.f;
  a &= r8;
  if(a == 0)
    f.setZ();
  else
    f.resetZ();
  
  f.resetN();
  f.setH();
  f.resetC();
}

void Cpu::opcode_xor_a(uint8_t &a, uint8_t r8) {
  Registers::FlagRegister &f = this->registers.f;
  a ^= r8;
  if(a == 0)
    f.setZ();
  else
    f.resetZ();
  
  f.resetN();
  f.resetH();
  f.resetC();
}

void Cpu::opcode_or_a(uint8_t &a, uint8_t r8) {
  Registers::FlagRegister &f = this->registers.f;
  a |= r8;
  if(a == 0)
    f.setZ();
  else
    f.resetZ();
  
  f.resetN();
  f.resetH();
  f.resetC();
}

void Cpu::opcode_cp_a(uint8_t &a, uint8_t r8) {
  uint8_t temp = a;
  opcode_sub_a(a, r8);
  a = temp;
}

void Cpu::opcode_jumpr(bool cc) {
  if(!cc)
    return;
  
  int8_t offset;
  std::tie(offset, this->pc) = this->memoryBus->fetchValue8(this->pc);
  if(this->pc + offset > 0)
    this->pc += offset;
  else
    return;
}

void Cpu::opcode_jump(bool cc) {
  if(!cc)
    return;

  int16_t newAddress;
  std::tie(newAddress, this->pc) = this->memoryBus->fetchValue16(this->pc);

  this->pc = newAddress;
}

void Cpu::opcode_cpl(uint8_t &a) {
  Registers::FlagRegister &f = this->registers.f;
  a = ~a;

  f.setN();
  f.setH();
}

void Cpu::opcode_return(bool cc) {
  if(!cc)
    return;
  
  std::tie(this->pc, this->registers.sp) = this->memoryBus->fetchValue16(this->registers.sp);
}

void Cpu::opcode_pop(void (Registers::*setReg)(uint16_t)) {
  uint16_t regVal;
  std::tie(regVal, this->registers.sp) = this->memoryBus->fetchValue16(this->registers.sp);
  (this->registers.*setReg)(regVal);
}

void Cpu::opcode_push(uint16_t (Registers::*getReg)(void)) {
  uint16_t regVal = (this->registers.*getReg)();
  this->registers.sp -= 2;
  this->memoryBus->writeto16(this->registers.sp, regVal);
}

void Cpu::opcode_call(bool cc) {
  if(!cc)
    return;

  uint16_t val;
  std::tie(val, this->pc) = this->memoryBus->fetchValue16(this->pc);
  this->registers.sp -= 2;
  this->memoryBus->writeto16(this->registers.sp, this->pc);
  this->pc = val;
}

void Cpu::opcode_rst(uint16_t vec) {
  this->registers.sp -= 2;
  this->memoryBus->writeto16(this->registers.sp, this->pc);
  this->pc = vec;
}

void Cpu::opcode_general_a(uint8_t &a, void (Cpu::*opcode_general_fn)(uint8_t &a, uint8_t r8)) {
  uint8_t val;
  std::tie(val, this->pc) = this->memoryBus->fetchValue8(this->pc);
  (this->*opcode_general_fn)(a, val);
}

void Cpu::opcode_ld_from_address(uint8_t &r8) {
  uint16_t address;
  std::tie(address, this->pc) = this->memoryBus->fetchValue16(this->pc);
  r8 = this->memoryBus->readat(address);
}

void Cpu::opcode_ldh_from_address(uint8_t &r8) {
  uint8_t addressh;
  std::tie(addressh, this->pc) = this->memoryBus->fetchValue8(this->pc);
  r8 = this->memoryBus->readat(0xFF00 + static_cast<uint16_t>(addressh));
}

void Cpu::opcode_ld_into_address(uint8_t r8) {
  uint16_t address;
  std::tie(address, this->pc) = this->memoryBus->fetchValue16(this->pc);
  this->memoryBus->writeto(address, r8);
}

void Cpu::opcode_ld_into_address(uint8_t r8, uint16_t address) {
  this->memoryBus->writeto(address, r8);
}

void Cpu::opcode_ldh_into_address(uint8_t r8) {
  uint8_t addressh;
  std::tie(addressh, this->pc) = this->memoryBus->fetchValue8(this->pc);
  this->memoryBus->writeto(0xFF00 + static_cast<uint16_t>(addressh), r8);
}

void Cpu::opcode_general_prefix_hl(void (Cpu::*fn) (uint8_t &r8)) {
  uint16_t hl = this->registers.get_hl();
  uint8_t hlval = this->memoryBus->readat(hl);
  (this->*fn)(hlval);
  this->memoryBus->writeto(hl, hlval);
}

void Cpu::opcode_general_prefix_hl(void (Cpu::*fn) (uint8_t u3, uint8_t &r8), uint8_t u3) {
  uint16_t hl = this->registers.get_hl();
  uint8_t hlval = this->memoryBus->readat(hl);
  (this->*fn)(u3, hlval);
  this->memoryBus->writeto(hl, hlval);
}

void Cpu::opcode_bit_hl(uint8_t u3) {
  uint16_t hl = this->registers.get_hl();
  uint8_t hlval = this->memoryBus->readat(hl);
  opcode_bit(u3, hlval);
  this->memoryBus->writeto(hl, hlval);
}
void Cpu::opcode_res_hl(uint8_t u3) {
  opcode_general_prefix_hl(&opcode_res, u3);
}

void Cpu::opcode_set_hl(uint8_t u3) {
  opcode_general_prefix_hl(&opcode_set, u3);
}

// OPCODE OPERATIONS IMPLEMENTATION

void Cpu::opcode_00(void) { return; }
void Cpu::opcode_01(void) { opcode_ld_general16(&Registers::get_bc, &Registers::set_bc); }
void Cpu::opcode_02(uint8_t a) { this->memoryBus->writeto(this->registers.get_bc(), a); }
void Cpu::opcode_03(void) { opcode_inc16(&Registers::get_bc, &Registers::set_bc); }
void Cpu::opcode_04(uint8_t &b) { opcode_inc(b); }
void Cpu::opcode_05(uint8_t &b) { opcode_dec(b); }
void Cpu::opcode_06(uint8_t &b) { opcode_ld_general(b); }
void Cpu::opcode_07(uint8_t &a) { opcode_rlca(a); }
void Cpu::opcode_08(void) { 
  uint16_t address;
  std::tie(address, this->pc) = this->memoryBus->fetchValue16(this->pc);
  this->memoryBus->writeto(address, this->registers.sp); 
}
void Cpu::opcode_09(void) { opcode_add16(&Registers::get_hl, &Registers::get_bc, &Registers::set_hl); }
void Cpu::opcode_0a(uint8_t &a) { opcode_ld_general(a, this->registers.get_bc()); }
void Cpu::opcode_0b(void) { opcode_dec16(&Registers::get_bc, &Registers::set_bc); }
void Cpu::opcode_0c(uint8_t &c) { opcode_inc(c); }
void Cpu::opcode_0d(uint8_t &c) { opcode_dec(c); }
void Cpu::opcode_0e(uint8_t &c) { opcode_ld_general(c); }
void Cpu::opcode_0f(uint8_t &a) { opcode_rrca(a); }

void Cpu::opcode_10(void) { ++(this->pc); }
void Cpu::opcode_11(void) { opcode_ld_general16(&Registers::get_de, &Registers::set_de); }
void Cpu::opcode_12(uint8_t a) { this->memoryBus->writeto(this->registers.get_de(), a); }
void Cpu::opcode_13(void) { opcode_dec16(&Registers::get_de, &Registers::set_de); }
void Cpu::opcode_14(uint8_t &d) { opcode_inc(d); }
void Cpu::opcode_15(uint8_t &d) { opcode_dec(d); }
void Cpu::opcode_16(uint8_t &d) { opcode_ld_general(d); }
void Cpu::opcode_17(uint8_t &a) { opcode_rla(a); }
void Cpu::opcode_18(void) { opcode_jumpr(); }
void Cpu::opcode_19(void) { opcode_add16(&Registers::get_hl, &Registers::get_de, &Registers::set_hl); }
void Cpu::opcode_1a(uint8_t &a) { opcode_ld_general(a, this->registers.get_de()); }
void Cpu::opcode_1b(void) { opcode_dec16(&Registers::get_de, &Registers::set_de); }
void Cpu::opcode_1c(uint8_t &e) { opcode_inc(e); }
void Cpu::opcode_1d(uint8_t &e) { opcode_dec(e); }
void Cpu::opcode_1e(uint8_t &e) { opcode_ld_general(e); }
void Cpu::opcode_1f(uint8_t &a) { opcode_rra(a); }

void Cpu::opcode_20(void) { opcode_jumpr(!(this->registers.f.getZ())); }
void Cpu::opcode_21(void) { opcode_ld_general16(&Registers::get_hl, &Registers::set_hl); }
void Cpu::opcode_22(uint8_t a) { 
  uint16_t hl = this->registers.get_hl();
  this->memoryBus->writeto(hl, a);
  this->registers.set_hl(hl+1); 
}
void Cpu::opcode_23(void) { opcode_inc16(&Registers::get_hl, &Registers::set_hl); }
void Cpu::opcode_24(uint8_t &h) { opcode_inc(h); }
void Cpu::opcode_25(uint8_t &h) { opcode_dec(h); }
void Cpu::opcode_26(uint8_t &h) { opcode_ld_general(h); }
void Cpu::opcode_27(void) { /* TODO */ }
void Cpu::opcode_28(void) { opcode_jumpr(this->registers.f.getZ()); }
void Cpu::opcode_29(void) { opcode_add16(&Registers::get_hl, &Registers::get_hl, &Registers::set_hl); }
void Cpu::opcode_2a(uint8_t &a) {
  uint16_t hl = this->registers.get_hl();
  a = this->memoryBus->readat(hl);
  this->registers.set_hl(hl+1);
}
void Cpu::opcode_2b(void) { opcode_dec16(&Registers::get_hl, &Registers::set_hl); }
void Cpu::opcode_2c(uint8_t &l) { opcode_inc(l); }
void Cpu::opcode_2d(uint8_t &l) { opcode_dec(l); }
void Cpu::opcode_2e(uint8_t &l) { opcode_ld_general(l); }
void Cpu::opcode_2f(uint8_t &a) { opcode_cpl(a); }

void Cpu::opcode_30(void) { opcode_jumpr(!(this->registers.f.getC())); }
void Cpu::opcode_31(void) { opcode_ld_general16(&Registers::get_sp, &Registers::set_sp); }
void Cpu::opcode_32(uint8_t a) { 
  uint16_t hl = this->registers.get_hl();
  this->memoryBus->writeto(hl, a);
  this->registers.set_hl(hl-1);
}
void Cpu::opcode_33(void) { opcode_inc16(&Registers::get_sp, &Registers::set_sp); }
void Cpu::opcode_34(void) { 
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_inc(val);
  this->memoryBus->writeto(hl, val);
}
void Cpu::opcode_35(void) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_dec(val);
  this->memoryBus->writeto(hl, val);
}
void Cpu::opcode_36(void) {
  uint8_t val;
  std::tie(val, this->pc) = this->memoryBus->fetchValue8(this->pc);
  this->memoryBus->writeto(this->registers.get_hl(), val);
}
void Cpu::opcode_37(void) {
  Registers::FlagRegister &f = this->registers.f;
  f.resetN();
  f.resetH();
  f.setC();
}
void Cpu::opcode_38(void) { opcode_jumpr(this->registers.f.getC()); }
void Cpu::opcode_39(void) { opcode_add16(&Registers::get_hl, &Registers::get_sp, &Registers::set_hl); }
void Cpu::opcode_3a(uint8_t &a) { 
  uint16_t hl = this->registers.get_hl();
  a = this->memoryBus->readat(hl);
  this->registers.set_hl(hl-1);
}
void Cpu::opcode_3b(void) { opcode_dec16(&Registers::get_sp, &Registers::set_sp); }
void Cpu::opcode_3c(uint8_t &a) { opcode_inc(a); }
void Cpu::opcode_3d(uint8_t &a) { opcode_dec(a); }
void Cpu::opcode_3e(uint8_t &a) { opcode_ld_general(a); }
void Cpu::opcode_3f(void) {
  Registers::FlagRegister &f = this->registers.f;

  f.resetN();
  f.resetH();

  bool carry = f.getC();

  if(carry)
    f.resetC();
  else
    f.setC();
}

/* % --------------- (most) LD instructions --------------- % */

// LD B, X
void Cpu::opcode_40(uint8_t &b) { opcode_ld(b, b); }
void Cpu::opcode_41(uint8_t &b, uint8_t c) { opcode_ld(b, c); }
void Cpu::opcode_42(uint8_t &b, uint8_t d) { opcode_ld(b, d); }
void Cpu::opcode_43(uint8_t &b, uint8_t e) { opcode_ld(b, e); }
void Cpu::opcode_44(uint8_t &b, uint8_t h) { opcode_ld(b, h); }
void Cpu::opcode_45(uint8_t &b, uint8_t l) { opcode_ld(b, l); }
void Cpu::opcode_46(uint8_t &b) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_ld(b, val);
}
void Cpu::opcode_47(uint8_t &b, uint8_t a) { opcode_ld(b, a); }

// LD C, X
void Cpu::opcode_48(uint8_t &c, uint8_t b) { opcode_ld(c, b); }
void Cpu::opcode_49(uint8_t &c) { opcode_ld(c, c); }
void Cpu::opcode_4a(uint8_t &c, uint8_t d) { opcode_ld(c, d); }
void Cpu::opcode_4b(uint8_t &c, uint8_t e) { opcode_ld(c, e); }
void Cpu::opcode_4c(uint8_t &c, uint8_t h) { opcode_ld(c, h); }
void Cpu::opcode_4d(uint8_t &c, uint8_t l) { opcode_ld(c, l); }
void Cpu::opcode_4e(uint8_t &c) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_ld(c, val);
}
void Cpu::opcode_4f(uint8_t &c, uint8_t a) { opcode_ld(c, a); }

// LD D, X
void Cpu::opcode_50(uint8_t &d, uint8_t b) { opcode_ld(d, b); }
void Cpu::opcode_51(uint8_t &d, uint8_t c) { opcode_ld(d, c); }
void Cpu::opcode_52(uint8_t &d) { opcode_ld(d, d); }
void Cpu::opcode_53(uint8_t &d, uint8_t e) { opcode_ld(d, e); }
void Cpu::opcode_54(uint8_t &d, uint8_t h) { opcode_ld(d, h); }
void Cpu::opcode_55(uint8_t &d, uint8_t l) { opcode_ld(d, l); }
void Cpu::opcode_56(uint8_t &d) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_ld(d, val);
}
void Cpu::opcode_57(uint8_t &d, uint8_t a) { opcode_ld(d, a); }

// LD E, X
void Cpu::opcode_58(uint8_t &e, uint8_t b) { opcode_ld(e, b); }
void Cpu::opcode_59(uint8_t &e, uint8_t c) { opcode_ld(e, c); }
void Cpu::opcode_5a(uint8_t &e, uint8_t d) { opcode_ld(e, d); }
void Cpu::opcode_5b(uint8_t &e) { opcode_ld(e, e); }
void Cpu::opcode_5c(uint8_t &e, uint8_t h) { opcode_ld(e, h); }
void Cpu::opcode_5d(uint8_t &e, uint8_t l) { opcode_ld(e, l); }
void Cpu::opcode_5e(uint8_t &e) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_ld(e, val);
}
void Cpu::opcode_5f(uint8_t &e, uint8_t a) { opcode_ld(e, a); }

// LD H, X
void Cpu::opcode_60(uint8_t &h, uint8_t b) { opcode_ld(h, b); }
void Cpu::opcode_61(uint8_t &h, uint8_t c) { opcode_ld(h, c); }
void Cpu::opcode_62(uint8_t &h, uint8_t d) { opcode_ld(h, d); }
void Cpu::opcode_63(uint8_t &h, uint8_t e) { opcode_ld(h, e); }
void Cpu::opcode_64(uint8_t &h) { opcode_ld(h, h); }
void Cpu::opcode_65(uint8_t &h, uint8_t l) { opcode_ld(h, l); }
void Cpu::opcode_66(uint8_t &h) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_ld(h, val);
}
void Cpu::opcode_67(uint8_t &h, uint8_t a) { opcode_ld(h, a); }

// LD L, X
void Cpu::opcode_68(uint8_t &l, uint8_t b) { opcode_ld(l, b); }
void Cpu::opcode_69(uint8_t &l, uint8_t c) { opcode_ld(l, c); }
void Cpu::opcode_6a(uint8_t &l, uint8_t d) { opcode_ld(l, d); }
void Cpu::opcode_6b(uint8_t &l, uint8_t e) { opcode_ld(l ,e); }
void Cpu::opcode_6c(uint8_t &l, uint8_t h) { opcode_ld(l, h); }
void Cpu::opcode_6d(uint8_t &l) { opcode_ld(l ,l); }
void Cpu::opcode_6e(uint8_t &l) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_ld(l, val);
}
void Cpu::opcode_6f(uint8_t &l, uint8_t a) { opcode_ld(l, a); }

// LD [HL], X
void Cpu::opcode_70(uint8_t b) { opcode_ld_hl(b); }
void Cpu::opcode_71(uint8_t c) { opcode_ld_hl(c); }
void Cpu::opcode_72(uint8_t d) { opcode_ld_hl(d); }
void Cpu::opcode_73(uint8_t e) { opcode_ld_hl(e); }
void Cpu::opcode_74(uint8_t h) { opcode_ld_hl(h); }
void Cpu::opcode_75(uint8_t l) { opcode_ld_hl(l); }
void Cpu::opcode_76(void) {
  /*
    TODO - IMPLEMENT HALT
  */
}
void Cpu::opcode_77(uint8_t a) { opcode_ld_hl(a); }

// LD A, X
void Cpu::opcode_78(uint8_t &a, uint8_t b) { opcode_ld(a, b); }
void Cpu::opcode_79(uint8_t &a, uint8_t c) { opcode_ld(a, c); }
void Cpu::opcode_7a(uint8_t &a, uint8_t d) { opcode_ld(a, d); }
void Cpu::opcode_7b(uint8_t &a, uint8_t e) { opcode_ld(a, e); }
void Cpu::opcode_7c(uint8_t &a, uint8_t h) { opcode_ld(a, h); }
void Cpu::opcode_7d(uint8_t &a, uint8_t l) { opcode_ld(a, l); }
void Cpu::opcode_7e(uint8_t &a) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_ld(a, val);
}
void Cpu::opcode_7f(uint8_t &a) { opcode_ld(a, a); }

/* % --------------- ADD instructions --------------- % */

void Cpu::opcode_80(uint8_t &a, uint8_t b) { opcode_add_a(a, b); }
void Cpu::opcode_81(uint8_t &a, uint8_t c) { opcode_add_a(a, c); }
void Cpu::opcode_82(uint8_t &a, uint8_t d) { opcode_add_a(a, d); }
void Cpu::opcode_83(uint8_t &a, uint8_t e) { opcode_add_a(a, e); }
void Cpu::opcode_84(uint8_t &a, uint8_t h) { opcode_add_a(a, h); }
void Cpu::opcode_85(uint8_t &a, uint8_t l) { opcode_add_a(a, l); }
void Cpu::opcode_86(uint8_t &a) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_add_a(a, val);
}
void Cpu::opcode_87(uint8_t &a) { opcode_add_a(a, a); }

/* % --------------- ADC instructions --------------- % */

void Cpu::opcode_88(uint8_t &a, uint8_t b) { opcode_adc_a(a, b); }
void Cpu::opcode_89(uint8_t &a, uint8_t c) { opcode_adc_a(a, c); }
void Cpu::opcode_8a(uint8_t &a, uint8_t d) { opcode_adc_a(a, d); }
void Cpu::opcode_8b(uint8_t &a, uint8_t e) { opcode_adc_a(a, e); }
void Cpu::opcode_8c(uint8_t &a, uint8_t h) { opcode_adc_a(a, h); }
void Cpu::opcode_8d(uint8_t &a, uint8_t l) { opcode_adc_a(a, l); }
void Cpu::opcode_8e(uint8_t &a) { 
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_adc_a(a, val); 
}
void Cpu::opcode_8f(uint8_t &a) { opcode_adc_a(a, a); }

/* % --------------- SUB instructions --------------- % */

void Cpu::opcode_90(uint8_t &a, uint8_t b) { opcode_sub_a(a, b); }
void Cpu::opcode_91(uint8_t &a, uint8_t c) { opcode_sub_a(a, c); }
void Cpu::opcode_92(uint8_t &a, uint8_t d) { opcode_sub_a(a, d); }
void Cpu::opcode_93(uint8_t &a, uint8_t e) { opcode_sub_a(a, e); }
void Cpu::opcode_94(uint8_t &a, uint8_t h) { opcode_sub_a(a, h); }
void Cpu::opcode_95(uint8_t &a, uint8_t l) { opcode_sub_a(a, l); }
void Cpu::opcode_96(uint8_t &a) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_sub_a(a, val);
}
void Cpu::opcode_97(uint8_t &a) { opcode_sub_a(a, a); }

/* % --------------- SBC instructions --------------- % */

void Cpu::opcode_98(uint8_t &a, uint8_t b) { opcode_sbc_a(a, b); }
void Cpu::opcode_99(uint8_t &a, uint8_t c) { opcode_sbc_a(a, c); }
void Cpu::opcode_9a(uint8_t &a, uint8_t d) { opcode_sbc_a(a, d); }
void Cpu::opcode_9b(uint8_t &a, uint8_t e) { opcode_sbc_a(a, e); }
void Cpu::opcode_9c(uint8_t &a, uint8_t h) { opcode_sbc_a(a, h); }
void Cpu::opcode_9d(uint8_t &a, uint8_t l) { opcode_sbc_a(a, l); }
void Cpu::opcode_9e(uint8_t &a) { 
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_sbc_a(a, val); 
}
void Cpu::opcode_9f(uint8_t &a) {
  a -= a;
  this->registers.f.setZ();
  this->registers.f.setN();
  if(hOverflowSub(0b0, this->registers.f.getC()))
    this->registers.f.setH();
}

/* % --------------- AND instructions --------------- % */

void Cpu::opcode_a0(uint8_t &a, uint8_t b) { opcode_and_a(a, b); }
void Cpu::opcode_a1(uint8_t &a, uint8_t c) { opcode_and_a(a, c); }
void Cpu::opcode_a2(uint8_t &a, uint8_t d) { opcode_and_a(a, d); }
void Cpu::opcode_a3(uint8_t &a, uint8_t e) { opcode_and_a(a, e); }
void Cpu::opcode_a4(uint8_t &a, uint8_t h) { opcode_and_a(a, h); }
void Cpu::opcode_a5(uint8_t &a, uint8_t l) { opcode_and_a(a, l); }
void Cpu::opcode_a6(uint8_t &a) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_and_a(a, val);
}
void Cpu::opcode_a7(uint8_t &a) { opcode_and_a(a, a); }

/* % --------------- XOR instructions --------------- % */

void Cpu::opcode_a8(uint8_t &a, uint8_t b) { opcode_xor_a(a, b); }
void Cpu::opcode_a9(uint8_t &a, uint8_t c) { opcode_xor_a(a, c); }
void Cpu::opcode_aa(uint8_t &a, uint8_t d) { opcode_xor_a(a, d); }
void Cpu::opcode_ab(uint8_t &a, uint8_t e) { opcode_xor_a(a, e); }
void Cpu::opcode_ac(uint8_t &a, uint8_t h) { opcode_xor_a(a, h); }
void Cpu::opcode_ad(uint8_t &a, uint8_t l) { opcode_xor_a(a, l); }
void Cpu::opcode_ae(uint8_t &a) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_xor_a(a, val);
}
void Cpu::opcode_af(uint8_t &a) { opcode_xor_a(a, a); }

/* % --------------- OR instructions --------------- % */

void Cpu::opcode_b0(uint8_t &a, uint8_t b) { opcode_or_a(a, b); }
void Cpu::opcode_b1(uint8_t &a, uint8_t c) { opcode_or_a(a, c); }
void Cpu::opcode_b2(uint8_t &a, uint8_t d) { opcode_or_a(a, d); }
void Cpu::opcode_b3(uint8_t &a, uint8_t e) { opcode_or_a(a, e); }
void Cpu::opcode_b4(uint8_t &a, uint8_t h) { opcode_or_a(a, h); }
void Cpu::opcode_b5(uint8_t &a, uint8_t l) { opcode_or_a(a, l); }
void Cpu::opcode_b6(uint8_t &a) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_or_a(a, val);
}
void Cpu::opcode_b7(uint8_t &a) { opcode_or_a(a, a); }

/* % --------------- CP instructions --------------- % */

void Cpu::opcode_b8(uint8_t &a, uint8_t b) { opcode_cp_a(a, b); }
void Cpu::opcode_b9(uint8_t &a, uint8_t c) { opcode_cp_a(a, c); }
void Cpu::opcode_ba(uint8_t &a, uint8_t d) { opcode_cp_a(a, d); }
void Cpu::opcode_bb(uint8_t &a, uint8_t e) { opcode_cp_a(a, e); }
void Cpu::opcode_bc(uint8_t &a, uint8_t h) { opcode_cp_a(a, h); }
void Cpu::opcode_bd(uint8_t &a, uint8_t l) { opcode_cp_a(a, l); }
void Cpu::opcode_be(uint8_t &a) {
  uint16_t hl = this->registers.get_hl();
  uint8_t val = this->memoryBus->readat(hl);
  opcode_cp_a(a, val);
}
void Cpu::opcode_bf(uint8_t &a) { opcode_cp_a(a, a); }

/* % --------------- remaining instructions --------------- % */

void Cpu::opcode_c0(void) { opcode_return(!this->registers.f.getZ()); }
void Cpu::opcode_c1(void) { opcode_pop(&Registers::set_bc); }
void Cpu::opcode_c2(void) { opcode_jump(!this->registers.f.getZ()); }
void Cpu::opcode_c3(void) { opcode_jump(); }
void Cpu::opcode_c4(void) { opcode_call(!this->registers.f.getZ()); }
void Cpu::opcode_c5(void) { opcode_push(&Registers::get_bc); }
void Cpu::opcode_c6(uint8_t &a) { opcode_general_a(a, &opcode_add_a); }
void Cpu::opcode_c7(void) { opcode_rst(0x00); }
void Cpu::opcode_c8(void) { opcode_return(this->registers.f.getZ()); }
void Cpu::opcode_c9(void) { opcode_return(); }
void Cpu::opcode_ca(void) { opcode_jump(this->registers.f.getZ()); }
void Cpu::opcode_cb(void) {} // TODO
void Cpu::opcode_cc(void) { opcode_call(this->registers.f.getZ()); }
void Cpu::opcode_cd(void) { opcode_call(); }
void Cpu::opcode_ce(uint8_t &a) { opcode_general_a(a, &opcode_adc_a); }
void Cpu::opcode_cf(void) { opcode_rst(0x08); }

void Cpu::opcode_d0(void) { opcode_return(!this->registers.f.getC()); }
void Cpu::opcode_d1(void) { opcode_pop(&Registers::set_de); }
void Cpu::opcode_d2(void) { opcode_jump(!this->registers.f.getC()); }
void Cpu::opcode_d3(void) {} // invalid opcode
void Cpu::opcode_d4(void) { opcode_call(!this->registers.f.getC()); }
void Cpu::opcode_d5(void) { opcode_push(&Registers::get_de); }
void Cpu::opcode_d6(uint8_t &a) { opcode_general_a(a, &opcode_sub_a); }
void Cpu::opcode_d7(void) { opcode_rst(0x10); }
void Cpu::opcode_d8(void) { opcode_return(this->registers.f.getC()); }
void Cpu::opcode_d9(void) { opcode_return(); enableInterrupts(); }
void Cpu::opcode_da(void) { opcode_jump(this->registers.f.getC()); }
void Cpu::opcode_db(void) {} // invalid opcode
void Cpu::opcode_dc(void) { opcode_call(this->registers.f.getC()); }
void Cpu::opcode_dd(void) {} // invalid opcode
void Cpu::opcode_de(uint8_t &a) { opcode_general_a(a, &opcode_sbc_a); }
void Cpu::opcode_df(void) { opcode_rst(0x18); }

void Cpu::opcode_e0(uint8_t &a) { opcode_ldh_into_address(a); }
void Cpu::opcode_e1(void) { opcode_pop(&Registers::set_hl); }
void Cpu::opcode_e2(uint8_t &a) { opcode_ld_into_address(a, 0xFF00 + static_cast<uint16_t>(0xFF00 + this->registers.c)); }
void Cpu::opcode_e3(void) {} // invalid opcode
void Cpu::opcode_e4(void) {} // invalid opcode
void Cpu::opcode_e5(void) { opcode_push(&Registers::get_hl); }
void Cpu::opcode_e6(uint8_t &a) { opcode_general_a(a, &opcode_and_a); }
void Cpu::opcode_e7(void) { opcode_rst(0x20); }
void Cpu::opcode_e8(void) { 
  Registers::FlagRegister &f = this->registers.f;
  int8_t signedVal;
  std::tie(signedVal, this->pc) = this->memoryBus->fetchValue8(this->pc);
  this->registers.sp += signedVal;

  uint8_t sp8 = static_cast<uint8_t>(this->registers.sp);
  if(signedVal > 0) {
    if(hOverflowAdd(sp8, signedVal))
      f.setH();
    else
      f.resetH();

    if(cOverflowAdd(sp8, signedVal))
      f.setC();
    else
      f.resetC();
  } else {
    if(hOverflowSub(sp8, -1 * signedVal))
      f.setH();
    else
      f.resetH();

    if(cOverflowSub(sp8, -1 * signedVal))
      f.setC();
    else
      f.resetC();
  }
}
void Cpu::opcode_e9(void) { this->pc = this->registers.get_hl(); }
void Cpu::opcode_ea(uint8_t r8) { opcode_ld_into_address(r8); }
void Cpu::opcode_eb(void) {} // invalid opcode
void Cpu::opcode_ec(void) {} // invalid opcode
void Cpu::opcode_ed(void) {} // invalid opcode
void Cpu::opcode_ee(uint8_t &a) { opcode_general_a(a, &opcode_xor_a); }
void Cpu::opcode_ef(void) { opcode_rst(0x28); }

void Cpu::opcode_f0(uint8_t &a) { opcode_ldh_from_address(a); }
void Cpu::opcode_f1(void) { opcode_pop(&Registers::set_af); }
void Cpu::opcode_f2(uint8_t &a) { opcode_ld(a, this->memoryBus->readat(0xFF00 + static_cast<uint16_t>(this->registers.c))); }
void Cpu::opcode_f3(void) { disableInterrupts(); }
void Cpu::opcode_f4(void) {} // invalid opcode
void Cpu::opcode_f5(void) { opcode_push(&Registers::get_af); }
void Cpu::opcode_f6(uint8_t &a) { opcode_general_a(a, &opcode_or_a); }
void Cpu::opcode_f7(void) { opcode_rst(0x30); }
void Cpu::opcode_f8(void) {
  Registers::FlagRegister &f = this->registers.f;

  uint16_t hl = this->registers.get_hl();
  uint16_t sp = this->registers.sp;
  int8_t signedVal;
  std::tie(signedVal, this->pc) = this->memoryBus->fetchValue8(this->pc);

  hl = (sp + signedVal);

  f.resetZ();
  f.resetN();

  uint8_t sp8 = static_cast<uint8_t>(sp);

  if(signedVal > 0) {
    if(hOverflowAdd(sp8, signedVal))
      f.setH();
    else
      f.resetH();

    if(cOverflowAdd(sp8, signedVal))
      f.setC();
    else
      f.resetC();
  } else {
    if(hOverflowSub(sp8, -1 * signedVal))
      f.setH();
    else
      f.resetH();

    if(cOverflowSub(sp8, -1 * signedVal))
      f.setC();
    else
      f.resetC();
  }
}
void Cpu::opcode_f9(void) { opcode_ld_general16(&Registers::get_hl, &Registers::set_sp); }
void Cpu::opcode_fa(uint8_t &a) { opcode_ld_from_address(a); }
void Cpu::opcode_fb(void) { enableInterrupts(); }
void Cpu::opcode_fc(void) {} // invalid opcode
void Cpu::opcode_fd(void) {} // invalid opcode
void Cpu::opcode_fe(uint8_t &a) { opcode_general_a(a, &opcode_cp_a); }
void Cpu::opcode_ff(void) { opcode_rst(0x38); }

void Cpu::opcode_cb00(uint8_t &b) { opcode_rlc(b); }
void Cpu::opcode_cb01(uint8_t &c) { opcode_rlc(c); }
void Cpu::opcode_cb02(uint8_t &d) { opcode_rlc(d); }
void Cpu::opcode_cb03(uint8_t &e) { opcode_rlc(e); }
void Cpu::opcode_cb04(uint8_t &h) { opcode_rlc(h); }
void Cpu::opcode_cb05(uint8_t &l) { opcode_rlc(l); }
void Cpu::opcode_cb06(void) { opcode_general_prefix_hl(&opcode_rlc); }
void Cpu::opcode_cb07(uint8_t &a) { opcode_rlc(a); }
void Cpu::opcode_cb08(uint8_t &b) { opcode_rrc(b); }
void Cpu::opcode_cb09(uint8_t &c) { opcode_rrc(c); }
void Cpu::opcode_cb0a(uint8_t &d) { opcode_rrc(d); }
void Cpu::opcode_cb0b(uint8_t &e) { opcode_rrc(e); }
void Cpu::opcode_cb0c(uint8_t &h) { opcode_rrc(h); }
void Cpu::opcode_cb0d(uint8_t &l) { opcode_rrc(l); }
void Cpu::opcode_cb0e(void) { opcode_general_prefix_hl(&opcode_rrc); }
void Cpu::opcode_cb0f(uint8_t &a) { opcode_rrc(a); }

void Cpu::opcode_cb10(uint8_t &b) { opcode_rl(b); }
void Cpu::opcode_cb11(uint8_t &c) { opcode_rl(c); }
void Cpu::opcode_cb12(uint8_t &d) { opcode_rl(d); }
void Cpu::opcode_cb13(uint8_t &e) { opcode_rl(e); }
void Cpu::opcode_cb14(uint8_t &h) { opcode_rl(h); }
void Cpu::opcode_cb15(uint8_t &l) { opcode_rl(l); }
void Cpu::opcode_cb16(void) { opcode_general_prefix_hl(&opcode_rl); }
void Cpu::opcode_cb17(uint8_t &a) { opcode_rl(a); }
void Cpu::opcode_cb18(uint8_t &b) { opcode_rr(b); }
void Cpu::opcode_cb19(uint8_t &c) { opcode_rr(c); }
void Cpu::opcode_cb1a(uint8_t &d) { opcode_rr(d); }
void Cpu::opcode_cb1b(uint8_t &e) { opcode_rr(e); }
void Cpu::opcode_cb1c(uint8_t &h) { opcode_rr(h); }
void Cpu::opcode_cb1d(uint8_t &l) { opcode_rr(l); }
void Cpu::opcode_cb1e(void) { opcode_general_prefix_hl(&opcode_rr); }
void Cpu::opcode_cb1f(uint8_t &a) { opcode_rr(a); }

void Cpu::opcode_cb20(uint8_t &b) { opcode_sla(b); }
void Cpu::opcode_cb21(uint8_t &c) { opcode_sla(c); }
void Cpu::opcode_cb22(uint8_t &d) { opcode_sla(d); }
void Cpu::opcode_cb23(uint8_t &e) { opcode_sla(e); }
void Cpu::opcode_cb24(uint8_t &h) { opcode_sla(h); }
void Cpu::opcode_cb25(uint8_t &l) { opcode_sla(l); }
void Cpu::opcode_cb26(void) { opcode_general_prefix_hl(&opcode_sla); }
void Cpu::opcode_cb27(uint8_t &a) { opcode_sla(a); }
void Cpu::opcode_cb28(uint8_t &b) { opcode_sra(b); }
void Cpu::opcode_cb29(uint8_t &c) { opcode_sra(c); }
void Cpu::opcode_cb2a(uint8_t &d) { opcode_sra(d); }
void Cpu::opcode_cb2b(uint8_t &e) { opcode_sra(e); }
void Cpu::opcode_cb2c(uint8_t &h) { opcode_sra(h); }
void Cpu::opcode_cb2d(uint8_t &l) { opcode_sra(l); }
void Cpu::opcode_cb2e(void) { opcode_general_prefix_hl(&opcode_sra); }
void Cpu::opcode_cb2f(uint8_t &a) { opcode_sra(a); }

void Cpu::opcode_cb30(uint8_t &b) { opcode_swap(b); }
void Cpu::opcode_cb31(uint8_t &c) { opcode_swap(c); }
void Cpu::opcode_cb32(uint8_t &d) { opcode_swap(d); }
void Cpu::opcode_cb33(uint8_t &e) { opcode_swap(e); }
void Cpu::opcode_cb34(uint8_t &h) { opcode_swap(h); }
void Cpu::opcode_cb35(uint8_t &l) { opcode_swap(l); }
void Cpu::opcode_cb36(void) { opcode_general_prefix_hl(&opcode_swap); }
void Cpu::opcode_cb37(uint8_t &a) { opcode_swap(a); }
void Cpu::opcode_cb38(uint8_t &b) { opcode_srl(b); }
void Cpu::opcode_cb39(uint8_t &c) { opcode_srl(c); }
void Cpu::opcode_cb3a(uint8_t &d) { opcode_srl(d); }
void Cpu::opcode_cb3b(uint8_t &e) { opcode_srl(e); }
void Cpu::opcode_cb3c(uint8_t &h) { opcode_srl(h); }
void Cpu::opcode_cb3d(uint8_t &l) { opcode_srl(l); }
void Cpu::opcode_cb3e(void) { opcode_general_prefix_hl(&opcode_srl);}
void Cpu::opcode_cb3f(uint8_t &a) { opcode_srl(a); }

void Cpu::opcode_cb40(uint8_t &b) { opcode_bit(0, b); }
void Cpu::opcode_cb41(uint8_t &c) { opcode_bit(0, c); }
void Cpu::opcode_cb42(uint8_t &d) { opcode_bit(0, d); }
void Cpu::opcode_cb43(uint8_t &e) { opcode_bit(0, e); }
void Cpu::opcode_cb44(uint8_t &h) { opcode_bit(0, h); }
void Cpu::opcode_cb45(uint8_t &l) { opcode_bit(0, l); }
void Cpu::opcode_cb46(void) { opcode_bit_hl(0); }
void Cpu::opcode_cb47(uint8_t &a) { opcode_bit(0, a); }
void Cpu::opcode_cb48(uint8_t &b) { opcode_bit(1, b); }
void Cpu::opcode_cb49(uint8_t &c) { opcode_bit(1, c); }
void Cpu::opcode_cb4a(uint8_t &d) { opcode_bit(1, d); }
void Cpu::opcode_cb4b(uint8_t &e) { opcode_bit(1, e); }
void Cpu::opcode_cb4c(uint8_t &h) { opcode_bit(1, h); }
void Cpu::opcode_cb4d(uint8_t &l) { opcode_bit(1, l); }
void Cpu::opcode_cb4e(void) { opcode_bit_hl(1); }
void Cpu::opcode_cb4f(uint8_t &a) { opcode_bit(1, a); }

void Cpu::opcode_cb50(uint8_t &b) { opcode_bit(2, b); }
void Cpu::opcode_cb51(uint8_t &c) { opcode_bit(2, c); }
void Cpu::opcode_cb52(uint8_t &d) { opcode_bit(2, d); }
void Cpu::opcode_cb53(uint8_t &e) { opcode_bit(2, e); }
void Cpu::opcode_cb54(uint8_t &h) { opcode_bit(2, h); }
void Cpu::opcode_cb55(uint8_t &l) { opcode_bit(2, l); }
void Cpu::opcode_cb56(void) { opcode_bit_hl(2); }
void Cpu::opcode_cb57(uint8_t &a) { opcode_bit(2, a); }
void Cpu::opcode_cb58(uint8_t &b) { opcode_bit(3, b); }
void Cpu::opcode_cb59(uint8_t &c) { opcode_bit(3, c); }
void Cpu::opcode_cb5a(uint8_t &d) { opcode_bit(3, d); }
void Cpu::opcode_cb5b(uint8_t &e) { opcode_bit(3, e); }
void Cpu::opcode_cb5c(uint8_t &h) { opcode_bit(3, h); }
void Cpu::opcode_cb5d(uint8_t &l) { opcode_bit(3, l); }
void Cpu::opcode_cb5e(void) { opcode_bit_hl(3); }
void Cpu::opcode_cb5f(uint8_t &a) { opcode_bit(3, a); }

void Cpu::opcode_cb60(uint8_t &b) { opcode_bit(4, b); }
void Cpu::opcode_cb61(uint8_t &c) { opcode_bit(4, c); }
void Cpu::opcode_cb62(uint8_t &d) { opcode_bit(4, d); }
void Cpu::opcode_cb63(uint8_t &e) { opcode_bit(4, e); }
void Cpu::opcode_cb64(uint8_t &h) { opcode_bit(4, h); }
void Cpu::opcode_cb65(uint8_t &l) { opcode_bit(4, l); }
void Cpu::opcode_cb66(void) { opcode_bit_hl(4); }
void Cpu::opcode_cb67(uint8_t &a) { opcode_bit(4, a); }
void Cpu::opcode_cb68(uint8_t &b) { opcode_bit(5, b); }
void Cpu::opcode_cb69(uint8_t &c) { opcode_bit(5, c); }
void Cpu::opcode_cb6a(uint8_t &d) { opcode_bit(5, d); }
void Cpu::opcode_cb6b(uint8_t &e) { opcode_bit(5, e); }
void Cpu::opcode_cb6c(uint8_t &h) { opcode_bit(5, h); }
void Cpu::opcode_cb6d(uint8_t &l) { opcode_bit(5, l); }
void Cpu::opcode_cb6e(void) { opcode_bit_hl(5); }
void Cpu::opcode_cb6f(uint8_t &a) { opcode_bit(5, a); }

void Cpu::opcode_cb70(uint8_t &b) { opcode_bit(6, b); }
void Cpu::opcode_cb71(uint8_t &c) { opcode_bit(6, c); }
void Cpu::opcode_cb72(uint8_t &d) { opcode_bit(6, d); }
void Cpu::opcode_cb73(uint8_t &e) { opcode_bit(6, e); }
void Cpu::opcode_cb74(uint8_t &h) { opcode_bit(6, h); }
void Cpu::opcode_cb75(uint8_t &l) { opcode_bit(6, l); }
void Cpu::opcode_cb76(void) { opcode_bit_hl(6); }
void Cpu::opcode_cb77(uint8_t &a) { opcode_bit(6, a); }
void Cpu::opcode_cb78(uint8_t &b) { opcode_bit(7, b); }
void Cpu::opcode_cb79(uint8_t &c) { opcode_bit(7, c); }
void Cpu::opcode_cb7a(uint8_t &d) { opcode_bit(7, d); }
void Cpu::opcode_cb7b(uint8_t &e) { opcode_bit(7, e); }
void Cpu::opcode_cb7c(uint8_t &h) { opcode_bit(7, h); }
void Cpu::opcode_cb7d(uint8_t &l) { opcode_bit(7, l); }
void Cpu::opcode_cb7e(void) { opcode_bit_hl(7); }
void Cpu::opcode_cb7f(uint8_t &a) { opcode_bit(7, a); }

void Cpu::opcode_cb80(uint8_t &b) { opcode_res(0, b); }
void Cpu::opcode_cb81(uint8_t &c) { opcode_res(0, c); }
void Cpu::opcode_cb82(uint8_t &d) { opcode_res(0, d); }
void Cpu::opcode_cb83(uint8_t &e) { opcode_res(0, e); }
void Cpu::opcode_cb84(uint8_t &h) { opcode_res(0, h); }
void Cpu::opcode_cb85(uint8_t &l) { opcode_res(0, l); }
void Cpu::opcode_cb86(void) { opcode_res_hl(0); }
void Cpu::opcode_cb87(uint8_t &a) { opcode_res(0, a); }
void Cpu::opcode_cb88(uint8_t &b) { opcode_res(1, b); }
void Cpu::opcode_cb89(uint8_t &c) { opcode_res(1, c); }
void Cpu::opcode_cb8a(uint8_t &d) { opcode_res(1, d); }
void Cpu::opcode_cb8b(uint8_t &e) { opcode_res(1, e); }
void Cpu::opcode_cb8c(uint8_t &h) { opcode_res(1, h); }
void Cpu::opcode_cb8d(uint8_t &l) { opcode_res(1, l); }
void Cpu::opcode_cb8e(void) { opcode_res_hl(1); }
void Cpu::opcode_cb8f(uint8_t &a) { opcode_res(1, a); }

void Cpu::opcode_cb90(uint8_t &b) { opcode_res(2, b); }
void Cpu::opcode_cb91(uint8_t &c) { opcode_res(2, c); }
void Cpu::opcode_cb92(uint8_t &d) { opcode_res(2, d); }
void Cpu::opcode_cb93(uint8_t &e) { opcode_res(2, e); }
void Cpu::opcode_cb94(uint8_t &h) { opcode_res(2, h); }
void Cpu::opcode_cb95(uint8_t &l) { opcode_res(2, l); }
void Cpu::opcode_cb96(void) { opcode_res_hl(2); }
void Cpu::opcode_cb97(uint8_t &a) { opcode_res_hl(2); }
void Cpu::opcode_cb98(uint8_t &b) { opcode_res(3, b); }
void Cpu::opcode_cb99(uint8_t &c) { opcode_res(3, c); }
void Cpu::opcode_cb9a(uint8_t &d) { opcode_res(3, d); }
void Cpu::opcode_cb9b(uint8_t &e) { opcode_res(3, e); }
void Cpu::opcode_cb9c(uint8_t &h) { opcode_res(3, h); }
void Cpu::opcode_cb9d(uint8_t &l) { opcode_res(3, l); }
void Cpu::opcode_cb9e(void) { opcode_res_hl(3); }
void Cpu::opcode_cb9f(uint8_t &a) { opcode_res(3, a); }

void Cpu::opcode_cba0(uint8_t &b) { opcode_res(4, b); }
void Cpu::opcode_cba1(uint8_t &c) { opcode_res(4, c); }
void Cpu::opcode_cba2(uint8_t &d) { opcode_res(4, d); }
void Cpu::opcode_cba3(uint8_t &e) { opcode_res(4, e); }
void Cpu::opcode_cba4(uint8_t &h) { opcode_res(4, h); }
void Cpu::opcode_cba5(uint8_t &l) { opcode_res(4, l); }
void Cpu::opcode_cba6(void) { opcode_res_hl(4); }
void Cpu::opcode_cba7(uint8_t &a) { opcode_res(4, a); }
void Cpu::opcode_cba8(uint8_t &b) { opcode_res(5, b); }
void Cpu::opcode_cba9(uint8_t &c) { opcode_res(5, c); }
void Cpu::opcode_cbaa(uint8_t &d) { opcode_res(5, d); }
void Cpu::opcode_cbab(uint8_t &e) { opcode_res(5, e); }
void Cpu::opcode_cbac(uint8_t &h) { opcode_res(5, h); }
void Cpu::opcode_cbad(uint8_t &l) { opcode_res(5, l); }
void Cpu::opcode_cbae(void) { opcode_res_hl(5); }
void Cpu::opcode_cbaf(uint8_t &a) { opcode_res(5, a); }

void Cpu::opcode_cbb0(uint8_t &b) { opcode_res(6, b); }
void Cpu::opcode_cbb1(uint8_t &c) { opcode_res(6, c); }
void Cpu::opcode_cbb2(uint8_t &d) { opcode_res(6, d); }
void Cpu::opcode_cbb3(uint8_t &e) { opcode_res(6, e); }
void Cpu::opcode_cbb4(uint8_t &h) { opcode_res(6, h); }
void Cpu::opcode_cbb5(uint8_t &l) { opcode_res(6, l); }
void Cpu::opcode_cbb6(void) { opcode_res_hl(6); }
void Cpu::opcode_cbb7(uint8_t &a) { opcode_res(6, a); }
void Cpu::opcode_cbb8(uint8_t &b) { opcode_res(7, b); }
void Cpu::opcode_cbb9(uint8_t &c) { opcode_res(7, c); }
void Cpu::opcode_cbba(uint8_t &d) { opcode_res(7, d); }
void Cpu::opcode_cbbb(uint8_t &e) { opcode_res(7, e); }
void Cpu::opcode_cbbc(uint8_t &h) { opcode_res(7, h); }
void Cpu::opcode_cbbd(uint8_t &l) { opcode_res(7, l); }
void Cpu::opcode_cbbe(void) { opcode_res_hl(7); }
void Cpu::opcode_cbbf(uint8_t &a) { opcode_res(7, a); }

void Cpu::opcode_cbc0(uint8_t &b) { opcode_set(0, b); }
void Cpu::opcode_cbc1(uint8_t &c) { opcode_set(0, c); }
void Cpu::opcode_cbc2(uint8_t &d) { opcode_set(0, d); }
void Cpu::opcode_cbc3(uint8_t &e) { opcode_set(0, e); }
void Cpu::opcode_cbc4(uint8_t &h) { opcode_set(0, h); }
void Cpu::opcode_cbc5(uint8_t &l) { opcode_set(0, l); }
void Cpu::opcode_cbc6(void) { opcode_set_hl(0); }
void Cpu::opcode_cbc7(uint8_t &a) { opcode_set(0, a); }
void Cpu::opcode_cbc8(uint8_t &b) { opcode_set(1, b); }
void Cpu::opcode_cbc9(uint8_t &c) { opcode_set(1, c); }
void Cpu::opcode_cbca(uint8_t &d) { opcode_set(1, d); }
void Cpu::opcode_cbcb(uint8_t &e) { opcode_set(1, e); }
void Cpu::opcode_cbcc(uint8_t &h) { opcode_set(1, h); }
void Cpu::opcode_cbcd(uint8_t &l) { opcode_set(1, l); }
void Cpu::opcode_cbce(void) { opcode_set_hl(1); }
void Cpu::opcode_cbcf(uint8_t &a) { opcode_set(1, a); }

void Cpu::opcode_cbd0(uint8_t &b) { opcode_set(2, b); }
void Cpu::opcode_cbd1(uint8_t &c) { opcode_set(2, c); }
void Cpu::opcode_cbd2(uint8_t &d) { opcode_set(2, d); }
void Cpu::opcode_cbd3(uint8_t &e) { opcode_set(2, e); }
void Cpu::opcode_cbd4(uint8_t &h) { opcode_set(2, h); }
void Cpu::opcode_cbd5(uint8_t &l) { opcode_set(2, l); }
void Cpu::opcode_cbd6(void) { opcode_set_hl(2); }
void Cpu::opcode_cbd7(uint8_t &a) { opcode_set(2, a); }
void Cpu::opcode_cbd8(uint8_t &b) { opcode_set(3, b); }
void Cpu::opcode_cbd9(uint8_t &c) { opcode_set(3, c); }
void Cpu::opcode_cbda(uint8_t &d) { opcode_set(3, d); }
void Cpu::opcode_cbdb(uint8_t &e) { opcode_set(3, e); }
void Cpu::opcode_cbdc(uint8_t &h) { opcode_set(3, h); }
void Cpu::opcode_cbdd(uint8_t &l) { opcode_set(3, l); }
void Cpu::opcode_cbde(void) { opcode_set_hl(3); }
void Cpu::opcode_cbdf(uint8_t &a) { opcode_set(3, a); }

void Cpu::opcode_cbe0(uint8_t &b) { opcode_set(4, b); }
void Cpu::opcode_cbe1(uint8_t &c) { opcode_set(4, c); }
void Cpu::opcode_cbe2(uint8_t &d) { opcode_set(4, d); }
void Cpu::opcode_cbe3(uint8_t &e) { opcode_set(4, e); }
void Cpu::opcode_cbe4(uint8_t &h) { opcode_set(4, h); }
void Cpu::opcode_cbe5(uint8_t &l) { opcode_set(4, l); }
void Cpu::opcode_cbe6(void) { opcode_set_hl(4); }
void Cpu::opcode_cbe7(uint8_t &a) { opcode_set(4, a); }
void Cpu::opcode_cbe8(uint8_t &b) { opcode_set(5, b); }
void Cpu::opcode_cbe9(uint8_t &c) { opcode_set(5, c); }
void Cpu::opcode_cbea(uint8_t &d) { opcode_set(5, d); } 
void Cpu::opcode_cbeb(uint8_t &e) { opcode_set(5, e); }
void Cpu::opcode_cbec(uint8_t &h) { opcode_set(5, h); }
void Cpu::opcode_cbed(uint8_t &l) { opcode_set(5, l); }
void Cpu::opcode_cbee(void) { opcode_set_hl(5); }
void Cpu::opcode_cbef(uint8_t &a) { opcode_set(5, a); }

void Cpu::opcode_cbf0(uint8_t &b) { opcode_set(6, b); }
void Cpu::opcode_cbf1(uint8_t &c) { opcode_set(6, c); }
void Cpu::opcode_cbf2(uint8_t &d) { opcode_set(6, d); }
void Cpu::opcode_cbf3(uint8_t &e) { opcode_set(6, e); }
void Cpu::opcode_cbf4(uint8_t &h) { opcode_set(6, h); }
void Cpu::opcode_cbf5(uint8_t &l) { opcode_set(6, l); }
void Cpu::opcode_cbf6(void) { opcode_set_hl(6); }
void Cpu::opcode_cbf7(uint8_t &a) { opcode_set(6, a); }
void Cpu::opcode_cbf8(uint8_t &b) { opcode_set(7, b); }
void Cpu::opcode_cbf9(uint8_t &c) { opcode_set(7, c); }
void Cpu::opcode_cbfa(uint8_t &d) { opcode_set(7, d); }
void Cpu::opcode_cbfb(uint8_t &e) { opcode_set(7, e); }
void Cpu::opcode_cbfc(uint8_t &h) { opcode_set(7, h); }
void Cpu::opcode_cbfd(uint8_t &l) { opcode_set(7, l); }
void Cpu::opcode_cbfe(void) { opcode_set_hl(7); }
void Cpu::opcode_cbff(uint8_t &a) { opcode_set(7, a); }