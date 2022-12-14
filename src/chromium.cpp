/*
   Copyright (C) 2000-2001 Dawit Alemayehu <adawit@kde.org>
   Copyright (C) 2006 Alexey Proskuryakov <ap@webkit.org>
   Copyright (C) 2007, 2008 Apple Inc. All rights reserved.
   Copyright (C) 2010 Patrick Gansterer <paroga@paroga.com>
   Copyright (C) 2022 Maroš Prejsa (rgnter) <maros.prejsa1@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License (LGPL)
   version 2 as published by the Free Software Foundation.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU Library General Public
   License along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
   This code is based on the java implementation in HTTPClient
   package by Ronald Tschalaer Copyright (C) 1996-1999.
*/

#include <epea.hpp>
#include <string>
#include <vector>
#include <limits.h>

constexpr char base64EncMap[64] = {
        0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
        0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
        0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
        0x59, 0x5A, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
        0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E,
        0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
        0x77, 0x78, 0x79, 0x7A, 0x30, 0x31, 0x32, 0x33,
        0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x2B, 0x2F
};
constexpr char base64DecMap[128] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x3F,
        0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
        0x3C, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
        0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
        0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
        0x17, 0x18, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
        0x31, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00
};

void epea::chromium::base64Encode(const char* data, unsigned len, std::string& result) {
    result.clear();
    if (!len)
        return;
    // If the input string is pathologically large, just return nothing.
    // Note: Keep this in sync with the "outLength" computation below.
    // Rather than being perfectly precise, this is a bit conservative.
    const unsigned maxInputBufferSize = UINT_MAX / 77 * 76 / 4 * 3 - 2;
    if (len > maxInputBufferSize)
        return;
    unsigned sidx = 0;
    unsigned didx = 0;
    unsigned outLength = ((len + 2) / 3) * 4;
    // Deal with the 76 character per line limit specified in RFC 2045.
    bool insertLFs = outLength > 76;
    if (insertLFs)
        outLength += ((outLength - 1) / 76);
    int count = 0;
    result.resize(outLength);
    // 3-byte to 4-byte conversion + 0-63 to ascii printable conversion
    if (len > 1) {
        while (sidx < len - 2) {
            if (insertLFs) {
                if (count && !(count % 76))
                    result[didx++] = '\n';
                count += 4;
            }
            result[didx++] = base64EncMap[(data[sidx] >> 2) & 077];
            result[didx++] = base64EncMap[((data[sidx + 1] >> 4) & 017) | ((data[sidx] << 4) & 077)];
            result[didx++] = base64EncMap[((data[sidx + 2] >> 6) & 003) | ((data[sidx + 1] << 2) & 077)];
            result[didx++] = base64EncMap[data[sidx + 2] & 077];
            sidx += 3;
        }
    }
    if (sidx < len) {
        if (insertLFs && (count > 0) && !(count % 76))
            result[didx++] = '\n';
        result[didx++] = base64EncMap[(data[sidx] >> 2) & 077];
        if (sidx < len - 1) {
            result[didx++] = base64EncMap[((data[sidx + 1] >> 4) & 017) | ((data[sidx] << 4) & 077)];
            result[didx++] = base64EncMap[(data[sidx + 1] << 2) & 077];
        } else
            result[didx++] = base64EncMap[(data[sidx] << 4) & 077];
    }
    // Add padding
    while (didx < result.size()) {
        result[didx] = '=';
        ++didx;
    }
}



bool epea::chromium::base64Decode(const std::string &data, std::vector<char>& out) {
    out.clear();
    unsigned len = data.length();
    out.resize(len);
    unsigned equalsSignCount = 0;
    unsigned outLength = 0;
    for (unsigned idx = 0; idx < len; ++idx) {
        unsigned char ch = data[idx];
        if (ch == '=') {
            ++equalsSignCount;
            // There should be no padding if length is a multiple of 4, and there
            // should never be more than 2 padding characters.
            if ((len % 4 || equalsSignCount > 2))
                return false;
        } else if (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') || ch == '+' || ch == '/') {
            if (equalsSignCount)
                return false;
            out[outLength] = base64DecMap[ch];
            ++outLength;
        }
    }
    if (!outLength)
        return !equalsSignCount;
    // Valid data is (n * 4 + [0,2,3]) characters long.
    if ((outLength % 4) == 1)
        return false;
    // 4-byte to 3-byte conversion
    outLength -= (outLength + 3) / 4;
    if (!outLength)
        return false;
    unsigned sidx = 0;
    unsigned didx = 0;
    if (outLength > 1) {
        while (didx < outLength - 2) {
            out[didx] = (((out[sidx] << 2) & 255) | ((out[sidx + 1] >> 4) & 003));
            out[didx + 1] = (((out[sidx + 1] << 4) & 255) | ((out[sidx + 2] >> 2) & 017));
            out[didx + 2] = (((out[sidx + 2] << 6) & 255) | (out[sidx + 3] & 077));
            sidx += 4;
            didx += 3;
        }
    }
    if (didx < outLength)
        out[didx] = (((out[sidx] << 2) & 255) | ((out[sidx + 1] >> 4) & 003));
    if (++didx < outLength)
        out[didx] = (((out[sidx + 1] << 4) & 255) | ((out[sidx + 2] >> 2) & 017));
    if (outLength < out.size())
        out.resize(outLength);
    return true;
}
