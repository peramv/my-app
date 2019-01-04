#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_rb_default_allocation_not_set_up : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_rb_default_allocation_not_set_up() { }
		~CIFast_IFast_ifastdbrkr_err_rb_default_allocation_not_set_up() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RB_DEFAULT_ALLOCATION_NOT_SET_UP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RB default allocations not set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RB-Standard-Zuweisungen nicht erstellt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se han configurado las asignaciones predeterminadas RB")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les répartitions de rebalancement par défaut ne sont pas réglées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Standaardallocaties RB zijn niet ingesteld")); }

        // Actions
	};
}



