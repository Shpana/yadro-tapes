#include "tapes/file_based_tape.hpp"

int main() {
  FileBasedTapeSpec spec = {};
  FileBasedTape tape = FileBasedTape::create(spec, "C:/Dev/");
  tape.move(Tape::Direction::left);
  return 0;
}
