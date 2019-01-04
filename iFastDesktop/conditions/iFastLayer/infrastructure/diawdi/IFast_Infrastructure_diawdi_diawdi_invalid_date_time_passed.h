#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_diawdi_diawdi_invalid_date_time_passed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_diawdi_diawdi_invalid_date_time_passed() { }
		~CIFast_Infrastructure_diawdi_diawdi_invalid_date_time_passed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_INVALID_DATE_TIME_PASSED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.\nAn invalid date-time was used")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.\nAn invalid date-time was used")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.\nEine ungültige Datums-Zeit wurde verwendet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.\n Se utilizó una fecha no válida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. \nUne date/heure invalide a été utilisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. \nEr is een ongeldige datum/tijd gebruikt")); }

        // Actions
	};
}



