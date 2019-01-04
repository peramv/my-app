#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_entry_both_fields : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_entry_both_fields() { }
		~CIFast_Infrastructure_ifastcbo_err_entry_both_fields() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTRY_BOTH_FIELDS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this data request.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this data request.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Datenanfrage nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce esta solicitud de datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas cette demande de données.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent deze gegevensaanvraag niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify data and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify data and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Daten und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify data and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez les données et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de gegevens en voer deze opnieuw in")); }
	};
}



