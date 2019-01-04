#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_batches_not_match : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_batches_not_match() { }
		~CIFast_IFast_ifastdbrkr_err_batches_not_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BATCHES_NOT_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batches do not match.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Batches do not match.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batches stimmen nicht überein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los lotes no coinciden")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les lots ne correspondent pas.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Batches komen niet overeen")); }

        // Actions
	};
}



