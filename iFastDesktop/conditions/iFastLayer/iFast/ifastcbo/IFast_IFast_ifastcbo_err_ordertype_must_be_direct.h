#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ordertype_must_be_direct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ordertype_must_be_direct() { }
		~CIFast_IFast_ifastcbo_err_ordertype_must_be_direct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ORDERTYPE_MUST_BE_DIRECT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Order type must be direct.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bestellart muss direkt sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de orden debe ser directo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'ordre doit être Direct.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ordertype moet direct zijn")); }

        // Actions
	};
}



