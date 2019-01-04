#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exr_activity_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exr_activity_not_allowed() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exr_activity_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_EXR_ACTIVITY_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must be Minimum when Pay Options is Minimum.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Amount must be Minimum when Pay Options is Minimum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag muss min sein, wenn “Zahlungsoptionen” min ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto debe ser Mín cuando Opciones de pago es Mín.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant doit être Minimum quand l'option de paiement est Minimum.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag moet min. zijn als Betalingsopties min. is")); }

        // Actions
	};
}



