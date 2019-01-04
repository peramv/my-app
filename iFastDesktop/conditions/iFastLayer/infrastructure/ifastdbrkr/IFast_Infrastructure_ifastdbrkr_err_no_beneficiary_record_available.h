#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_no_beneficiary_record_available : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_no_beneficiary_record_available() { }
		~CIFast_Infrastructure_ifastdbrkr_err_no_beneficiary_record_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_BENEFICIARY_RECORD_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Default value used.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Default value used.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Standardwert wurde verwendet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se utilizó el valor predeterminado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Valeur par défaut utilisée")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Standaardwaarde is gebruikt")); }

        // Actions
	};
}



