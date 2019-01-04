#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_benef_reason_must_be_current_benef_for_new_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_benef_reason_must_be_current_benef_for_new_entity() { }
		~CIFast_IFast_ifastcbo_err_resp_benef_reason_must_be_current_benef_for_new_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_BENEF_REASON_MUST_BE_CURRENT_BENEF_FOR_NEW_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reason must be Current Beneficiary when creating RESP Beneficiary Entity.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Reason must be Current Beneficiary when creating RESP Beneficiary Entity.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Reason must be Current Beneficiary when creating RESP Beneficiary Entity.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La raison doit être Bénéficiaire actuel lors de la création de l'entité bénéficiaire REEE.")); }

        // Actions
	};
}



