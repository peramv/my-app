#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_acct_balance_term_and_del : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_acct_balance_term_and_del() { }
		~CIFast_Infrastructure_ifastcbo_err_acct_balance_term_and_del() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_BALANCE_TERM_AND_DEL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Field Tag %FIELD_TAG%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Field Tag '^'.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Feld-Kennzeichen %FIELD_TAG%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Etiqueta de campo no válida %FIELD_TAG%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'étiquette de champ %FIELD_TAG% est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige veldtag %FIELD_TAG%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den CBO-Code.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code CBO.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de CBO-code")); }
	};
}



