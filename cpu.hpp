#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Registers.hpp"
#include "MemoryBus.hpp"

class Cpu {
  public:
    Registers registers = Registers();
    MemoryBus *memoryBus = nullptr;
    uint16_t pc = 0x100;

    bool interruptsEnabled = false;
    bool isHalted = false;

    Cpu(MemoryBus *memoryBus): memoryBus(memoryBus) {}

    void disableInterrupts(void);
    void enableInterrupts(void);
    
    void halt(void);
    void run(void);

    // handles executing the current instruction (which is what pc points to)
    uint16_t execInstruction();

    // check for overflow at bits 3 and 7 for H and C flag respectively
    bool cOverflowAdd(uint8_t, uint8_t);
    bool hOverflowAdd(uint8_t, uint8_t);

    bool cOverflowSub(uint8_t, uint8_t);
    bool hOverflowSub(uint8_t, uint8_t);

    bool cOverflowAdd16(uint16_t, uint16_t);
    bool hOverflowAdd16(uint16_t, uint16_t);
    // functions for executing all opcodes

    // TODO - categorize function declarations (and definitions in cpu.cpp) based on
    //        whether they are arithmetic / bit-shift / load / etc. functions

    void opcode_inc(uint8_t &r8); // general function to increment some 8-bit register: r8++
    void opcode_dec(uint8_t &r8); // general function to decrement some 8-bit register: r8--
    void opcode_inc16(uint16_t (Registers::*getReg)(), void (Registers::*setReg)(uint16_t)); // increase 16-bit register by 1: setReg(getReg()+1)
    void opcode_dec16(uint16_t (Registers::*getReg)(), void (Registers::*setReg)(uint16_t)); // decrease 16-bit register by 1: setReg(getReg()-1)
    void opcode_ld_general(uint8_t &r8); // general function to load some arbitrary value into an 8-bit register: r8 = val
    void opcode_ld_general(uint8_t &r8, uint16_t address); // general function to load some arbitrary value at some address into an 8-bit register: r8 = [address]
    void opcode_ld_general16(uint16_t (Registers::*getReg)(), void (Registers::*setReg)(uint16_t)); // load a general 16-bit value into a 16-bit register: setReg(getReg()) {setReg and getReg refer to different registers)
    void opcode_rlca(uint8_t &a); // function to shift a, 7th bit becomes both 0 bit and carry bit: C <- [7, 0] <- [7]
    void opcode_rrca(uint8_t &a); // function to shift a, 0th bit becomes both 7th bit and carry bit: [0] -> [7,0] -> C
    void opcode_rlc(uint8_t &r8); // same as rlca but for any register r8
    void opcode_rrc(uint8_t &r8); // same as rrca but for any register r8
    void opcode_rla(uint8_t &a); // same as rlca except 7th bit only becomes carry and the old carry replaces the 0th bit: C <- [7, 0] <- C
    void opcode_rra(uint8_t &a); // same as rrca except 0th bit only becomes carry and the old carry replaces the 7th bit: C -> [7, 0] -> C
    void opcode_rl(uint8_t &r8); // same as rla but for any register r8
    void opcode_rr(uint8_t &r8); // same as rra but for any register r8
    void opcode_sla(uint8_t &r8); // C <- [7 <- 0] <- 0
    void opcode_sra(uint8_t &r8); // [7] -> [7 -> 0] -> C
    void opcode_bit(uint8_t u3, uint8_t r8); // Z flag = bit u3 of r8
    void opcode_res(uint8_t u3, uint8_t &r8); // reset bit u3 of r8
    void opcode_set(uint8_t u3, uint8_t &r8); // set bit u3 of r8 
    void opcode_swap(uint8_t &r8); // swaps upper and lower 4 bits of r8
    void opcode_srl(uint8_t &r8); // 0 -> [7, 0] -> C
    void opcode_ld(uint8_t &rd, uint8_t r8); // opcodes 40 - 6f, 78 - 7f ( and a few others, check opcode table online)
    void opcode_ld_from_address(uint8_t &r8); // r8 = [address at pc]
    void opcode_ldh_from_address(uint8_t &r8); // r8 = [0xFF00 + address at pc]
    void opcode_ld_into_address(uint8_t r8); // [address at pc] = r8
    void opcode_ld_into_address(uint8_t r8, uint16_t address);
    void opcode_ldh_into_address(uint8_t r8); // [0xFF00 + address] = r8
    void opcode_ld_hl(uint8_t r8); // opcodes 70 - 77
    void opcode_add16(uint16_t (Registers::*getRegD)(), uint16_t (Registers::*getRegS)(), void (Registers::*setRegD)(uint16_t)); // 16-bit regD += 16-bit RegS
    void opcode_add_a(uint8_t &a, uint8_t r8); // opcodes 80 - 87
    void opcode_adc_a(uint8_t &a, uint8_t r8); // opcodes 0x88 - 0x8f
    void opcode_sub_a(uint8_t &a, uint8_t r8); // opcodes 0x90 - 0x97
    void opcode_sbc_a(uint8_t &a, uint8_t r8); // opcodes 0x98 - 0x9f
    void opcode_and_a(uint8_t &a, uint8_t r8); // opcodes 0xa0 - 0xa7
    void opcode_xor_a(uint8_t &a, uint8_t r8); // opcodes 0xa8 - 0xaf
    void opcode_or_a(uint8_t &a, uint8_t r8); // opcodes 0xb0 - 0xb7
    void opcode_cp_a(uint8_t &a, uint8_t r8); // opcodes 0xb8 - 0xbf
    void opcode_jumpr(bool cc = true); // relative jump (i.e pc = pc + val), cc is condition for jumping
    void opcode_jump(bool cc = true); // absolute jump (i.e pc = val), cc is condition for jumping
    void opcode_cpl(uint8_t &a); // complement a: a = ~a
    void opcode_return(bool cc = true); // return operation
    void opcode_pop(void (Registers::*setReg)(uint16_t)); // pop operation
    void opcode_push(uint16_t (Registers::*getReg)(void)); // push operation
    void opcode_call(bool cc = true); // call function
    void opcode_rst(uint16_t vec); // same as call with few rst supported vectors (i.e $00, $08, $10, ... , $30, $38)
    void opcode_general_a(uint8_t &a, void (Cpu::*opcode_general_fn)(uint8_t &a, uint8_t r8)); // pass in a and some function that acts on a and r8, performs f(a, r8)
    void opcode_general_prefix_hl(void (Cpu::*fn) (uint8_t &r8)); // opcodefn $CB prefix on [HL]
    void opcode_general_prefix_hl(void (Cpu::*fn) (uint8_t u3, uint8_t &r8), uint8_t u3); // opcodefn $CB prefix on [HL]
    void opcode_bit_hl(uint8_t u3); // change u3 bit in [hl]
    void opcode_res_hl(uint8_t u3); // reset u3 bit in [hl]
    void opcode_set_hl(uint8_t u3); // set u3 bit in [hl]

    void opcode_00(void); // NOP | 1, 4 | - - - -
    void opcode_01(void); // LD BC, n16 | 1, 4 | - - - -
    void opcode_02(uint8_t a); // LD [BC], A | 1, 8 | - - - -
    void opcode_03(void); // INC BC | 1, 8 | - - - -
    void opcode_04(uint8_t &b); // INC B | 1, 4 | Z 0 H -
    void opcode_05(uint8_t &b); // DEC B | 1, 4| Z 1 H -
    void opcode_06(uint8_t &b); // LD B, n8 | 2, 8 | - - - -
    void opcode_07(uint8_t &a); // RLCA | 1, 4 | 0 0 0 C
    void opcode_08(void); // LD [a16], SP | 3, 20 | - - - -
    void opcode_09(void); // ADD HL, BC | 1, 8 | - 0 H C
    void opcode_0a(uint8_t &a); // LD A, [BC] | 1, 8 | - - - -
    void opcode_0b(void); // DEC BC | 1, 8 | - - - -
    void opcode_0c(uint8_t &c); // INC C | 1, 4 | Z 0 H -
    void opcode_0d(uint8_t &c); // DEC C | 1, 4 | Z 1 H -
    void opcode_0e(uint8_t &c); // LD C, n8 | 2, 8 | - - - -
    void opcode_0f(uint8_t &a); // RRCA | 1, 4 | 0 0 0 C

    void opcode_10(void); // STOP n8 | 2, 8 | - - - -
    void opcode_11(void); // LD DE, n16 | 3, 12 | - - - -
    void opcode_12(uint8_t a); // LD [DE] A | 1, 8 | - - - -
    void opcode_13(void); // INC DE | 1, 8 | - - - -
    void opcode_14(uint8_t &d); // INC D | 1, 4 | Z 0 H -
    void opcode_15(uint8_t &d); // DEC D | 1, 4 | Z 1 H -
    void opcode_16(uint8_t &d); // LD D, n8 | 2, 8 | - - - -
    void opcode_17(uint8_t &a); // RLA | 1, 4 | 0 0 0 C
    
    void opcode_18(void); // JR e8 | 2, 12 | - - - -
    void opcode_19(void); // ADD HL, DE | 1, 8 | - 0 H C
    void opcode_1a(uint8_t &a); // LD A, [DE] | 1, 8 | - - - -
    void opcode_1b(void); // DEC DE | 1, 8 | - - - -
    void opcode_1c(uint8_t &e); // INC E | 1, 4 | Z 0 H -
    void opcode_1d(uint8_t &e); // DEC E | 1, 4 | Z 1 H -
    void opcode_1e(uint8_t &e); // LD E, n8 | 2, 8 | - - - -
    void opcode_1f(uint8_t &a); // RRA | 1, 4 | 0 0 0 C

    void opcode_20(void); // JR NZ, e8 | 2, 12/8 | - - - -
    void opcode_21(void); // LD HL, n16 | 3, 12 | - - - -
    void opcode_22(uint8_t a); // LD [HL+], A | 1, 8 | - - - -
    void opcode_23(void); // INC HL | 1, 8 | - - - -
    void opcode_24(uint8_t &h); // INC H | 1, 4 | Z 0 H -
    void opcode_25(uint8_t &h); // DEC H | 1, 4 | Z 1 H -
    void opcode_26(uint8_t &h); // LD H, n8 | 2, 8 | - - - -
    void opcode_27(void); // DAA | 1, 4 | Z - 0 C
    void opcode_28(void); // JR Z, e8 | 2, 12/8 | - - - -
    void opcode_29(void); // ADD HL, HL | 1, 8 | - 0 H C
    void opcode_2a(uint8_t &a); // LD A, [HL+] | 1, 8 | - - - -
    void opcode_2b(void); // DEC HL | 1, 8 | - - - -
    void opcode_2c(uint8_t &l); // INC L | 1, 4 | Z 0 H -
    void opcode_2d(uint8_t &l); // DEC L | 1, 4 | Z 1 H -
    void opcode_2e(uint8_t &l); // LD L, n8 | 2, 8 | - - - -
    void opcode_2f(uint8_t &a); // CPL | 1, 4 | - 1 1 -

    void opcode_30(void); // JR NC, e8 | 2, 12/8 | - - - -
    void opcode_31(void); // LD SP, n16 | 3, 12 | - - - -
    void opcode_32(uint8_t a); // LD [HL-], A | 1, 8 | - - - -
    void opcode_33(void); // INC SP | 1, 8 | - - - -
    void opcode_34(void); // INC [HL] | 1, 12 | Z 0 H -
    void opcode_35(void); // DEC [HL] | 1, 12 | Z 1 H -
    void opcode_36(void); // LD [HL], n8 | 2, 12 | - - - -
    void opcode_37(void); // SCF | 1, 4 | - 0 0 1 
    void opcode_38(void); // JR C, e8 | 2, 12/8 | - - - -
    void opcode_39(void); // ADD HL, SP | 1, 8 | - 0 H C
    void opcode_3a(uint8_t &a); // LD A, [HL-] | 1, 8 | - - - -
    void opcode_3b(void); // DEC SP | 1, 8 | - - - -
    void opcode_3c(uint8_t &a); // INC A | 1, 4 | Z 0 H -
    void opcode_3d(uint8_t &a); // DEC A | 1, 4 | Z 1 H -
    void opcode_3e(uint8_t &a); // LD A, n8 | 1, 4 | - - - -
    void opcode_3f(void); // CCF | 1, 4 | - 0 0 C

    /* % --------------- LD instructions --------------- % */

    // LD B, X
    void opcode_40(uint8_t &b); // LD B, B | 1, 4 | - - - -
    void opcode_41(uint8_t &b, uint8_t c); // LD B, C | 1, 4 | - - - -
    void opcode_42(uint8_t &b, uint8_t d); // LD B, D | 1, 4 | - - - -
    void opcode_43(uint8_t &b, uint8_t e); // LD B, E | 1, 4 | - - - -
    void opcode_44(uint8_t &b, uint8_t h); // LD B, H | 1, 4 | - - - -
    void opcode_45(uint8_t &b, uint8_t l); // LD B, L | 1, 4 | - - - -
    void opcode_46(uint8_t &b); // LD B, [HL] | 1, 4 | - - - -
    void opcode_47(uint8_t &b, uint8_t a); // LD B, A | 1, 4 | - - - -

    // LD C, X
    void opcode_48(uint8_t &c, uint8_t b); // LD C, B | 1, 4 | - - - -
    void opcode_49(uint8_t &c); // LD C, C | 1, 4 | - - - -
    void opcode_4a(uint8_t &c, uint8_t d); // LD C, D | 1, 4 | - - - -
    void opcode_4b(uint8_t &c, uint8_t e); // LD C, E | 1, 4 | - - - -
    void opcode_4c(uint8_t &c, uint8_t h); // LD C, H | 1, 4 | - - - -
    void opcode_4d(uint8_t &c, uint8_t l); // LD C, L | 1, 4 | - - - -
    void opcode_4e(uint8_t &c); // LD C, [HL] | 1, 8 | - - - -
    void opcode_4f(uint8_t &c, uint8_t e); // LD C, A | 1, 4 | - - - -

    // LD D, X
    void opcode_50(uint8_t &d, uint8_t b); // LD D, B | 1, 4 | - - - -
    void opcode_51(uint8_t &d, uint8_t c); // LD D, C | 1, 4 | - - - -
    void opcode_52(uint8_t &d); // LD D, D | 1, 4 | - - - -
    void opcode_53(uint8_t &d, uint8_t e); // LD D, E | 1, 4 | - - - -
    void opcode_54(uint8_t &d, uint8_t h); // LD D, H | 1, 4 | - - - -
    void opcode_55(uint8_t &d, uint8_t l); // LD D, L | 1, 4 | - - - -
    void opcode_56(uint8_t &d); // LD D, [HL] | 1, 8 | - - - -
    void opcode_57(uint8_t &d, uint8_t a); // LD D, A | 1, 4 | - - - -

    // LD E, X
    void opcode_58(uint8_t &e, uint8_t b); // LD E, B | 1, 4 | - - - -
    void opcode_59(uint8_t &e, uint8_t c); // LD E, C | 1, 4 | - - - -
    void opcode_5a(uint8_t &e, uint8_t d); // LD E, D | 1, 4 | - - - -
    void opcode_5b(uint8_t &e); // LD E, E | 1, 4 | - - - -
    void opcode_5c(uint8_t &e, uint8_t h); // LD E, H | 1, 4 | - - - -
    void opcode_5d(uint8_t &e, uint8_t l); // LD E, L | 1, 4 | - - - -
    void opcode_5e(uint8_t &e); // LD E, [HL] | 1, 8 | - - - -
    void opcode_5f(uint8_t &e, uint8_t a); // LD E, A | 1, 4 | - - - -

    // LD H, X
    void opcode_60(uint8_t &h, uint8_t b); // LD H, B | 1, 4 | - - - -
    void opcode_61(uint8_t &h, uint8_t c); // LD H, C | 1, 4 | - - - -
    void opcode_62(uint8_t &h, uint8_t d); // LD H, D | 1, 4 | - - - -
    void opcode_63(uint8_t &h, uint8_t e); // LD H, E | 1, 4 | - - - -
    void opcode_64(uint8_t &h); // LD H, H | 1, 4 | - - - -
    void opcode_65(uint8_t &h, uint8_t l); // LD H, L | 1, 4 | - - - -
    void opcode_66(uint8_t &h); // LD H, [HL] | 1, 8 | - - - -
    void opcode_67(uint8_t &h, uint8_t a); // LD H, A | 1, 4 | - - - -

    // LD L, X
    void opcode_68(uint8_t &l, uint8_t b); // LD L, B | 1, 4 | - - - -
    void opcode_69(uint8_t &l, uint8_t c); // LD L, C | 1, 4 | - - - -
    void opcode_6a(uint8_t &l, uint8_t d); // LD L, D | 1, 4 | - - - -
    void opcode_6b(uint8_t &l, uint8_t e); // LD L, E | 1, 4 | - - - -
    void opcode_6c(uint8_t &l, uint8_t h); // LD L, H | 1, 4 | - - - -
    void opcode_6d(uint8_t &l); // LD L, L | 1, 4 | - - - -
    void opcode_6e(uint8_t &l); // LD L, [HL] | 1, 4 | - - - -
    void opcode_6f(uint8_t &l, uint8_t a); // LD L, A | 1, 4 | - - - -

    // LD [HL], X
    void opcode_70(uint8_t b); // LD [HL], B | 1, 8 | - - - -
    void opcode_71(uint8_t c); // LD [HL], C | 1, 8 | - - - -
    void opcode_72(uint8_t d); // LD [HL], D | 1, 8 | - - - -
    void opcode_73(uint8_t e); // LD [HL], E | 1, 8 | - - - -
    void opcode_74(uint8_t h); // LD [HL], H | 1, 8 | - - - -
    void opcode_75(uint8_t l); // LD [HL], L | 1, 8 | - - - -
    void opcode_76(void); // HALT | 1, 4 | - - - -
    void opcode_77(uint8_t a); // LD [HL], A | 1, 8 | - - - -

    // LD A, X
    void opcode_78(uint8_t &a, uint8_t b); // LD A, B | 1, 4 | - - - -
    void opcode_79(uint8_t &a, uint8_t c); // LD A, C | 1, 4 | - - - -
    void opcode_7a(uint8_t &a, uint8_t d); // LD A, D | 1, 4 | - - - -
    void opcode_7b(uint8_t &a, uint8_t e); // LD A, E | 1, 4 | - - - -
    void opcode_7c(uint8_t &a, uint8_t h); // LD A, H | 1, 4 | - - - -
    void opcode_7d(uint8_t &a, uint8_t l); // LD A, L | 1, 4 | - - - -
    void opcode_7e(uint8_t &a); // LD A, [HL] | 1, 4 | - - - -
    void opcode_7f(uint8_t &a); // LD A, A | 1, 4 | - - - -

    /* % --------------- ADD instructions --------------- % */
    void opcode_80(uint8_t &a, uint8_t b); // ADD A, B | 1, 4 | Z 0 H C
    void opcode_81(uint8_t &a, uint8_t c); // ADD A, C | 1, 4 | Z 0 H C
    void opcode_82(uint8_t &a, uint8_t d); // ADD A, D | 1, 4 | Z 0 H C
    void opcode_83(uint8_t &a, uint8_t e); // ADD A, E | 1, 4 | Z 0 H C
    void opcode_84(uint8_t &a, uint8_t h); // ADD A, H | 1, 4 | Z 0 H C
    void opcode_85(uint8_t &a, uint8_t l); // ADD A, L | 1, 4 | Z 0 H C
    void opcode_86(uint8_t &a); // ADD A, [HL] | 1, 8 | Z 0 H C
    void opcode_87(uint8_t &a); // ADD A, A | 1, 4 | Z 0 H C

    /* % --------------- ADC instructions --------------- % */
    void opcode_88(uint8_t &a, uint8_t b);  // ADC A, B | 1, 4 | Z 0 H C
    void opcode_89(uint8_t &a, uint8_t c);  // ADC A, C | 1, 4 | Z 0 H C
    void opcode_8a(uint8_t &a, uint8_t d);  // ADC A, D | 1, 4 | Z 0 H C
    void opcode_8b(uint8_t &a, uint8_t e);  // ADC A, E | 1, 4 | Z 0 H C
    void opcode_8c(uint8_t &a, uint8_t h);  // ADC A, H | 1, 4 | Z 0 H C
    void opcode_8d(uint8_t &a, uint8_t l);  // ADC A, L | 1, 4 | Z 0 H C
    void opcode_8e(uint8_t &a);  // ADC A, [HL] | 1, 8 | Z 0 H C
    void opcode_8f(uint8_t &a);  // ADC A, A | 1, 4 | Z 0 H C

    /* % --------------- SUB instructions --------------- % */
    void opcode_90(uint8_t &a, uint8_t b); // A, B | 1, 4 | Z 1 H C
    void opcode_91(uint8_t &a, uint8_t c); // A, C | 1, 4 | Z 1 H C
    void opcode_92(uint8_t &a, uint8_t d); // A, D | 1, 4 | Z 1 H C
    void opcode_93(uint8_t &a, uint8_t e); // A, E | 1, 4 | Z 1 H C
    void opcode_94(uint8_t &a, uint8_t h); // A, H | 1, 4 | Z 1 H C
    void opcode_95(uint8_t &a, uint8_t l); // A, L | 1, 4 | Z 1 H C
    void opcode_96(uint8_t &a); // A, [HL] | 1, 8 | Z 1 H C
    void opcode_97(uint8_t &a); // A, A | 1, 4 | Z 1 H C

    /* % --------------- SBC instructions --------------- % */
    void opcode_98(uint8_t &a, uint8_t b); // SBC A, B | 1, 4 | Z 1 H C
    void opcode_99(uint8_t &a, uint8_t c); // SBC A, C | 1, 4 | Z 1 H C
    void opcode_9a(uint8_t &a, uint8_t d); // SBC A, D | 1, 4 | Z 1 H C
    void opcode_9b(uint8_t &a, uint8_t e); // SBC A, E | 1, 4 | Z 1 H C
    void opcode_9c(uint8_t &a, uint8_t h); // SBC A, H | 1, 4 | Z 1 H C
    void opcode_9d(uint8_t &a, uint8_t l); // SBC A, L | 1, 4 | Z 1 H C
    void opcode_9e(uint8_t &a); // SBC A, [HL] | 1, 8 | Z 1 H C
    void opcode_9f(uint8_t &a); // SBC A, A | 1, 4 | Z 1 H -

    /* % --------------- AND instructions --------------- % */
    void opcode_a0(uint8_t &a, uint8_t b); // AND A, B | 1, 4 | Z 0 1 0
    void opcode_a1(uint8_t &a, uint8_t c); // AND A, C | 1, 4 | Z 0 1 0
    void opcode_a2(uint8_t &a, uint8_t d); // AND A, D | 1, 4 | Z 0 1 0
    void opcode_a3(uint8_t &a, uint8_t e); // AND A, E | 1, 4 | Z 0 1 0
    void opcode_a4(uint8_t &a, uint8_t h); // AND A, H | 1, 4 | Z 0 1 0
    void opcode_a5(uint8_t &a, uint8_t l); // AND A, L | 1, 4 | Z 0 1 0
    void opcode_a6(uint8_t &a); // AND A, [HL] | 1, 8 | Z 0 1 0
    void opcode_a7(uint8_t &a); // AND A, A | 1, 4 | Z 0 1 0

    /* % --------------- XOR instructions --------------- % */
    void opcode_a8(uint8_t &a, uint8_t b); // XOR A, B | 1, 4 | Z 0 0 0
    void opcode_a9(uint8_t &a, uint8_t c); // XOR A, C | 1, 4 | Z 0 0 0
    void opcode_aa(uint8_t &a, uint8_t d); // XOR A, D | 1, 4 | Z 0 0 0
    void opcode_ab(uint8_t &a, uint8_t e); // XOR A, E | 1, 4 | Z 0 0 0
    void opcode_ac(uint8_t &a, uint8_t h); // XOR A, H | 1, 4 | Z 0 0 0
    void opcode_ad(uint8_t &a, uint8_t l); // XOR A, L | 1, 4 | Z 0 0 0
    void opcode_ae(uint8_t &a); // XOR A, [HL] | 1, 8 | Z 0 0 0
    void opcode_af(uint8_t &a); // XOR A, A | 1, 4 | 1 0 0 0

    /* % --------------- OR instructions --------------- % */
    void opcode_b0(uint8_t &a, uint8_t b); // OR A, B | 1, 4 | Z 0 0 0
    void opcode_b1(uint8_t &a, uint8_t c); // OR A, C | 1, 4 | Z 0 0 0
    void opcode_b2(uint8_t &a, uint8_t d); // OR A, D | 1, 4 | Z 0 0 0 
    void opcode_b3(uint8_t &a, uint8_t e); // OR A, E | 1, 4 | Z 0 0 0
    void opcode_b4(uint8_t &a, uint8_t h); // OR A, H | 1, 4 | Z 0 0 0
    void opcode_b5(uint8_t &a, uint8_t l); // OR A, L | 1, 4 | Z 0 0 0
    void opcode_b6(uint8_t &a); // OR A, [HL] | 1, 8 | Z 0 0 0
    void opcode_b7(uint8_t &a); // OR A, A | 1, 4 | Z 0 0 0

    /* % --------------- CP instructions --------------- % */
    void opcode_b8(uint8_t &a, uint8_t b); // CP A, B | 1, 4 | Z 1 H C
    void opcode_b9(uint8_t &a, uint8_t c); // CP A, C | 1, 4 | Z 1 H C
    void opcode_ba(uint8_t &a, uint8_t d); // CP A, D | 1, 4 | Z 1 H C
    void opcode_bb(uint8_t &a, uint8_t e); // CP A, E | 1, 4 | Z 1 H C
    void opcode_bc(uint8_t &a, uint8_t h); // CP A, H | 1, 4 | Z 1 H C
    void opcode_bd(uint8_t &a, uint8_t l); // CP A, L | 1, 4 | Z 1 H C
    void opcode_be(uint8_t &a); // CP A, [HL] | 1, 8 | Z 1 H C
    void opcode_bf(uint8_t &a); // CP A, A | 1, 4 | 1 1 0 0

    /* % --------------- remaining instructions --------------- % */
    void opcode_c0(void); // RET NZ | 1, 20/8 | - - - -
    void opcode_c1(void); // POP BC | 1, 12 | - - - -
    void opcode_c2(void); // JP NZ, a16 | 3, 16/12 | - - - -
    void opcode_c3(void); // JP a16 | 3, 16 | - - - -
    void opcode_c4(void); // CALL NZ, a16 | 3, 24/12 | - - - -
    void opcode_c5(void); // PUSH BC | 1, 16 | - - - -
    void opcode_c6(uint8_t &a); // ADD A, n8 | 2, 8 | Z 0 H C
    void opcode_c7(void); // RST $00 | 1, 16 | - - - -
    void opcode_c8(void); // RET Z | 1, 20/8 | - - - -
    void opcode_c9(void); // RET | 1, 16 | - - - -
    void opcode_ca(void); // JP Z, a16 | 3, 16/12 | - - - -
    void opcode_cb(void); // PREFIX | 1, 4 | - - - -
    void opcode_cc(void); // CALL Z, a16 | 3, 24/12 | - - - -
    void opcode_cd(void); // CALL a16 | 3, 24 | - - - -
    void opcode_ce(uint8_t &a); // ADC A, n8 | 2, 8 | Z 0 H C
    void opcode_cf(void); // RST $08 | 1, 16 | - - - -

    void opcode_d0(void); // RET NC | 1, 20/8 | - - - -
    void opcode_d1(void); // POP DE | 1, 12 | - - - -
    void opcode_d2(void); // JP NC, a16 | 3, 16/12 | - - - -
    void opcode_d3(void); // invalid opcode
    void opcode_d4(void); // CALL NC, a16 | 3, 24/12 | - - - -
    void opcode_d5(void); // PUSH DE | 1, 16 | - - - -
    void opcode_d6(uint8_t &a); // SUB A, n8 | 2, 8 | Z 0 H C
    void opcode_d7(void); // RST $10 | 1, 16 | - - - -
    void opcode_d8(void); // RET C | 1, 20/8 | - - - -
    void opcode_d9(void); // RETI | 1, 16 | - - - -
    void opcode_da(void); // JP C, a16 | 3, 16/12 | - - - -
    void opcode_db(void); // invalid opcode
    void opcode_dc(void); // CALL C, a16 | 3, 24/12 | - - - -
    void opcode_dd(void); // invalid opcode
    void opcode_de(uint8_t &a); // SBC A, n8 | 2, 8 | Z 1 H C
    void opcode_df(void); // RST $18 | 1, 16 | - - - -

    void opcode_e0(uint8_t &a); // LDH [a8], A | 2, 12 | - - - -
    void opcode_e1(void); // POP HL | 1, 12 | - - - -
    void opcode_e2(uint8_t &a); // LD [C], A | 1, 8 | - - - -
    void opcode_e3(void); // invalid opcode
    void opcode_e4(void); // invalid opcode
    void opcode_e5(void); // PUSH HL | 1, 16 | - - - -
    void opcode_e6(uint8_t &r8); // AND A, n8 | 2, 8 | Z 0 1 0
    void opcode_e7(void); // RST $20 | 1, 16 | - - - -
    void opcode_e8(void); // ADD SP, e8 | 2, 16 | 0 0 H C
    void opcode_e9(void); // JP HL | 1, 4 | - - - -
    void opcode_ea(uint8_t a); // LD [a16], A | 3, 16  | - - - -
    void opcode_eb(void); // invalid opcode
    void opcode_ec(void); // invalid opcode
    void opcode_ed(void); // invalid opcode
    void opcode_ee(uint8_t &a); // XOR A, n8 | 2, 8 | Z 0 0 0
    void opcode_ef(void); // RST $28

    void opcode_f0(uint8_t &a); // LDH A, [a8] | 2, 12 | - - - -
    void opcode_f1(void); // POP AF | 1, 12 | Z N H C
    void opcode_f2(uint8_t &a); // LD A, [a8] | 2, 12 | - - - -
    void opcode_f3(void); // DI | 1, 4 | - - - -
    void opcode_f4(void); // invalid opcode
    void opcode_f5(void); // PUSH AF | 1, 16 | - - - -
    void opcode_f6(uint8_t &a); // OR A, n8 | 2, 8 | Z 0 0 0
    void opcode_f7(void); // RST $30 | 1, 16 | - - - -
    void opcode_f8(void); // LD HL, SP + e8 | 2, 12 | 0 0 H C
    void opcode_f9(void); // LD SP, HL | 1, 8 | - - - -
    void opcode_fa(uint8_t &a); // LD A, [a16] | 3, 16 | - - - -
    void opcode_fb(void); // EI | 1, 4 | - - - -
    void opcode_fc(void); // invalid opcode
    void opcode_fd(void); // invalid opcode
    void opcode_fe(uint8_t &a); // CP A, n8 | 2, 8 | Z 1 H C
    void opcode_ff(void); // RST $38 | 1, 16 | - - - -

    void opcode_cb00(uint8_t &b); // RLC B | 2, 8 | Z 0 0 C
    void opcode_cb01(uint8_t &c); // RLC C | 2, 8 | Z 0 0 C
    void opcode_cb02(uint8_t &d); // RLC D | 2, 8 | Z 0 0 C
    void opcode_cb03(uint8_t &e); // RLC E | 2, 8 | Z 0 0 C
    void opcode_cb04(uint8_t &h); // RLC H | 2, 8 | Z 0 0 C
    void opcode_cb05(uint8_t &l); // RLC L | 2, 8 | Z 0 0 C
    void opcode_cb06(void); // RLC [HL] | 2, 16 | Z 0 0 C
    void opcode_cb07(uint8_t &a); // RLC A | 2, 8 | Z 0 0 C
    void opcode_cb08(uint8_t &b); // RRC B | 2, 8 | Z 0 0 C
    void opcode_cb09(uint8_t &c); // RRC C | 2, 8 | Z 0 0 C
    void opcode_cb0a(uint8_t &d); // RRC D | 2, 8 | Z 0 0 C 
    void opcode_cb0b(uint8_t &e); // RRC E | 2, 8 | Z 0 0 C
    void opcode_cb0c(uint8_t &h); // RRC H | 2, 8 | Z 0 0 C
    void opcode_cb0d(uint8_t &l); // RRC L | 2, 8 | Z 0 0 C
    void opcode_cb0e(void); // RRC [HL] | 2, 8 | Z 0 0 C
    void opcode_cb0f(uint8_t &a); // RRC A | 2, 8 | Z 0 0 C

    void opcode_cb10(uint8_t &b); // RL B | 2, 8 | Z 0 0 C
    void opcode_cb11(uint8_t &c); // RL C | 2, 8 | Z 0 0 C
    void opcode_cb12(uint8_t &d); // RL D | 2, 8 | Z 0 0 C
    void opcode_cb13(uint8_t &e); // RL E | 2, 8 | Z 0 0 C
    void opcode_cb14(uint8_t &h); // RL H | 2, 8 | Z 0 0 C
    void opcode_cb15(uint8_t &l); // RL L | 2, 8 | Z 0 0 C
    void opcode_cb16(void); // RL [HL] | 2, 16 | Z 0 0 C
    void opcode_cb17(uint8_t &a); // RL A | 2, 8 | Z 0 0 C
    void opcode_cb18(uint8_t &b); // RR B | 2, 8 | Z 0 0 C
    void opcode_cb19(uint8_t &c); // RR C | 2, 8 | Z 0 0 C
    void opcode_cb1a(uint8_t &d); // RR D | 2, 8 | Z 0 0 C
    void opcode_cb1b(uint8_t &e); // RR E | 2, 8 | Z 0 0 C
    void opcode_cb1c(uint8_t &h); // RR H | 2, 8 | Z 0 0 C
    void opcode_cb1d(uint8_t &l); // RR L | 2, 8 | Z 0 0 C
    void opcode_cb1e(void); // RR [HL] | 2, 16 | Z 0 0 C
    void opcode_cb1f(uint8_t &a); // RR A | 2, 8 | Z 0 0 C

    void opcode_cb20(uint8_t &b); // SLA B | 2, 8 | Z 0 0 C
    void opcode_cb21(uint8_t &c); // SLA C | 2, 8 | Z 0 0 C
    void opcode_cb22(uint8_t &d); // SLA D | 2, 8 | Z 0 0 C
    void opcode_cb23(uint8_t &e); // SLA E | 2, 8 | Z 0 0 C
    void opcode_cb24(uint8_t &h); // SLA H | 2, 8 | Z 0 0 C
    void opcode_cb25(uint8_t &l); // SLA L | 2, 8 | Z 0 0 C
    void opcode_cb26(void); // SLA [HL] | 2, 16 | Z 0 0 C
    void opcode_cb27(uint8_t &a); // SLA A | 2, 8 | Z 0 0 C
    void opcode_cb28(uint8_t &b); // SRA B | 2, 8 | Z 0 0 C
    void opcode_cb29(uint8_t &c); // SRA C | 2, 8 | Z 0 0 C
    void opcode_cb2a(uint8_t &d); // SRA D | 2, 8 | Z 0 0 C
    void opcode_cb2b(uint8_t &e); // SRA E | 2, 8 | Z 0 0 C
    void opcode_cb2c(uint8_t &h); // SRA H | 2, 8 | Z 0 0 C
    void opcode_cb2d(uint8_t &l); // SRA L | 2, 8 | Z 0 0 C
    void opcode_cb2e(void); // SRA [HL] | 2, 16 | Z 0 0 C
    void opcode_cb2f(uint8_t &a); // SRA A | 2, 16 | Z 0 0 C

    void opcode_cb30(uint8_t &b); // SWAP B | 2, 8 | Z 0 0 0
    void opcode_cb31(uint8_t &c); // SWAP C | 2, 8 | Z 0 0 0
    void opcode_cb32(uint8_t &d); // SWAP D | 2, 8 | Z 0 0 0
    void opcode_cb33(uint8_t &e); // SWAP E | 2, 8 | Z 0 0 0
    void opcode_cb34(uint8_t &h); // SWAP H | 2, 8 | Z 0 0 0
    void opcode_cb35(uint8_t &l); // SWAP L | 2, 8 | Z 0 0 0
    void opcode_cb36(void); // SWAP [HL] | 2, 16 | Z 0 0 0
    void opcode_cb37(uint8_t &a); // SWAP A | 2, 8 | Z 0 0 0
    void opcode_cb38(uint8_t &b); // SRL B | 2, 8 | Z 0 0 C
    void opcode_cb39(uint8_t &c); // SRL C | 2, 8 | Z 0 0 C
    void opcode_cb3a(uint8_t &d); // SRL D | 2, 8 | Z 0 0 C
    void opcode_cb3b(uint8_t &e); // SRL E | 2, 8 | Z 0 0 C
    void opcode_cb3c(uint8_t &h); // SRL H | 2, 8 | Z 0 0 C
    void opcode_cb3d(uint8_t &l); // SRL L | 2, 8 | Z 0 0 C
    void opcode_cb3e(void); // SRL [HL] | 2, 16 | Z 0 0 C
    void opcode_cb3f(uint8_t &a); // SRL A | 2, 8 | Z 0 0 C

    void opcode_cb40(uint8_t &b); // BIT 0, B | 2, 8 | Z 0 1 -
    void opcode_cb41(uint8_t &c); // BIT 0, C | 2, 8 | Z 0 1 -
    void opcode_cb42(uint8_t &d); // BIT 0, D | 2, 8 | Z 0 1 -
    void opcode_cb43(uint8_t &e); // BIT 0, E | 2, 8 | Z 0 1 -
    void opcode_cb44(uint8_t &h); // BIT 0, H | 2, 8 | Z 0 1 -
    void opcode_cb45(uint8_t &l); // BIT 0, L | 2, 8 | Z 0 1 -
    void opcode_cb46(void); // BIT 0, [HL] | 2, 12 | Z 0 1 -
    void opcode_cb47(uint8_t &a); // BIT 0, A | 2, 8 | Z 0 1 -
    void opcode_cb48(uint8_t &b); // BIT 1, B | 2, 8 | Z 0 1 -
    void opcode_cb49(uint8_t &c); // BIT 1, C | 2, 8 | Z 0 1 -
    void opcode_cb4a(uint8_t &d); // BIT 1, D | 2, 8 | Z 0 1 -
    void opcode_cb4b(uint8_t &e); // BIT 1, E | 2, 8 | Z 0 1 -
    void opcode_cb4c(uint8_t &h); // BIT 1, H | 2, 8 | Z 0 1 -
    void opcode_cb4d(uint8_t &l); // BIT 1, L | 2, 8 | Z 0 1 -
    void opcode_cb4e(void); // BIT 1, [HL] | 2, 12 | Z 0 1 -
    void opcode_cb4f(uint8_t &a); // BIT 1, A | 2, 8 | Z 0 1 -

    void opcode_cb50(uint8_t &b); // BIT 2, B | 2, 8 | Z 0 1 -
    void opcode_cb51(uint8_t &c); // BIT 2, C | 2, 8 | Z 0 1 -
    void opcode_cb52(uint8_t &d); // BIT 2, D | 2, 8 | Z 0 1 -
    void opcode_cb53(uint8_t &e); // BIT 2, E | 2, 8 | Z 0 1 -
    void opcode_cb54(uint8_t &h); // BIT 2, H | 2, 8 | Z 0 1 -
    void opcode_cb55(uint8_t &l); // BIT 2, L | 2, 8 | Z 0 1 -
    void opcode_cb56(void); // BIT 2, [HL] | 2, 12 | Z 0 1 -
    void opcode_cb57(uint8_t &a); // BIT 2, A | 2, 8 | Z 0 1 -
    void opcode_cb58(uint8_t &b); // BIT 3, B | 2, 8 | Z 0 1 -
    void opcode_cb59(uint8_t &c); // BIT 3, C | 2, 8 | Z 0 1 -
    void opcode_cb5a(uint8_t &d); // BIT 3, D | 2, 8 | Z 0 1 -
    void opcode_cb5b(uint8_t &e); // BIT 3, E | 2, 8 | Z 0 1 -
    void opcode_cb5c(uint8_t &h); // BIT 3, H | 2, 8 | Z 0 1 -
    void opcode_cb5d(uint8_t &l); // BIT 3, L | 2, 8 | Z 0 1 -
    void opcode_cb5e(void); // BIT 3, [HL] | 2, 12 | Z 0 1 -
    void opcode_cb5f(uint8_t &a); // BIT 3, A | 2, 8 | Z 0 1 -
    
    void opcode_cb60(uint8_t &b); // BIT 4, B | 2, 8 | Z 0 1 -
    void opcode_cb61(uint8_t &c); // BIT 4, C | 2, 8 | Z 0 1 -
    void opcode_cb62(uint8_t &d); // BIT 4, D | 2, 8 | Z 0 1 -
    void opcode_cb63(uint8_t &e); // BIT 4, E | 2, 8 | Z 0 1 -
    void opcode_cb64(uint8_t &h); // BIT 4, H | 2, 8 | Z 0 1 -
    void opcode_cb65(uint8_t &l); // BIT 4, L | 2, 8 | Z 0 1 -
    void opcode_cb66(void); // BIT 4, [HL] | 2, 12 | Z 0 1 -
    void opcode_cb67(uint8_t &a); // BIT 4, A | 2, 8 | Z 0 1 -
    void opcode_cb68(uint8_t &b); // BIT 5, B | 2, 8 | Z 0 1 -
    void opcode_cb69(uint8_t &c); // BIT 5, C | 2, 8 | Z 0 1 -
    void opcode_cb6a(uint8_t &d); // BIT 5, D | 2, 8 | Z 0 1 -
    void opcode_cb6b(uint8_t &e); // BIT 5, E | 2, 8 | Z 0 1 -
    void opcode_cb6c(uint8_t &h); // BIT 5, H | 2, 8 | Z 0 1 -
    void opcode_cb6d(uint8_t &l); // BIT 5, L | 2, 8 | Z 0 1 -
    void opcode_cb6e(void); // BIT 5, [HL] | 2, 12 | Z 0 1 -
    void opcode_cb6f(uint8_t &a); // BIT 5, A | 2, 8 | Z 0 1 -

    void opcode_cb70(uint8_t &b); // BIT 6, B | 2, 8 | Z 0 1 -
    void opcode_cb71(uint8_t &c); // BIT 6, C | 2, 8 | Z 0 1 -
    void opcode_cb72(uint8_t &d); // BIT 6, D | 2, 8 | Z 0 1 -
    void opcode_cb73(uint8_t &e); // BIT 6, E | 2, 8 | Z 0 1 -
    void opcode_cb74(uint8_t &h); // BIT 6, H | 2, 8 | Z 0 1 -
    void opcode_cb75(uint8_t &l); // BIT 6, L | 2, 8 | Z 0 1 -
    void opcode_cb76(void); // BIT 6, [HL] | 2, 12 | Z 0 1 -
    void opcode_cb77(uint8_t &a); // BIT 6, A | 2, 8 | Z 0 1 -
    void opcode_cb78(uint8_t &b); // BIT 7, B | 2, 8 | Z 0 1 -
    void opcode_cb79(uint8_t &c); // BIT 7, C | 2, 8 | Z 0 1 -
    void opcode_cb7a(uint8_t &d); // BIT 7, D | 2, 8 | Z 0 1 -
    void opcode_cb7b(uint8_t &e); // BIT 7, E | 2, 8 | Z 0 1 -
    void opcode_cb7c(uint8_t &h); // BIT 7, H | 2, 8 | Z 0 1 -
    void opcode_cb7d(uint8_t &l); // BIT 7, L | 2, 8 | Z 0 1 -
    void opcode_cb7e(void); // BIT 7, [HL] | 2, 12 | Z 0 1 -
    void opcode_cb7f(uint8_t &a); // BIT 7, A | 2, 8 | Z 0 1 -
    
    void opcode_cb80(uint8_t &b); // RES 0, B | 2, 8 | - - - -
    void opcode_cb81(uint8_t &c); // RES 0, C | 2, 8 | - - - -
    void opcode_cb82(uint8_t &d); // RES 0, D | 2, 8 | - - - -
    void opcode_cb83(uint8_t &e); // RES 0, E | 2, 8 | - - - -
    void opcode_cb84(uint8_t &h); // RES 0, H | 2, 8 | - - - -
    void opcode_cb85(uint8_t &l); // RES 0, L | 2, 8 | - - - -
    void opcode_cb86(void); // RES 0, [HL] | 2, 12 | - - - -
    void opcode_cb87(uint8_t &a); // RES 0, A | 2, 8 | - - - -
    void opcode_cb88(uint8_t &b); // RES 1, B | 2, 8 | - - - -
    void opcode_cb89(uint8_t &c); // RES 1, C | 2, 8 | - - - -
    void opcode_cb8a(uint8_t &d); // RES 1, D | 2, 8 | - - - -
    void opcode_cb8b(uint8_t &e); // RES 1, E | 2, 8 | - - - -
    void opcode_cb8c(uint8_t &h); // RES 1, H | 2, 8 | - - - -
    void opcode_cb8d(uint8_t &l); // RES 1, L | 2, 8 | - - - -
    void opcode_cb8e(void); // RES 1, [HL] | 2, 16 | - - - -
    void opcode_cb8f(uint8_t &a); // RES 1, A | 2, 8 | - - - -

    void opcode_cb90(uint8_t &b); // RES 2, B | 2, 8 | - - - -
    void opcode_cb91(uint8_t &c); // RES 2, C | 2, 8 | - - - -
    void opcode_cb92(uint8_t &d); // RES 2, D | 2, 8 | - - - -
    void opcode_cb93(uint8_t &e); // RES 2, E | 2, 8 | - - - -
    void opcode_cb94(uint8_t &h); // RES 2, H | 2, 8 | - - - -
    void opcode_cb95(uint8_t &l); // RES 2, L | 2, 8 | - - - -
    void opcode_cb96(void); // RES 2, [HL] | 2, 16 | - - - -
    void opcode_cb97(uint8_t &a); // RES 2, A | 2, 8 | - - - -
    void opcode_cb98(uint8_t &b); // RES 3, B | 2, 8 | - - - -
    void opcode_cb99(uint8_t &c); // RES 3, C | 2, 8 | - - - -
    void opcode_cb9a(uint8_t &d); // RES 3, D | 2, 8 | - - - -
    void opcode_cb9b(uint8_t &e); // RES 3, E | 2, 8 | - - - -
    void opcode_cb9c(uint8_t &h); // RES 3, H | 2, 8 | - - - -
    void opcode_cb9d(uint8_t &l); // RES 3, L | 2, 8 | - - - -
    void opcode_cb9e(void); // RES 3, [HL] | 2, 16 | - - - -
    void opcode_cb9f(uint8_t &a); // RES 3, A | 2, 8 | - - - -

    void opcode_cba0(uint8_t &b); // RES 4, B | 2, 8 | - - - -
    void opcode_cba1(uint8_t &c); // RES 4, C | 2, 8 | - - - -
    void opcode_cba2(uint8_t &d); // RES 4, D | 2, 8 | - - - -
    void opcode_cba3(uint8_t &e); // RES 4, E | 2, 8 | - - - -
    void opcode_cba4(uint8_t &h); // RES 4, H | 2, 8 | - - - -
    void opcode_cba5(uint8_t &l); // RES 4, L | 2, 8 | - - - -
    void opcode_cba6(void); // RES 4, [HL] | 2, 16 | - - - -
    void opcode_cba7(uint8_t &a); // RES 4, A | 2, 8 | - - - -
    void opcode_cba8(uint8_t &b); // RES 5, B | 2, 8 | - - - -
    void opcode_cba9(uint8_t &c); // RES 5, C | 2, 8 | - - - -
    void opcode_cbaa(uint8_t &d); // RES 5, D | 2, 8 | - - - -
    void opcode_cbab(uint8_t &e); // RES 5, E | 2, 8 | - - - -
    void opcode_cbac(uint8_t &h); // RES 5, H | 2, 8 | - - - -
    void opcode_cbad(uint8_t &l); // RES 5, L | 2, 8 | - - - -
    void opcode_cbae(void); // RES 5, [HL] | 2, 16 | - - - -
    void opcode_cbaf(uint8_t &a); // RES 5, A | 2, 8 | - - - -

    void opcode_cbb0(uint8_t &b); // RES 6, B | 2, 8 | - - - -
    void opcode_cbb1(uint8_t &c); // RES 6, C | 2, 8 | - - - -
    void opcode_cbb2(uint8_t &d); // RES 6, D | 2, 8 | - - - -
    void opcode_cbb3(uint8_t &e); // RES 6, E | 2, 8 | - - - -
    void opcode_cbb4(uint8_t &h); // RES 6, H | 2, 8 | - - - -
    void opcode_cbb5(uint8_t &l); // RES 6, L | 2, 8 | - - - -
    void opcode_cbb6(void); // RES 6, [HL] | 2, 16 | - - - -
    void opcode_cbb7(uint8_t &a); // RES 6, A | 2, 8 | - - - -
    void opcode_cbb8(uint8_t &b); // RES 7, B | 2, 8 | - - - -
    void opcode_cbb9(uint8_t &c); // RES 7, C | 2, 8 | - - - -
    void opcode_cbba(uint8_t &d); // RES 7, D | 2, 8 | - - - -
    void opcode_cbbb(uint8_t &e); // RES 7, E | 2, 8 | - - - -
    void opcode_cbbc(uint8_t &h); // RES 7, H | 2, 8 | - - - -
    void opcode_cbbd(uint8_t &l); // RES 7, L | 2, 8 | - - - -
    void opcode_cbbe(void); // RES 7, [HL] | 2, 16 | - - - -
    void opcode_cbbf(uint8_t &a); // RES 7, A | 2, 8 | - - - -

    void opcode_cbc0(uint8_t &b); // SET 0, B | 2, 8 | - - - -
    void opcode_cbc1(uint8_t &c); // SET 0, C | 2, 8 | - - - -
    void opcode_cbc2(uint8_t &d); // SET 0, D | 2, 8 | - - - -
    void opcode_cbc3(uint8_t &e); // SET 0, E | 2, 8 | - - - -
    void opcode_cbc4(uint8_t &h); // SET 0, H | 2, 8 | - - - -
    void opcode_cbc5(uint8_t &l); // SET 0, L | 2, 8 | - - - -
    void opcode_cbc6(void); // SET 0, [HL] | 2, 16 | - - - -
    void opcode_cbc7(uint8_t &a); // SET 0, A | 2, 8 | - - - -
    void opcode_cbc8(uint8_t &b); // SET 1, B | 2, 8 | - - - -
    void opcode_cbc9(uint8_t &c); // SET 1, C | 2, 8 | - - - -
    void opcode_cbca(uint8_t &d); // SET 1, D | 2, 8 | - - - -
    void opcode_cbcb(uint8_t &e); // SET 1, E | 2, 8 | - - - -
    void opcode_cbcc(uint8_t &h); // SET 1, H | 2, 8 | - - - -
    void opcode_cbcd(uint8_t &l); // SET 1, L | 2, 8 | - - - -
    void opcode_cbce(void); // SET 1, [HL] | 2, 16 | - - - -
    void opcode_cbcf(uint8_t &a); // SET 1, A | 2, 8 | - - - -

    void opcode_cbd0(uint8_t &b); // SET 2, B | 2, 8 | - - - -
    void opcode_cbd1(uint8_t &c); // SET 2, C | 2, 8 | - - - -
    void opcode_cbd2(uint8_t &d); // SET 2, D | 2, 8 | - - - -
    void opcode_cbd3(uint8_t &e); // SET 2, E | 2, 8 | - - - -
    void opcode_cbd4(uint8_t &h); // SET 2, H | 2, 8 | - - - -
    void opcode_cbd5(uint8_t &l); // SET 2, L | 2, 8 | - - - -
    void opcode_cbd6(void); // SET 2, [HL] | 2, 16 | - - - -
    void opcode_cbd7(uint8_t &a); // SET 2, A | 2, 8 | - - - -
    void opcode_cbd8(uint8_t &b); // SET 3, B | 2, 8 | - - - -
    void opcode_cbd9(uint8_t &c); // SET 3, C | 2, 8 | - - - -
    void opcode_cbda(uint8_t &d); // SET 3, D | 2, 8 | - - - -
    void opcode_cbdb(uint8_t &e); // SET 3, E | 2, 8 | - - - -
    void opcode_cbdc(uint8_t &h); // SET 3, H | 2, 8 | - - - -
    void opcode_cbdd(uint8_t &l); // SET 3, L | 2, 8 | - - - -
    void opcode_cbde(void); // SET 3, [HL] | 2, 16 | - - - -
    void opcode_cbdf(uint8_t &a); // SET 3, A | 2, 8 | - - - -

    void opcode_cbe0(uint8_t &b); // SET 4, B | 2, 8 | - - - -
    void opcode_cbe1(uint8_t &c); // SET 4, C | 2, 8 | - - - -
    void opcode_cbe2(uint8_t &d); // SET 4, D | 2, 8 | - - - -
    void opcode_cbe3(uint8_t &e); // SET 4, E | 2, 8 | - - - -
    void opcode_cbe4(uint8_t &h); // SET 4, H | 2, 8 | - - - -
    void opcode_cbe5(uint8_t &l); // SET 4, L | 2, 8 | - - - -
    void opcode_cbe6(void); // SET 4, [HL] | 2, 16 | - - - -
    void opcode_cbe7(uint8_t &a); // SET 4, A | 2, 8 | - - - -
    void opcode_cbe8(uint8_t &b); // SET 5, B | 2, 8 | - - - -
    void opcode_cbe9(uint8_t &c); // SET 5, C | 2, 8 | - - - -
    void opcode_cbea(uint8_t &d); // SET 5, D | 2, 8 | - - - -
    void opcode_cbeb(uint8_t &e); // SET 5, E | 2, 8 | - - - -
    void opcode_cbec(uint8_t &h); // SET 5, H | 2, 8 | - - - -
    void opcode_cbed(uint8_t &l); // SET 5, L | 2, 8 | - - - -
    void opcode_cbee(void); // SET 5, [HL] | 2, 16 | - - - -
    void opcode_cbef(uint8_t &a); // SET 5, A | 2, 8 | - - - -
    
    void opcode_cbf0(uint8_t &b); // SET 6, B | 2, 8 | - - - -
    void opcode_cbf1(uint8_t &c); // SET 6, C | 2, 8 | - - - -
    void opcode_cbf2(uint8_t &d); // SET 6, D | 2, 8 | - - - -
    void opcode_cbf3(uint8_t &e); // SET 6, E | 2, 8 | - - - -
    void opcode_cbf4(uint8_t &h); // SET 6, H | 2, 8 | - - - -
    void opcode_cbf5(uint8_t &l); // SET 6, L | 2, 8 | - - - -
    void opcode_cbf6(void); // SET 6, [HL] | 2, 16 | - - - -
    void opcode_cbf7(uint8_t &a); // SET 6, A | 2, 8 | - - - -
    void opcode_cbf8(uint8_t &b); // SET 7, B | 2, 8 | - - - -
    void opcode_cbf9(uint8_t &c); // SET 7, C | 2, 8 | - - - -
    void opcode_cbfa(uint8_t &d); // SET 7, D | 2, 8 | - - - -
    void opcode_cbfb(uint8_t &e); // SET 7, E | 2, 8 | - - - -
    void opcode_cbfc(uint8_t &h); // SET 7, H | 2, 8 | - - - -
    void opcode_cbfd(uint8_t &l); // SET 7, L | 2, 8 | - - - -
    void opcode_cbfe(void); // SET 7, [HL] | 2, 16 | - - - -
    void opcode_cbff(uint8_t &a); // SET 7, A | 2, 8 | - - - -
};