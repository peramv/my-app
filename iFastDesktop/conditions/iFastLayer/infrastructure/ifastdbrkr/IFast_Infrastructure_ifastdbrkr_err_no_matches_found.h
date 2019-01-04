#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_no_matches_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_no_matches_found() { }
		~CIFast_Infrastructure_ifastdbrkr_err_no_matches_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_MATCHES_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid reinvest shares.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid reinvest shares.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Wiederanlage-Beteiligungen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Reinversión de acciones no válida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Parts de réinvestissement invalides")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige herinvesteringsaandelen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify reinvest shares and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify reinvest shares and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Wiederanlage-Beteiligungen und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify reinvest shares and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez les parts réinvesties et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de herinvesteringsaandelen en voer deze opnieuw in")); }
	};
}



