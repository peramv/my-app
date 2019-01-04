#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_resp_record_locked : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_resp_record_locked() { }
		~CIFast_IFast_ifastdbrkr_err_resp_record_locked() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_RECORD_LOCKED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESPContrDetl record is locked. Try later.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement des détails de cotisation REEE est verrouillé. Réessayez plus tard.")); }

        // Actions
	};
}



