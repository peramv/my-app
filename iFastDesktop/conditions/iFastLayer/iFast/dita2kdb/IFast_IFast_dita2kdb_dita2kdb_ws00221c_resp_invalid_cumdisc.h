#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cumdisc : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cumdisc() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cumdisc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_CUMDISC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date must not be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Effective Date must not be blanc.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Effektivdatum darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia no puede estar en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Date d'entrée en vigueur doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingangsdatum mag niet leeg zijn")); }

        // Actions
	};
}



