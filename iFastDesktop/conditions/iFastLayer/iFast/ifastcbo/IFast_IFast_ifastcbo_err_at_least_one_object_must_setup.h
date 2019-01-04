#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_at_least_one_object_must_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_at_least_one_object_must_setup() { }
		~CIFast_IFast_ifastcbo_err_at_least_one_object_must_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AT_LEAST_ONE_OBJECT_MUST_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one where used record has to be set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("At least one where used record has to be set up.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins un enregistrement de contrats associés doit être réglé.")); }

        // Actions
	};
}



