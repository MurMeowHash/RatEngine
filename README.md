# RatEngine
A modern, high-performance render engine, focused on optimized realtime rendering and extensible engine architecture. Current implementation targets Vulkan 1.2+ and Windows.

## Features
- Render Hardware Interface (RHI) abstracting rendering, resource management, and graphics API initialization
- Multithreaded architecture with dedicated Game and Render threads
- Platform Abstraction Layer (PAL) enabling future cross-platform support
- Custom CPU and GPU memory allocators for optimized memory management
- Custom Dependency Injection framework supporting multiple dependency contexts and composition roots
