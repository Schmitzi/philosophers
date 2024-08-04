1 1 has taken a fork
410 1 died

   [33m┌[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m┐[0m
   [33m│[0m                                 [33m│[0m
   [33m│[0m   [33mfuncheck[0m -- [1m1.1.3[0m             [33m│[0m
   [33m│[0m                                 [33m│[0m
   [33m│[0m   - program: [1m./philo[0m            [33m│[0m
   [33m│[0m                                 [33m│[0m
   [33m│[0m   - arguments:                  [33m│[0m
   [33m│[0m       * [1m1[0m                       [33m│[0m
   [33m│[0m       * [1m410[0m                     [33m│[0m
   [33m│[0m       * [1m200[0m                     [33m│[0m
   [33m│[0m       * [1m200[0m                     [33m│[0m
   [33m│[0m       * [1m3[0m                       [33m│[0m
   [33m└[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m┘[0m

[44m[1m INFO [0m If your program wait for stdin input, you can type here or pipe it.
[33m───────────── TTY ────────────[0m
[33m──────────────────────────────[0m
[46m[1m TASK [0m Testable functions fetching [42m[1m ✓ [0m
[44m[1m INFO [0m Functions detected count: [1m8[0m
┏[43m [1mpthread_create (calloc) [0m [33m272[0m bytes allocated in [33m1[0m allocations is not freed
┗━┳━━ make_threads at thread.c:26:7 (0x40263c)
  ┗━┳━━ thread_init at thread.c:58:6 (0x4027ac)
    ┗━━━━ main at main.c:28:7 (0x401d51)
┏[43m [1mpthread_create (calloc) [0m [33m272[0m bytes allocated in [33m1[0m allocations is not freed
┗━┳━━ thread_init at thread.c:56:6 (0x40277d)
  ┗━━━━ main at main.c:28:7 (0x401d51)


┏[42m [1musleep [0m when this function is failing, allocations are not freed in [33m2[0m contexts 
┗━┳━━ ?? at ?? (0x42cf)
  ┗━┳━━ ?? at ?? (0x5de2)
    ┗━┳━━ ft_usleep at time.c:36:3 (0x402910)
      ┗━┳━━ take_forks at routine.c:90:3 (0x40256d)
        ┗━┳━━ eat at routine.c:102:3 (0x402409)
          ┗━┳━━ routine at routine.c:66:3 (0x4022d9)
            ┗━┳━━ ?? at ?? (0x94ac2)
              ┗━━━━ ?? at ?? (0x12684f)
┏[43m [1mpthread_create (calloc) [0m [33m272[0m bytes allocated in [33m1[0m allocations is not freed
┗━┳━━ make_threads at thread.c:26:7 (0x40263c)
  ┗━┳━━ thread_init at thread.c:58:6 (0x4027ac)
    ┗━━━━ main at main.c:28:7 (0x401d51)
┏[43m [1mpthread_create (calloc) [0m [33m272[0m bytes allocated in [33m1[0m allocations is not freed
┗━┳━━ thread_init at thread.c:56:6 (0x40277d)
  ┗━━━━ main at main.c:28:7 (0x401d51)

┏[42m [1musleep [0m when this function is failing, allocations are not freed in [33m2[0m contexts 
┗━┳━━ ?? at ?? (0x42cf)
  ┗━┳━━ ?? at ?? (0x5de2)
    ┗━┳━━ ft_usleep at time.c:36:3 (0x402910)
      ┗━┳━━ take_forks at routine.c:90:3 (0x40256d)
        ┗━┳━━ eat at routine.c:102:3 (0x402409)
          ┗━┳━━ routine at routine.c:66:3 (0x4022d9)
            ┗━┳━━ ?? at ?? (0x94ac2)
              ┗━━━━ ?? at ?? (0x12684f)
┏[43m [1mpthread_create (calloc) [0m [33m272[0m bytes allocated in [33m1[0m allocations is 