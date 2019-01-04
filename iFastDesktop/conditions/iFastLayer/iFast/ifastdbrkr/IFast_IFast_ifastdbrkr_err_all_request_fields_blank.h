#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_all_request_fields_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_all_request_fields_blank() { }
		~CIFast_IFast_ifastdbrkr_err_all_request_fields_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ALL_REQUEST_FIELDS_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Input parameters cannot be all blank")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Input parameters cannot be all blank")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs des paramètres saisis ne peuvent être tous vides.")); }

        // Actions
	};
}



