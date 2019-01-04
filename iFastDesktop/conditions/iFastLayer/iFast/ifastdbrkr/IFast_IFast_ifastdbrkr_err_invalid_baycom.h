#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_baycom : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_baycom() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_baycom() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_BAYCOM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Baycom.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Baycom ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Baycom no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("BayCom invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig Baycom")); }

        // Actions
	};
}



