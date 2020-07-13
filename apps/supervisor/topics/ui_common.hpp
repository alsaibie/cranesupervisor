/*
 * MIT License
 * 
 * Copyright (c) 2020 Ali AlSaibie
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * 
 * File: ui_common.hpp
 * Project: Crane Supervisor
 * Author: Ali AlSaibie (ali.alsaibie@ku.edu.kw)
 * -----
 * Modified By: Ali AlSaibie (ali.alsaibie@ku.edu.kw>)
 */
#ifndef UI_COMMON_HPP_
#define UI_COMMON_HPP_

namespace MachineRFX {

enum class UserSystemModes_t {
    Manual_Mode = 1,
    Pressure_Control,
    Pressure_Assist,
    Volume_Control,
    EndOfList
};

enum class UserInputSource_t {
    Onboard = 1,
    Offboard
};

inline UserSystemModes_t& operator++(UserSystemModes_t& m) {
    m = static_cast<UserSystemModes_t>(static_cast<int>(m) + 1);

    if (m == UserSystemModes_t::EndOfList) {
        m = UserSystemModes_t::Manual_Mode;
    }
    return m;
};

}  // namespace MachineRFX

#endif // UI_COMMON_HPP_