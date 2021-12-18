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

#ifndef OHOS_CELL_INFORMATION_H
#define OHOS_CELL_INFORMATION_H

#include "parcel.h"

namespace OHOS {
namespace Telephony {
class CellInformation : public Parcelable {
public:
    static const int32_t MAX_CELL_NUM = 10;
    enum class CellType { CELL_TYPE_NONE = 0, CELL_TYPE_GSM, CELL_TYPE_LTE, CELL_TYPE_WCDMA };
    CellInformation() = default;
    virtual ~CellInformation() = default;
    virtual bool Marshalling(Parcel &parcel) const = 0;
    static CellInformation *Unmarshalling(Parcel &parcel);
    virtual bool ReadFromParcel(Parcel &parcel) = 0;
    virtual CellInformation::CellType GetNetworkType() const = 0;
    virtual std::string ToString() const = 0;
    void Init(int32_t mcc, int32_t mnc, int32_t cellId);

    virtual int32_t GetArfcn() const = 0;
    virtual int32_t GetCellId() const;
    virtual int32_t GetMcc() const;
    virtual int32_t GetMnc() const;
    virtual uint64_t GetTimeStamp() const;
    virtual int32_t GetSignalLevel() const;
    virtual bool GetIsCamped() const;
    virtual void SetIsCamped(bool isCamped);
    virtual void SetSignalLevel(int32_t signalLevel);
protected:
    int32_t mcc_ = 0;
    int32_t mnc_ = 0;
    int32_t cellId_ = 0;
    uint64_t timeStamp_ = 0;
    int32_t signalLevel_ = 0;
    bool isCamped_ = false;
};

class GsmCellInformation : public CellInformation {
public:
    GsmCellInformation() = default;
    virtual ~GsmCellInformation() = default;
    bool Marshalling(Parcel &parcel) const override;
    static GsmCellInformation *Unmarshalling(Parcel &parcel);
    bool ReadFromParcel(Parcel &parcel) override;
    CellInformation::CellType GetNetworkType() const override;
    std::string ToString() const override;
    void SetGsmParam(int32_t bsic, int32_t lac, int32_t arfcn);
    void UpdateLocation(int32_t cellId, int32_t lac);
    GsmCellInformation(const GsmCellInformation &gsmCell);
    GsmCellInformation &operator=(const GsmCellInformation &gsmCell);
    bool operator==(const GsmCellInformation &other) const;

    int32_t GetLac() const;
    int32_t GetBsic() const;
    int32_t GetArfcn() const override;
private:
    int32_t bsic_ = 0;
    int32_t lac_ = 0;
    int32_t arfcn_ = 0;
};

class LteCellInformation : public CellInformation {
public:
    LteCellInformation() = default;
    virtual ~LteCellInformation() = default;
    bool Marshalling(Parcel &parcel) const override;
    static LteCellInformation *Unmarshalling(Parcel &parcel);
    bool ReadFromParcel(Parcel &parcel) override;
    CellInformation::CellType GetNetworkType() const override;
    std::string ToString() const override;
    void SetLteParam(int32_t pci, int32_t tac, int32_t arfcn);
    LteCellInformation(const LteCellInformation &lteCell);
    LteCellInformation &operator=(const LteCellInformation &lteCell);
    bool operator==(const LteCellInformation &other) const;
    void UpdateLocation(int32_t cellId, int32_t tac);
    int32_t GetPci() const;
    int32_t GetTac() const;
    int32_t GetArfcn() const override;
private:
    int32_t pci_ = 0;
    int32_t tac_ = 0;
    int32_t earfcn_ = 0;
};

class WcdmaCellInformation : public CellInformation {
public:
    WcdmaCellInformation() = default;
    virtual ~WcdmaCellInformation() = default;
    bool Marshalling(Parcel &parcel) const override;
    static WcdmaCellInformation *Unmarshalling(Parcel &parcel);
    bool ReadFromParcel(Parcel &parcel) override;
    CellInformation::CellType GetNetworkType() const override;
    std::string ToString() const override;
    void SetWcdmaParam(int32_t psc, int32_t lac, int32_t arfcn);
    WcdmaCellInformation(const WcdmaCellInformation &wcdmaCell);
    WcdmaCellInformation &operator=(const WcdmaCellInformation &wcdmaCell);
    bool operator==(const WcdmaCellInformation &other) const;
    void UpdateLocation(int32_t cellId, int32_t lac);
    int32_t GetPsc() const;
    int32_t GetLac() const;
    int32_t GetArfcn() const override;
private:
    int32_t lac_ = 0;
    int32_t psc_ = 0;
    int32_t uarfcn_ = 0;
};
} // namespace Telephony
} // namespace OHOS
#endif // OHOS_CELL_INFORMATION_H