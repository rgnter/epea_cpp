/*
    MIT License

    Copyright (C) 2022 Maroš Prejsa (rgnter) <maros.prejsa1@gmail.com>

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


#ifndef EDUPAGE_EPEA_HPP
#define EDUPAGE_EPEA_HPP

#include <string>
#include <string_view>

namespace epea
{

    /**
     * Encode payload.<br>
     * Payload is compressed and encoded to base64 and then it's prepended with "<code>dz:</code>".
     * @param payload Payload.
     * @return Encoded payload.
     */
    std::string encode(const std::string& payload);

    /**
     * Decode payload.
     * @param payload Payload.
     * @return Decoded payload.
     */
    std::string decode(const std::string& payload);

    namespace chromium
    {

        /**
         * Encodes ascii to base64
         * @param data Data
         * @param len  Data length
         * @param out  Buffer
         */
        void base64Encode(const char* data, unsigned len, std::string& out);

        /**
         * Decodes base64 to ascii
         * @param data Data
         * @param len  Data length
         * @param out  Buffer
         * @return Boolean
         */
        bool base64Decode(const char* data, unsigned len, std::string& out);

    }
}

#endif //EDUPAGE_EPEA_HPP
