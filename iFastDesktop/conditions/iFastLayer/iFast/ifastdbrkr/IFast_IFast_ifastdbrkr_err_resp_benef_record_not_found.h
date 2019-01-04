#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_resp_benef_record_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_resp_benef_record_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_resp_benef_record_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_BENEF_RECORD_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESPBenefInfo record not found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement d'information sur le bénéficiaire REEE est introuvable.")); }

        // Actions
	};
}



