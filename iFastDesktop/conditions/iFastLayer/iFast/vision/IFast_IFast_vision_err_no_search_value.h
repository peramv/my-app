#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_vision_err_no_search_value : public CConditionObject
	{
	public:
		CIFast_IFast_vision_err_no_search_value() { }
		~CIFast_IFast_vision_err_no_search_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_SEARCH_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The search request doesn't have a value for search")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The search request doesn't have a value for search")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Suchanfrage hat keinen Suchwert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La solicitud de búsqueda no tiene un valor para la búsqueda")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande de recherche ne contient aucune valeur de recherche.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De zoekopdracht bevat geen waarde voor het zoeken")); }

        // Actions
	};
}



