#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_search_for_slsrep_by_broker_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_search_for_slsrep_by_broker_code() { }
		~CIFast_IFast_ifastdbrkr_err_search_for_slsrep_by_broker_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SEARCH_FOR_SLSREP_BY_BROKER_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Search for sales representative by broker code not supported.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La recherche de responsables par code de courtier n'est pas prise en charge.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Suche nach Verkaufsvertreter durch Brokercode wird nicht unterstützt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no soporta la búsqueda del representante de ventas por código de corredor.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La recherche d'un représentant des ventes par code de courtier n'est pas supportée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Zoeken naar vertegenwoordiger op makelaarscode wordt niet ondersteund")); }

        // Actions
	};
}



