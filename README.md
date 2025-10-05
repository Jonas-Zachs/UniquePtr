# UniquePtr

A small `std::unique_ptr`-like C++ class created for practice and learning purposes.  
It helps understand ownership semantics, dynamic memory management, and move-only class design.

## Features
- Exclusive ownership of a dynamically allocated object  
- Automatic cleanup when the pointer goes out of scope  
- Move constructor and move assignment operator  
- Deleted copy constructor and copy assignment (non-copyable)  
- Utility functions: `get()`, `reset()`, and `release()`  

## Note
This is not a replacement for `std::unique_ptr` — it’s a simplified version made only for educational use.
