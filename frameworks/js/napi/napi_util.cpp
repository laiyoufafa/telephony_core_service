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

#include "napi_util.h"

#include <codecvt>
#include <cstdio>
#include <locale>
#include <vector>
#include <cstring>
#include <memory>

#include "telephony_log_wrapper.h"
#include "enum_convert_for_js.h"

namespace OHOS {
namespace Telephony {
static constexpr const char *JS_ERROR_TELEPHONY_INVALID_INPUT_PARAMETER_STRING =
    "BusinessError 401: Parameter error. The type of parameter should match or the number of parameters must match.";
static constexpr const char *JS_ERROR_TELEPHONY_UNKNOW_ERROR_STRING = "Unknown error code.";
static constexpr const char *JS_ERROR_TELEPHONY_ARGUMENT_ERROR_STRING = "Invalid parameter value.";
static constexpr const char *JS_ERROR_TELEPHONY_SERVICE_ERROR_STRING = "Operation failed. Cannot connect to service.";
static constexpr const char *JS_ERROR_TELEPHONY_SYSTEM_ERROR_STRING = "System internal error.";
static constexpr const char *JS_ERROR_CALL_DIAL_POLICY_NOT_MET_STRING = "The dialing policy is not met.";
static constexpr const char *JS_ERROR_CALL_WRONG_MOBILE_NUMBER_STRING = "Wrong mobile number format.";
static constexpr const char *JS_ERROR_CALL_ABNORMAL_CALL_STATUS_STRING = "Abnormal call status.";
static constexpr const char *JS_ERROR_CALL_ABNORMAL_VIDEO_CALL_STATUS_STRING = "Abnormal video call status.";
static constexpr const char *JS_ERROR_DEVICE_NOT_SUPPORT_THIS_API_STRING = "The device does not support this API.";
static constexpr const char *JS_ERROR_TELEPHONY_NO_SIM_CARD_STRING = "Do not have sim card.";
static const int32_t MAX_TEXT_LENGTH = 4096;

std::string NapiUtil::ToUtf8(std::u16string str16)
{
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> {}.to_bytes(str16);
}

std::u16string NapiUtil::ToUtf16(std::string str)
{
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> {}.from_bytes(str);
}

napi_value NapiUtil::CreateErrorMessage(napi_env env, const std::string &msg, int32_t errorCode)
{
    napi_value result = nullptr;
    napi_value message = nullptr;
    NAPI_CALL(env, napi_create_string_utf8(env, msg.c_str(), msg.length(), &message));
    napi_value codeValue = nullptr;
    NAPI_CALL(env, napi_create_int32(env, errorCode, &codeValue));
    NAPI_CALL(env, napi_create_object(env, &result));
    NAPI_CALL(env, napi_set_named_property(env, result, "code", codeValue));
    NAPI_CALL(env, napi_set_named_property(env, result, "message", message));
    return result;
}

napi_value NapiUtil::CreateUndefined(napi_env env)
{
    napi_value result = nullptr;
    NAPI_CALL(env, napi_get_undefined(env, &result));
    return result;
}

bool NapiUtil::MatchValueType(napi_env env, napi_value value, napi_valuetype targetType)
{
    napi_valuetype valueType = napi_undefined;
    NAPI_CALL_BASE(env, napi_typeof(env, value, &valueType), false);
    return valueType == targetType;
}

bool NapiUtil::MatchParameters(
    napi_env env, const napi_value parameters[], std::initializer_list<napi_valuetype> valueTypes)
{
    if (parameters == nullptr) {
        return false;
    }
    int i = 0;
    for (auto beg = valueTypes.begin(); beg != valueTypes.end(); ++beg) {
        if (!MatchValueType(env, parameters[i], *beg)) {
            return false;
        }
        ++i;
    }
    return true;
}

void NapiUtil::SetPropertyInt32(napi_env env, napi_value object, const std::string &name, int32_t value)
{
    napi_value propertyValue = nullptr;
    NAPI_CALL_RETURN_VOID(env, napi_create_int32(env, value, &propertyValue));
    NAPI_CALL_RETURN_VOID(env, napi_set_named_property(env, object, name.c_str(), propertyValue));
}

void NapiUtil::SetPropertyInt64(napi_env env, napi_value object, const std::string &name, int64_t value)
{
    napi_value propertyValue = nullptr;
    NAPI_CALL_RETURN_VOID(env, napi_create_int64(env, value, &propertyValue));
    NAPI_CALL_RETURN_VOID(env, napi_set_named_property(env, object, name.c_str(), propertyValue));
}

void NapiUtil::SetPropertyStringUtf8(napi_env env, napi_value object, const std::string &name, const std::string &value)
{
    napi_value propertyValue = nullptr;
    NAPI_CALL_RETURN_VOID(env, napi_create_string_utf8(env, value.c_str(), value.length(), &propertyValue));
    NAPI_CALL_RETURN_VOID(env, napi_set_named_property(env, object, name.c_str(), propertyValue));
}

void NapiUtil::SetPropertyBoolean(napi_env env, napi_value object, const std::string &name, bool value)
{
    napi_value propertyValue = nullptr;
    NAPI_CALL_RETURN_VOID(env, napi_get_boolean(env, value, &propertyValue));
    NAPI_CALL_RETURN_VOID(env, napi_set_named_property(env, object, name.c_str(), propertyValue));
}

napi_value NapiUtil::ToInt32Value(napi_env env, int32_t value)
{
    napi_value staticValue = nullptr;
    NAPI_CALL(env, napi_create_int32(env, value, &staticValue));
    return staticValue;
}

bool NapiUtil::HasNamedProperty(napi_env env, napi_value object, const std::string &propertyName)
{
    bool hasProperty = false;
    NAPI_CALL_BASE(env, napi_has_named_property(env, object, propertyName.data(), &hasProperty), false);
    return hasProperty;
}

bool NapiUtil::HasNamedTypeProperty(
    napi_env env, napi_value object, napi_valuetype type, const std::string &propertyName)
{
    bool hasProperty = false;
    NAPI_CALL_BASE(env, napi_has_named_property(env, object, propertyName.data(), &hasProperty), false);
    if (hasProperty) {
        napi_value value = nullptr;
        NAPI_CALL_BASE(env, napi_get_named_property(env, object, propertyName.data(), &value), false);
        return MatchValueType(env, value, type);
    }
    return false;
}

bool NapiUtil::MatchObjectProperty(
    napi_env env, napi_value object, std::initializer_list<std::pair<std::string, napi_valuetype>> pairList)
{
    if (object == nullptr) {
        return false;
    }
    for (auto beg = pairList.begin(); beg != pairList.end(); ++beg) {
        if (!HasNamedTypeProperty(env, object, beg->second, beg->first)) {
            return false;
        }
    }
    return true;
}

bool NapiUtil::MatchOptionPropertyType(
    napi_env env, napi_value object, napi_valuetype type, const std::string &propertyName)
{
    bool hasProperty = false;
    NAPI_CALL_BASE(env, napi_has_named_property(env, object, propertyName.data(), &hasProperty), false);
    if (hasProperty) {
        napi_value value = nullptr;
        NAPI_CALL_BASE(env, napi_get_named_property(env, object, propertyName.data(), &value), false);
        return MatchValueType(env, value, type);
    }
    return true;
}

std::string NapiUtil::GetStringFromValue(napi_env env, napi_value value)
{
    char msgChars[MAX_TEXT_LENGTH] = {0};
    size_t msgLength = 0;
    NAPI_CALL_BASE(env, napi_get_value_string_utf8(env, value, msgChars, MAX_TEXT_LENGTH, &msgLength), "");
    TELEPHONY_LOGI("NapiUtil GetStringFromValue msgLength = %{public}zu", msgLength);
    if (msgLength > 0) {
        return std::string(msgChars, 0, msgLength);
    } else {
        return "";
    }
}

napi_value NapiUtil::GetNamedProperty(napi_env env, napi_value object, const std::string &propertyName)
{
    napi_value value = nullptr;
    bool hasProperty = false;
    NAPI_CALL(env, napi_has_named_property(env, object, propertyName.data(), &hasProperty));
    if (hasProperty) {
        NAPI_CALL(env, napi_get_named_property(env, object, propertyName.data(), &value));
    }
    return value;
}

napi_value NapiUtil::HandleAsyncWork(napi_env env, BaseContext *baseContext, const std::string &workName,
    napi_async_execute_callback execute, napi_async_complete_callback complete)
{
    TELEPHONY_LOGI("NapiUtil HandleAsyncWork workName = %{public}s", workName.c_str());
    std::unique_ptr<BaseContext> context(baseContext);
    if (context == nullptr) {
        std::string errorCode = std::to_string(napi_invalid_arg);
        std::string errorMessage = "error at baseContext is nullptr";
        NAPI_CALL(env, napi_throw_error(env, errorCode.c_str(), errorMessage.c_str()));
        return nullptr;
    }
    napi_value result = nullptr;
    if (context->callbackRef == nullptr) {
        NAPI_CALL(env, napi_create_promise(env, &context->deferred, &result));
    } else {
        NAPI_CALL(env, napi_get_undefined(env, &result));
    }
    napi_value resource = CreateUndefined(env);
    napi_value resourceName = nullptr;
    NAPI_CALL(env, napi_create_string_utf8(env, workName.data(), NAPI_AUTO_LENGTH, &resourceName));
    NAPI_CALL(env,
        napi_create_async_work(env, resource, resourceName, execute, complete, (void *)context.get(), &context->work));
    napi_status queueWorkStatus = napi_queue_async_work(env, context->work);
    if (queueWorkStatus == napi_ok) {
        context.release();
        TELEPHONY_LOGI("NapiUtil HandleAsyncWork napi_queue_async_work ok");
    } else {
        std::string errorCode = std::to_string(queueWorkStatus);
        std::string errorMessage = "error at napi_queue_async_work";
        NAPI_CALL(env, napi_throw_error(env, errorCode.c_str(), errorMessage.c_str()));
    }
    TELEPHONY_LOGI("NapiUtil HandleAsyncWork end");
    return result;
}

void NapiUtil::Handle1ValueCallback(napi_env env, BaseContext *baseContext, napi_value callbackValue)
{
    TELEPHONY_LOGI("Handle1ValueCallback start");
    if (baseContext == nullptr) {
        TELEPHONY_LOGI("Handle1ValueCallback serious error baseContext nullptr");
        std::string errorCode = std::to_string(napi_invalid_arg);
        std::string errorMessage = "error at baseContext is nullptr";
        NAPI_CALL_RETURN_VOID(env, napi_throw_error(env, errorCode.c_str(), errorMessage.c_str()));
        return;
    }
    if (baseContext->callbackRef != nullptr) {
        TELEPHONY_LOGI("Handle1ValueCallback start normal callback");
        napi_value recv = CreateUndefined(env);
        napi_value callbackFunc = nullptr;
        NAPI_CALL_RETURN_VOID(env, napi_get_reference_value(env, baseContext->callbackRef, &callbackFunc));
        napi_value callbackValues[] = {callbackValue};
        napi_value result = nullptr;
        NAPI_CALL_RETURN_VOID(
            env, napi_call_function(env, recv, callbackFunc, std::size(callbackValues), callbackValues, &result));
        NAPI_CALL_RETURN_VOID(env, napi_delete_reference(env, baseContext->callbackRef));
        TELEPHONY_LOGI("Handle1ValueCallback normal callback end");
    } else if (baseContext->deferred != nullptr) {
        TELEPHONY_LOGI("Handle1ValueCallback start promise callback");
        if (baseContext->resolved) {
            NAPI_CALL_RETURN_VOID(env, napi_resolve_deferred(env, baseContext->deferred, callbackValue));
            TELEPHONY_LOGI("Handle1ValueCallback napi_resolve_deferred end");
        } else {
            NAPI_CALL_RETURN_VOID(env, napi_reject_deferred(env, baseContext->deferred, callbackValue));
            TELEPHONY_LOGI("Handle1ValueCallback napi_reject_deferred end");
        }
        TELEPHONY_LOGI("Handle1ValueCallback promise callback end");
    }
    napi_delete_async_work(env, baseContext->work);
    delete baseContext;
    baseContext = nullptr;
    TELEPHONY_LOGI("Handle1ValueCallback end");
}

void NapiUtil::Handle2ValueCallback(napi_env env, BaseContext *baseContext, napi_value callbackValue)
{
    TELEPHONY_LOGI("Handle2ValueCallback start");
    if (baseContext == nullptr) {
        TELEPHONY_LOGI("Handle2ValueCallback serious error baseContext nullptr");
        std::string errorCode = std::to_string(napi_invalid_arg);
        std::string errorMessage = "error at baseContext is nullptr";
        NAPI_CALL_RETURN_VOID(env, napi_throw_error(env, errorCode.c_str(), errorMessage.c_str()));
        return;
    }
    if (baseContext->callbackRef != nullptr) {
        TELEPHONY_LOGI("Handle2ValueCallback start normal callback");
        napi_value recv = CreateUndefined(env);
        napi_value callbackFunc = nullptr;
        NAPI_CALL_RETURN_VOID(env, napi_get_reference_value(env, baseContext->callbackRef, &callbackFunc));
        napi_value callbackValues[] = {nullptr, nullptr};
        callbackValues[0] = baseContext->resolved ? CreateUndefined(env) : callbackValue;
        callbackValues[1] = baseContext->resolved ? callbackValue : CreateUndefined(env);
        napi_value result = nullptr;
        NAPI_CALL_RETURN_VOID(
            env, napi_call_function(env, recv, callbackFunc, std::size(callbackValues), callbackValues, &result));
        NAPI_CALL_RETURN_VOID(env, napi_delete_reference(env, baseContext->callbackRef));
        TELEPHONY_LOGI("Handle2ValueCallback normal callback end");
    } else if (baseContext->deferred != nullptr) {
        TELEPHONY_LOGI("Handle2ValueCallback start promise callback");
        if (baseContext->resolved) {
            NAPI_CALL_RETURN_VOID(env, napi_resolve_deferred(env, baseContext->deferred, callbackValue));
        } else {
            NAPI_CALL_RETURN_VOID(env, napi_reject_deferred(env, baseContext->deferred, callbackValue));
        }
        TELEPHONY_LOGI("Handle2ValueCallback promise callback end");
    }
    napi_delete_async_work(env, baseContext->work);
    delete baseContext;
    baseContext = nullptr;
    TELEPHONY_LOGI("Handle2ValueCallback end");
}

void NapiUtil::DefineEnumClassByName(
    napi_env env, napi_value exports, std::string_view enumName, size_t arrSize, const napi_property_descriptor *desc)
{
    auto construct = [](napi_env env, napi_callback_info info) -> napi_value { return nullptr; };
    napi_value result = nullptr;
    napi_status status =
        napi_define_class(env, enumName.data(), NAPI_AUTO_LENGTH, construct, nullptr, arrSize, desc, &result);
    if (status != napi_ok) {
        TELEPHONY_LOGE("DefineEnumClassByName napi_define_class failed ret = %d", status);
    }
    status = napi_set_named_property(env, exports, enumName.data(), result);
    if (status != napi_ok) {
        TELEPHONY_LOGE("DefineEnumClassByName napi_set_named_property failed ret = %d", status);
    }
}

JsError NapiUtil::ConverErrorMessageForJs(int32_t errorCode)
{
    JsError error = {};
    if (CreateParameterErrorMessageForJs(errorCode, error)) {
        return error;
    }

    if (!CreateCommonErrorMessageForJs(errorCode, error) && !CreateCallErrorMessageForJs(errorCode, error)) {
        error.errorCode = JS_ERROR_TELEPHONY_UNKNOW_ERROR;
        error.errorMessage = JS_ERROR_TELEPHONY_UNKNOW_ERROR_STRING;
        TELEPHONY_LOGE("NapiUtil::ConverErrorMessageForJs errorCode is out of range");
    }

    TELEPHONY_LOGI(
        "NapiUtil::ConverErrorMessageForJs errorCode from %{public}d to %{public}d", errorCode, error.errorCode);
    return error;
}

bool NapiUtil::CreateParameterErrorMessageForJs(int32_t errorCode, JsError &error)
{
    bool flag = true;
    switch (errorCode) {
        case ERROR_PARAMETER_COUNTS_INVALID:
        case ERROR_PARAMETER_TYPE_INVALID:
        case napi_status::napi_generic_failure:
        case napi_status::napi_invalid_arg:
            error.errorCode = JS_ERROR_TELEPHONY_INVALID_INPUT_PARAMETER;
            error.errorMessage = JS_ERROR_TELEPHONY_INVALID_INPUT_PARAMETER_STRING;
            break;
        case ERROR_SLOT_ID_INVALID:
            error.errorCode = JS_ERROR_TELEPHONY_ARGUMENT_ERROR;
            error.errorMessage = JS_ERROR_TELEPHONY_ARGUMENT_ERROR_STRING;
            break;
        default:
            flag = false;
            break;
    }

    return flag;
}

bool NapiUtil::CreateCommonErrorMessageForJs(int32_t errorCode, JsError &error)
{
    if ((errorCode < COMMON_ERR_OFFSET || errorCode >= CALL_ERR_OFFSET)) {
        return false;
    }
    bool flag = true;

    switch (errorCode) {
        case TELEPHONY_ERR_ARGUMENT_MISMATCH:
        case TELEPHONY_ERR_ARGUMENT_INVALID:
        case TELEPHONY_ERR_ARGUMENT_NULL:
        case TELEPHONY_ERR_SLOTID_INVALID:
            error.errorCode = JS_ERROR_TELEPHONY_ARGUMENT_ERROR;
            error.errorMessage = JS_ERROR_TELEPHONY_ARGUMENT_ERROR_STRING;
            break;
        case TELEPHONY_ERR_DESCRIPTOR_MISMATCH:
        case TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL:
        case TELEPHONY_ERR_WRITE_DATA_FAIL:
        case TELEPHONY_ERR_WRITE_REPLY_FAIL:
        case TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL:
        case TELEPHONY_ERR_REGISTER_CALLBACK_FAIL:
        case TELEPHONY_ERR_UNINIT:
        case TELEPHONY_ERR_UNREGISTER_CALLBACK_FAIL:
            error.errorCode = JS_ERROR_TELEPHONY_SERVICE_ERROR;
            error.errorMessage = JS_ERROR_TELEPHONY_SERVICE_ERROR_STRING;
            break;
        case TELEPHONY_ERR_FAIL:
        case TELEPHONY_ERR_MEMCPY_FAIL:
        case TELEPHONY_ERR_MEMSET_FAIL:
        case TELEPHONY_ERR_STRCPY_FAIL:
        case TELEPHONY_ERR_LOCAL_PTR_NULL:
        case TELEPHONY_ERR_SUBSCRIBE_BROADCAST_FAIL:
        case TELEPHONY_ERR_ADD_DEATH_RECIPIENT_FAIL:
        case TELEPHONY_ERR_STRTOINT_FAIL:
            error.errorCode = JS_ERROR_TELEPHONY_SYSTEM_ERROR;
            error.errorMessage = JS_ERROR_TELEPHONY_SYSTEM_ERROR_STRING;
            break;
        case TELEPHONY_ERR_NO_SIM_CARD:
            error.errorCode = JS_ERROR_TELEPHONY_NO_SIM_CARD;
            error.errorMessage = JS_ERROR_TELEPHONY_NO_SIM_CARD_STRING;
            break;
        default:
            flag = false;
            break;
    }
    return flag;
}

bool NapiUtil::CreateCallErrorMessageForJs(int32_t errorCode, JsError &error)
{
    if ((errorCode < CALL_ERR_OFFSET || errorCode >= CELLULAR_DATA_ERR_OFFSET)) {
        return false;
    }
    bool flag = true;

    switch (errorCode) {
        case CALL_ERR_INVALID_DIAL_SCENE:
        case CALL_ERR_INVALID_VIDEO_STATE:
        case CALL_ERR_UNKNOW_DIAL_TYPE:
        case CALL_ERR_UNKNOW_CALL_TYPE:
        case CALL_ERR_DIAL_IS_BUSY:
            error.errorCode = JS_ERROR_CALL_DIAL_POLICY_NOT_MET;
            error.errorMessage = JS_ERROR_CALL_DIAL_POLICY_NOT_MET_STRING;
            break;
        case CALL_ERR_NUMBER_OUT_OF_RANGE:
        case CALL_ERR_PHONE_NUMBER_EMPTY:
            error.errorCode = JS_ERROR_CALL_WRONG_MOBILE_NUMBER;
            error.errorMessage = JS_ERROR_CALL_WRONG_MOBILE_NUMBER_STRING;
            break;
        case CALL_ERR_INVALID_CALLID:
        case CALL_ERR_CALL_STATE:
        case CALL_ERR_CALL_IS_NOT_ACTIVATED:
        case CALL_ERR_CALL_IS_NOT_ON_HOLDING:
        case CALL_ERR_ILLEGAL_CALL_OPERATION:
        case CALL_ERR_DIAL_FAILED:
        case CALL_ERR_ANSWER_FAILED:
        case CALL_ERR_REJECT_FAILED:
        case CALL_ERR_HOLD_FAILED:
            error.errorCode = JS_ERROR_CALL_ABNORMAL_CALL_STATUS;
            error.errorMessage = JS_ERROR_CALL_ABNORMAL_CALL_STATUS_STRING;
            break;
        case CALL_ERR_VIDEO_ILLEGAL_MEDIA_TYPE:
        case CALL_ERR_VIDEO_IN_PROGRESS:
        case CALL_ERR_VIDEO_ILLEAGAL_SCENARIO:
        case CALL_ERR_VIDEO_MODE_CHANGE_NOTIFY_FAILED:
            error.errorCode = JS_ERROR_CALL_ABNORMAL_VIDEO_CALL_STATUS;
            error.errorMessage = JS_ERROR_CALL_ABNORMAL_VIDEO_CALL_STATUS_STRING;
            break;
        case CALL_ERR_FUNCTION_NOT_SUPPORTED:
            error.errorCode = JS_ERROR_DEVICE_NOT_SUPPORT_THIS_API;
            error.errorMessage = JS_ERROR_DEVICE_NOT_SUPPORT_THIS_API_STRING;
            break;
        default:
            flag = false;
            break;
    }
    return flag;
}

JsError NapiUtil::ConverErrorMessageWithPermissionForJs(
    int32_t errorCode, const std::string &funcName, const std::string &permission)
{
    if (errorCode == TELEPHONY_ERR_PERMISSION_ERR) {
        JsError error = {};
        error.errorCode = JS_ERROR_TELEPHONY_PERMISSION_DENIED;
        error.errorMessage = "BusinessError 201: Permission denied. An attempt was made to " + funcName +
                             " forbidden by permission: " + permission;
        return error;
    }
    return ConverErrorMessageForJs(errorCode);
}

napi_value NapiUtil::CreateError(napi_env env, int32_t err, const std::string &msg)
{
    napi_value businessError = nullptr;
    napi_value errorCode = nullptr;
    NAPI_CALL(env, napi_create_int32(env, err, &errorCode));
    napi_value errorMessage = nullptr;
    NAPI_CALL(env, napi_create_string_utf8(env, msg.c_str(), NAPI_AUTO_LENGTH, &errorMessage));
    napi_create_error(env, nullptr, errorMessage, &businessError);
    napi_set_named_property(env, businessError, "code", errorCode);
    return businessError;
}

void NapiUtil::ThrowError(napi_env env, int32_t errorCode, const std::string &message)
{
    napi_value error = CreateError(env, errorCode, message);
    napi_throw(env, error);
}
} // namespace Telephony
} // namespace OHOS