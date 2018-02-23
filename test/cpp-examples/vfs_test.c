/* http://www.win.tue.nl/~aeb/linux/vfs/trail.html
 *
 */
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int fd;
  char buf[512];
        
  fd = open("/tmp/tes.txt", O_RDONLY);
  
  if (fd < 0) {
    printf ("cannot open file\n");
    return -1;
  }
  
  read(fd, buf, sizeof(buf));
  return 0;
}