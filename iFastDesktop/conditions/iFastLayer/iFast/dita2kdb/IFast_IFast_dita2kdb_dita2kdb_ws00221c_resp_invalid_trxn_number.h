#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_trxn_number : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_trxn_number() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_trxn_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_TRXN_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sales representative cannot be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone Responsable doit être renseignee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verkaufsvertreter darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El representante de ventas no puede estar en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Représentant des ventes doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vertegenwoordiger kan niet leeg zijn")); }

        // Actions
	};
}



