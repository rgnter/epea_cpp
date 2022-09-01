# epea
Edupage's payload "encryption" algorithms implemented in C++

## Usage
```cpp
#include <epea.hpp>
#include <cstdio>
#include <string>

 // ex. encode and decode payload for sending a message
const std::string payload(
        "selectedUser=xxxxx&text=Hello from C++!&attachements=%7B%7D&receipt=0&typ=sprava")
        
const auto encoded = epea::encode(payload);
printf("Encoded payload: %s\n", encoded.c_str());

const auto decoded = epea::decode(encoded);
printf("Decoded payload: %s\n", encoded.c_str());
assert(encoded == decoded);
```

## Licenses
- MIT
- LGPL (modified chromium's wtf base64 algorithms)

## Building requirements
- C++20
- CMake 3.16+
- zlib