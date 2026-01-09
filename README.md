# alloc-lite v1: The Bump Allocator


Created my first Bump allocator. it has a complexity of (O)1 since it literally just moves the pointer every time memory is requested.

had a couple rookie mistakes like:
- I made the dumb mistake of initializing a variable outside of main LOL
- Then I followed that up by not wrapping my init in an if statement
- ok these minor typos are starting to catch up
- ran into an implicit declaration issue…. forgot to put al_init in header file
