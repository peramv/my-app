#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_resp_benef_record_version_not_match : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_resp_benef_record_version_not_match() { }
		~CIFast_IFast_ifastdbrkr_err_resp_benef_record_version_not_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_BENEF_RECORD_VERSION_NOT_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to update record, RESPBenefInfo records do not match.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de mettre à jour l'enregistrement, les enregistrement d'information sur le bénéficiaire REEE ne correspondent pas.")); }

        // Actions
	};
}



