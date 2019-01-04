#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_persist_request : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_persist_request() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_persist_request() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_PERSIST_REQUEST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Persistent Request was made with no Persistent Scope")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une demande de suivi a été faite sans délimitation de suivi.")); }

        // Actions
	};
}



