#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_sales_rep_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_sales_rep_exists() { }
		~CIFast_IFast_ifastcbo_err_no_sales_rep_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_SALES_REP_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sales Representative entered does not exist. Create now?")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Sales Representative entered does not exist. Create now?")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verkaufsvertreter existiert nicht. Jetzt erstellen?")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El representante de ventas introducido no existe. ¿Desea crearlo ahora?")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le représentant des ventes saisi n'existe pas. Voulez-vous le créer maintenant?")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingevoerde vertegenwoordiger bestaat niet. Maken?")); }

        // Actions
	};
}



