#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_rts_ifast_not_responding : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_rts_ifast_not_responding() { }
		~CIFast_IFast_ifastdbrkr_err_rts_ifast_not_responding() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RTS_IFAST_NOT_RESPONDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("iFast is not responding.  Please contact the service desk.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("iFAST ne répond pas. Veuillez communiquer avec le centre de services.")); }

        // Actions
	};
}



