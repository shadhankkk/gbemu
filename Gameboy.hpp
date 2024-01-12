#include "cpu.hpp"
#include "Gpu.hpp"

typedef uint8_t instruction;

class Gameboy {
  public:
    Gameboy(MemoryBus memoryc, const std::vector<instruction> &rom): memory(memoryc), cpu(Cpu(&memory)), ROM(rom) {}

    void run(void);

  private:
    Cpu cpu;
    MemoryBus memory;
    Gpu gpu;
    const std::vector<instruction> ROM;
};