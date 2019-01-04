#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_unexpected_data_length_returned : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_unexpected_data_length_returned() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_unexpected_data_length_returned() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_UNEXPECTED_DATA_LENGTH_RETURNED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Communication with host had an error, Unexpected data size returned from host. Expected %expected% bytes, but got %got%. CICS return code is %CICSError%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Communication with host had an error, Unexpected data size returned from host. Expected %expected% bytes, but got %got%. CICS return code is %CICSError%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kommunikation mit dem Host war fehlerhaft, unerwartete Datengröße von Host zurückgegeben. Erwartet wurden %expected% Byte, erhalten jedoch %got% Byte. CICS-Rückgabecode ist %CICSError%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comunicación con el host tuvo un error, El host devolvió un tamaño de datos inesperado. Se esperaban %expected% bytes, pero se recibieron %got%. El código de retorno CICS es %CICSError%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La communication avec l'hôte comporte une erreur, un format de données imprévu a été renvoyé par l'hôte. Multiplets excomptés : %expected%, reçus : %got%. Code de renvoi CICS : %CICSError%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Communicatie met host had een fout, onverwachte gegevensgrootte geretourneerd van host. Verwachtte %expected% bytes, maar kreeg %got%. CICS retourcode is %CICSError%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify data entered. If entry is correct, contact a supervision and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify data entered. If entry is correct, contact a supervision and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die eingegebenen Daten. Wenn der Eintrag richtig ist, wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique los datos introducidos. Si los datos son correctos, notifique de este mensaje a un supervisor.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez les données saisies. Si elles sont exactes, communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de ingevoerde gegevens. Als de invoer juist is, neemt u contact op met een supervisor en meldt u dit bericht")); }
	};
}



