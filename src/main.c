#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "printer.h"
#include "standart.h"
#include "udev.h"
#include "extended.h"
#include "global.h"

/***
SAMPLE OUTPUT

Name:        Intel Core i7-4790K
Frequency:   4.0 GHz
NºCores:     4 cores(8 threads)
AXV:         AVX,AVX2
SSE:         SSE,SSE2,SSE4.1,SSE4.2
FMA:         FMA3
AES:         Yes
SHA:         No
L1 Size:     32KB(Data)32KB(Instructions)
L2 Size:     512KB
L3 Size:     8MB
Peak FLOPS:  512 GFLOP/s(in simple precision)

***/

static const char* VERSION = "0.34";

void print_help(int argc, char *argv[]) {
  printf("Usage: %s [--version] [--help] [--style STYLE]\n\
Options: \n\
  --style    Set logo style color\n\
    default:   Default style color\n\
    dark:      Dark style color\n\
  --help     Print this help and exit\n\
  --version  Print cpufetch version and exit\n",
  argv[0]);
}

void print_version() {
  printf("cpufetch v%s\n",VERSION);
}

int main(int argc, char* argv[]) {
  if(!parseArgs(argc,argv))
    return EXIT_FAILURE;

  if(showHelp()) {
    print_help(argc, argv);
    return EXIT_SUCCESS;
  }

  if(showVersion()) {
    print_version();
    return EXIT_SUCCESS;
  }

  struct cpuInfo* cpu = get_cpu_info();
  if(cpu == NULL)
    return EXIT_FAILURE;

  struct cache* cach = get_cache_info();
  struct frequency* freq = get_frequency_info();
  struct ascii* art = set_ascii(get_cpu_vendor(cpu),getStyle());
  if(art == NULL)
    return EXIT_FAILURE;

  char* cpuName = get_str_cpu_name();
  char* maxFrequency = get_str_freq(freq);
  char* nCores = get_str_ncores(cpu);
  char* avx = get_str_avx(cpu);
  char* sse = get_str_sse(cpu);
  char* fma = get_str_fma(cpu);
  char* aes = get_str_aes(cpu);
  char* sha = get_str_sha(cpu);
  char* l1 = get_str_l1(cach);
  char* l2 = get_str_l2(cach);
  char* l3 = get_str_l3(cach);
  char* pp = get_str_peak_performance(cpu,get_freq(freq));

  setAttribute(art,ATTRIBUTE_NAME,cpuName);
  setAttribute(art,ATTRIBUTE_FREQUENCY,maxFrequency);
  setAttribute(art,ATTRIBUTE_NCORES,nCores);
  setAttribute(art,ATTRIBUTE_AVX,avx);
  setAttribute(art,ATTRIBUTE_SSE,sse);
  setAttribute(art,ATTRIBUTE_FMA,fma);
  setAttribute(art,ATTRIBUTE_AES,aes);
  setAttribute(art,ATTRIBUTE_SHA,sha);
  setAttribute(art,ATTRIBUTE_L1,l1);
  setAttribute(art,ATTRIBUTE_L2,l2);
  setAttribute(art,ATTRIBUTE_L3,l3);
  setAttribute(art,ATTRIBUTE_PEAK,pp);

  print_ascii(art);

  free(cpuName);
  free(maxFrequency);
  free(nCores);
  free(avx);
  free(sse);
  free(fma);
  free(aes);
  free(sha);
  free(l1);
  free(l2);
  free(l3);
  free(pp);

  free(cpu);
  free(art);
  free_cache_struct(cach);
  free_freq_struct(freq);

  return EXIT_SUCCESS;
}
