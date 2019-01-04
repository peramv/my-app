#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_active : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_active() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_PIN_NUMBER_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account indicated is not active as of trade date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account indicated is not active as of trade date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das angezeigte Konto ist nicht ab dem Handelsdatum aktiv.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta indicada no está activa a la fecha de transacción")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte est marqué comme inactif en date de la transaction.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aangegeven account is niet actief vanaf de handelsdatum")); }

        // Actions
	};
}



