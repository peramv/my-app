#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sales_rep_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sales_rep_empty() { }
		~CIFast_IFast_ifastcbo_err_sales_rep_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SALES_REP_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sales representative cannot be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone Responsable doit être renseignee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verkaufsvertreter darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El representante de ventas no puede estar en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Représentant des ventes doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vertegenwoordiger kan niet leeg zijn")); }

        // Actions
	};
}



