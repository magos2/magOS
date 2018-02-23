struct gdt_desc {
	int a;
	int b;
};

struct gdt_desc gdt_cs;
struct gdt_desc gdt[256];

void for_asm () {
  int i;
  for (i=0; i < 256; i++) {
    gdt[i].a = gdt_cs.a;
    gdt[i].b = gdt_cs.b;
  }
}

int main(void) {
  for_asm();
  
  return 0;
}