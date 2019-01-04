#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_full_redemption_not_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_full_redemption_not_allow() { }
		~CIFast_IFast_ifastcbo_err_full_redemption_not_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FULL_REDEMPTION_NOT_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Full redemption is not allowed. LipTaxByJuris table was not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Full redemption is not allowed. LipTaxByJuris table was not found.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Full redemption is not allowed. LipTaxByJuris table was not found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Rachat total non autorisé. La table d'imposition selon la juridiction de la police d'assurance vie est introuvable.")); }

        // Actions
	};
}



