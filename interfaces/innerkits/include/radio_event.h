/*
 * Copyright (C) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef RADIO_EVENT_H
#define RADIO_EVENT_H
enum RadioEvent {
    // modem
    RADIO_STATE_CHANGED = 0,
    RADIO_GET_STATUS,
    RADIO_SET_STATUS,
    RADIO_GET_VOICE_TECH,
    RADIO_VOICE_TECH_CHANGED,

    RADIO_POWER,
    RADIO_ON,
    RADIO_AVAIL,
    RADIO_OFF,
    RADIO_NOT_AVAIL,
    RADIO_DATA_CALL_LIST_CHANGED,
    RADIO_IMS_NETWORK_STATE_CHANGED,
    RADIO_ICC_STATUS_CHANGED,
    RADIO_CONNECTED,
    RADIO_ICC_REFRESH,
    RADIO_PCODATA,
    RADIO_GSM_SMS,
    RADIO_CDMA_SMS,
    RADIO_CALL_STATUS_INFO,
    RADIO_CALL_USSD_NOTICE,
    RADIO_CALL_SS_NOTICE,
    RADIO_CALL_RINGBACK_VOICE,
    RADIO_CALL_SRVCC_STATUS,
    RADIO_CALL_EMERGENCY_NUMBER_REPORT,

    RADIO_SMS_ON_SIM,
    RADIO_SMS_STATUS,
    RADIO_RESTRICTED_STATE,
    RADIO_CELL_BROADCAST,
    RADIO_CDMA_CELL_BROADCAST,
    RADIO_RIL_SETUP_DATA_CALL,
    RADIO_RIL_DEACTIVATE_DATA_CALL,

    // cellular call
    RADIO_DIAL = 101,
    RADIO_REJECT_CALL,
    RADIO_HANGUP_CONNECT,
    RADIO_ACCEPT_CALL,
    RADIO_CURRENT_CALLS,
    RADIO_HOLD_CALL,
    RADIO_ACTIVE_CALL,
    RADIO_SWAP_CALL,
    RADIO_JOIN_CALL,
    RADIO_SPLIT_CALL,
    RADIO_CALL_SUPPLEMENT,
    RADIO_GET_CALL_WAIT,
    RADIO_SET_CALL_WAIT,
    RADIO_GET_CALL_FORWARD,
    RADIO_SET_CALL_FORWARD,
    RADIO_GET_CALL_CLIP,
    RADIO_SET_CALL_CLIP,
    RADIO_GET_CALL_CLIR,
    RADIO_SET_CALL_CLIR,
    RADIO_GET_CALL_RESTRICTION,
    RADIO_SET_CALL_RESTRICTION,
    RADIO_SEND_DTMF,
    RADIO_START_DTMF,
    RADIO_STOP_DTMF,
    RADIO_SET_CALL_PREFERENCE_MODE,
    RADIO_GET_CALL_PREFERENCE_MODE,
    RADIO_SET_IMS_SWITCH_STATUS,
    RADIO_GET_IMS_SWITCH_STATUS,
    RADIO_SET_USSD,
    RADIO_GET_USSD,
    RADIO_SET_CMUT,
    RADIO_GET_CMUT,
    RADIO_GET_EMERGENCY_CALL_LIST,
    RADIO_SET_EMERGENCY_CALL_LIST,
    RADIO_GET_CALL_FAIL_REASON,

    // Ims sms
    RADIO_SEND_IMS_GSM_SMS = 201,
    RADIO_SEND_SMS,
    RADIO_SEND_CDMA_SMS,
    RADIO_STORAGE_SMS,
    RADIO_DELETE_SMS,
    RADIO_SEND_SMS_EXPECT_MORE,
    RADIO_ADD_CDMA_SMS,
    RADIO_DEL_CDMA_SMS,
    RADIO_UPDATE_CDMA_SMS,
    RADIO_SET_IMS_SMS,
    RADIO_GET_IMS_SMS,

    // Network Search
    RADIO_NETWORK_STATE = 301,
    RADIO_VOICE_REG_STATE,
    RADIO_DATA_REG_STATE,
    RADIO_OPERATOR,
    RADIO_GET_SIGNAL_STRENGTH,
    RADIO_SIGNAL_STRENGTH_UPDATE,
    RADIO_NETWORK_SEARCH_RESULT,
    RADIO_GET_NETWORK_SELECTION_MODE,
    RADIO_SET_NETWORK_SELECTION_MODE,
    RADIO_GET_NEIGHBORING_CELL_INFO,
    RADIO_GET_CURRENT_CELL_INFO,
    RADIO_NETWORK_TIME_UPDATE,
    RADIO_NETWORK_TIME_ZONE_UPDATE,
    RADIO_SET_PREFERRED_NETWORK_MODE,
    RADIO_GET_PREFERRED_NETWORK_MODE,
    RADIO_NITZ_UPDATE,
    RADIO_GET_IMS_REG_STATUS,
    RADIO_GET_IMEI,
    RADIO_SET_PS_ATTACH_STATUS,
    RADIO_GET_MEID,
    RADIO_GET_RADIO_CAPABILITY,
    RADIO_SET_RADIO_CAPABILITY,
    RADIO_CHANNEL_CONFIG_UPDATE,
    RADIO_SET_LOCATION_UPDATE,
    RADIO_CURRENT_CELL_UPDATE,
    RADIO_SET_DATA_CONNECT_ACTIVE,
    RADIO_SET_DEVICE_STATE,
    RADIO_SET_NOTIFICATION_FILTER,

    // module internal events
    RADIO_PS_CONNECTION_ATTACHED = 401,
    RADIO_PS_CONNECTION_DETACHED,
    RADIO_IMS_REG_STATUS_UPDATE,
    RADIO_NR_STATE_CHANGED,
    RADIO_NR_FREQUENCY_CHANGED,
    RADIO_PS_RAT_CHANGED,
    RADIO_PS_ROAMING_OPEN,
    RADIO_PS_ROAMING_CLOSE,
    RADIO_EMERGENCY_STATE_OPEN,
    RADIO_EMERGENCY_STATE_CLOSE,

    // SIM
    RADIO_SIM_GET_STATUS = 501,
    RADIO_SIM_IO,
    RADIO_SIM_GET_IMSI,
    RADIO_SIM_GET_ICCID,
    RADIO_SIM_GET_LOCK_STATUS,
    RADIO_SIM_SET_LOCK,
    RADIO_SIM_CHANGE_PASSWD,
    RADIO_SIM_ENTER_PIN,
    RADIO_SIM_UNLOCK_PIN,
    RADIO_SIM_PIN_INPUT_TIMES,
    RADIO_SIM_ENTER_PIN2,
    RADIO_SIM_UNLOCK_PIN2,
    RADIO_SIM_PIN2_INPUT_TIMES,
    RADIO_SIM_CARD_ENABLED,
    RADIO_SIM_STATE_CHANGE,
    RADIO_SIM_STATE_READY,
    RADIO_SIM_STATE_LOCKED,
    RADIO_SIM_STATE_SIMLOCK,
    RADIO_IMSI_LOADED_READY,
    RADIO_SIM_RECORDS_LOADED,
    RADIO_SIM_ACCOUNT_LOADED,

    // STK
    RADIO_STK_SESSION_END,
    RADIO_STK_PROACTIVE_COMMAND,
    RADIO_STK_ALPHA_NOTIFY,
    RADIO_STK_EVENT_NOTIFY,
    RADIO_STK_CALL_SETUP,
    RADIO_STK_SEND_TERMINAL_RESPONSE,
    RADIO_STK_SEND_ENVELOPE,
    RADIO_STK_SEND_CALL_SETUP_REQUEST_RESULT,
    RADIO_STK_IS_READY,

    RADIO_UPDATE_SMS,
    RADIO_SET_SMS_CENTER_ADDRESS,
    RADIO_GET_SMS_CENTER_ADDRESS,
    RADIO_SET_CELL_BROADCAST,
    RADIO_SET_CDMA_CELL_BROADCAST,
    RADIO_GET_CELL_BROADCAST,
    RADIO_GET_CDMA_CELL_BROADCAST,
    RADIO_ACTIVE_CDMA_CELL_BROADCAST,

    // Card
    RADIO_CARD_TYPE_CHANGE,

    // IMS core service
    RADIO_IMS_SERVICE_STATUS_UPDATE = 1000,
    RADIO_IMS_REGISTER_STATE_UPDATE,

    // IMS call
    RADIO_IMS_CALL_STATUS_INFO,
    RADIO_IMS_GET_CALL_DATA,

    // IMS supplement
    RADIO_IMS_SET_CLIP,
    RADIO_IMS_SET_COLR,
    RADIO_IMS_GET_COLR,
    RADIO_IMS_SET_COLP,
    RADIO_IMS_GET_COLP,
};
#endif // RADIO_EVENT_H
