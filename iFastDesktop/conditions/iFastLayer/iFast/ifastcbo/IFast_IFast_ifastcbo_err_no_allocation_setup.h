#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_allocation_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_allocation_setup() { }
		~CIFast_IFast_ifastcbo_err_no_allocation_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ALLOCATION_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one allocation item has to be set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens ein Zuweisungselement muss erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse al menos un elemento de asignación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins un élément de répartition doit être réglé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet ten minste één allocatie-item zijn ingesteld")); }

        // Actions
	};
}



