#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_exist_as_bad : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_exist_as_bad() { }
		~CIFast_IFast_ifastdbrkr_err_exist_as_bad() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXIST_AS_BAD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exists as a bad record - Modification only allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Exists as a bad record - Modification only allowed.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Exists as a bad record - Modification only allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un enregistrement Mauvais existe – modification autorisée uniquement.")); }

        // Actions
	};
}



