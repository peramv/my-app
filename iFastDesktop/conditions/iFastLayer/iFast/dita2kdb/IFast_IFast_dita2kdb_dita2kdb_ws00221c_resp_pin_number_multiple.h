#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_multiple : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_multiple() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_multiple() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_PIN_NUMBER_MULTIPLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error occured updating bank table.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Error occured updating bank table.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Beim Aktualisieren der Banktabelle ist ein Fehler aufgetreten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se produjo un error al actualizar la tabla de bancos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur s'est produite lors de la mise à jour de la table bancaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een fout opgetreden bij het bijwerken van de banktabel")); }

        // Actions
	};
}



