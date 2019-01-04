#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_more_than_one_match_the_search_criteria : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_more_than_one_match_the_search_criteria() { }
		~CIFast_IFast_ifastdbrkr_err_more_than_one_match_the_search_criteria() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MORE_THAN_ONE_MATCH_THE_SEARCH_CRITERIA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("More than 1 account match the search criteria.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehr als ein Konto entspricht den Suchkriterien.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Más de una cuenta coincide con los criterios de búsqueda.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plus d'un compte correspond au critère de recherche.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn meerdere accounts die aan de zoekcriteria voldoen")); }

        // Actions
	};
}



