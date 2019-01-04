#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_unit_purchase_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_unit_purchase_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_unit_purchase_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNIT_PURCHASE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Purchases in units are not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Käufe in Anteilen nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten las compras en unidades.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Achats en unités non autorisés")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aankopen in eenheid zijn niet toegestaan")); }

        // Actions
	};
}



