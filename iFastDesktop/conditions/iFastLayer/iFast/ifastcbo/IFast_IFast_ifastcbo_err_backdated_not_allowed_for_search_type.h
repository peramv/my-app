#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_backdated_not_allowed_for_search_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_backdated_not_allowed_for_search_type() { }
		~CIFast_IFast_ifastcbo_err_backdated_not_allowed_for_search_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BACKDATED_NOT_ALLOWED_FOR_SEARCH_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Backdated is not allowed for Searching with %SEARCH_TYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Antidatage non autorisé pour la recherche de type %SEARCH_TYPE%")); }

        // Actions
	};
}



