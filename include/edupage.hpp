//
// Created by maros on 01/09/2022.
//

#ifndef EDUPAGE_EDUPAGE_HPP
#define EDUPAGE_EDUPAGE_HPP

#include <string>
#include <string_view>

namespace eplib
{

    /**
     * Encode payload.
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

    /**
     *    Copyright (C) 2000-2001 Dawit Alemayehu <adawit@kde.org>
     *    Copyright (C) 2006 Alexey Proskuryakov <ap@webkit.org>
     *    Copyright (C) 2007, 2008 Apple Inc. All rights reserved.
     *    Copyright (C) 2010 Patrick Gansterer <paroga@paroga.com>
     *    Copyright (C) 2022 Maroš Prejsa <maros.prejsa1@gmail.com>
     */
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

#endif //EDUPAGE_EDUPAGE_HPP
