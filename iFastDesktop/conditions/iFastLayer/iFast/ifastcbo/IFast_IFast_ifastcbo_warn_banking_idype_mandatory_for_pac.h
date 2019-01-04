#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_banking_idype_mandatory_for_pac : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_banking_idype_mandatory_for_pac() { }
		~CIFast_IFast_ifastcbo_warn_banking_idype_mandatory_for_pac() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BANKING_IDYPE_MANDATORY_FOR_PAC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("PAC setup using %FILE_PROC% requires banking instructions of ID Type %IDTYPE%  for collection.")); }

        // Actions
	};
}



