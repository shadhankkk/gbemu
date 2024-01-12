#include <iostream>
#include <vector>

class MemoryBus {
  public:
    std::pair<uint8_t, uint16_t> fetchInstruction(uint16_t pc);
    std::pair<uint8_t, uint16_t> fetchValue8(uint16_t pc);
    std::pair<uint16_t, uint16_t> fetchValue16(uint16_t pc);
    uint8_t readat(uint16_t address);
    uint16_t readat16(uint16_t address);
    void writeto(uint16_t address, uint8_t value);
    void writeto16(uint16_t address, uint16_t value);
    void loadRom(std::vector<uint8_t> &rom);
  private:
    std::vector<uint8_t> memory = std::vector<uint8_t>(0xFFFF, 0);
};