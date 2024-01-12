#include "Registers.hpp"
// methods for reading values from virtual 16-bit registers
uint16_t Registers::get_af() {
  uint16_t aExt = this->a;

  return ((aExt << 8) | (this->f).value);
}

uint16_t Registers::get_bc() {
  uint16_t bExt = this->b;

  return ((bExt << 8) | (this->c));
}

uint16_t Registers::get_de() {
  uint16_t dExt = this->d;

  return ((dExt << 8) | (this->e));
}

uint16_t Registers::get_hl() {
  uint16_t hExt = this->h;

  return ((hExt << 8) | (this->l));
}

uint16_t Registers::get_sp() {
  return (this->sp);
}

// methods for setting the values of virtual 16-bit registers: af, bc, de, hl
void Registers::set_af(uint16_t value) {
  uint8_t aTemp = static_cast<uint8_t>((value & 0xFF00) >> 8);
  uint8_t fTemp = static_cast<uint8_t>(value & 0x00FF);
  this->a = aTemp;
  this->f.value = fTemp;
}

void Registers::set_bc(uint16_t value) {
  uint8_t bTemp = static_cast<uint8_t>((value & 0xFF00) >> 8);
  uint8_t cTemp = static_cast<uint8_t>(value & 0x00FF);
  this->b = bTemp;
  this->c = cTemp;
  return;
}

void Registers::set_de(uint16_t value) {
  uint8_t dTemp = static_cast<uint8_t>((value & 0xFF00) >> 8);
  uint8_t eTemp = static_cast<uint8_t>(value & 0x00FF);
  this->d = dTemp;
  this->e = eTemp;
  return;
}

void Registers::set_hl(uint16_t value) {
  uint8_t hTemp = static_cast<uint8_t>((value & 0xFF00) >> 8);
  uint8_t lTemp = static_cast<uint8_t>(value & 0x00FF);
  this->h = hTemp;
  this->l = lTemp;
  return;
}

void Registers::set_sp(uint16_t value) {
  this->sp = value;
}