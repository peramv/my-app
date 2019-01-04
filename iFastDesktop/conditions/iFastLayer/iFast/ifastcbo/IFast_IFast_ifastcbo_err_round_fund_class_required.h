#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_round_fund_class_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_round_fund_class_required() { }
		~CIFast_IFast_ifastcbo_err_round_fund_class_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ROUND_FUND_CLASS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Rounding Fund/Class value are required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Rounding Fund/Class value are required.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Rounding Fund/Class value are required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur du fonds/de la classe d'arrondissement est requise.")); }

        // Actions
	};
}



