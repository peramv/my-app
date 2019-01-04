#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_no_ach_activy : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_no_ach_activy() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_no_ach_activy() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACCT_MARKED_NO_ACH_ACTIVY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Client's age is beyond allowable age range to hold the locked in account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Client's age is beyond allowable age range to hold the locked in account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Alter des Kunden liegt außerhalb des erlaubten Altersbereich für das festgeschriebene Konto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La edad del cliente excede el rango de edades permitidas para mantener la cuenta congelada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'âge du client est inférieur à la plage d'âge autorisée pour le titulaire du compte immobilisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De leeftijd van de klant ligt buiten het toegestane leeftijdsbereik om houder te zijn van het vergrendelde account")); }

        // Actions
	};
}



