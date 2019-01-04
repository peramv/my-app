#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_no_related_chui_functions : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_no_related_chui_functions() { }
		~CIFast_Infrastructure_ifastdbrkr_err_no_related_chui_functions() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_RELATED_CHUI_FUNCTIONS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this cumulative discount number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this cumulative discount number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Kumulativ-Diskontnummer nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este número de descuento acumulativo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce numéro d'escompte cumulatif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent dit cumulatieve kortingsnummer niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify cumulative discount number and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify cumulative discount number and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Kumulativ-Diskontnummer und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify cumulative discount number and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le numéro d'escompte cumulatif et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het cumulatieve kortingsnummer en voer dit opnieuw in")); }
	};
}



