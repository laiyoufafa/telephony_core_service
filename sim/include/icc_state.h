/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ICC_STATE__
#define __ICC_STATE__

#include <iostream>
#include <string>
#include <vector>

namespace OHOS {
namespace Telephony {
const int ICC_CONTENT_UNKNOWN = -1;
const int ICC_CARD_ABSENT = 0;
const int ICC_CONTENT_READY = 1;
const int ICC_CONTENT_PIN = 2;
const int ICC_CONTENT_PUK = 3;
const int ICC_CONTENT_SIMLOCK = 4;

const int CONTENT_INDEX_INVALID = -1;
const int ICC_CONTENT_NUM = 0;
const int PIN_SUBSTITUE_FALSE = 0;
const int PIN_SUBSTITUE_TRUE = 1;

const int ICC_PIN_STATE_UNKNOWN = 0;
const int ICC_PIN_NOT_VERIFIED = 1;
const int ICC_PIN_VERIFIED = 2;
const int ICC_PIN_DISABLED = 3;
const int ICC_PIN_BLOCKED_ENABLED = 4;
const int ICC_PIN_BLOCKED_PERM = 5;

const int ICC_UNKNOWN_TYPE = 0;
const int ICC_SIM_TYPE = 1;
const int ICC_USIM_TYPE = 2;
const int ICC_RUIM_TYPE = 3;
const int ICC_CSIM_TYPE = 4;
const int ICC_ISIM_TYPE = 5;

const int ICC_SIMLOCK_UNKNOWN = 0;
const int ICC_SIMLOCK_IN_PROGRESS = 1;
const int ICC_SIMLOCK_READY = 2;

class IccContent {
public:
    IccContent();
    ~IccContent() {}

public:
    int32_t simLockSubState_;
    int32_t substitueOfPin1_;
    int32_t stateOfPin1_;
    int32_t stateOfPin2_;
};

// icc state
class IccState {
public:
    IccState();
    ~IccState() {}

public:
    int32_t simType_;
    int32_t simStatus_;
};
} // namespace Telephony
} // namespace OHOS
#endif // __ICC_STATE__
