#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_beneficiary_name : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_beneficiary_name() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_beneficiary_name() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_BENEFICIARY_NAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Csw Control Seq-ConfNumber does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Csw Control Seq-ConfNumber does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Csw Control Seq-ConfNumber existiert nicht")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo Csw Contol Seq-ConfNumber no existe")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de confirmation de la séquence de contrôle x est inexistant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Csw Contol Seq-ConfNumber bestaat niet")); }

        // Actions
	};
}



