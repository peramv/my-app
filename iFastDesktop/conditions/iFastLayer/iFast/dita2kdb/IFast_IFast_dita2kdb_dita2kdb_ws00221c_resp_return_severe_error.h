#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_return_severe_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_return_severe_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_return_severe_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_RETURN_SEVERE_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Trade Date: User not permitted to post backdated transaction.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Date d'operation invalide : l'utilisateur n'est pas autorisé a antidater la transaction")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Handelsdatum: Der Benutzer ist nicht berechtigt, eine zurückdatierte Transaktion zu verbuchen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fecha de transacción no válida: no se permite al usuario introducir transacciones antedatadas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date de transaction invalide : l'utilisateur n'est pas autorisé à enregistrer une transaction antidatée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige handelsdatum: Gebruiker mag transactie niet met terugwerkende kracht boeken")); }

        // Actions
	};
}



