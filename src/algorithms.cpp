/*
    MIT License

    Copyright (c) 2022 Maroš Prejsa (rgnter) <maros.prejsa1@gmail.com>

            Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
            to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
            copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
            AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "epea.hpp"

#include <zlib.h>
#include <cstdio>
#include <memory>
#include <vector>
#include <stdexcept>
#include <exception>

struct data_s {
    std::shared_ptr<uint8_t> data;
    std::size_t length;
};

/**
 * Compress data.
 * @param data Data to compress.
 * @return Struct containing pointer to compressed buffer and it's length.
 */
data_s compress(const std::string &data) {
    auto compressedLength = data.length() + 256;
    auto compressed = std::shared_ptr<uint8_t>(
            new uint8_t[compressedLength]
    );

    int32_t status;
    z_stream stream{
            .zalloc = Z_NULL,
            .zfree  = Z_NULL,
            .opaque = Z_NULL
    };

    status = deflateInit2(
            &stream,
            Z_DEFAULT_COMPRESSION,
            Z_DEFLATED,
            -15, // raw deflate
            8,
            Z_DEFAULT_STRATEGY
    );
    if (status != Z_OK)
        throw std::logic_error("Couldn't initialize deflate");

    stream.avail_in = data.length();     // data length
    stream.avail_out = compressedLength;  // compressed length
    stream.next_in = (Bytef *) data.data();   // data
    stream.next_out = (Bytef *) compressed.get(); // compressed data

    // compress
    do {
        status = deflate(&stream, Z_FINISH);
        if (status == Z_OK) {
            deflateEnd(&stream);
            abort(); /* todo allocate more bytes to compressed compressed */
        }
    } while (status != Z_STREAM_END);

    deflateEnd(&stream);
    return data_s{compressed, stream.total_out};
}

std::string epea::encode(const std::string &payload) {
    auto compressed = compress(payload);
    auto data = compressed.data.get();

    std::string stringified;
    chromium::base64Encode((char*) data, compressed.length, stringified);

    return std::string("dz:").append(stringified);
}

std::string epea::decode(const std::string &payload) {
    return "";
}
