#ifndef SUPPORT_H
#define SUPPORT_H

int     CpuCtor             (Cpu_t* myCpu, const char* data_read);
int     CpuDtor             (Cpu_t* myCpu);
int     PrintMemoryListing  (Cpu_t* myCpu);

#endif 