#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_field_max_len_exceeded : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_field_max_len_exceeded() { }
		~CIFast_Infrastructure_dicbocore_err_field_max_len_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_MAX_LEN_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Field %FIELD% with a maximum length of, %LENGTH% characters, has been exceeded.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Field '^' with a maximum length of, '^' characters, has been exceeded.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die maximale Länge des Feldes %FIELD% von %LENGTH% Zeichen wurde überschritten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se ha excedido la longitud máxima de %LENGTH% caracteres del campo %FIELD%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La longueur maximale du champ, qui est de %LENGTH% caractères, a été excédée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Veld %FIELD% met een maximumlengte van %LENGTH% tekens, is overschreden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter a value of fewer characters in length.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Enter a value of fewer characters in length.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie einen Wert mit weniger Zeichen ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Enter a value of fewer characters in length.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Entrez une valeur composée de moins de caractères.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Geef een waarde op met minder tekens")); }
	};
}



