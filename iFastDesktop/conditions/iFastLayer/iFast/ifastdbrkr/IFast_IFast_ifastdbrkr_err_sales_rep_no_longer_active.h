#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_sales_rep_no_longer_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_sales_rep_no_longer_active() { }
		~CIFast_IFast_ifastdbrkr_err_sales_rep_no_longer_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SALES_REP_NO_LONGER_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sales Representative is no longer active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verkaufsvertreter ist nicht mehr aktiv")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El representante de ventas ya no está activo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le représentant des ventes n'est plus actif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vertegenwoordiger is niet langer actief")); }

        // Actions
	};
}



