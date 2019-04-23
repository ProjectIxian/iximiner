# ArioMiner v0.1
### Arionum miner for CPU and GPU 

## Dev Fee
In order to support development, this miner has 1% dev fee included - 1 minute from 100 minutes it will mine for developer. Mining settings are downloaded from http://coinfee.changeling.biz/index.json each time it switches to developer mining mode.  

## Features
- optimized argon2 hashing library - both in speed and in memory usage; everything not related to arionum mining was stripped down, indexing calculation was replaced with precalculated versions (improvements in the range of 10% - 50% compared to existing miners)
- support for both CPU and GPU mining using multiple engines perfectly addapted to your hardware
- support for autodetecting the best version of the CPU hasher for your machine (SSE2/SSSE3/AVX2/AVX512F)
- support for autotuning mode to get best settings for GPU mining 
- support for proxy mode, to act as an aggregator for multiple small miners and providing a nice UI dashboard for an overall view of your farm

## Releases
There are binaries compiled for Windows 10, Ubuntu 16.04 & 18.04, Centos 7 and HiveOS. Just pick the one that best suits you and skip to usage information. If for some reason the binaries don't work for you or you want the cutting edge version of this software you can try building it yourself using below instructions (build instructions are only provided for Ubuntu).
You can get the binaries from here:
https://github.com/bogdanadnan/ariominer/releases

## Build it yourself
What you need:
- Recent Ubuntu distribution (recommended - 16.04 or higher)
- Git client
- CMake 3
- GCC & G++ version 7 or higher. It can be compiled with CLang as well.
- CUDA toolkit
- OpenCL libraries and headers

Instructions:
- run the following snippet:
```sh
$ git clone http://github.com/bogdanadnan/ariominer.git
$ cd ariominer
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Usage:  
**!!! In some cases (mostly on Windows) the miner doesn't properly detect AVX2 optimization for CPU. If AVX2 doesn't appear in optimization features list for CPU at miner startup, please verify on google if your CPU model has it. If it does have AVX2 support, please run it with "--force-cpu-optimization AVX2" option. This will give a serious boost to hash rate speed so it does worth the effort to check. !!!**
  
- starting in miner mode:
```sh
       ariominer --mode miner --pool <pool / proxy address> --wallet <wallet address> --name <worker name> --cpu-intensity <intensity> --gpu-intensity-cblocks <intensity> --gpu-intensity-gblocks <intensity>  
```
- starting in autotune mode:
```sh
       ariominer --mode autotune --block-type GPU --intensity-start <intensity> --intensity-stop <intensity> --intensity-step <intensity>
```
- starting in proxy mode:
```sh
       ariominer --mode proxy --port <proxy port> --pool <pool address> --wallet <wallet address> --name <proxy name>
```

Parameters:  
--help: show this help text  
--verbose: print more informative text during run  
--mode <mode>: start in specific mode - arguments: miner / proxy  
- miner: this instance will mine for arionum  
- autotune: for finding best intensity for GPU mining  
- proxy: this instance will act as a hub for multiple miners; useful to aggregate multiple miners into a single instance reducing the load on the pool [TODO]

--pool <pool address>: pool/proxy address to connect to (eg. http://aropool.com:80)  
--wallet <wallet address>: wallet address; this is optional if in miner mode and you are connecting to a proxy  
--name <worker identifier>: worker identifier this is optional if in miner mode and you are connecting to a proxy  
--port <proxy port>: proxy specific option, port on which to listen for clients this is optional, defaults to 8088  
--cpu-intensity: miner specific option, mining intensity on CPU; value from 0 (disabled) to 100 (full load); this is optional, defaults to 100 (\*)  
--gpu-intensity-cblocks: miner specific option, mining intensity on GPU; value from 0 (disabled) to 100 (full load); this is optional, defaults to 100 (\*); you can add more entries separated by comma for each GPU  
--gpu-intensity-gblocks: miner specific option, mining intensity on GPU; value from 0 (disabled) to 100 (full load); this is optional, defaults to 100 (\*); you can add more entries separated by comma for each GPU  
--gpu-filter: miner specific option, filter string for device selection; it will select only devices that have in description the specified string; this is optional, defaults to ""; you can add more entries separated by comma  
--force-cpu-optimization: miner specific option, what type of CPU optimization to use; values: REF, SSE2, SSSE3, AVX2, AVX512F; this is optional, defaults to autodetect, change only if autodetected one crashes  
--block-type: miner specific option, override block type sent by pool; useful for tuning intensity; values: CPU, GPU; don't use for regular mining, shares submitted during opposite block type will be rejected  
--update-interval: how often should we update mining settings from pool, in seconds; increasing it will lower the load on pool but will increase rejection rate; this is optional, defaults to 2 sec and can't be set lower than that  
--report-interval: how often should we display mining reports, in seconds; this is optional, defaults to 10 sec  
--intensity-start: autotune specific option, start intensity for autotuning (default 1)  
--intensity-stop: autotune specific option, stop intensity for autotuning (default 100)  
--intensity-step: autotune specific option, intensity steps for autotuning (default 1)  
--autotune-step-time: autotune specific option, how much time should wait in a step before measuring h/s, in seconds (minimum 10, default 20)  

(\*) Mining intensity depends on the number of CPU/GPU cores and available memory. Full load (100) is dynamically calculated by the application. You can use fractional numbers for better tuning.

