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

#ifndef OHOS_SIM_MANAGER_H
#define OHOS_SIM_MANAGER_H

#include "event_handler.h"
#include "i_sim_manager.h"
#include "i_tel_ril_manager.h"
#include "sim_state_manager.h"
#include "sim_file_manager.h"
#include "sim_sms_manager.h"
#include "sim_account_manager.h"
#include "icc_dialling_numbers_manager.h"
#include "stk_manager.h"

namespace OHOS {
namespace Telephony {
const int32_t SLOT_ID_ZERO = 0;
class SimManager : public ISimManager {
public:
    SimManager(std::shared_ptr<ITelRilManager> telRilManager);
    virtual ~SimManager();
    // Init
    virtual bool OnInit(int32_t slotCount) override;
    virtual void SetNetworkSearchManager(int32_t slotCount,
            std::shared_ptr<INetworkSearch> networkSearchManager) override;
    // SimState
    virtual bool HasSimCard(int32_t slotId) override;
    virtual int32_t GetSimState(int32_t slotId) override;
    virtual int32_t GetCardType(int32_t slotId) override;
    virtual bool UnlockPin(int32_t slotId, std::string pin, LockStatusResponse &response) override;
    virtual bool UnlockPuk(
        int32_t slotId, std::string newPin, std::string puk, LockStatusResponse &response) override;
    virtual bool AlterPin(
        int32_t slotId, std::string newPin, std::string oldPin, LockStatusResponse &response) override;
    virtual bool SetLockState(int32_t slotId, const LockInfo &options, LockStatusResponse &response) override;
    virtual int32_t GetLockState(int32_t slotId, LockType lockType) override;
    virtual int32_t RefreshSimState(int32_t slotId) override;
    virtual bool UnlockPin2(int32_t slotId, std::string pin2, LockStatusResponse &response) override;
    virtual bool UnlockPuk2(
        int32_t slotId, std::string newPin2, std::string puk2, LockStatusResponse &response) override;
    virtual bool AlterPin2(
        int32_t slotId, std::string newPin2, std::string oldPin2, LockStatusResponse &response) override;
    virtual bool UnlockSimLock(int32_t slotId, const PersoLockInfo &lockInfo, LockStatusResponse &response) override;
    // SimAccount
    virtual bool IsSimActive(int32_t slotId) override;
    virtual bool SetActiveSim(int32_t slotId, int32_t enable) override;
    virtual bool GetSimAccountInfo(int32_t slotId, IccAccountInfo &info) override;
    virtual bool SetDefaultVoiceSlotId(int32_t slotId) override;
    virtual bool SetDefaultSmsSlotId(int32_t slotId) override;
    virtual bool SetDefaultCellularDataSlotId(int32_t slotId) override;
    virtual bool SetPrimarySlotId(int32_t slotId) override;
    virtual bool SetShowNumber(int32_t slotId, const std::u16string number) override;
    virtual bool SetShowName(int32_t slotId, const std::u16string name) override;
    virtual int32_t GetDefaultVoiceSlotId() override;
    virtual int32_t GetDefaultSmsSlotId() override;
    virtual int32_t GetDefaultCellularDataSlotId() override;
    virtual int32_t GetPrimarySlotId() override;
    virtual std::u16string GetShowNumber(int32_t slotId) override;
    virtual std::u16string GetShowName(int32_t slotId) override;
    virtual bool GetActiveSimAccountInfoList(std::vector<IccAccountInfo> &iccAccountInfoList) override;
    virtual bool GetOperatorConfigs(int slotId, OperatorConfig &poc) override;
    virtual bool HasOperatorPrivileges(const int32_t slotId) override;
    // STK
    virtual bool SendEnvelopeCmd(int32_t slotId, const std::string &cmd) override;
    virtual bool SendTerminalResponseCmd(int32_t slotId, const std::string &cmd) override;
    // SimFile
    virtual std::u16string GetSimOperatorNumeric(int32_t slotId) override;
    virtual std::u16string GetISOCountryCodeForSim(int32_t slotId) override;
    virtual std::u16string GetSimSpn(int32_t slotId) override;
    virtual std::u16string GetSimIccId(int32_t slotId) override;
    virtual std::u16string GetIMSI(int32_t slotId) override;
    virtual std::u16string GetLocaleFromDefaultSim(int32_t slotId) override;
    virtual std::u16string GetSimGid1(int32_t slotId) override;
    virtual std::u16string GetSimTelephoneNumber(int32_t slotId) override;
    virtual std::u16string GetSimTeleNumberIdentifier(const int32_t slotId) override;
    virtual std::u16string GetVoiceMailIdentifier(int32_t slotId) override;
    virtual std::u16string GetVoiceMailNumber(int32_t slotId) override;
    virtual int ObtainSpnCondition(int32_t slotId, bool roaming, std::string operatorNum) override;
    virtual bool SetVoiceMailInfo(
        int32_t slotId, const std::u16string &mailName, const std::u16string &mailNumber) override;
    // SimSms
    virtual bool AddSmsToIcc(int32_t slotId, int status, std::string &pdu, std::string &smsc) override;
    virtual bool UpdateSmsIcc(
        int32_t slotId, int index, int status, std::string &pduData, std::string &smsc) override;
    virtual bool DelSmsIcc(int32_t slotId, int index) override;
    virtual std::vector<std::string> ObtainAllSmsOfIcc(int32_t slotId) override;
    // IccDiallingNumbers
    virtual std::vector<std::shared_ptr<DiallingNumbersInfo>> QueryIccDiallingNumbers(int slotId, int type) override;
    virtual bool AddIccDiallingNumbers(
        int slotId, int type, const std::shared_ptr<DiallingNumbersInfo> &diallingNumber) override;
    virtual bool DelIccDiallingNumbers(
        int slotId, int type, const std::shared_ptr<DiallingNumbersInfo> &diallingNumber) override;
    virtual bool UpdateIccDiallingNumbers(
        int slotId, int type, const std::shared_ptr<DiallingNumbersInfo> &diallingNumber) override;
    // Event register
    virtual void RegisterCoreNotify(int32_t slotId, const HANDLE &handler, int what) override;
    virtual void UnRegisterCoreNotify(int32_t slotId, const HANDLE &observerCallBack, int what) override;
private:
    bool IsValidSlotId(int32_t slotId);
private:
    std::shared_ptr<Telephony::ITelRilManager> telRilManager_ = nullptr;
    std::vector<std::shared_ptr<Telephony::SimStateManager>> simStateManager_;
    std::vector<std::shared_ptr<Telephony::SimFileManager>> simFileManager_;
    std::vector<std::shared_ptr<Telephony::SimSmsManager>> simSmsManager_;
    std::vector<std::shared_ptr<Telephony::SimAccountManager>> simAccountManager_;
    std::vector<std::shared_ptr<Telephony::IccDiallingNumbersManager>> iccDiallingNumbersManager_;
    std::vector<std::shared_ptr<Telephony::StkManager>> stkManager_;
    int32_t slotCount_ = SLOT_ID_ZERO;
};
} // namespace Telephony
} // namespace OHOS
#endif // OHOS_SIM_MANAGER_H
