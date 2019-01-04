#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dol_tran_not_authorized : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dol_tran_not_authorized() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dol_tran_not_authorized() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DOL_TRAN_NOT_AUTHORIZED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date is 29th, 30th or 31st.  Do you want to select end of month?")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Effective Date is 29th, 30th or 31st.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Effektivdatum ist der 29., 30. oder 31..")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia es el 29, el 30 o el 31.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur est le 29, le 30 ou le 31. Voulez-vous sélectionner la fin de mois?")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingangsdatum is de 29ste, 30ste of 31ste")); }

        // Actions
	};
}



