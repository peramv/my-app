#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_mkt_index_entry : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_mkt_index_entry() { }
		~CIFast_IFast_ifastcbo_err_duplicate_mkt_index_entry() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_MKT_INDEX_ENTRY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate Index Entry.  (%CODE%, %DATE%).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Duplicate Index Entry.  (%CODE%, %DATE%).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Duplicate Index Entry.  (%CODE%, %DATE%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Copie de saisie d'indexation (%CODE%, %DATE%)")); }

        // Actions
	};
}



