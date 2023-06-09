/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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

#include "ims_core_service_callback_proxy.h"

#include "message_option.h"
#include "message_parcel.h"

namespace OHOS {
namespace Telephony {
ImsCoreServiceCallbackProxy::ImsCoreServiceCallbackProxy(const sptr<IRemoteObject> &impl)
    : IRemoteProxy<ImsCoreServiceCallbackInterface>(impl) {}

int32_t ImsCoreServiceCallbackProxy::ImsServiceStatusReport(int32_t slotId, const ImsServiceStatus &imsServiceStatus)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCoreServiceCallbackProxy::GetDescriptor())) {
        TELEPHONY_LOGE("write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("write slotId fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteRawData((const void *)&imsServiceStatus, sizeof(ImsServiceStatus))) {
        TELEPHONY_LOGE("write imsServiceStatus fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SERVICE_STATUS_REPORT, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCoreServiceCallbackProxy::ImsRegistrationStatusResponse(
    const ImsResponseInfo &info, const ImsRegistrationStatus &imsRegStatus)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCoreServiceCallbackProxy::GetDescriptor())) {
        TELEPHONY_LOGE("write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRawData((const void *)&info, sizeof(ImsResponseInfo))) {
        TELEPHONY_LOGE("write info fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteRawData((const void *)&imsRegStatus, sizeof(ImsRegistrationStatus))) {
        TELEPHONY_LOGE("write imsRegStatus fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_REGISTRATION_STATUS_RESPONSE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCoreServiceCallbackProxy::ImsNetworkStateChange(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCoreServiceCallbackProxy::GetDescriptor())) {
        TELEPHONY_LOGE("write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("write slotId fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_NETWORK_STATE_CHANGE_REPORT, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}
} // namespace Telephony
} // namespace OHOS
