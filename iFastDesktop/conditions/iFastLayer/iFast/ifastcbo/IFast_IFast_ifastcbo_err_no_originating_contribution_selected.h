#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_originating_contribution_selected : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_originating_contribution_selected() { }
		~CIFast_IFast_ifastcbo_err_no_originating_contribution_selected() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ORIGINATING_CONTRIBUTION_SELECTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No originating contribution selected.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune cotisation d'origine sélectionnée")); }

        // Actions
	};
}



