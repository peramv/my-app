#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_process_type_must_be_11 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_process_type_must_be_11() { }
		~CIFast_IFast_ifastdbrkr_err_process_type_must_be_11() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PROCESS_TYPE_MUST_BE_11")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("ProcessType must be 11.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verarbeitungsart muss 11 sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de proceso debe ser 11.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de processus doit être 11.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verwerkingstype moet 11 zijn")); }

        // Actions
	};
}



