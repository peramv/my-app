#pragma once

#include "ConditionObject.h"

namespace CND
{
    class CIFast_IFast_ifastcbo_err_tr_out_must_be_cancelled : public CConditionObject
    {
    public:
        CIFast_IFast_ifastcbo_err_tr_out_must_be_cancelled() { }
        ~CIFast_IFast_ifastcbo_err_tr_out_must_be_cancelled() { }

    public:
        // General
        virtual DString GetConditionName() const { return DString(I_("ERR_TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION")); }
        virtual DString GetGroupName() const { return DString(I_("iFast")); }
        virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
        virtual int GetSeverity() const { return 6; }

        // Messages
        virtual DString GetMessage_EN_US() const { return DString(I_("Transfer-out transaction must be cancelled prior to this operation.")); }
        virtual DString GetMessage_DE_DE() const { return DString(I_("Transfer-out transaction must be cancelled prior to this operation.")); }
        virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction de transfert sortant doit être annulée préalablement à cette opération.")); }

        // Actions
    };
}



