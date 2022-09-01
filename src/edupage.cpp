
#include "edupage.hpp"

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

constexpr int unicodeUtf16MaxCodePoint = 0xffff;

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

std::string eplib::encode(const std::string &payload) {
    auto compressed = compress(payload);
    auto data = compressed.data.get();

    std::string stringified;
    chromium::base64Encode((char*) data, compressed.length, stringified);

    return std::string("dz:").append(stringified);
}

std::string eplib::decode(const std::string &payload) {
    return "";
}
