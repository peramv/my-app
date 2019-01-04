#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_batch_does_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_batch_does_not_exist() { }
		~CIFast_IFast_ifastdbrkr_err_batch_does_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BATCH_DOES_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batch does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batch existiert NICHT.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El lote NO existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Lot inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Batch bestaat NIET")); }

        // Actions
	};
}



