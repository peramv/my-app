#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawd23_diawd23_update_awdobj_fail : public CConditionObject
	{
	public:
		CIFast_IFast_diawd23_diawd23_update_awdobj_fail() { }
		~CIFast_IFast_diawd23_diawd23_update_awdobj_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_UPDATE_AWDOBJ_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The search request doesn't have a search criteria")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Au moins un champ doit être rempli pour exécuter une recherche de client.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Suchanfrage hat keine Suchkriterien.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La solicitud de búsqueda no tiene un criterio de búsqueda")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande de recherche n'a aucun critère de recherche.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De zoekopdracht bevat geen zoekcriteria")); }

        // Actions
	};
}



