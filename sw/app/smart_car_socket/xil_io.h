#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <unistd.h>
#include <fcntl.h>

#define PAGE_SIZE  ((size_t)getpagesize())
#define PAGE_MASK ((uint64_t) (long)~(PAGE_SIZE - 1))

void Xil_Out32(uint64_t phyaddr, uint32_t val)
{
	int fd;
	volatile uint8_t *map_base;
	uint64_t base = phyaddr & PAGE_MASK;
	uint64_t pgoffset = phyaddr & (~PAGE_MASK);

	if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
	{
		perror("open /dev/mem:");
	}

	map_base = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
			fd, base);
	if(map_base == MAP_FAILED)
	{
		perror("mmap:");
	}
	*(volatile uint32_t *)(map_base + pgoffset) = val; 
	close(fd);
	munmap((void *)map_base, PAGE_SIZE);
}

int Xil_In32(uint64_t phyaddr)
{
	int fd;
	uint32_t val;
	volatile uint8_t *map_base;
	uint64_t base = phyaddr & PAGE_MASK;
	uint64_t pgoffset = phyaddr & (~PAGE_MASK);
	//open /dev/mem
	if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
	{
		perror("open /dev/mem:");
	}
	//mmap
	map_base = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
			fd, base);
	if(map_base == MAP_FAILED)
	{
		perror("mmap:");
	}
	val = *(volatile uint32_t *)(map_base + pgoffset);
	close(fd);
	munmap((void *)map_base, PAGE_SIZE);

	return val;
}
