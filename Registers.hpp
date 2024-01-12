#include "iostream"

// class for all general purpose registers in CPU
class Registers {
  // this class is for the "f" register as it is special in that has flag bits
  public:
    class FlagRegister {
      public:
        // zero, subtract, hc, and carry bits are 7th, 6th, 5th and 4th bits respectively in the flag register
        
        uint8_t value = 0;
        uint8_t zMask = 0b1 << 7;
        uint8_t nMask = 0b1 << 6;
        uint8_t hMask = 0b1 << 5;
        uint8_t cMask = 0b1 << 4;

        FlagRegister(uint8_t val): value(val){};

        // methods for getting each flag bit value

        bool getZ() {
          return this->value & zMask;
        }

        bool getN() {
          return this->value & nMask;
        }

        bool getH() {
          return this->value & hMask;
        }

        bool getC() {
          return this->value & cMask;
        }

        // methods for setting flags to 1

        void setZ() {
          this->value |= zMask;
        }

        void setN() {
          this->value |= nMask;
        }

        void setH() {
          this->value |= hMask;
        }

        void setC() {
          this->value |= cMask;
        }

        // methods for clearing flags to 0

        void resetZ() {
          this->value &= ~zMask;
        }

        void resetN() {
          this->value &= ~nMask;
        }

        void resetH() {
          this->value &= ~hMask;
        }

        void resetC() {
          this->value &= ~cMask;
        }
    };

  public:
    uint8_t a = 0x01;
    uint8_t b = 0x00;
    uint8_t c = 0x13;
    uint8_t d = 0x00;
    uint8_t e = 0xd8;
    FlagRegister f = FlagRegister(0xb0);
    uint8_t h = 0x01;
    uint8_t l = 0x4d;
    uint16_t sp = 0xfffe;

    // methods for reading values from virtual 16-bit registers
    uint16_t get_af();
    uint16_t get_bc();
    uint16_t get_de();
    uint16_t get_hl();
    uint16_t get_sp();

    // methods for setting the values of virtual 16-bit registers: af, bc, de, hl
    void set_af(uint16_t value);
    void set_bc(uint16_t value);
    void set_de(uint16_t value);
    void set_hl(uint16_t value);
    void set_sp(uint16_t value);
};