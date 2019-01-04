#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_dealer_num : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_dealer_num() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_dealer_num() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_DEALER_NUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction failed. Error code: %code%.  Error message: %msg%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Echec de la transaction. Code d'erreur: %code%. Message d'erreur: %msg%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaktion fehlgeschlagen. Fehlercode: %code% Fehlermeldung: %msg%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La transacción falló. Código de error: %code%.  Mensaje de error: %msg%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de transaction. Code d'erreur : %code%. Message d'erreur : %msg%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Transactie is mislukt. Foutcode: %code%.  Foutbericht: %msg%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



