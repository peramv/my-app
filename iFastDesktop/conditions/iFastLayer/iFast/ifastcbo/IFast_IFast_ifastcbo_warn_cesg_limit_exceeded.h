#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_cesg_limit_exceeded : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_cesg_limit_exceeded() { }
		~CIFast_IFast_ifastcbo_warn_cesg_limit_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CESG_LIMIT_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("CESG limit of %WARNPARM14% has been exceeded.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La limite SCEE de %WARNPARM14% a été excédée.")); }

        // Actions
	};
}



