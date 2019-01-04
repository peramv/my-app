#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_alloc_for_acct_type06 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_alloc_for_acct_type06() { }
		~CIFast_IFast_ifastcbo_err_alloc_for_acct_type06() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ALLOC_FOR_ACCT_TYPE06")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Default allocations may not be set up for an Omnibus account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Default allocations may not be set up for an Omnibus account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Standard-Zuweisungen können für ein Gemeinschaftskonto nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No pueden configurarse asignaciones predeterminadas para una cuenta Omnibus.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les répartitions par défaut ne peuvent être réglées pour un compte omnibus.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Standaardallocaties mogen niet worden ingesteld voor een verzamelaccount")); }

        // Actions
	};
}



