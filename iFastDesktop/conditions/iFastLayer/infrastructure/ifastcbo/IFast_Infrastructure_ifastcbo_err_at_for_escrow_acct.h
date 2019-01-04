#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_at_for_escrow_acct : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_at_for_escrow_acct() { }
		~CIFast_Infrastructure_ifastcbo_err_at_for_escrow_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AT_FOR_ESCROW_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid field type, %FIELD%, expecting %TYPE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid field type, '^', expecting '^'.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Feldtyp bei %FIELD%, erwartet wird %TYPE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de campo no válido, %FIELD%, se esperaba %TYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de champ invalide : %FIELD%, type escompté : %TYPE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig veldtype, %FIELD%, verwacht %TYPE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Make sure the correct type is used.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Make sure the correct type is used.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Vergewissern Sie sich, dass der richtige Typ verwendet wird.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Make sure the correct type is used.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Assurez-vous que le type utilisé est exact.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Zorg ervoor dat het juiste type is gebruikt")); }
	};
}



