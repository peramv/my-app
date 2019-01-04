#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_no_alloc_systematic_on_clan_plan : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_no_alloc_systematic_on_clan_plan() { }
		~CIFast_Infrastructure_ifastcbo_err_no_alloc_systematic_on_clan_plan() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ALLOC_SYSTEMATIC_ON_CLAN_PLAN")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Number specified, %INDEX%, is out of range.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Number specified, '^', is out of range.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die festgelegte Anzahl %INDEX% liegt außerhalb des Bereichs.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número especificado, %INDEX%, está fuera de rango.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro spécifié, %INDEX%, est hors plage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Opgegeven nummer, %INDEX%, ligt buiten het bereik")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Make sure the number is correct.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Make sure the number is correct.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Vergewissern Sie sich, dass es sich um die richtige Nummer handelt.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Make sure the number is correct.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Assurez-vous que le numéro est exact.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Zorg ervoor dat het juiste nummer is gebruikt")); }
	};
}



