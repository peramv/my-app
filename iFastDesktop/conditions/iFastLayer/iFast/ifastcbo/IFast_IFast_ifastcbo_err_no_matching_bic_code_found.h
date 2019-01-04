#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_matching_bic_code_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_matching_bic_code_found() { }
		~CIFast_IFast_ifastcbo_err_no_matching_bic_code_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_MATCHING_BIC_CODE_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No matching BIC code found for the participant id value  (%PID%).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No matching BIC code found for the participant id value  (%PID%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun code BIC correspondant n'a été trouvé pour la valeur du code du participant (%PID%).")); }

        // Actions
	};
}



