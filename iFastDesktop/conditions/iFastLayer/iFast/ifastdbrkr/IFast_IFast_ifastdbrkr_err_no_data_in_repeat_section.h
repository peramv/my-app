#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_data_in_repeat_section : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_data_in_repeat_section() { }
		~CIFast_IFast_ifastdbrkr_err_no_data_in_repeat_section() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_DATA_IN_REPEAT_SECTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No data provided in repeating section.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No data provided in repeating section.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No data provided in repeating section.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune donnée n'a été saisie dans la section de répétition.")); }

        // Actions
	};
}



