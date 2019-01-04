#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_chgd_by_dif_operator : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_chgd_by_dif_operator() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_chgd_by_dif_operator() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_CHGD_BY_DIF_OPERATOR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareholder number cannot be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone Numero d'actionnaire doit être renseignee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktionärsnummer darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de accionista no puede estar en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Numéro d'actionnaire doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aandeelhoudersnummer kan niet leeg zijn")); }

        // Actions
	};
}



