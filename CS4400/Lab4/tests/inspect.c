#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <elf.h>
#include <string.h>

// Lab 4 Tim Dorny u0829896

/* Given the in-memory ELF header pointer as `ehdr` and a section
   header pointer as `shdr`, returns a pointer to the memory that
   contains the in-memory content of the section */
#define AT_SEC(ehdr, shdr) ((void *)(ehdr) + (shdr)->sh_offset)

static void check_for_shared_object(Elf64_Ehdr *ehdr);
static void fail(char *reason, int err_code);
Elf64_Shdr *section_by_name(Elf64_Ehdr *ehdr, char *name);
Elf64_Shdr *section_by_index(Elf64_Ehdr *ehdr, int index);

int main(int argc, char **argv) {
  int fd;
  size_t len;
  void *p;
  Elf64_Ehdr *ehdr;

  if (argc != 2)
    fail("expected one file on the command line", 0);

  /* Open the shared-library file */
  fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    fail("could not open file", errno);

  /* Find out how big the file is: */
  len = lseek(fd, 0, SEEK_END);

  /* Map the whole file into memory: */
  p = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
  if (p == (void*)-1)
    fail("mmap failed", errno);

  /* Since the ELF file starts with an ELF header, the in-memory image
     can be cast to a `Elf64_Ehdr *` to inspect it: */
  ehdr = (Elf64_Ehdr *)p;

  /* Check that we have the right kind of file: */
  check_for_shared_object(ehdr);

  /* Add a call to your work here */
  // Get pointer to ".dynsym" section header
  Elf64_Shdr *dynsyms_header = section_by_name(ehdr, ".dynsym");
  // Get pointer to location of symbol table in memory.
  Elf64_Sym *dynsyms = AT_SEC(ehdr, dynsyms_header);
  // Get pointer to location of ".dynstr" section in memory
  char *dynstrs = AT_SEC(ehdr, section_by_name(ehdr, ".dynstr"));
  int i;
  // Loop bound
  int count = dynsyms_header->sh_size / sizeof(Elf64_Sym);
  // Look through the symbol table and find any functions contained within.
  for (i = 0; i < count; i++){
    // Check for functions
    if (ELF64_ST_TYPE(dynsyms[i].st_info) == STT_FUNC){
      // If the function is indexed in the ".text" or ".plt" sections, print the name of that function.
      if (dynsyms[i].st_shndx == 11 || dynsyms[i].st_shndx == 10){
        printf("%s\n", dynstrs + dynsyms[i].st_name);
      }
      // I hit a roadblock when trying to read the machine code using the process found in the lecture slides (commented out below),
      // Not sure entirely what the issue was but I was getting strange characters when attempting to read the instructions...


      // Then we can look at the machine code
      //Elf64_Shdr *ihdr = section_by_index(ehdr, dynsyms[i].st_shndx);
      //printf("sectioned by index: %d\n", dynsyms[i].st_shndx);
      //char *mcode = AT_SEC(ehdr, ihdr) + (dynsyms[i].st_value - ihdr->sh_addr);
      //printf("MACHINECODE:\n");
      //int j;
      //for (j = 0; j < 10; j++){
      //printf("%d\n", *mcode);
      //*mcode++;
      //}
    }
  }




  return 0;
}





static void check_for_shared_object(Elf64_Ehdr *ehdr) {
  if ((ehdr->e_ident[EI_MAG0] != ELFMAG0)
      || (ehdr->e_ident[EI_MAG1] != ELFMAG1)
      || (ehdr->e_ident[EI_MAG2] != ELFMAG2)
      || (ehdr->e_ident[EI_MAG3] != ELFMAG3))
    fail("not an ELF file", 0);

  if (ehdr->e_ident[EI_CLASS] != ELFCLASS64)
    fail("not a 64-bit ELF file", 0);

  if (ehdr->e_type != ET_DYN)
    fail("not a shared-object file", 0);
}

static void fail(char *reason, int err_code) {
  fprintf(stderr, "%s (%d)\n", reason, err_code);
  exit(1);
}





// My code below:

Elf64_Shdr *section_by_index(Elf64_Ehdr *ehdr, int index){
  // Pointer to section headers
  Elf64_Shdr *shdr = (void*)ehdr+ehdr->e_shoff;
  // return pointer to the indexed section header.
  return &shdr[index];
}


Elf64_Shdr *section_by_name(Elf64_Ehdr *ehdr, char *name){
  // Pointer to section headers
  Elf64_Shdr *shdr = (void*)ehdr+ehdr->e_shoff;
  // Pointer to section header strings
  char* strs = (void*)ehdr+shdr[ehdr->e_shstrndx].sh_offset;
  int i;
  Elf64_Word shName;
  // Used when checking if the provided string is found in the section header names.
  int checkFail = 0;

  // Use section header names as offsets to parse each section header's string.
  for (i = 0; i < ehdr->e_shnum; i++){
    // If section header name equals the one given, store its sh_name field into shName
    if (strcmp((char*)strs+shdr[i].sh_name, name) == 0){
      shName = *strs+shdr[i].sh_name;
      // Name was found.
      checkFail = 1;
    }
  }
  // If a matching string wasn't found, return NULL
  if (checkFail == 0){
    return NULL;
  }

  int j;
  // Look through section headers to find the one with the correct name.
  for (j = 0; j < ehdr->e_shnum; j++){
    if (shdr[j].sh_name == shName){
      // Return a pointer to the named section header.
      return &shdr[j];
    }
  }
  // This point should never be reached but just in case returns NULL
  return NULL;
}
