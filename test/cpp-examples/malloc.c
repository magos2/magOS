
#include <stdlib.h>
#include <stdio.h>

#define PAGE_SIZE 4096

#define KHEAP_DMA_START  0x100000      //DMA : 1MB-16MB
#define KHEAP_DMA_END    0x1000000     
#define KHEAP_PAGE_START 0x1000000     //KERNEL PAGES HEAP : 16MB-256MB
#define KHEAP_PAGE_END   0x10000000    
#define KHEAP_START      0x10000000    //KERNEL HEAP : 256MB-1GB
#define KHEAP_END        0x40000000    
#define KMALLOC_MIN_SIZE  32//bytes
#define KMALLOC_MAX_SIZE  (PAGE_SIZE - sizeof(struct chunk_head)) 

#define next_chunk(chunk)  ((struct chunk_head*)((unsigned long)chunk + sizeof(struct chunk_head) + chunk->size))
#define real_size(chunk)   (chunk->size + sizeof(struct chunk_head))
#define is_free(chunk)    (chunk->inuse == 0)
#define is_used(chunk)    (chunk->inuse > 0)

#define DEBUG 1

struct chunk_head {
  size_t size;
  int inuse; /*0 free, >0 used*/
};

unsigned long kheap_start;
unsigned long kheap_end;

char * mem; /*memory, to simulate real memory*/
unsigned long start_mem;
unsigned long end_mem;

void mem_init()
{
  mem = (char*) malloc(1024*1024*16); /*16Mo*/
  kheap_start = (unsigned long)mem;
  kheap_end = kheap_start;
}

int ksbrk ()
{
  struct chunk_head * new_chunk;
  
  new_chunk = (struct chunk_head  *)kheap_end;
  kheap_end += PAGE_SIZE;
  new_chunk->inuse = 0;
  new_chunk->size = PAGE_SIZE - sizeof(struct chunk_head);
  return 0;
}

void kmalloc_init ()
{
  ksbrk();
}
	
/*kmalloc algo
Constantes
- KHEAP-DMA-START  1MB
...
- Structures
  chunk :
     - size : int
     - free : int
- ALGO
- variable : chunk pointe sur debut du heap
             realsz = size + taille(structure chunk)
- Allouer sz bytes dans le heap kernel
  - parcourir le heap depuis le debut et trouver
  un chunk free dont la chunk.size >= realsz
    --tester chaque chunk si corrompu
      si taille < Minsize 
  - si non trouve, il faut augmenter le kheap via ksbrk
    -- OOM si on ne peut pas augmenter le heap
    -- prendre le premier chunk
  - ici le chunk est trouvé
  -- spliter le chunk si sa taille est grande.
     -- si chunk.size > realsz + MALLOC-MINSIZE
        new-chunk = loc(chunk) + realsz
        new-chunk.free=yes
        new-chunk.size = chunk.sz - realsz
  -- chunk.free = used
  -- returner loc(chunck) + size(struct chunk) 
*/
void * kmalloc (size_t size) 
{
  size_t realsz, sz;
  struct chunk_head *chunk, *new_chunk;
  int err;
  
  if (size > PAGE_SIZE - sizeof(struct chunk_head)) {
     printf ("error, we cannot allocate more than %d bytes\n", KMALLOC_MAX_SIZE);
     return NULL;
  }
  sz = (size > KMALLOC_MIN_SIZE)?size:KMALLOC_MIN_SIZE;
  realsz = sz + sizeof(struct chunk_head);
  chunk = (struct chunk_head*) kheap_start;
  while (((unsigned long)chunk < kheap_end) && (is_used(chunk) || chunk->size < sz)) {
    if (chunk->size <= 0) {
      printf("error , corrupted chunk  at %p, size=%d, inuse=%d\n", chunk, chunk->size, chunk->inuse);
      return NULL;
    }
    chunk = next_chunk(chunk);
  }
  if ((unsigned long)chunk >= kheap_end) { //increase the heap
      err = ksbrk();
      if (err) {
        printf("OOM, cannot extend heap beyond %ld\n", kheap_end);
        return NULL;
      }
  }
  if(chunk->size > sz + sizeof(struct chunk_head) + KMALLOC_MIN_SIZE) {
    new_chunk = (struct chunk_head*)((unsigned long)chunk + realsz);
    new_chunk->inuse = 0;
    new_chunk->size = chunk->size - realsz;
  }
  chunk->size = sz;
  chunk->inuse = 1;
#if DEBUG
  printf("allocated chunk at %p, size=%d, inuse=%d\n", chunk, chunk->size, chunk->inuse);
#endif
  return (char*)chunk + sizeof(struct chunk_head);
}

/* ALGO
 * liberer la memoire a <addr>
   F1: recuperer le chunk
       si free , ne rien faire return.
   F2: p = chunk suivant
       si p est free
         chunk.size += p.size
         goto F2
   F3: chunk.free = yes
  */
void kfree (void *addr)
{
  struct chunk_head *chunk, *chp;
  
  chunk = (struct chunk_head *)((char*)addr - sizeof(struct chunk_head));
  if (!chunk->inuse)
    return;
  chp = next_chunk(chunk);
  while ((unsigned long)chp < kheap_end && !chp->inuse){
    if (chp->size <= 0) {
      printf("error , corrupted chunk  at %p, size=%d, inuse=%d\n", chp, chp->size, chp->inuse);
      return;
    }
    chunk->size += real_size(chp);
    chp = next_chunk(chp);
  }
  chunk->inuse = 0;
}

void show_mem ()
{
  struct chunk_head *chunk;
  size_t free_mem, used_mem, total_mem;
  
  free_mem=used_mem=total_mem=0;
  printf("chunks: ");
  chunk = (struct chunk_head*) kheap_start;
  while ((unsigned long)chunk < kheap_end) {
    printf("[%x,%dB,%s]", (int)chunk, chunk->size, (is_used(chunk))?"used":"free");
    if (is_used(chunk))
      used_mem += chunk->size;
    else
      free_mem += chunk->size;
    total_mem += chunk->size;
    chunk = next_chunk(chunk);
  }
  printf("\n");
  printf("memory total:%d free:%d used:%d\n\n", total_mem, free_mem, used_mem);
}

int main(void)
{
  char *v1, *v2, *v3;
  
  mem_init();
  
  kmalloc_init ();
  
  show_mem ();
  
  v1 = (char*) kmalloc (24);
  v2 = (char*) kmalloc (64);
  v3 = (char*) kmalloc (4088);
  
  show_mem ();
  
  kfree (v3);
  show_mem ();
  kfree (v2);
  show_mem ();
  kfree (v1);
  show_mem ();
  return 0;
}







  
  
  
  
  
  
        
        