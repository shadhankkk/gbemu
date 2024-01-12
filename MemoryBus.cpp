#include "MemoryBus.hpp"

// fetches instruction at pc
std::pair<uint8_t, uint16_t> MemoryBus::fetchInstruction(uint16_t pc) {
  return std::pair<uint8_t, uint16_t>(this->memory[static_cast<int>(pc)], pc+1);
}

std::pair<uint8_t, uint16_t> MemoryBus::fetchValue8(uint16_t pc) {
  return fetchInstruction(pc);
}

std::pair<uint16_t, uint16_t> MemoryBus::fetchValue16(uint16_t pc) {
  uint16_t temp = static_cast<uint16_t>(readat(pc));
  uint16_t temp2 = static_cast<uint16_t>(readat(pc+1));
  temp2 <<= 8;

  return std::pair<uint16_t, uint16_t>((temp & temp2), pc+2);
}

// reads and returns whatever value is stored at address
uint8_t MemoryBus::readat(uint16_t address) {
  return this->memory[address];
}

uint16_t MemoryBus::readat16(uint16_t address) {
  return fetchValue16(address).first;
}

void MemoryBus::writeto(uint16_t address, uint8_t value) {
  this->memory[address] = value;
  return;
}

void MemoryBus::writeto16(uint16_t address, uint16_t value) {
  uint8_t lh = static_cast<uint8_t>(value);
  uint8_t uh = static_cast<uint8_t>(value >> 8);
  writeto(address, lh);
  writeto(address+1, uh);
}

void MemoryBus::loadRom(std::vector<uint8_t> &rom) {
  for(int i=0; i<rom.size(); i++) {
    this->memory[i] = rom[i];
  }
}