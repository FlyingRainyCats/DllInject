#include <algorithm>
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
  if (argc != 4) {
    fprintf_s(stderr, "Usage: ShellCodeToMasm \"input.bin\" \"output.asm\" \"fn_name\"\n\n");
    return 0;
  }

  auto fn_name = argv[3];
  FILE* fInput{};
  FILE* fOutput{};
  if (auto err = fopen_s(&fInput, argv[1], "rb"); err != 0) {
    fprintf_s(stderr, "ERROR: I/O error reading input  (err = %d)\n", err);
    return 1;
  }
  if (auto err = fopen_s(&fOutput, argv[2], "wb"); err != 0) {
    fprintf_s(stderr, "ERROR: I/O error reading output (err = %d)\n", err);
    return 2;
  }

  const char* pre_body =
      "; Generated ASM code from bytes\n"
      "PUBLIC %s\n"
      ".386\n"
      ".model flat, c\n"
      // ".stack 4096\n"
      "\n"
      ".code\n"
      ".safeseh SEH_handler\n"
      "SEH_handler proc\n "
      "ret\n"
      "SEH_handler   endp\n"
      "\n"
      "%s PROC\n";
  const char* post_body =
      "\n%s ENDP\n"
      "END\n"
      "\n";
  fprintf(fOutput, pre_body, fn_name, fn_name);

  char buffer[4096]{};
  char output_buffer[4 + 16 * 6 + 10]{};
  strcpy_s(output_buffer, "db  ");

  while (true) {
    auto bytes_read = fread_s(buffer, sizeof(buffer), sizeof(buffer[0]), _countof(buffer), fInput);
    if (bytes_read == 0) {
      break;
    }

    for (auto i = 0; i < bytes_read; i += 16) {
      auto last_row_idx = std::min(bytes_read - i, size_t{16}) - 1;
      for (auto j = 0; j <= last_row_idx; j++) {
        sprintf_s(&output_buffer[4 + j * 6], 7, " 0%02xh%c", (uint8_t)buffer[i + j], last_row_idx == j ? '\n' : ',');
      }
      fwrite(output_buffer, sizeof(char), 4 + last_row_idx * 6 + 6, fOutput);
    }
  }
  fprintf(fOutput, post_body, fn_name);
  fclose(fInput);
  fclose(fOutput);
  return 0;
}
