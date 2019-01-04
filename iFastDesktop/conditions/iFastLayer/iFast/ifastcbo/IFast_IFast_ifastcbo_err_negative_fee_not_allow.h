#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_negative_fee_not_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_negative_fee_not_allow() { }
		~CIFast_IFast_ifastcbo_err_negative_fee_not_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEGATIVE_FEE_NOT_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Negative fee is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Negative Provision ist nicht erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite una comisión negativa")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais négatifs ne sont pas autorisés.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Negatieve kosten zijn niet toegestaan")); }

        // Actions
	};
}



