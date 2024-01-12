#include <iostream>
#include <vector>
#include <fstream>
#include "Gameboy.hpp"

void Gameboy::run(void) {
  int x = 0;
  while(true) {
    x++;
    uint16_t currPc = this->cpu.execInstruction();
    if(this->memory.readat(0xff02) >= 0x80) {
      char c = this->memory.readat(0xff01);
      std::cout << static_cast<int>(c) << std::endl;
      this->memory.writeto(0xff01, 0x0);
    }

    if(currPc >= this->ROM.size())
      return;
    
    if(x>520)
      return;
  };
}

int main() {
  std::ifstream romfile("./03-op sp,hl.gb", std::ios::binary);
  
  if(!romfile.is_open()) {
    std::cerr << "Error opening file." << std::endl;
    return 1;
  }

  romfile.seekg(0, std::ios::end);
  std::streampos filesize = romfile.tellg();
  romfile.seekg(0, std::ios::beg);
  std::vector<char> romchar(static_cast<size_t>(filesize));
  romfile.read(romchar.data(), filesize);
  romfile.close();

  std::vector<uint8_t> rom(static_cast<size_t>(filesize));

  for(int i=0; i<rom.size(); i++) {
    rom[i] = static_cast<uint8_t>(romchar[i]);
  }

  // for(int i=0x100; i<0x105; i++) {
  //   std::cout << std::hex << static_cast<uint32_t>(rom[i]) << std::endl;
  // }
  
  MemoryBus memory = MemoryBus();
  memory.loadRom(rom);
  Gameboy gameboy = Gameboy(memory, rom);
  gameboy.run();
}