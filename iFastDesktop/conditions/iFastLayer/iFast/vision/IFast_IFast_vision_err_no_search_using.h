#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_vision_err_no_search_using : public CConditionObject
	{
	public:
		CIFast_IFast_vision_err_no_search_using() { }
		~CIFast_IFast_vision_err_no_search_using() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_SEARCH_USING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The search request doesn't have the using criteria")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Au moins une zone doit être renseignée pour exécuter une recherche de client")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Suchanfrage hat keine Benutzungskriterien.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La solicitud de búsqueda no tiene los criterios de uso")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande de recherche n'a aucun critère d'utilisation.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De zoekopdracht bevat het gebruikscriterium niet")); }

        // Actions
	};
}



