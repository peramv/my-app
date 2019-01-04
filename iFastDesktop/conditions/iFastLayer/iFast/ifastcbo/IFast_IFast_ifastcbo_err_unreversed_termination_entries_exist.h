#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_unreversed_termination_entries_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_unreversed_termination_entries_exist() { }
		~CIFast_IFast_ifastcbo_err_unreversed_termination_entries_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNREVERSED_TERMINATION_ENTRIES_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unreversed Termination Entries exist that may need to be reversed and reprocessed.")); }		
		virtual DString GetMessage_FR_CA() const { return DString(I_("Des entrées de résiliation non contrepassées existent et doivent être contrepassées puis traitées à nouveau.")); }

        // Actions
	};
}



