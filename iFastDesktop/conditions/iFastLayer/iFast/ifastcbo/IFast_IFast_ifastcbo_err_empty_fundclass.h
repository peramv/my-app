#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_empty_fundclass : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_empty_fundclass() { }
		~CIFast_IFast_ifastcbo_err_empty_fundclass() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EMPTY_FUNDCLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Code and Class Code can not be empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund Code and Class Code can not be empty.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund Code and Class Code can not be empty.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de fonds et le code de classe sont requis.")); }

        // Actions
	};
}



