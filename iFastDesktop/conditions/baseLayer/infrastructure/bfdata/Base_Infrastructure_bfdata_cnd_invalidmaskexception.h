#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfdata_cnd_invalidmaskexception : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfdata_cnd_invalidmaskexception() { }
		~CBase_Infrastructure_bfdata_cnd_invalidmaskexception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("CND_InvalidMaskException")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfdata")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this yield date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this yield date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt dieses Nominalverzinsungs-Datum nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce esta fecha de rendimiento.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas cette date de rendement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent deze rendementsdatum niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify yield date and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify yield date and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das Nominal-Verzinsungsdatum und geben Sie es erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique la fecha de rendimiento y vuelva a introducirla.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la date de rendement et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de rendementsdatum en voer deze opnieuw in")); }
	};
}



